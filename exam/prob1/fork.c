#include <stdio.h>
#include <stdint.h>
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
	
	pid_t pid_1, pid_2 ;

        printf("Please enter a number greater than 0:\n"); 
        scanf("%d", &n);	// stores the entered number to n

		while (n <= 0)
		{
			printf("Looks like you've entered a number less than 0, Please enter a number greater than 0:\n"); 
  			scanf("%d", &n);	// stores the entered number to n
		}

		pid_1 = fork();
        pid_2 = fork();

		if (pid_1 == 0)
		{
            int total = 0;
            for (int i = 1; i <= n; i++){
                total += i;
            }

            const char *name = "N";
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
        else if (pid_2 == 0) {

            int total_1 = 0;
            
            for (int i = 1; i <= n; i++){
                total_1 += n+i;
            }

            const char *name = "2N";
            const int SIZE = 4096;
            int shm_fd_1;
            void* ptr_1;

            /* Create the shared memory object */
            shm_fd_1 = shm_open(name, O_CREAT | O_RDWR, 0666);

            /* configure the size of the shared memory segment */
            ftruncate(shm_fd_1,SIZE);

            /* now map the shared memory segment in the address space of the process */
            ptr_1 = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_1, 0);

            if (ptr_1 == MAP_FAILED) {
                printf("Map failed\n");
                return -1;
            }
            /**
             * Now write to the shared memory region.
             *
             */
            
            sprintf(ptr_1,"%d", total_1);
            return 0;

        } else {

			printf("Parents waiting...\n");
			while (wait(NULL) > 0);

            const char *name_1 = "N";
            const char *name_2 = "2N";
            const int SIZE = 4096;
            int shm_fd, shm_fd_1;
            void *ptr_1, *ptr_2;
            int i;

            /* open the shared memory segment */
            shm_fd = shm_open(name_1, O_RDONLY, 0666);
            shm_fd_1 = shm_open(name_2, O_RDONLY, 0666);

            if (shm_fd == -1 || shm_fd_1 == -1) {
                printf("shared memory failed\n");
                exit(-1);
            }

            /* now map the shared memory segment in the address space of the process */
            ptr_1 = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
            ptr_2 = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd_1, 0);

            if (ptr_1 == MAP_FAILED || ptr_2 == MAP_FAILED) {
                printf("Map failed\n");
                exit(-1);
            }

            /* now read from the shared memory region */
            int *final_1 = (int *)ptr_1;
            int *final_2 = (int *)ptr_2;

            // printf("%ls\n", (int *)final_1);
            // printf("%ls\n", (int *)final_2);

            // I do NOT know how to add dereference and add two void pointers
            int final = (int) final_1 + (int) final_2;
            printf("%d\n", final);
			printf("Parent Complete.\n");
            return 0;
		}
	return 0; 
}

