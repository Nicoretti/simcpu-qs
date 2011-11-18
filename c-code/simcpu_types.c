#include "simcpu_types.h"

void debug_output(TextSegment* text_segment) {

  printf("Exec %s\t with param: %d\n", symtable[text_segment->opcode], text_segment->param);
}

void print_data_segment(uint8_t* data_segment, uint8_t start, uint8_t end) {
    int i = 0;
    // no range checks for start, end because
    // this nodes would have to be checked
    // and because we are the only ones using this code
    // this will be the easier solution :)
    printf("Data-Segment-Dump (from: %d, to: %d)\n", start, end);
    for (i = start; i < end; i++) {
        printf("Address (%d): %d\n", i, (char) data_segment[i]); 
    }
		printf("\n");
}

void print_text_segment(Memory* memory, uint8_t start, uint8_t end) {
    int i = 0;
    // no range checks for start, end because
    // this nodes would have to be checked
    // and because we are the only ones using this code
    // this will be the easier solution :)
    printf("\nText-Segment-Dump (from: %d, to: %d)\n", start, end);
    for (i = start; i < end; i++) {
        printf("Address (%d), Opcode: %d, n=%d\n", i, memory->text[i].opcode, (char) memory->text[i].param); 
    }
}

void print_flags(CpuStatus* cpu_status) {
	printf("PSW: Zero-bit: %d | Carry-bit: %d | Negation-bit: %d\n", 
				 cpu_status->zero_bit, cpu_status->carry_bit, cpu_status->negation_bit);
}

void set_flags_by_result(CpuStatus* cpu_status, uint16_t result) {

		if (result == 0) { 
				cpu_status->zero_bit = 1; 
		}
		else { 
				cpu_status->zero_bit = 0; 
		}

		if ((result & 0xFF00) != 0) {
			cpu_status->carry_bit = 1;
		} else {
			cpu_status->carry_bit = 0;
		}

		cpu_status->negation_bit = (result & 0x0080) >> 7;
		print_flags(cpu_status);
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
		//printf("==> Result before: 0x%d\n", result);
    result += value; 
		//printf("==> Result after: 0x%d\n", result);
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
}

void add_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

    uint16_t result = cpu_status->accu;
    result += data_segment[address]; 
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
}

void sub_value(CpuStatus* cpu_status, uint8_t value) {

    uint16_t result = cpu_status->accu;
    result -= value; 
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
}

void sub_value_by_address(CpuStatus* cpu_status, uint8_t* data_segment, uint8_t address) {

    uint16_t result = cpu_status->accu;
    result -= data_segment[address]; 
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
}

void jump(CpuStatus* cpu_status, uint8_t value) {
    
    cpu_status->ips = value;
    set_flags_by_result(cpu_status, cpu_status->accu);
}

void brz(CpuStatus* cpu_status, uint8_t value) {

	if(cpu_status->zero_bit == 1){
		//TODO
	  cpu_status->ips += (char) value;
	} else {
	  cpu_status->ips += 1;
	}
	set_flags_by_result(cpu_status, cpu_status->accu);
}

void brc(CpuStatus* cpu_status, uint8_t value) {
	
	if(cpu_status->carry_bit == 1){
		//TODO
	  cpu_status->ips += (char) value;
	} else {
	  cpu_status->ips += 1;
	}
	set_flags_by_result(cpu_status, cpu_status->accu);
}

void brn(CpuStatus* cpu_status, uint8_t value) {
	
	if(cpu_status->negation_bit == 1){
		//TODO
	  cpu_status->ips += (char) value;
	} else {
	  cpu_status->ips += 1;
	}
	set_flags_by_result(cpu_status, cpu_status->accu);
}

void end(CpuStatus* cpu_status) {
    exit(EXIT_SUCCESS);
}

uint8_t is_jump_valid(CpuStatus* cpu_status, uint8_t offset) {

    unsigned int destination = cpu_status->ips + (char) offset;
		return (destination >=0 && destination < MAX_LENGTH) ? 1 : 0;
}
