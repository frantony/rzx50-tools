CROSS_COMPILE?=/opt/ct-ng-1.14.0/rzx50-uclibc-0.32.1-olthreads/bin/mipsel-rzx50-linux-uclibc-

CC=$(CROSS_COMPILE)gcc

CFLAGS=-W -Wall

all: jz4750d_gpio_dump rzx50_lcd_mode findkey

jz4750d_gpio: jz4750d_gpio_dump.c jz4750d_gpio.h
	$(CC) $(CFLAGS) -o $@ $<

rzx50_lcd_mode: rzx50_lcd_mode.c jz4750_lcd.h
	$(CC) $(CFLAGS) -o $@ $<

findkey: findkey.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f jz4750d_gpio_dump
	rm -f rzx50_lcd_mode
	rm -f findkey
