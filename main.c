#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <sys/mman.h>

#define KB 1000
#define MB 1000 * KB
#define GB 1000 * MB

//#define NUMOFREADS 10000000 //MUST BE LOWER THAN 7 ZEROES

enum input_type {INTS=0, BYTES=1, KILOBYTES=2, MEGABYTES=3, GIGABYTES=4};

long totaltime; 
long count;

void AverageOutput(){
	printf("Test successfully completed :D\nAverage latency: %lu nanoseconds\n", totaltime / count);
}

void Sigint_handler(int sig){
	AverageOutput();
	exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]){

	signal(SIGINT, Sigint_handler);
	long modifier, elements;
	struct timespec initialTime, finalTime;
	long offset, meantime;
	enum input_type input = INTS;

	srand(time(NULL));

	if (argc != 4){
		puts("USAGE: mem-stress-test [TYPE] [SIZE] [TESTS]\n\nAVAILABLE ARGS:\n-i: give input in sizeof(int)s\n-b: give input in bytes\n-k: give input in kilobytes\n-m: give input in megabytes\n-g: give input in gigabytes\n\nRuns \033[;;4mTESTS\033[m test polls on memory latency time\n\n");
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

	long NUMOFREADS = strtol(argv[3], NULL, 10);
	if (NUMOFREADS > 10000000){
		perror("ERROR: QUANTITY OF TESTS IS TOO HIGH, WILL CAUSE LONG OVERFLOW OF RESULT\nPLEASE USE A NUMBER OF TESTS < 10000000");
		exit(EXIT_FAILURE);
	}
	
	char *BigInt = mmap(NULL, modifier * elements, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (BigInt == MAP_FAILED){
		perror("MMAP HAS FAILED\n");
		exit(EXIT_FAILURE);
	}
	puts("Map successfully allocated :D\n");



	puts("\nSequentially filling array \033[;;5m...\033[m");
	for (long address = 0; address < modifier * elements; address++){
		int value = rand();
		/* May this legendary if statement rest in peace:
		 * if (count % (long)(log(((modifier * elements) / (2^(sizeof(long) * 8)/10)))) == 0){
		 */
		if (address % 1000 == 0){
 			clock_gettime(CLOCK_REALTIME, &initialTime);
			*(BigInt + count) = value;
			clock_gettime(CLOCK_REALTIME, &finalTime);
			totaltime += (finalTime.tv_nsec - initialTime.tv_nsec);
			count += 1;
		}
		else{
			*(BigInt + address) = value;
		}
	}
	AverageOutput();

	totaltime = 0;
	count = 0;
	puts("\nTesting latency for memory read \033[;;5m...\033[m");
	for (count = 0; count < NUMOFREADS; count++){

		offset = rand() % (elements - 1);
 		clock_gettime(CLOCK_REALTIME, &initialTime);
		char x = *(BigInt + (offset));
		clock_gettime(CLOCK_REALTIME, &finalTime);
		totaltime += (finalTime.tv_nsec - initialTime.tv_nsec);

	}
	AverageOutput();
	
	munmap(BigInt, modifier * elements);


	return EXIT_SUCCESS;
}
