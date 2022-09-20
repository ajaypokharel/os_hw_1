
#from multiprocessing import shared_memory
from multiprocessing.dummy import Process
from multiprocessing.managers import SharedMemoryManager
from random import random, randint
from time import sleep


def producer(sl, size):

    for i in range(10):
        sleep(random())
        item = randint(0,1000)

        print(f"Job {item} started \n")
        
        while (sl[-1] == size):
            print(".", end="")
            sleep(0.01)

        sl[sl[-3]] = item
        sl[-3] = (sl[-3] + 1) % size

        sl[-1] += 1

def consumer(sl, size):

    for i in range(10):
        sleep(random())

        while (sl[-1] == 0): 
            print(",", end="")
            sleep(0.01)

        item = sl[sl[-2]]
        sl[-2] = (sl[-2] + 1) % size
        sl[-1] -= 1
        print(f'Job {item} finished')


if __name__=="__main__":
    size = 5

    with SharedMemoryManager() as smm:
        sl = smm.ShareableList([0]*(size+3))    # extra two space to store counters
        p = Process(target=producer, args=(sl, size))
        c = Process(target=consumer, args=(sl, size))
        p.start()
        c.start()
        p.join()
        c.join()
