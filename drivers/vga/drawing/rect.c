#include <drivers/vga/vga.h>
#include <libc/types.h>

static volatile vga_pixel_t* _buf = (volatile vga_pixel_t*)VGA_OFFSET;
static uint16_t              _xp;
static uint16_t              _yp;
static uint16_t              _w;
static uint16_t              _h;

static void _set_dims(uint32_t pos, uint32_t dims);

void vga_draw_rect(uint32_t pos, uint32_t dims, vga_pixel_t col) {
    _set_dims(pos, dims);

    for (uint16_t y = _yp; y < _yp + _h; y++) {
        for (uint16_t x = _xp; x < _xp + _w; x++) {
            _buf[y * VGA_WIDTH + x] = col;
        }
    }
}

void vga_draw_square(uint32_t pos, uint16_t dim, vga_pixel_t col) {
    vga_draw_rect(pos, dim | dim << 16, col);
}

static void _set_dims(uint32_t pos, uint32_t dims) {
    _xp = pos >> 16;
    _yp = pos & 0xFFFF;

    _w = dims >> 16;
    _h = dims & 0xFFFF;
}