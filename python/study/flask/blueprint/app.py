from flask import Flask,request
from flask import render_template

app = Flask(__name__)

# 引入
from admin import admin_blue
from user import user_blue

@app.route('/')
def main():  # put application's code here
    return create_user()

@app.route('/user', methods=['POST'])
def create_user():
    user_data = request.json
    # 根据请求中的JSON数据创建用户，并返回相应结果
    return 'User created: {}'.format(user_data['username'])

@app.route('/hello_world')
def hello_world():  # put application's code here
    return '你好china'

@app.route('/my')
def my():  # put application's code here
    return '这里是李嘉俊'

@app.route('/my/blog/<blog_id>')
def blog_detail(blog_id):  # put application's code here
    return '您访问的博客是{}'.format(blog_id)

@app.route('/book/list')
def book_detail():  # put application's code here
    page = request.args.get('page', default=1, type=int)
    return '你获取的是{}'.format(page)

@app.route('/template/blog/<blog_id>')
def template(blog_id):  # put application's code here
    uesr = User('lijiajun', 'wy15195382735@163.com')
    person = {
        'username': 'zhangsan',
        'email': 'zhangsan的email'
    }
    return render_template('demo.html', blog_id=blog_id, user=uesr, person=person)

app.register_blueprint(admin_blue)
app.register_blueprint(user_blue)

if __name__ == '__main__':
    app.run(port=5001)
