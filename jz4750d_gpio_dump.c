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

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#include "jz4750d_gpio.h"

void print_register(char *name, uint32_t value)
{
	int i;
#define BUFLEN 128
	char buffer[BUFLEN];

	snprintf(buffer, BUFLEN, "%08x", value);
	printf("%6s <%s> ", name, buffer);
	for (i = 0; buffer[i]; i++) {

		if (buffer[i] == '0') {
			printf("0000");
		} else if (buffer[i] == '1') {
			printf("0001");
		} else if (buffer[i] == '2') {
			printf("0010");
		} else if (buffer[i] == '3') {
			printf("0011");
		} else if (buffer[i] == '4') {
			printf("0100");
		} else if (buffer[i] == '5') {
			printf("0101");
		} else if (buffer[i] == '6') {
			printf("0110");
		} else if (buffer[i] == '7') {
			printf("0111");
		} else if (buffer[i] == '8') {
			printf("1000");
		} else if (buffer[i] == '9') {
			printf("1001");
		} else if (buffer[i] == 'a') {
			printf("1010");
		} else if (buffer[i] == 'b') {
			printf("1011");
		} else if (buffer[i] == 'c') {
			printf("1100");
		} else if (buffer[i] == 'd') {
			printf("1101");
		} else if (buffer[i] == 'e') {
			printf("1110");
		} else if (buffer[i] == 'f') {
			printf("1111");
		} else {
			printf("errr\n");
		}
		printf(".");
	}

	printf("\n");
}

void print_port(volatile uint32_t *gpio_base, int port)
{
	print_register("PXPIN", gpio_base[GPIO_PXPIN(port)]);
	print_register("PXDAT", gpio_base[GPIO_PXDAT(port)]);
	print_register("PXIM", gpio_base[GPIO_PXIM(port)]);
	print_register("PXPE", gpio_base[GPIO_PXPE(port)]);
	print_register("PXFUN", gpio_base[GPIO_PXFUN(port)]);
	print_register("PXSEL", gpio_base[GPIO_PXSEL(port)]);
	print_register("PXDIR", gpio_base[GPIO_PXDIR(port)]);
	print_register("PXTRG", gpio_base[GPIO_PXTRG(port)]);
}

int main()
{
	unsigned long mem_fd;
	volatile uint32_t *gpio_base;

	mem_fd = open("/dev/mem", O_RDWR);
	gpio_base = (uint32_t *)mmap(0, GPIO_SIZE, \
	PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);

	printf("PORT A:\n");
	print_port(gpio_base, GPIO_PORTA);
	printf("PORT B:\n");
	print_port(gpio_base, GPIO_PORTB);
	printf("PORT C:\n");
	print_port(gpio_base, GPIO_PORTC);
	printf("PORT D:\n");
	print_port(gpio_base, GPIO_PORTD);
	printf("PORT E:\n");
	print_port(gpio_base, GPIO_PORTE);
	printf("PORT F:\n");
	print_port(gpio_base, GPIO_PORTF);

	munmap((void *)gpio_base, GPIO_SIZE);
	close(mem_fd);

	return 0;
}
