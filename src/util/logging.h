// septumfunk 2024
#pragma once
#include <stdio.h>
#include <stdlib.h>

#define panic(format, args...) { fprintf(stderr, format, args); exit(-1);  }