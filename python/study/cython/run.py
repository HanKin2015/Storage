import fb
import timeit

def fibonacci(n):
    if n <= 0:
        raise ValueError("n必须是正整数")

    if n == 1:
        return 0
    elif n == 2:
        return 1
    else:
        a, b = 0, 1
        for _ in range(3, n + 1):
            a, b = b, a + b
        return b

# 纯Python版本
python_time = timeit.timeit("fibonacci(300)", setup="from __main__ import fibonacci", number=1000000)

# Cython版本
cython_time = timeit.timeit("fb.fibonacci(300)", setup="import fb", number=1000000)

print("纯Python版本执行时间:", python_time)
print("Cython版本执行时间:", cython_time)