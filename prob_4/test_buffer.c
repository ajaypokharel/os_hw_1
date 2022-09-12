#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <unistd.h>
#define buffer_size 10

int main()
{
	int item;	

	int buffer[buffer_size];

	int counter = 0;

	int in = 0;

	int out = 0;

	while (1)
	{
		int item = rand() % 100 + 1 ;

		if (item % 2 == 0) {
			while (counter == buffer_size);

			buffer[in] = item;
			printf(" Item %d Produced By Producer \n\n", in % buffer_size + 1);
			in = (in + 1) % buffer_size;
			counter++;

		} else {

			while (counter == 0);

			buffer[out] = 0;

			printf(" Item %d Consumed By Consumer \n\n", out % buffer_size + 1);

			out = (out + 1) % buffer_size;
			counter--; 
		}

	}

	printf("\n\n The End \n\n");

	return 0;
}