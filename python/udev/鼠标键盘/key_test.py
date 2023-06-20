import pynput
import time
import re
import threading


class ControlMouseKeyboard(object):
    mouse = pynput.mouse.Controller()
    keyboard = pynput.keyboard.Controller()

    mouse_listener = None
    keyboard_listener = None
    mouse_keyboard_move = []
    time_order = []

    default_keys = {
        'Key.alt': pynput.keyboard.Key.alt,
        'Key.alt_l': pynput.keyboard.Key.alt_l,
        'Key.alt_r': pynput.keyboard.Key.alt_r,
        'Key.alt_gr': pynput.keyboard.Key.alt_gr,
        'Key.backspace': pynput.keyboard.Key.backspace,
        'Key.caps_lock': pynput.keyboard.Key.caps_lock,
        'Key.cmd': pynput.keyboard.Key.cmd,
        'Key.cmd_l': pynput.keyboard.Key.cmd_l,
        'Key.cmd_r': pynput.keyboard.Key.cmd_r,
        'Key.ctrl': pynput.keyboard.Key.ctrl,
        'Key.ctrl_l': pynput.keyboard.Key.ctrl_l,
        'Key.ctrl_r': pynput.keyboard.Key.ctrl_r,
        'Key.delete': pynput.keyboard.Key.delete,
        'Key.down': pynput.keyboard.Key.down,
        'Key.end': pynput.keyboard.Key.end,
        'Key.enter': pynput.keyboard.Key.enter,
        'Key.esc': pynput.keyboard.Key.esc,
        'Key.f1': pynput.keyboard.Key.f1,
        'Key.f2': pynput.keyboard.Key.f2,
        'Key.f3': pynput.keyboard.Key.f3,
        'Key.f4': pynput.keyboard.Key.f4,
        'Key.f5': pynput.keyboard.Key.f5,
        'Key.f6': pynput.keyboard.Key.f6,
        'Key.f7': pynput.keyboard.Key.f7,
        'Key.f8': pynput.keyboard.Key.f8,
        'Key.f9': pynput.keyboard.Key.f9,
        'Key.f10': pynput.keyboard.Key.f10,
        'Key.f11': pynput.keyboard.Key.f11,
        'Key.f12': pynput.keyboard.Key.f12,
        'Key.f13': pynput.keyboard.Key.f13,
        'Key.f14': pynput.keyboard.Key.f14,
        'Key.f15': pynput.keyboard.Key.f15,
        'Key.f16': pynput.keyboard.Key.f16,
        'Key.f17': pynput.keyboard.Key.f17,
        'Key.f18': pynput.keyboard.Key.f18,
        'Key.f19': pynput.keyboard.Key.f19,
        'Key.f20': pynput.keyboard.Key.f20,
        'Key.home': pynput.keyboard.Key.home,
        'Key.left': pynput.keyboard.Key.left,
        'Key.page_down': pynput.keyboard.Key.page_down,
        'Key.page_up': pynput.keyboard.Key.page_up,
        'Key.right': pynput.keyboard.Key.right,
        'Key.shift': pynput.keyboard.Key.shift,
        'Key.shift_l': pynput.keyboard.Key.shift_l,
        'Key.shift_r': pynput.keyboard.Key.shift_r,
        'Key.space': pynput.keyboard.Key.space,
        'Key.tab': pynput.keyboard.Key.tab,
        'Key.up': pynput.keyboard.Key.up,
        'Key.insert': pynput.keyboard.Key.insert,
        'Key.menu': pynput.keyboard.Key.menu,
        'Key.num_lock': pynput.keyboard.Key.num_lock,
        'Key.pause': pynput.keyboard.Key.pause,
        'Key.print_screen': pynput.keyboard.Key.print_screen,
        'Key.scroll_lock': pynput.keyboard.Key.scroll_lock
    }

    def set_mouse_coordinates(self, x, y):
        # 设置鼠标坐标
        self.mouse.position = (x, y)

    def mouse_move_scroll(self, x, y):
        # 鼠标滚轮
        self.mouse.scroll(x, y)              # 滚动鼠标

    def mouse_move(self, x, y):
        # 监听鼠标移动
        happen_time = time.time()
        self.time_order.append(happen_time)
        time_index = self.time_order.index(happen_time)
        if time_index != 0:
            sleep_time = happen_time - self.time_order[time_index - 1]
        else:
            sleep_time = 0
        self.mouse_keyboard_move.append((x, y, sleep_time))

    def mouse_right_click(self, x, y, key, state):
        happen_time = time.time()
        self.time_order.append(happen_time)
        time_index = self.time_order.index(happen_time)
        if time_index != 0:
            sleep_time = happen_time - self.time_order[time_index - 1]
        else:
            sleep_time = 0
        self.mouse_keyboard_move.append((x, y, key, state, sleep_time))

    def mouse_click(self, x, y, button, pressed):
        # 监听鼠标点击
        if pressed:
            if button == pynput.mouse.Button.left:
                self.mouse_right_click(x, y, 'left', 'pressed')
            elif button == pynput.mouse.Button.middle:
                self.mouse_right_click(x, y, 'middle', 'pressed')
            elif button == pynput.mouse.Button.right:
                self.mouse_right_click(x, y, 'right', 'pressed')
        else:
            if button == pynput.mouse.Button.left:
                self.mouse_right_click(x, y, 'left', 'release')
            elif button == pynput.mouse.Button.middle:
                self.mouse_right_click(x, y, 'middle', 'release')
            elif button == pynput.mouse.Button.right:
                self.mouse_right_click(x, y, 'right', 'release')

    def mouse_scroll(self, x, y, dx, dy):
        # 监听鼠标滚轮
        happen_time = time.time()
        self.time_order.append(happen_time)
        time_index = self.time_order.index(happen_time)
        if time_index != 0:
            sleep_time = happen_time - self.time_order[time_index - 1]
        else:
            sleep_time = 0
        self.mouse_keyboard_move.append((x, y, 'middle', dx, dy * 50, sleep_time))

    def listener_mouse(self):
        # 监听鼠标、键盘
        self.mouse_listener = pynput.mouse.Listener(on_move=self.mouse_move, on_click=self.mouse_click,
                                                    on_scroll=self.mouse_scroll)
        self.keyboard_listener = pynput.keyboard.Listener(on_press=self.keyboard_input_press,
                                                          on_release=self.keyboard_input_release)
        self.mouse_listener.start()
        self.keyboard_listener.start()
        self.mouse_listener.join()
        self.keyboard_listener.join()
        return

    def keyboard_input_press(self, key):  # 按键按下
        happen_time = time.time()
        self.time_order.append(happen_time)
        time_index = self.time_order.index(happen_time)
        if time_index != 0:
            sleep_time = happen_time - self.time_order[time_index - 1]
        else:
            sleep_time = 0
        self.mouse_keyboard_move.append((str(key), True, sleep_time))

    def keyboard_input_release(self, key):  # 按键释放
        happen_time = time.time()
        self.time_order.append(happen_time)
        time_index = self.time_order.index(happen_time)
        if time_index != 0:
            sleep_time = happen_time - self.time_order[time_index - 1]
        else:
            sleep_time = 0
        self.mouse_keyboard_move.append((str(key), False, sleep_time))
        if key == pynput.keyboard.Key.esc:
            self.stop_listener_keyoard()
            with open('aa.txt', "w") as f:
                for i in self.mouse_keyboard_move:
                    f.write(str(i) + '\n')
                f.close()

    def stop_listener_keyoard(self):
        pynput.keyboard.Listener.stop(self.keyboard_listener)
        pynput.mouse.Listener.stop(self.mouse_listener)

    def click_mouse_press(self, x, y, keys):
        self.set_mouse_coordinates(x, y)
        if keys == 'left':
            self.mouse.press(pynput.mouse.Button.left)
        elif keys == 'right':
            self.mouse.press(pynput.mouse.Button.right)
        elif keys == 'middle':
            self.mouse.press(pynput.mouse.Button.middle)

    def click_mouse_release(self, x, y, keys):
        self.set_mouse_coordinates(x, y)
        if keys == 'left':
            self.mouse.release(pynput.mouse.Button.left)
        elif keys == 'right':
            self.mouse.release(pynput.mouse.Button.right)
        elif keys == 'middle':
            self.mouse.release(pynput.mouse.Button.middle)

    def playback(self):
        with open(r'D:\Users\Sangfor\Desktop\aa.txt', 'a',encoding='utf-8') as f:
            for line in f.readlines():
                double_list = re.findall(r'[A-Za-z0-9._/;\[\]\\\=\-\`]+', line)
                print(double_list)
                if 'pressed' in line:
                    time.sleep(float(double_list[4]))
                    self.click_mouse_press(int(double_list[0]), int(double_list[1]), double_list[2])
                elif 'release' in line:
                    time.sleep(float(double_list[4]))
                    self.click_mouse_release(int(double_list[0]), int(double_list[1]), double_list[2])
                elif 'middle' in line:
                    time.sleep(float(double_list[5]))
                    self.mouse_move_scroll(int(double_list[3]), int(double_list[4]))
                elif 'Key' in line:
                    if 'Key.esc' in line:
                        pass
                    else:
                        if 'True' in line:
                            self.keyboard_press_key(self.default_keys[double_list[0]])
                        if 'False' in line:
                            self.keyboard_release_key(self.default_keys[double_list[0]])
                else:
                    if 'True' in line:
                        self.keyboard_press_key(double_list[0])
                    elif 'False' in line:
                        self.keyboard_release_key(double_list[0])
                    else:
                        time.sleep(0.005)
                        self.set_mouse_coordinates(int(double_list[0]), int(double_list[1]))

    def keyboard_press_key(self, word):
        self.keyboard.press(word)  # 按下

    def keyboard_release_key(self, word):
        self.keyboard.release(word)  # 松开

    def listener_all(self):
        thread_obj = threading.Thread(target=A.listener_mouse)
        thread_obj.start()


if __name__ == '__main__':
    A = ControlMouseKeyboard()
    A.listener_all()
    # A.playback()
