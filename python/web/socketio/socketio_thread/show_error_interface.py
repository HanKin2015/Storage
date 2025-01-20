import threading
import tkinter as tk
from tkinter import messagebox
import json

class BlueprintInterface:
    @staticmethod
    def show_error(message):
        """显示错误提示框"""
        # 创建一个新的线程来运行 Tkinter
        def run_tkinter():
            root = tk.Tk()
            root.withdraw()  # 隐藏主窗口
            root.attributes('-topmost', True)   # 设置窗口为置顶
            messagebox.showerror("删除以下映射白名单", message)
            root.destroy()  # 销毁主窗口

        if len(message) == 0:
            logger.info("message length is zero, no error")
            return
        json_strings = [json.dumps(item, ensure_ascii=False) for item in message]
        message = "\n".join(json_strings)
        # 启动 Tkinter 线程
        threading.Thread(target=run_tkinter).start()

    @classmethod
    def check_white_list_valid(self):
        self.show_error("hejian")
        print("hejianhejian")
        