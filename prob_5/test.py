
#from multiprocessing import shared_memory
from multiprocessing.dummy import Process
from multiprocessing.managers import SharedMemoryManager
from random import random, randint
from time import sleep


def producer(sl, size, counter):

    for i in range(20):
        sleep(random())
        item = randint(0,1000) + 1

        if item % 2 == 0:
            if counter == size:
                print(" Buffer Full \n")
                continue
            print()
            sl[sl[-1]] = item
            print(" Item %d Produced By Producer \n\n").format( sl[-1] % size + 1)
            counter += 1

def consumer(sl, size, counter):

    for i in range(20):
        sleep(random())

        if counter == 0:
            print(" Buffer Empty \n")
            continue

        item = sl[sl[-2]]
        
        print("Item %d Consumed By Consumer \n\n").format(sl[-2] % size + 1)

        counter -= 1
        


if __name__=="__main__":
    size = 5

    with SharedMemoryManager() as smm:
        sl = smm.ShareableList([0]*(size))
        global counter
        counter = 0
        p = Process(target=producer, args=(sl, size, counter))
        c = Process(target=consumer, args=(sl, size, counter))
        p.start()
        c.start()
        p.join()
        c.join()
