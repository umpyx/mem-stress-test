#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define KB 1000
#define MB 1000 * KB
#define GB 1000 * MB

enum input_type {INTS=0, BYTES=1, KILOBYTES=2, MEGABYTES=3, GIGABYTES=4};

int main(int argc, char *argv[]){
	int opt;
	long modifier;
	enum input_type input = INTS;

	if (argc < 4){
		puts("USAGE: mem-stress-test [ARGS] [SIZE]\n\nAVAILABLE ARGS:\n-i: give input in sizeof(int)s\n-b: give input in bytes\n-k: give input in kilobytes\n-m: give input in megabytes\n-g: give input in gigabytes\n");
		exit(1);
	}
	while ((opt = getopt(argc, argv, "ibkmg")) != -1){
		switch(opt){
			case 'i':
				modifier = sizeof(int);
				break;
			case 'b':
				modifier = sizeof(char);
				break;
			case 'k':
				modifier = KB;
				break;
			case 'm':
				modifier = MB;
				break;
			case 'g':
				modifier = GB;
				break;
			default:
				abort();
				break;
		}
	}



	//srand(time(NULL));
    	int numOfInts = strtol(argv[1], NULL, 10);
	
	printf("%lu", strlen(argv[1]));
    	//int *MyInt = malloc(numOfInts * sizeof(int));
	int *BigInt = mmap(BigInt, modifier * number, PROT_READ | PROT_WRITE, MAP_PRIVATE);

	for (int offset = 0; offset < numOfInts; offset++){
		int value = rand() % 100;
		BigInt[offset] = value;
        	printf("ELEMENT %d: %d\n", offset, MyInt[offset]);
	}
	
	free(BigInt);
	return 0;
}
