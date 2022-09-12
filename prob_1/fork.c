#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int n;
	
	pid_t pid;

        printf("Please enter a number greater than 0:\n"); 
        scanf("%d", &n);	// stores the entered number to n

		while (n <= 0)
		{
			printf("Looks like you've entered a number less than 0, Please enter a number greater than 0:\n"); 
  			scanf("%d", &n);	// stores the entered number to n
		}

		pid = fork();

		if (pid == 0)
		{
            int total = 0;
            for (int i = 1; i <= n; i++){
                total += i;
            }

            const char *name = "OS";
            const int SIZE = 4096;
            int shm_fd;
            void* ptr;

            /* Create the shared memory object */
            shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

            /* configure the size of the shared memory segment */
            ftruncate(shm_fd,SIZE);

            /* now map the shared memory segment in the address space of the process */
            ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

            if (ptr == MAP_FAILED) {
                printf("Map failed\n");
                return -1;
            }
            /**
             * Now write to the shared memory region.
             *
             */
            sprintf(ptr,"%d", total);
            return 0;
		}
		else
		{

			printf("Parents waiting...\n");
			wait(NULL);

            const char *name = "OS";
            const int SIZE = 4096;
            int shm_fd;
            void *ptr;
            int i;

            /* open the shared memory segment */
            shm_fd = shm_open(name, O_RDONLY, 0666);

            if (shm_fd == -1) {
                printf("shared memory failed\n");
                exit(-1);
            }

            /* now map the shared memory segment in the address space of the process */
            ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

            if (ptr == MAP_FAILED) {
                printf("Map failed\n");
                exit(-1);
            }

            /* now read from the shared memory region */
            printf("%s\n", (char *)ptr);

			printf("Parent Complete.\n");
            return 0;
		}
	return 0; 
}

