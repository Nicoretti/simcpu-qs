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

	Memory memory;

	if (argc < 2)
	{
		printf("Usage: simcpu 'filename.txt'\n");
		return 1;
	}
  
  fp = fopen(argv[1], "r");

	if (!fp)
	{
		printf("Inputfile is not readable!\n");
		return 1;
	}else
	{
		printf("Inputfile is readable!\n");
	}

	while((c = getc(fp)) != EOF )
	{
		if ('\n' == c) 
		{
			lines++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	printf("Number of lines: %d\n", lines);

	for (i = 0; i < lines; i++) 
	{
      fscanf(fp, "%d", &intline);
	    //printf("As Integer %d\n", intline);
			sample = (uint16_t) intline;
			opcode = (sample & 0xFF00) >> 8;
			value = sample & 0x00FF;
			printf("Opcode %d; Value %d\n", opcode, value);
			memory.text[i].opcode = opcode;
			memory.text[i].param = value;
	}

	if(!fclose(fp))
	{
		printf("Inputfile is closed correctly!\n");
	}else 
	{
		printf("Inputfile is not closed correctly!\n");
	}

	printMemoryUntil(&memory, 5);


	return 0;
}
