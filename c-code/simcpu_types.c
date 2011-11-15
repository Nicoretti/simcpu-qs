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
        printf("Address (%d): %d\n", i, data_segment[i]); 
    }
}

void print_text_segment(Memory* memory, uint8_t start, uint8_t end) {
    int i = 0;
    // no range checks for start, end because
    // this nodes would have to be checked
    // and because we are the only ones using this code
    // this will be the easier solution :)
    printf("Text-Segment-Dump (from: %d, to: %d)\n", start, end);
    for (i = start; i < end; i++) {
        printf("Address (%d), Opcode: %d, n=%d\n", i, memory->text[i].opcode, memory->text[i].param); 
    }
}

void set_flags_by_result(CpuStatus* cpu_status, uint16_t result) {

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

    uint16_t result = cpu_status->accu;
    result += data_segment[address]; 
    set_flags_by_result(cpu_status, result);
    cpu_status->accu = (uint8_t) result;
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
	  cpu_status->ips += value;
		set_flags_by_result(cpu_status, cpu_status->accu);
	}
}

void brc(CpuStatus* cpu_status, uint8_t value) {
	
	if(cpu_status->carry_bit == 1){
	  cpu_status->ips += value;
		set_flags_by_result(cpu_status, cpu_status->accu);
	}

}

void brn(CpuStatus* cpu_status, uint8_t value) {
	
	if(cpu_status->negation_bit == 1){
	  cpu_status->ips += value;
		set_flags_by_result(cpu_status, cpu_status->accu);
	}
}

void end(CpuStatus* cpu_status) {
    exit(EXIT_SUCCESS);
}

uint8_t is_jump_valid(CpuStatus* cpu_status, uint8_t offset) {

    uint8_t current_ip = cpu_status->ips;
    uint8_t destination = current_ip + offset;
		//TODO
    printf("DEBUG: %d\n",((destination <= MAX_LENGTH) && (destination >= 0)));// ? 1 : 0;
		return 0;
}
