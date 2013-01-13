/*
 * Copyright (C) 2012 Antony Pavlov <antonynpavlov@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <getopt.h>

#include "jz4750_lcd.h"

#define FB_DEVICE "/dev/fb0"

#define LCD_MODE_NONE 0
#define LCD_MODE_RZX50 1
#define LCD_MODE_A320 2

static void usage()
{
	printf("Usage: \n rzx50_lcd_mode [ options ] \n");
	printf("Options: \n");
	printf(" -h , --help          this help \n");
	printf(" -N , --normal        normal mode (480x272) \n");
	printf(" -L , --a320          Dingoo A320 compatible (320x240) \n");
}

static struct option long_options[] = {
               {"help",		no_argument,		0, 'h'},
               {"normal",	no_argument,		0, 'N'},
               {"a320",		no_argument,		0, 'L'},
               {0, 0, 0, 0}
};

int main(int argc, char **argv)
{
	struct jz4750lcd_info jz4750_lcd_info;
	int fb_descr;
	int ret;
	int lcd_mode;

	lcd_mode = LCD_MODE_NONE;

	if (argc < 2) {
		usage();
		exit(1);
	}

	while (1) {
		int c;
		int option_index = 0;

		c = getopt_long(argc, \
				argv, \
				"hLN", \
				long_options, \
				&option_index);

		if (c == -1)
			break;

		switch (c) {
			case 'h':
				usage();
				exit(0);

			case 'N':
				lcd_mode = LCD_MODE_RZX50;
				break;

			case 'L':
				lcd_mode = LCD_MODE_A320;
				break;

			default:
				printf("bad option\n");
				usage();
				exit(1);
		}
	}

	if (lcd_mode == LCD_MODE_NONE)
		exit(0);

	fb_descr = open(FB_DEVICE, O_RDONLY);
	if (fb_descr < 0) {
		printf("error: can't open %s\n", FB_DEVICE);
		exit(1);
	}

	bzero(&jz4750_lcd_info, sizeof(jz4750_lcd_info));

	ret = ioctl(fb_descr, FBIO_GET_MODE, &jz4750_lcd_info);
	printf("ret = %d\n", ret);

	printf("fg_change=%08x fg0.x = %d, fg0.y = %d, fg0.w = %d, fg0.h = %d\n",
		jz4750_lcd_info.osd.fg_change,
		jz4750_lcd_info.osd.fg0.x,
		jz4750_lcd_info.osd.fg0.y,
		jz4750_lcd_info.osd.fg0.w,
		jz4750_lcd_info.osd.fg0.h);

	jz4750_lcd_info.osd.fg_change = FG0_CHANGE_POSITION | FG0_CHANGE_SIZE;
	if (lcd_mode == LCD_MODE_A320) {
		jz4750_lcd_info.osd.fg0.x = 80;
		jz4750_lcd_info.osd.fg0.y = 16;
		jz4750_lcd_info.osd.fg0.w = 320;
		jz4750_lcd_info.osd.fg0.h = 240;
	}

	if (lcd_mode == LCD_MODE_RZX50) {
		jz4750_lcd_info.osd.fg0.x = 0;
		jz4750_lcd_info.osd.fg0.y = 0;
		jz4750_lcd_info.osd.fg0.w = 480;
		jz4750_lcd_info.osd.fg0.h = 272;
	}

	ret = ioctl(fb_descr, FBIO_SET_MODE, &jz4750_lcd_info);
	printf("ret = %d\n", ret);

	close(fb_descr);

	return 0;
}
