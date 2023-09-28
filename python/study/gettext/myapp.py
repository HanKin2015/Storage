import gettext

# 设置当前的语言环境
gettext.install('hj', localedir='D:\\Github\\Storage\\python\\study\\gettext\\')

# 获取翻译后的文本
translated_text = gettext.gettext('Hello, world!')

print(translated_text)