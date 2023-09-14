from admin import admin_blue

# 用户部分的接口
@admin_blue.route('/alluser')
def register():
    return 'alluser'

@admin_blue.route('/deluser')
def login():
    return 'deluser'