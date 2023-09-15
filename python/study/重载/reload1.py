# 不管两个函数放在前后都不行

import time

def main(device_id):
    print(device_id)

def main():
    main("he")

if __name__ == '__main__':
    start_time = time.time()

    main()
    
    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))