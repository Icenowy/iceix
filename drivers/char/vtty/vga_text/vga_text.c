#include <vtty/vga_text.h>

#include <arch/int.h>
#include <arch/portio.h>
#include <arch/vga.h>

static size_t cursor_pos;

static vga_text_color_t color;

static volatile vga_text_entry_t *buffer;

static void vtty_update_cursor () {
	mask_interrupt ();
	outb (VGA_CRT_IC, 0x0f); // oprand for update LOW byte
	outb (VGA_CRT_DC, (unsigned char) (cursor_pos & 0xFF));
	outb (VGA_CRT_IC, 0x0e); // oprand for update HIGH byte
	outb (VGA_CRT_DC, (unsigned char) ( (cursor_pos >> 8) & 0xFF));
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

void vtty_write (const void *buf, size_t nbyte) {
	const char *cbuf = (const char *)buf;
	size_t line_number;
	for (size_t i = 0; i<nbyte; i++) {
		switch (cbuf[i]) {
		case '\n':
			line_number = cursor_pos / VGA_TEXT_WIDTH;
			cursor_pos = (line_number+1) * VGA_TEXT_WIDTH;
			break;
		default:
			mask_interrupt ();
			buffer[cursor_pos++] = vga_text_make_entry (cbuf[i], color);
			allow_interrupt ();
		}
	}
	vtty_update_cursor ();
}