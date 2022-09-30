#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>


void msleep(long msec) /*sleep msec milliseconds */
{
	struct timespec ts;
	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec %1000)*1000000;
	nanosleep(&ts, &ts);
}

void msleepRand(int max) /*sleep random long up to max milliseconds*/
{
	if (max<=0) max=100;
	int r = rand();
	msleep(r%max);
}


int main()
{
	const int SIZE = 5;
	const char *name = "producer-consumer";

	int shm_fd, *in, *out, *counter, i;
	struct timespec ts;


	int *buffer; 

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE+3); //the last two numbers are in and out 

	/* now map the shared memory segment in the address space of the process */
	buffer = (int *)mmap(0,SIZE+3, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (buffer == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
	in = buffer + SIZE;
	out = buffer + SIZE+1;
	counter = buffer + SIZE + 2;

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */

	printf("Begin to produce: \n");
	*in = 0;
	*out = 0;

	for (i=0; i<25; i++) {
		msleepRand(200); //sleep up to 0.2 second
		int item = rand()%1000;
		printf("Produce %d.", item);
		fflush(stdout);

		while (buffer[*counter] == SIZE) {
			printf(".");
			fflush(stdout);
			msleep(10); //sleep 10ms
		}
		buffer[*in] = item;
		printf("\n");
		*in = (*in+1)% SIZE;
		buffer[*counter]++;
	}

	return 0;
}
