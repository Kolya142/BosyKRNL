#pragma once

typedef struct keyboarddev {
    bool keys[256];
    char key;
    bool alt, shift, super, ctrl, caps;
} keyboarddev_t;

extern volatile keyboarddev_t keyboard;
