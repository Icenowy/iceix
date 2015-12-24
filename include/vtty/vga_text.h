#ifndef _VTTY_VGA_TEXT_H_H
#define _VTTY_VGA_TEXT_H_H

#include <vtty/vtty.h>

#include <arch/address.h>
#include <arch/vga.h>

#include <stdint.h>

enum vga_text_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

typedef uint8_t vga_text_color_t;
typedef uint16_t vga_text_entry_t;

static inline vga_text_color_t vga_text_make_color
	(enum vga_text_color fg, enum vga_text_color bg)
{
	return fg | bg<<4;
}

static inline vga_text_entry_t vga_text_make_entry
	(char c, vga_text_color_t cl)
{
	uint16_t c16 = c;
	uint16_t color16 = cl;
	return c16 | color16 << 8;
}

#define VGA_TEXT_WIDTH 80
#define VGA_TEXT_HEIGHT 25

/* Physical address */
static vga_text_entry_t* const VGA_TEXT_VGABUF = (uint16_t *) VGA_MEM_TEXT_ADDRESS_VIRT;

#endif
