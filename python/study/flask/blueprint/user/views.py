from user import user_blue

# 用户部分的接口
@user_blue.route('/register')
def register():
    return 'register'

@user_blue.route('/login')
def login():
    return 'login'

@user_blue.route('/modify_password')
def modify_password():
    return 'modify_password'