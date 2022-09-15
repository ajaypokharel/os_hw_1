
#from multiprocessing import shared_memory
from multiprocessing.dummy import Process
from multiprocessing.managers import SharedMemoryManager
from random import random, randint
from time import sleep


def producer(sl, size):

    for i in range(10):
        sleep(random())
        item = randint(0,100)

        print(str(item)+ " is produced \n")
        print("Item {0} Produced By Producer \n".format( sl[-1] % size + 1))

        while ((sl[-1]+1) % size == sl[-2]):
            print(".", end="")
            sleep(0.01)

        sl[sl[-1]] = item
        sl[-1] += 1 # last element acts as a counter
        if sl[-1] == size:  # if counter == bufferSize; do nothing
            sl[-1] = 0

def consumer(sl, size):

    for i in range(10):
        sleep(random())

        while (sl[-1] == sl[-2]):
            print(",", end="")
            sleep(0.01)
        
        item = sl[sl[-2]]
        print("Item "+ str(item)+" is consumed\n")
        print("Item {0} Consumed By Consumer \n".format(sl[-2] % size + 1))
        
        sl[-2] += 1 # second_last element acts as a counter
        if sl[-2] == size:  ## if counter == bufferSize; do nothing
            sl[-2] = 0


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
