import pandas as pd

def magic_print(content):
    print(f"content is {content}")
    print("content is {content}")

print("hello world!")

magic_print("12345")

"""
运行结果如下：
hello world!
content is 12345
content is {content}
"""