from a import *
import time

def main():
    a.main("he")

if __name__ == '__main__':
    start_time = time.time()

    main()
    
    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))