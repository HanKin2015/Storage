# Flask框架最基本的使用
https://zhuanlan.zhihu.com/p/637789895
https://zhuanlan.zhihu.com/p/622394487

## 1、Flask框架介绍
Flask诞生于2010年，是Armin ronacher（阿明·罗纳彻）用 Python 语言基于 Werkzeug 工具箱编写的轻量级Web开发框架。

Flask 本身相当于一个内核，其他几乎所有的功能都要用到扩展（邮件扩展Flask-Mail，用户认证Flask-Login，数据库Flask-SQLAlchemy），都需要用第三方的扩展来实现。比如可以用 Flask 扩展加入ORM、窗体验证工具，文件上传、身份验证等。Flask 没有默认使用的数据库，你可以选择 MySQL，也可以用 NoSQL。

flask的 WSGI 工具箱采用 Werkzeug（路由模块），模板引擎则使用 Jinja2。Itsdangrous（token加密模块），Click(终端命令管理工具)，flask内核本身，这5个核心模块组成 Flask 框架。

官方文档：https://flask.palletsprojects.com/en/2.0.x/

中文文档：https://dormousehole.readthedocs.io

Flask常用第三方扩展包：
Flask-SQLAlchemy：操作数据库,ORM；
Flask-script：终端脚本工具，脚手架； ( 淘汰，官方内置脚手架：Click)
Flask-migrate：管理迁移数据库；
Flask-Session：Session存储方式指定；
Flask-Mail：邮件；
Flask-Login：认证用户状态；（django内置Auth模块，用于实现用户登录退出，）
Flask-OpenID：认证, OAuth；（三方授权，）
Flask-RESTful：开发REST API的工具；
Flask JSON-RPC: 开发json-rpc远程服务[过程]调用
Flask-Bable：提供国际化和本地化支持，翻译；
Flask-Moment：本地化日期和时间
Flask-Admin：简单而可扩展的管理接口的框架
Flask-Bootstrap：集成前端Twitter Bootstrap框架（前后端分离，除了admin站点，基本不用这玩意）
Flask-WTF：表单生成模块；（前后端分离，csrf集成在这个模块中，除了admin站点，基本不用这玩意）
Flask-Marshmallow：序列化（类似djangorestframework的序列化器）
可以通过 https://pypi.org/search/?c=Framework+%3A%3A+Flask 查看更多flask官方推荐的扩展

## 2、flask和开发工具pychram安装
pip install Flask

pychram请到官网下载。（专业版最好）

## 3、项目配置之debug模式
新建项目的时候记得选择flask。
```
# 运行代码
if __name__ == '__main__':
    app.run(debug=True)
```

## 4、修改host
如果想让在同一个网络下的其他设备可以访问的话，需要修改为0.0.0.0或者也可以使用 --host=你的ipaddress也行。
然后就可以在另外一台电脑进行网页访问了。

## 5、修改端口号
就是修改项目运行的端口号。
--host=0.0.0.0 --port=5001

## 6、后面的教程
当前还是小白，后面的代码似乎不完整，运行不起来，后面学会了再来看看。
原来是教程中部分代码有单词写错误。

## 7、已明白蓝图的作用
- 首先蓝图函数是不能有参数的
- 蓝图函数是提供给前端界面的接口函数
- 蓝图调用python写的后端函数，相当于是中间连接的桥梁
- 蓝图需要注册

## 8、路由参数
```
@app.route("/download_report/<path:filename>")
def download_report(filename):
    dirpath = os.path.join(app.root_path, 'new_report_zip')
```
在 Flask 中，<path:filename> 是一种路由参数，它告诉 Flask 期望在 URL 中接收一个名为 filename 的变量。path 转换器是 Flask 路由系统中的一种特殊类型，它允许你匹配一个包含斜线（/）的路径。

默认情况下，路由中的变量部分只会匹配到下一个斜线之前的部分。例如，如果你有一个路由 /download_report/<filename>，那么它只会匹配像 /download_report/file.zip 这样不包含额外斜线的 URL。但是，如果你想匹配包含斜线的路径，比如 /download_report/folder/subfolder/file.zip，你就需要使用 path 转换器。

调用的时候为：
```
url = "http://1.2.3.4:8852/download_report/tmp/usbtrace-x64.zip"
```

## 9、蓝图路由另外一种写法
```
from flask_restful import Resource, Api
from flask import Blueprint

report_bp = Blueprint("reports", __name__)
report_api = Api(report_bp)

def GetTotal(Resource):
    pass

report_api.add_resource(GetTotal, "/totals")
```

## 10、使用Postman工具调试
Postman官网上这样介绍它:"Manage all of your organization's APIs in Postman, with the industry's most complete API development environment."看的出来Postman是功能强大的API测试的工具
Postman 提供功能强大的 Web API 和 HTTP 请求的调试，它能够发送任何类型的HTTP 请求 (GET, POST, PUT, DELETE...)，并且能附带任何数量的参数和 Headers。不仅如此，它还提供测试数据和环境配置数据的导入导出，付费的 Post Cloud 用户还能够创建自己的 Team Library 用来团队协作式的测试，并能够将自己的测试收藏夹和用例数据分享给团队。

如果本机调试就不需要修改任何端口和host了，直接使用pycharm运行项目。
打开Postman工具，新建请求，选择POST请求（根据自己的接口选择对应的请求类型），输入url，注意这里只能填写127.0.0.1而不是ip地址额。
如果需要输入参数，选择Body=》raw=》数据类型选择JSON：
```
{
    "ip": "12.12.12.70",
    "password": "hello@147258",
    "port": 22
}
```
最后点击Send就会有结果返回啦！

