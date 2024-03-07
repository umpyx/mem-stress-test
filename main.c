#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
enum input_type {INTS=0, BYTES=1, KILOBYTES=2, MEGABYTES=3, GIGABYTES=4};

int main(int argc, char *argv[]){
	int opt;
	enum input_type input = INTS;

	if (argc < 2){
		puts("USAGE: mem-stress-test [ARGS] [SIZE]\n\nAVAILABLE ARGS:\n-i: give input in sizeof(int)s\n-b: give input in bytes\n-k: give input in kilobytes\n-m: give input in megabytes\n-g: give input in gigabytes\n");
		exit(1);
	}
	while ((opt = getopt(argc, argv, "ibkmg")) != -1){
		switch(opt){
			case 'i':
				input = INTS;
				break;
			case 'b':
				input = BYTES;
				break;
			case 'k':
				input = KILOBYTES;
				break;
			case 'm':
				input = MEGABYTES;
				break;
			case 'g':
				input = GIGABYTES;
				break;
			default:
				abort();
				break;
		}
	}

	if (input = INTS){
		numOfInts = argv[3]

	//srand(time(NULL));
    	int numOfInts = strtol(argv[1], NULL, 10);
	
	printf("%lu", strlen(argv[1]));
    	int *MyInt = malloc(numOfInts * sizeof(int));
	
	for (int offset = 0; offset < numOfInts; offset++){
		int value = rand() % 100;
		MyInt[offset] = value;
        	printf("ELEMENT %d: %d\n", offset, MyInt[offset]);
	}
	
	free(MyInt);
	return 0;
}
