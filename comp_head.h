#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

enum Commands {

    PUSH = 1,
    ADD  = 2,
    SUB  = 3,
    MUL  = 4,
    DIV  = 5,
    OUT  = 6,
    DUMP = 7,
    IN   = 8,
    HLT  = 0
};