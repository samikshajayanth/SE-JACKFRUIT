#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "student_mgmt.h"
#include "cgpa.h"

#define STORAGE_VERSION 1u
static const char STORAGE_MAGIC[8] = {'S','T','U','D','R','M','S','\0'};

typedef struct {
    char magic[8];
    uint32_t version;
    uint32_t count;
    uint32_t checksum;
} StorageHeader;

static uint32_t checksum_bytes(const unsigned char* data, size_t size) {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < size; i++) {
        hash ^= data[i];
        hash *= 16777619u;
    }
    return hash;
}

static int roll_numbers_equal(const char* left, const char* right) {
    if (!left || !right) return 0;
    for (size_t i = 0; i < MAX_ROLL_LEN; i++) {
        unsigned char a = (unsigned char)left[i];
        unsigned char b = (unsigned char)right[i];
        if (a >= 'A' && a <= 'Z') a = (unsigned char)(a - 'A' + 'a');
        if (b >= 'A' && b <= 'Z') b = (unsigned char)(b - 'A' + 'a');
        if (a != b) return 0;
        if (a == '\0') return 1;
    }
    return 0;
}

static int persisted_record_is_valid(const Student* s) {
    if (!s) return 0;
    if (!memchr(s->roll_no, '\0', sizeof(s->roll_no)) ||
        !memchr(s->name, '\0', sizeof(s->name)) ||
        !memchr(s->department, '\0', sizeof(s->department))) return 0;
    return validate_student_fields(s);
}

