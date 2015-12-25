#include <vtty/vga_text.h>

#include <kernel/int.h>
#include <arch/portio.h>
#include <arch/vga.h>

#include <string.h>

static size_t cursor_pos;

static vga_text_color_t color;

static vga_text_entry_t *volatile buffer;

static void vtty_scroll (size_t lines) {
	mask_interrupt ();
	if (lines >= VGA_TEXT_HEIGHT) lines = VGA_TEXT_HEIGHT;
	size_t units = lines * VGA_TEXT_WIDTH;
	_vmemmove (buffer, buffer+units, (VGA_TEXT_HEIGHT * VGA_TEXT_WIDTH) - units);
	_vmemset (buffer + (VGA_TEXT_HEIGHT * VGA_TEXT_WIDTH) - units, 0, sizeof (vga_text_entry_t) * units);
	allow_interrupt ();
}

static void vtty_update_cursor () {
	mask_interrupt ();
	outb (0x0e, VGA_CRT_IC); // oprand for update HIGH byte
	outb ((unsigned char) ( (cursor_pos >> 8) & 0xFF), VGA_CRT_DC);
	outb (0x0f, VGA_CRT_IC); // oprand for update LOW byte
	outb ((unsigned char) (cursor_pos & 0xFF), VGA_CRT_DC);
	allow_interrupt ();
}

void vtty_initialize (void) {
	mask_interrupt ();
	cursor_pos = 0;
	color = vga_text_make_color (COLOR_LIGHT_GREY, COLOR_BLACK);
	buffer = (vga_text_entry_t *) VGA_TEXT_VGABUF;
	for (size_t i = 0; i< VGA_TEXT_HEIGHT * VGA_TEXT_WIDTH; i++) {
		buffer[i] = vga_text_make_entry (' ', color);
	}
	allow_interrupt ();
	vtty_update_cursor ();
}

void vtty_newline () {
	size_t line_number;
	line_number = cursor_pos / VGA_TEXT_WIDTH + 1;
	if (line_number >= VGA_TEXT_HEIGHT) {
		vtty_scroll (line_number - VGA_TEXT_HEIGHT + 1);
		line_number = VGA_TEXT_HEIGHT-1;
	}
	cursor_pos = line_number * VGA_TEXT_WIDTH;
}

void vtty_write (const void *buf, size_t nbyte) {
	const char *cbuf = (const char *)buf;
	for (size_t i = 0; i<nbyte; i++) {
		switch (cbuf[i]) {
		case '\n':
			vtty_newline ();
			break;
		default:
			mask_interrupt ();
			buffer[cursor_pos++] = vga_text_make_entry (cbuf[i], color);
			if (! (cursor_pos % VGA_TEXT_WIDTH)) {
				cursor_pos--;
				vtty_newline ();
			}
			allow_interrupt ();
		}
	}
	vtty_update_cursor ();
}
