#include "simcpu_types.h"


int j;
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

extern void set_flags_by_result(CpuStatus* cpu_status, uint16_t result) {

		if (result == 0) { 
				cpu_status->zero_bit = 1; 
		}
		else { 
				cpu_status->zero_bit = 0; 
		}
		cpu_status->carry_bit = (result & 0xff00) >> 8;
		cpu_status->negation_bit = (result & 0x0080) >> 7;
}

void nop() {}

void load_value(CpuStatus* cpu_status, uint8_t value) {
    
    cpu_status->accu = value;
    set_flags_by_result(cpu_status, value);
}

void load_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address){

    cpu_status->accu = data_segment[address];
    set_flags_by_result(cpu_status, data_segment[address]);
}


void store_value(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

    data_segment[address] = cpu_status->accu;
    set_flags_by_result(cpu_status, cpu_status->accu);
}

void add_value(CpuStatus* cpu_status, uint8_t value) {
    
    uint16_t result = cpu_status->accu;
    result += value; 
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
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
