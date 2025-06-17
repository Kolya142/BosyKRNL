#include <bosykrnl/arch/x86/drivers/keyboard.h>

volatile keyboarddev_t keyboard;

static int to_ctrl(byte_t code) {
    code &= ~0b10000000;
    code -= 1;
    return "\x1b"          // 00: esc
           "1234567890"    // 01-0A: digits
           "-=\x08\x09"    // 0B-0E: special, backspace, tab
           "qwertyuiop"    // 0F-18: letters
           "[]"            // 19-1A: square brackets
           "\r\x80"        // 1B-1C: enter, ctrl
           "asdfghjkl"     // 1D-25: letters
           ";'`"           // 26-28: special
           "\x81\\"        // 29-2A: left shift, backslash
           "zxcvbnm"       // 2B-31: letters
           ",./"           // 32-34: special
           "\x81\x00\x82"  // 35-37: right shift, print screen, alt
           " "             // 38: space
           "\x83"          // 39: caps lock
           "\x00\x00\x00\x00\x00\x00\x00\x0\x00\x00" // 3A-43: F1-F10
           "\x00\x00\x00"  // 44-46: num lock, scroll lock, home
           "\x00\x00"      // 47-48: up, page up
           "-"             // 49: minus
           "\x00\x00\x00"  // 4A-4C: left, center, right
           "+"             // 4D: plus
           "\x00"          // 4E: end
           "\x00\x00"      // 4F-50: down, page down
           "\x00\x7F"      // 51-52: insert, delete
        [code];
}

static INT_DEF(keyboard_handler) {
    if (!(inb(0x64) & 1)) {
	return;
    }

    byte_t scode = inb(0x60);
    int code = to_ctrl(scode);

    // FIXME
    
    char key = code;
    
    switch (code) {
    case 0:
	return;
    }

    keyboard.key = key;
    keyboard.keys[key] = !(scode & 0b10000000);
}

void keyboard_init() {
    idt_set(33, keyboard_handler, 0x08, 0x8E);
}
