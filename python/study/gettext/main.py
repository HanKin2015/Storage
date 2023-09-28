import gettext

locale_dir = "D:\\Github\\Storage\\python\\study\\gettext\\locale"

# 设置当前的语言环境
#gettext.install('messages', localedir=locale_dir)

# 创建一个简单的翻译对象
translator = gettext.translation('messages', localedir=locale_dir, languages=['en'])
#atexit.register(translator.install) # 若想实现自动安装，则可以添加这一句。
_ = translator.gettext

# 翻译文本
print(_("Hello, world!"))