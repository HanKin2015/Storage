import types
import monkey  # 导入用到的别人写的monkey模块

monkey1 = monkey.Me()
monkey2 = monkey.Me()

def i_am_human(self):
    print("I am human")

monkey2.who_am_i = types.MethodType(i_am_human, monkey2)
monkey1.who_am_i()
monkey2.who_am_i()

obj = monkey.Me()
obj.who_am_i()

"""
I am a Monkey
I am human
I am a Monkey
"""