#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/io.h>
#include <libc/types.h>

#include "kernel.h"

static keypress_t _pressed_key;

void editor_init() {
    set_out_attr(VGA_BLACK, VGA_WHITE_LI);
    vgabuff_fill(0);

    set_out_attr(VGA_WHITE, VGA_GRAY);
    set_cursor_pos(0, 0);
    char int_s[5];
    for (int i = 1; i <= VGA_HEIGHT; i++) {
        if (i < 10)
            printc(' ');

        str_fi(int_s, i);
        prints(int_s);
        prints(" |");

        if (i != 25)
            printc('\n');
    }

    set_out_attr(VGA_BLACK, VGA_WHITE_LI);
    set_cursor_pos(0, 5);
}

void editor_start() {
    while (TRUE) {
        getkey(&_pressed_key, TRUE);
        uint16_t offset = get_cursor_off();

        switch (_pressed_key.code) {
            case 0x1C:
                set_cursor_off((offset + VGA_WIDTH) - (offset % VGA_WIDTH) + 5);
                break;
            
            case 0xE: {
                if (offset == 5)
                    break;

                if (CALC_COLUMN(offset) == 5)
                    set_cursor_off(offset - 5);
                
                printc('\b');
                break;
            }

            case 0x11: {
                if (_pressed_key.ctrl && CALC_ROW(offset) > 0) {
                    set_cursor_off(offset - VGA_WIDTH);
                    break;
                }
                goto editor_key_default;
            }

            case 0x1E: {
                if (_pressed_key.ctrl && CALC_COLUMN(offset) > 5) {
                    set_cursor_off(offset - 1);
                    break;
                }
                goto editor_key_default;
            }

            case 0x1F: {
                if (_pressed_key.ctrl && CALC_ROW(offset) < VGA_HEIGHT - 1) {
                    set_cursor_off(offset + VGA_WIDTH);
                    break;
                }
                goto editor_key_default;
            }

            case 0x20: {
                if (_pressed_key.ctrl && CALC_COLUMN(offset) < VGA_WIDTH - 1) {
                    vgacur_set_offset(offset + 1);
                    break;
                }
                goto editor_key_default;
            }

            case 0x2D: {
                if (_pressed_key.ctrl) {
                    vgabuff_fill(0);
                    editor_init();
                    break;
                }
                goto editor_key_default;
            }

            case 0x2: {
                if (_pressed_key.ctrl) {
                    set_out_attr(VGA_BLACK, VGA_WHITE_LI);
                    break;
                }
                goto editor_key_default;
            }

            case 0x3: {
                if (_pressed_key.ctrl) {
                    set_out_attr(VGA_BLUE, VGA_WHITE_LI);
                    break;
                }
                goto editor_key_default;
            }

            case 0x4: {
                if (_pressed_key.ctrl) {
                    set_out_attr(VGA_GREEN, VGA_WHITE_LI);
                    break;
                }
                goto editor_key_default;
            }

            case 0x5: {
                if (_pressed_key.ctrl) {
                    set_out_attr(VGA_CYAN, VGA_WHITE_LI);
                    break;
                }
                goto editor_key_default;
            }

            case 0x6: {
                if (_pressed_key.ctrl) {
                    set_out_attr(VGA_RED, VGA_WHITE_LI);
                    break;
                }
            }

editor_key_default:
            default: {
                if (CALC_COLUMN(offset) == VGA_WIDTH - 1)
                    set_cursor_off((offset + VGA_WIDTH) - (offset % VGA_WIDTH) + 5);
                
                printc(_pressed_key.c);
                break;
            }
        }
    }
}