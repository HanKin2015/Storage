from flask import Blueprint

# 用户部分接口的统一头
admin_blue = Blueprint('admin', __name__, url_prefix='/admin')
from . import views