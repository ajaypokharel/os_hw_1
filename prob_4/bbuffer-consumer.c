#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>

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
	const char *name = "producer-consumer";
	const int SIZE = 5;

	int shm_fd;
	int *buffer;
	int *in, *out, *counter;
	int i;

	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	buffer = (int *) mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (buffer == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	in = buffer+SIZE;
	out = buffer+SIZE+1;
	counter= buffer+SIZE+2;

	int item;
	for (i=0; i<25; i++) {
		msleepRand(400);
		while (buffer[*counter] == 0) {
			printf(".");
			fflush(stdout);
			msleep(10);
		}
		item = buffer[*out];
		printf("Consume %d\n", item);
		*out = *out+1;
		buffer[*counter]--;
		if (*out == SIZE) *out=0;
	}


	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}
