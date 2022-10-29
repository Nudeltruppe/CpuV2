#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include <cpu_core.h>

#include <stdarg.h>

#include <programing.h>

uint8_t memory_[0xffff] = { 0 };

uint8_t cpu_fetch_byte(uint16_t addr) {
	silent(debugf("fetching byte at 0x%x", addr));
	return memory_[addr];
}

void cpu_write_byte(uint16_t addr, uint8_t val) {
	silent(debugf("writing byte 0x%x at 0x%x", val, addr));
	memory_[addr] = val;
}

uint8_t cpu_io_read(uint16_t addr) {
	silent(debugf("reading byte from io at 0x%x", addr));

		switch (addr) {
        case 0x0:
			{
				uint8_t val = 0;
				for (int i = 0; i < 8; i++) {
					val |= gpio_get(i + 8) << i;
				}
				return val;
			}
        default:
         	silent(debugf("invalid io address %x", addr));
            return 0x0;
    }

}

void cpu_io_write(uint16_t addr, uint8_t val) {
	silent(debugf("writing byte 0x%x to io at 0x%x", val, addr));
	
	switch (addr) {
        case 0x0:
			for (int i = 0; i < 8; i++) {
				gpio_put(i, (val & 1 << i) ? true : false);
			}
            return;
        default:
            silent(debugf("invalid io address %x", addr));
            return;
    }
}

uint16_t current_emit = 0;
uint16_t emit(instruction_t instr) {
    cpu_write_instruction(instr, current_emit);
    uint16_t result = current_emit;
    current_emit += sizeof(instruction_t);
    return result;
}



int main() {
    stdio_init_all();

	for (int i = 0; i < 8; i++) {
		gpio_init(i);
		gpio_set_dir(i, GPIO_OUT);
	}

	for (int i = 0; i < 8; i++) {
		gpio_init(i + 8);
		gpio_set_dir(i + 8, GPIO_IN);
	}

	programing_mode();
    core_run();

	while (true) {}
}