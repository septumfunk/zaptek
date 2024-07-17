// septumfunk 2024
#pragma once

/// Finds a specified file, then returns its size in bytes.
/// On success, returns x, where x is file size in bytes.
/// On failure, returns -1.
int get_file_size(const char *path);

/// Finds a specified file, then returns a string of its contents.
/// On success, returns x, where x is the file size in bytes.
/// On failure, returns -1.
int file_as_string(const char *path, unsigned int size, char *output);

/// Quickly loads a file into a dynamically allocated string.
/// Use this for quick and dirty file loads, where you don't care if it crashes the program.
/// This function uses dynamic memory. Please be sure to free the returned pointer.
char *quickload(const char *path);