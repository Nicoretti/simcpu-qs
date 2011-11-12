#include "simcpu_types.h"


int i;
void printMemoryUntil(Memory* memory, int value) {
	if (value >= MAX_LENGTH) {
		printf("Invalid input");
		return;
	}
	printf("TextSegment:\n");
	for(j = 0; j < value; j++) {
	   printf("%d: Op:%d | Val:%d\n",j, memory->text[j].opcode, memory->text[j].param);
	}
}

void zero_bit_check(CpuStatus* cpu_status) {

    if (cpu_status->accu == 0) { 
        cpu_status->zero_bit = 1; 
    }
    else { 
        cpu_status->zero_bit = 0; 
    }
}

void nop() {}

void load_value(CpuStatus* cpu_status, uint8_t value) {
    
    cpu_status->accu = value;
    zero_bit_check(cpu_status);
}

void load_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address){

}


void store_value(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

void add_value(CpuStatus* cpu_status, uint8_t value) {
    
    
}

void add_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

void sub_value(CpuStatus* cpu_status, uint8_t value) {

}

void sub_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

}

void jump(CpuStatus* cpu_status, uint8_t value) {

}

void brz(CpuStatus* cpu_status, uint8_t value) {

}

void brc(CpuStatus* cpu_status, uint8_t value) {

}

void brn(CpuStatus* cpu_status, uint8_t value) {

}

void end(CpuStatus* cpu_status) {

}
