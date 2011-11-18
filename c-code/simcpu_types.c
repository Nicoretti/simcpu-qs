#include "simcpu_types.h"

static const char* symtable []= { 
		"NOP",    "LDA #n",  "LDA (n)", 
		"STA n",  "ADD #n" , "ADD (n)",
    "SUB #n", "SUB (n)", "JMP n", 
		"BRZ #n", "BRC #n",  "BRN #", 
		"END"
};

void debug_output(TextSegment* text_segment) {

  printf("Exec %s\t with param: %u\n", symtable[text_segment->opcode], (unsigned int) text_segment->param);
}

void print_data_segment(uint8_t* data_segment, uint8_t start, uint8_t end) {
    uint8_t i = 0;
    // no range checks for start, end because
    // this nodes would have to be checked
    // and because we are the only ones using this code
    // this will be the easier solution :)
    printf("Data-Segment-Dump (from: %u, to: %u)\n", 
					 (unsigned int) start, (unsigned int) end);
    for (i = start; i < end; i++) {
        printf("Address (%u): %d\n", (unsigned int) i, (int) data_segment[i]); 
    }
		printf("\n");
}

void print_text_segment(Memory* memory, uint8_t start, uint8_t end) {
    uint8_t i = 0;
    // no range checks for start, end because
    // this nodes would have to be checked
    // and because we are the only ones using this code
    // this will be the easier solution :)
    printf("\nText-Segment-Dump (from: %u, to: %u)\n", 
					 (unsigned int) start, (unsigned int) end);
    for (i = start; i < end; i++) {
        printf("Address (%u), Opcode: %u, n=%d\n", 
					  (unsigned int) i, (unsigned int) memory->text[i].opcode, 
						(int) memory->text[i].param); 
    }
}

void print_flags(CpuStatus* cpu_status) {
	printf("PSW: Zero-bit: %u | Carry-bit: %u | Negation-bit: %u\n", 
				 (unsigned int) cpu_status->zero_bit, 
				 (unsigned int) cpu_status->carry_bit, 
				 (unsigned int) cpu_status->negation_bit);
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
	  cpu_status->ips += (int) value;
	} else {
	  cpu_status->ips += 1;
	}
	set_flags_by_result(cpu_status, cpu_status->accu);
}

void brc(CpuStatus* cpu_status, uint8_t value) {
	
	if(cpu_status->carry_bit == 1){
	  cpu_status->ips += (int) value;
	} else {
	  cpu_status->ips += 1;
	}
	set_flags_by_result(cpu_status, cpu_status->accu);
}

void brn(CpuStatus* cpu_status, uint8_t value) {
	
	if(cpu_status->negation_bit == 1){
	  cpu_status->ips += (int) value;
	} else {
	  cpu_status->ips += 1;
	}
	set_flags_by_result(cpu_status, cpu_status->accu);
}

void end() {
    exit(EXIT_SUCCESS);
}

uint8_t is_jump_valid(CpuStatus* cpu_status, uint8_t offset) {

    int destination = (int) (cpu_status->ips + (int) offset);
		return (uint8_t) ((destination >=0 && destination < MAX_LENGTH) ? 1 : 0);
}
