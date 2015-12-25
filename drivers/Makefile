vga_text_objs = drivers/char/vtty/vga_text/vga_text.o

pic_objs = drivers/arch/pic.o

i8254_objs = drivers/arch/i8254.o

objs += $(vga_text_objs) $(pic_objs) $(i8254_objs)

drivers/char/vtty/vga_text/vga_text.o: drivers/char/vtty/vga_text/vga_text.c include/vtty/vga_text.h include/arch/int.h include/arch/portio.h include/arch/vga.h
