// septumfunk 2024
#pragma once

/// Finds a specified file, then returns its size in bytes.
/// On success, returns x, where x is file size in bytes.
/// On failure, returns -1.
int zt_get_file_size(const char *path);
