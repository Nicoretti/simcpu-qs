#include "simcpu_types.h"


/**
 * Entry point to the application
 */
int main (int argc, const char * argv[]) 
{
	FILE *fp;
	int c, i;
	int lines = 0;
  uint8_t opcode = 0;
	uint8_t value = 0;
	uint16_t sample = 0;
	int intline = 0;

  CpuStatus cpu_status;
	Memory memory;

	if (argc < 2)
	{
		printf("Usage: simcpu 'filename.txt'\n");
		exit(EXIT_FAILURE);
	}
  
  fp = fopen(argv[1], "r");

	if (!fp)
	{
		printf("Inputfile is not readable!\n");
		exit(EXIT_FAILURE);
	}else
	{
		printf("Inputfile is readable!\n");
	}

	while((c = getc(fp)) != EOF )
	{
		if ('\n' == (char) c) 
		{
			lines++;
		}
	}

	// reset filepointer at the beginning
	(void) fseek(fp, 0, SEEK_SET);

	// prepare memory
	for (i = 0; i < MAX_LENGTH; i++)
	{
		memory.text[i].opcode = END;
		memory.data[i] = 0;
	}
	printf("Number of lines read: %d\n", lines);

	for (i = 0; i < lines; i++) 
	{
      (void) fscanf(fp, "%d", &intline);
	    //printf("As Integer %d\n", intline);
			sample = (uint16_t) intline;
			opcode = (sample & 0xFF00) >> 8;
			value = sample & 0x00FF;
			//printf("Opcode %d; Value %d\n", opcode, value);
			memory.text[i].opcode = opcode;
			memory.text[i].param = value;
	}

	// Print opcode and params
  //print_text_segment(&memory,0, lines);

	if(fclose(fp) == 0)
	{
		printf("Inputfile is closed correctly!\n");
	}

	cpu_status.ips = 0;
	cpu_status.accu = 0;
	cpu_status.zero_bit = 0;
	cpu_status.carry_bit = 0;
	cpu_status.negation_bit = 0;

	while (1 == 1) {
			// fetch
			TextSegment text_seg = memory.text[cpu_status.ips];
			debug_output(&text_seg);
			// decode
			switch (text_seg.opcode) 
			{
					// executes
					case NOP:
							nop();
							cpu_status.ips += 1;
							break;
					case LDAV:
							load_value(&cpu_status, text_seg.param);
							cpu_status.ips += 1;
							break;
					case LDAA:
							load_value_by_address(&cpu_status, memory.data, text_seg.param);
							cpu_status.ips += 1;
							break;
					case STA:
							store_value(&cpu_status, memory.data, text_seg.param);
							cpu_status.ips += 1;
							break;
					case ADDV:
							add_value(&cpu_status, text_seg.param);
							cpu_status.ips += 1;
							break;
					case ADDA:
							add_value_by_address(&cpu_status, memory.data, text_seg.param);
							cpu_status.ips += 1;
							break;
					case SUBV:
							sub_value(&cpu_status, text_seg.param);
							cpu_status.ips += 1;
							break;
					case SUBA:
							sub_value_by_address(&cpu_status, memory.data, text_seg.param);
							cpu_status.ips += 1;
							break;
					case JMP:
							jump(&cpu_status, text_seg.param);
							break;
					case BRZ:
							if ((is_jump_valid(&cpu_status, text_seg.param)) == 1) {
									brz(&cpu_status, text_seg.param);
							}
							else {
									printf("Invalid BRZ.\n");
									printf("Exit\n");
									exit(EXIT_FAILURE);
							}
							break;
					case BRC:
							if ((is_jump_valid(&cpu_status, text_seg.param)) == 1) {
									brc(&cpu_status, text_seg.param);
							}
							else {
									printf("Invalid BRC\n");
									printf("Exit\n");
									exit(EXIT_FAILURE);
							}
							break;
					case BRN:
							if ((is_jump_valid(&cpu_status, text_seg.param)) == 1) {
									brn(&cpu_status, text_seg.param);
							}
							else {
									printf("Invalid BRN.\n");
									printf("Exit\n");
									exit(EXIT_FAILURE);
							}
							break;
					case END:
							print_data_segment(memory.data, 0, 4);
							print_text_segment(&memory, 0, 10);
							end(&cpu_status);
			}
	}

	return 0;
}
