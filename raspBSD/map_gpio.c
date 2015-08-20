#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096
#define PERI_BASE_ADDR 0x20000000
#define GPIO_BASE_ADDR (PERI_BASE_ADDR + 0x20000)

struct peripheral {
	int map_fd; //file descriptor when opening /dev/mem
	void *map; //pointer to map returned by mmap
	unsigned long p_addr; //physical address we want to map = offset in the /dev/mem mmap
}

struct peripheral *p

void map_gpio(unsigned long gpio_addr) {

	//pointer to peripheral structure
	p->p_addr = gpio_addr;

	//open /dev/mem
	if (p->map_fd = open("/dev/mem", O_RDWR) < 0) {
		perror("open");
		exit(1);
	}

	//close file descriptor
	close(p->map_fd);
	//create a mapping to gpio's physical address p_addr
	if (p->map = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,  p->map_fd, p->p_addr)< 0) {
		perror("mmap");
		exit(1);
	}
}

void unmap_gpio(void) {
	munmap(p->map);
}

//set a GPIO pin as input
void set_input(int pin) {
	unsigned int addr;
	unsigned int bit;
	addr = p->p_addr + (pin/10); //each registers lets you set 10 pins
	//input requires appropriate bits to be set as 000, so bitshift 111 to correct bit position
	//and then take inverse 
	bit = ~(7 << (10 % pin)*3);
	*addr &= bit; //keep old registers values the same
}

	


