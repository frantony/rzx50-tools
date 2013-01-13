/*
 * Copyright (C) 2012 Antony Pavlov <antonynpavlov@gmail.com>
 *
 * based on http://stackoverflow.com/questions/1485116/capturing-keystrokes-in-gnu-linux-in-c
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


#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct keytable {
	char *key_name;
	unsigned int key_value;
}keys[] = {
	{ "KEY_RESERVED", KEY_RESERVED, },
	{ "KEY_ESC", KEY_ESC, }, /* A320: SELECT button */
	{ "KEY_BACKSPACE", KEY_BACKSPACE, }, /* A320: Right shoulder button */
	{ "KEY_TAB", KEY_TAB, }, /* A320: Left shoulder button */
	{ "KEY_ENTER", KEY_ENTER, }, /* A320: START button */
	{ "KEY_LEFTCTRL", KEY_LEFTCTRL, }, /* A320: A button */
	{ "KEY_LEFTSHIFT", KEY_LEFTSHIFT, }, /* A320: Y button */
	{ "KEY_LEFTALT", KEY_LEFTALT, }, /* A320: B button */
	{ "KEY_SPACE", KEY_SPACE, }, /* A320: X button */
	{ "KEY_UP", KEY_UP, }, /* A320: D-pad up */
	{ "KEY_LEFT", KEY_LEFT, }, /* A320: D-pad left */
	{ "KEY_RIGHT", KEY_RIGHT, }, /* A320: D-pad right */
	{ "KEY_DOWN", KEY_DOWN, }, /* A320: D-pad down */
	{ "KEY_POWER", KEY_POWER, }, /* A320: POWER slider */
	{ "KEY_PAUSE", KEY_PAUSE, }, /* A320: POWER hold */
};

static void show_key(struct input_event *ev)
{
	unsigned int i;

	for (i = 0; i < (sizeof(keys) / sizeof(struct keytable)); i++) {
		if (ev->code == keys[i].key_value) {
			printf("key %i (%s) state %i\n",
				ev->code, keys[i].key_name, ev->value);
			return;
		}
	}

	printf("key %i state %i\n", ev->code, ev->value);
}

int main(int argc, char **argv)
{
	int fd;
	struct input_event ev;

	if (argc < 2) {
		printf("usage: %s <device>\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);

	while (1) {
		read(fd, &ev, sizeof(struct input_event));

		if (ev.type == EV_KEY) {
			show_key(&ev);
		}
	}
}
