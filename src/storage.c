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

static int persisted_record_is_valid(const Student* s) {
    if (!s) return 0;
    if (!memchr(s->roll_no, '\0', sizeof(s->roll_no)) ||
        !memchr(s->name, '\0', sizeof(s->name)) ||
        !memchr(s->department, '\0', sizeof(s->department))) return 0;
    return validate_student_fields(s);
}

int load_students(const char* path, Student* students, int* count, int capacity) {
    FILE* fp;
    StorageHeader header;
    Student buffer[MAX_RECORDS];

    if (!path || !students || !count || capacity < 0 || capacity > MAX_RECORDS)
        return STORAGE_ERR_PARAM;
    fp = fopen(path, "rb");
    if (!fp) return errno == ENOENT ? STORAGE_NOT_FOUND : STORAGE_ERR_IO;

    if (fread(&header, sizeof(header), 1, fp) != 1) {
        fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    if (memcmp(header.magic, STORAGE_MAGIC, sizeof(STORAGE_MAGIC)) != 0 ||
        header.version != STORAGE_VERSION || header.count > MAX_RECORDS) {
        fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    if ((int)header.count > capacity) {
        fclose(fp);
        return STORAGE_ERR_CAPACITY;
    }
    if (header.count > 0 &&
        fread(buffer, sizeof(Student), header.count, fp) != header.count) {
        fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    int trailing = fgetc(fp);
    if (trailing != EOF || ferror(fp)) {
        fclose(fp);
        return STORAGE_ERR_CORRUPT;
    }
    if (fclose(fp) != 0) return STORAGE_ERR_IO;
    if (checksum_bytes((const unsigned char*)buffer,
                       (size_t)header.count * sizeof(Student)) != header.checksum)
        return STORAGE_ERR_CORRUPT;

    for (uint32_t i = 0; i < header.count; i++) {
        if (!persisted_record_is_valid(&buffer[i])) return STORAGE_ERR_CORRUPT;
        update_student_academics(&buffer[i]);
    }
    if (header.count > 0) memcpy(students, buffer, (size_t)header.count * sizeof(Student));
    *count = (int)header.count;
    return STORAGE_SUCCESS;
}

int save_students(const char* path, const Student* students, int count) {
    char temp_path[512], backup_path[512];
    StorageHeader header;
    FILE* fp;
    int had_old_file = 0, write_failed = 0;
    size_t path_len;

    if (!path || !students || count < 0 || count > MAX_RECORDS) return STORAGE_ERR_PARAM;
    for (int i = 0; i < count; i++) {
        if (!persisted_record_is_valid(&students[i])) return STORAGE_ERR_PARAM;
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

    (void)remove(backup_path);
    if (rename(path, backup_path) == 0) had_old_file = 1;
    else if (errno != ENOENT) {
        (void)remove(temp_path);
        return STORAGE_ERR_IO;
    }

    if (rename(temp_path, path) != 0) {
        if (had_old_file) (void)rename(backup_path, path);
        (void)remove(temp_path);
        return STORAGE_ERR_IO;
    }
    if (had_old_file) (void)remove(backup_path);
    return STORAGE_SUCCESS;
}
