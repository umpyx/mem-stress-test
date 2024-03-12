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

	long modifier;
	enum input_type input = INTS;
	long elements;

	srand(time(NULL));

	if (argc != 3){
		puts("USAGE: mem-stress-test [ARGS] [SIZE]\n\nAVAILABLE ARGS:\n-i: give input in sizeof(int)s\n-b: give input in bytes\n-k: give input in kilobytes\n-m: give input in megabytes\n-g: give input in gigabytes\n");
		exit(EXIT_FAILURE);
	}
	int opt;
	opt = getopt(argc, argv, "i:b:k:m:g:");
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
				printf("UNKNOWN OPTION: %c", opt);
				exit(EXIT_FAILURE);
				break;
		}
	elements = strtol(optarg, NULL, 10);

	
    	//int *MyInt = malloc(numOfInts * sizeof(int)); //DELETE SOON
	int *BigInt = mmap(NULL, modifier * elements, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (BigInt == MAP_FAILED){
		perror("MMAP HAS FAILED\n");
		exit(EXIT_FAILURE);
	}

	struct timespec initial;
	clock_gettime(CLOCK_REALTIME, &initial);
	
	
	munmap(BigInt, modifier * elements);
	return EXIT_SUCCESS;
}
