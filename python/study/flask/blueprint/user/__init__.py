from flask import Blueprint

# 用户部分接口的统一头
user_blue = Blueprint('user', __name__, url_prefix='/user')
from . import views