/* Read and validate into a temporary buffer; caller data changes only on success. */
static int read_students_file(const char* path, Student* students, int* count, int capacity) {
    FILE* fp;
    StorageHeader header;
    Student buffer[MAX_RECORDS];

    fp = fopen(path, "rb");
    if (!fp) return errno == ENOENT ? STORAGE_NOT_FOUND : STORAGE_ERR_IO;

    if (fread(&header, sizeof(header), 1, fp) != 1) {
        (void)fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    if (memcmp(header.magic, STORAGE_MAGIC, sizeof(STORAGE_MAGIC)) != 0 ||
        header.version != STORAGE_VERSION || header.count > MAX_RECORDS) {
        (void)fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    if ((int)header.count > capacity) {
        (void)fclose(fp);
        return STORAGE_ERR_CAPACITY;
    }
    if (header.count > 0 &&
        fread(buffer, sizeof(Student), header.count, fp) != header.count) {
        (void)fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    int trailing = fgetc(fp);
    if (trailing != EOF || ferror(fp)) {
        (void)fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    if (fclose(fp) != 0) return STORAGE_ERR_IO;

    if (checksum_bytes((const unsigned char*)buffer,
                       (size_t)header.count * sizeof(Student)) != header.checksum)
        return STORAGE_ERR_CORRUPT;

    for (uint32_t i = 0; i < header.count; i++) {
        if (!persisted_record_is_valid(&buffer[i])) return STORAGE_ERR_CORRUPT;
        for (uint32_t j = 0; j < i; j++) {
            if (roll_numbers_equal(buffer[i].roll_no, buffer[j].roll_no))
                return STORAGE_ERR_CORRUPT;
        }
        update_student_academics(&buffer[i]);
    }

    if (header.count > 0)
        memcpy(students, buffer, (size_t)header.count * sizeof(Student));
    *count = (int)header.count;
    return STORAGE_SUCCESS;
}

int load_students(const char* path, Student* students, int* count, int capacity) {
    char backup_path[512], corrupt_path[512];
    size_t path_len;
    int primary_result, backup_count = 0;
    Student backup_records[MAX_RECORDS];

    if (!path || !students || !count || capacity < 0 || capacity > MAX_RECORDS)
        return STORAGE_ERR_PARAM;
    path_len = strlen(path);
    if (path_len == 0 || path_len + 9 >= sizeof(corrupt_path))
        return STORAGE_ERR_PARAM;
    (void)snprintf(backup_path, sizeof(backup_path), "%s.bak", path);
    (void)snprintf(corrupt_path, sizeof(corrupt_path), "%s.corrupt", path);

    primary_result = read_students_file(path, students, count, capacity);
    if (primary_result == STORAGE_SUCCESS) return STORAGE_SUCCESS;
    if (primary_result != STORAGE_NOT_FOUND && primary_result != STORAGE_ERR_CORRUPT)
        return primary_result;

    /* A crash between renaming the old store to .bak and promoting .tmp
       leaves no primary file. A checksum failure can also use a valid backup. */
    if (read_students_file(backup_path, backup_records, &backup_count, capacity) != STORAGE_SUCCESS)
        return primary_result;

    if (primary_result == STORAGE_NOT_FOUND) {
        if (rename(backup_path, path) != 0) return STORAGE_ERR_IO;
    } else {
        if (remove(corrupt_path) != 0 && errno != ENOENT) return STORAGE_ERR_IO;
        if (rename(path, corrupt_path) != 0) return STORAGE_ERR_IO;
        if (rename(backup_path, path) != 0) {
            (void)rename(corrupt_path, path);
            return STORAGE_ERR_IO;
        }
        (void)remove(corrupt_path);
    }

    if (backup_count > 0)
        memcpy(students, backup_records, (size_t)backup_count * sizeof(Student));
    *count = backup_count;
    return STORAGE_SUCCESS;
}

int save_students(const char* path, const Student* students, int count) {
    char temp_path[512], backup_path[512];
    StorageHeader header;
    FILE* fp;
    FILE* existing;
    int had_old_file = 0, write_failed = 0;
    size_t path_len;

    if (!path || !students || count < 0 || count > MAX_RECORDS) return STORAGE_ERR_PARAM;
    for (int i = 0; i < count; i++) {
        if (!persisted_record_is_valid(&students[i])) return STORAGE_ERR_PARAM;
        for (int j = 0; j < i; j++) {
            if (roll_numbers_equal(students[i].roll_no, students[j].roll_no))
                return STORAGE_ERR_PARAM;
        }
    }
    path_len = strlen(path);
    if (path_len == 0 || path_len + 5 >= sizeof(temp_path)) return STORAGE_ERR_PARAM;
    (void)snprintf(temp_path, sizeof(temp_path), "%s.tmp", path);
    (void)snprintf(backup_path, sizeof(backup_path), "%s.bak", path);

    memset(&header, 0, sizeof(header));
    memcpy(header.magic, STORAGE_MAGIC, sizeof(STORAGE_MAGIC));
    header.version = STORAGE_VERSION;
    header.count = (uint32_t)count;
    header.checksum = checksum_bytes((const unsigned char*)students,
                                     (size_t)count * sizeof(Student));

    (void)remove(temp_path);
    fp = fopen(temp_path, "wb");
    if (!fp) return STORAGE_ERR_IO;
    if (fwrite(&header, sizeof(header), 1, fp) != 1) write_failed = 1;
    if (!write_failed && count > 0 &&
        fwrite(students, sizeof(Student), (size_t)count, fp) != (size_t)count)
        write_failed = 1;
    if (!write_failed && fflush(fp) != 0) write_failed = 1;
    if (fclose(fp) != 0) write_failed = 1;
    if (write_failed) {
        (void)remove(temp_path);
        return STORAGE_ERR_IO;
    }

    /* Preserve an orphaned .bak when the primary file is missing. It may be
       the only recoverable copy after an interrupted previous save. */
    existing = fopen(path, "rb");
    if (existing) {
        (void)fclose(existing);
        if (remove(backup_path) != 0 && errno != ENOENT) {
            (void)remove(temp_path);
            return STORAGE_ERR_IO;
        }
        if (rename(path, backup_path) != 0) {
            (void)remove(temp_path);
            return STORAGE_ERR_IO;
        }
        had_old_file = 1;
    } else if (errno != ENOENT) {
        (void)remove(temp_path);
        return STORAGE_ERR_IO;
    }

    if (rename(temp_path, path) != 0) {
        if (had_old_file) (void)rename(backup_path, path);
        (void)remove(temp_path);
        return STORAGE_ERR_IO;
    }
    (void)remove(backup_path);
    return STORAGE_SUCCESS;
}
