import gettext

localedir = "D:\\Github\\Storage\\python\\study\\gettext\\practice\\locale"
_ = gettext.gettexts

def load_translation_file(os_language):
    """加载翻译文件（practice必须要和mo文件名一样）
    """
    if os_language == "en":
        lang = gettext.translation('practice_en_US', localedir=localedir, languages=['en_CN'])
        lang.install('practice_zh_CN')
        _ = lang.gettext
    else:
        _ = gettext.gettext


# 翻译字段
HELLO = _("嗨")
WORLD = _("世界")
MOTTO = _("我就是我，不一样的烟火")

if __name__ == '__main__':
    print("translation main")