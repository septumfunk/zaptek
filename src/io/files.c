// septumfunk 2024
#include <io/files.h>
#include <stdio.h>
#include <util/logging.h>
#include <util/memory_safety.h>

int get_file_size(const char *path) {
    FILE *f;
    int status = fopen_s(&f, path, "r");
    if (status < 0)
        return -1;
    
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fclose(f);
    return length;
}

int file_as_string(const char *path, unsigned int size, char *output) {
    FILE *f;
    int status = fopen_s(&f, path, "r");
    if (status != 0)
        return -1;

    int length = fread(output, size, 1, f);
    if (length < 0)
        return -1;

    fclose(f);
    return length;
}

char *quickload(const char *path) {
    int filesize = get_file_size(path);
    if (filesize < 0)
        panic("Failed to stat file \"%s\" for its size.", path);
    
    char *contents = calloc(filesize + 1, sizeof(char)); // +1 for null terminator
    nullsafe(contents);
    
    filesize = file_as_string(path, filesize, contents);
    if (filesize < 0)
        panic("Failed to read contents of file \"%s\".", path);
    
    return contents;
}