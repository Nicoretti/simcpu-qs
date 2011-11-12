#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


int main (int argc, const char * argv[]) 
{
	FILE *fp;
	int c, i;
	int lines = 0;
	char line[8];
  uint8_t opcode = 0;
	uint8_t value = 0;
	uint16_t sample = 0;
	int intline = 0;

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

	printf("Number of lines: %d\n", lines);

	//for (i = 0; i < lines; i++) 
	//{
      fscanf(fp, "%d", &intline);
			//printf("As String: %s\n", line);
	    //sscanf(line, "%d", &intline);
	    printf("As Integer %d\n", intline);
			sample = (uint16_t) intline;
			//opcode = (sample & 0xF0) >> 8;
			//value = sample & 0x0F;
			//printf("Opcode %d; Value %d\n", opcode, value);
	//}

	if(!fclose(fp))
	{
		printf("Inputfile is closed correctly!\n");
	}else 
	{
		printf("Inputfile is not closed correctly!\n");
	}



	return 0;
}
