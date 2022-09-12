
#from multiprocessing import shared_memory
from multiprocessing.dummy import Process
from multiprocessing.managers import SharedMemoryManager
from random import random, randint
from time import sleep

def consumer(sl, size):

    for i in range(20):
        sleep(random())

        while (sl[-1] == sl[-2]):
            print(",", end="")
            sleep(0.01)
        
        item = sl[sl[-2]]
        print("Item "+str(item)+" is consumed")
        sl[-2] += 1
        if sl[-2] == size:
            sl[-2] = 0


def producer(sl, size):

    for i in range(20):
        sleep(random())
        item = randint(0,100)

        print(str(item)+ " is produced ", end="")

        while ((sl[-1]+1) % size == sl[-2]):
            print(".", end="")
            sleep(0.01)

        print()
        sl[sl[-1]] = item
        sl[-1] += 1
        if sl[-1] == size:
            sl[-1] = 0

if __name__=="__main__":
    size = 5

    with SharedMemoryManager() as smm:
        sl = smm.ShareableList([0]*(size+2))
        p = Process(target=producer, args=(sl, size))
        c = Process(target=consumer, args=(sl, size))
        p.start()
        c.start()
        p.join()
        c.join()
