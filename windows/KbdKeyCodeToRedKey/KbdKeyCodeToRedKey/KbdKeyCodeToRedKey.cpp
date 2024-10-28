// KbdKeyCodeToRedKey.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

enum RedKey {
	REDKEY_INVALID,
	REDKEY_ESCAPE,
	REDKEY_1,
	REDKEY_2,
	REDKEY_3,
	REDKEY_4,
	REDKEY_5,
	REDKEY_6,
	REDKEY_7,
	REDKEY_8,
	REDKEY_9,
	REDKEY_0,
	REDKEY_MINUS,
	REDKEY_EQUALS,
	REDKEY_BACKSPACE,
	REDKEY_TAB,
	REDKEY_Q,
	REDKEY_W,
	REDKEY_E,
	REDKEY_R,
	REDKEY_T,
	REDKEY_Y,
	REDKEY_U,
	REDKEY_I,
	REDKEY_O,
	REDKEY_P,
	REDKEY_L_BRACKET,
	REDKEY_R_BRACKET,
	REDKEY_ENTER,
	REDKEY_L_CTRL,
	REDKEY_A,
	REDKEY_S,
	REDKEY_D,
	REDKEY_F,
	REDKEY_G,
	REDKEY_H,
	REDKEY_J,
	REDKEY_K,
	REDKEY_L,
	REDKEY_SEMICOLON,
	REDKEY_QUOTE,

	REDKEY_BACK_QUOTE,
	REDKEY_L_SHIFT,
	REDKEY_BACK_SLASH,
	REDKEY_Z,
	REDKEY_X,
	REDKEY_C,
	REDKEY_V,
	REDKEY_B,
	REDKEY_N,
	REDKEY_M,
	REDKEY_COMMA,
	REDKEY_PERIOD,
	REDKEY_SLASH,
	REDKEY_R_SHIFT,
	REDKEY_PAD_MULTIPLY,
	REDKEY_L_ALT,
	REDKEY_SPACE,
	REDKEY_CAPS_LOCK,
	REDKEY_F1,
	REDKEY_F2,
	REDKEY_F3,
	REDKEY_F4,
	REDKEY_F5,
	REDKEY_F6,
	REDKEY_F7,
	REDKEY_F8,
	REDKEY_F9,
	REDKEY_F10,
	REDKEY_NUM_LOCK,
	REDKEY_SCROLL_LOCK,
	REDKEY_PAD_7,
	REDKEY_PAD_8,
	REDKEY_PAD_9,
	REDKEY_PAD_MINUS,
	REDKEY_PAD_4,
	REDKEY_PAD_5,
	REDKEY_PAD_6,
	REDKEY_PAD_PLUS,
	REDKEY_PAD_1,
	REDKEY_PAD_2,
	REDKEY_PAD_3,
	REDKEY_PAD_0,
	REDKEY_PAD_POINT,

	REDKEY_EUROPEAN = 0x56,
	REDKEY_F11,
	REDKEY_F12,

	REDKEY_JAPANESE_HIRAGANA_KATAKANA = 0x70,
	REDKEY_JAPANESE_BACKSLASH = 0x73,
	REDKEY_JAPANESE_HENKAN = 0x79,
	REDKEY_JAPANESE_MUHENKAN = 0x7B,
	REDKEY_JAPANESE_YEN = 0x7D,

	REDKEY_KOREAN_HANGUL_HANJA = 0xf1,
	REDKEY_KOREAN_HANGUL = 0xf2,

	REDKEY_ESCAPE_BASE = 0x100,
	REDKEY_PAD_ENTER = REDKEY_ESCAPE_BASE + 0x1c,
	REDKEY_R_CTRL = REDKEY_ESCAPE_BASE + 0x1d,
	REDKEY_MUTE = REDKEY_ESCAPE_BASE + 0x20,
	REDKEY_FAKE_L_SHIFT = REDKEY_ESCAPE_BASE + 0x2a,
	REDKEY_VOLUME_DOWN = REDKEY_ESCAPE_BASE + 0x2e,
	REDKEY_VOLUME_UP = REDKEY_ESCAPE_BASE + 0x30,
	REDKEY_PAD_DIVIDE = REDKEY_ESCAPE_BASE + 0x35,
	REDKEY_FAKE_R_SHIFT = REDKEY_ESCAPE_BASE + 0x36,
	REDKEY_CTRL_PRINT_SCREEN = REDKEY_ESCAPE_BASE + 0x37,
	REDKEY_R_ALT = REDKEY_ESCAPE_BASE + 0x38,
	REDKEY_CTRL_BREAK = REDKEY_ESCAPE_BASE + 0x46,
	REDKEY_HOME = REDKEY_ESCAPE_BASE + 0x47,
	REDKEY_UP = REDKEY_ESCAPE_BASE + 0x48,
	REDKEY_PAGEUP = REDKEY_ESCAPE_BASE + 0x49,
	REDKEY_LEFT = REDKEY_ESCAPE_BASE + 0x4b,
	REDKEY_RIGHT = REDKEY_ESCAPE_BASE + 0x4d,
	REDKEY_END = REDKEY_ESCAPE_BASE + 0x4f,
	REDKEY_DOWN = REDKEY_ESCAPE_BASE + 0x50,
	REDKEY_PAGEDOWN = REDKEY_ESCAPE_BASE + 0x51,
	REDKEY_INSERT = REDKEY_ESCAPE_BASE + 0x52,
	REDKEY_DELETE = REDKEY_ESCAPE_BASE + 0x53,
	REDKEY_LEFT_CMD = REDKEY_ESCAPE_BASE + 0x5b,
	REDKEY_RIGHT_CMD = REDKEY_ESCAPE_BASE + 0x5c,
	REDKEY_MENU = REDKEY_ESCAPE_BASE + 0x5d,

	REDKEY_PAUSE,

	REDKEY_NUM_KEYS
};

enum KbdKeyCode {
	KBD_KEYCODE_RETURN = 0x0D,
	KBD_KEYCODE_0 = 0x30,
	KBD_KEYCODE_1,
	KBD_KEYCODE_2,
	KBD_KEYCODE_3,
	KBD_KEYCODE_4,
	KBD_KEYCODE_5,
	KBD_KEYCODE_6,
	KBD_KEYCODE_7,
	KBD_KEYCODE_8,
	KBD_KEYCODE_9,
	KBD_KEYCODE_SEMICOLON,
	KBD_KEYCODE_APOSTROPH,
	KBD_KEYCODE_BACKQUAT,
	KBD_KEYCODE_PERIOD,
	KBD_KEYCODE_BACKSLASH,
	KBD_KEYCODE_BACK_SPACE,
	KBD_KEYCODE_TAB,
	KBD_KEYCODE_A,
	KBD_KEYCODE_B,
	KBD_KEYCODE_C,
	KBD_KEYCODE_D,
	KBD_KEYCODE_E,
	KBD_KEYCODE_F,
	KBD_KEYCODE_G,
	KBD_KEYCODE_H,
	KBD_KEYCODE_I,
	KBD_KEYCODE_J,
	KBD_KEYCODE_K,
	KBD_KEYCODE_L,
	KBD_KEYCODE_M,
	KBD_KEYCODE_N,
	KBD_KEYCODE_O,
	KBD_KEYCODE_P,
	KBD_KEYCODE_Q,
	KBD_KEYCODE_R,
	KBD_KEYCODE_S,
	KBD_KEYCODE_T,
	KBD_KEYCODE_U,
	KBD_KEYCODE_V,
	KBD_KEYCODE_W,
	KBD_KEYCODE_X,
	KBD_KEYCODE_Y,
	KBD_KEYCODE_Z,
	KBD_KEYCODE_SLASH,
	KBD_KEYCODE_R_SHIFT,
	KBD_KEYCODE_PAD_MULTIPLY,
	KBD_KEYCODE_L_ALT,
	KBD_KEYCODE_SPACE,
	KBD_KEYCODE_CAPS_LOCK,
	KBD_KEYCODE_F1,
	KBD_KEYCODE_F2,
	KBD_KEYCODE_F3,
	KBD_KEYCODE_F4,
	KBD_KEYCODE_F5,
	KBD_KEYCODE_F6,
	KBD_KEYCODE_F7,
	KBD_KEYCODE_F8,
	KBD_KEYCODE_F9,
	KBD_KEYCODE_F10,
	KBD_KEYCODE_NUM_LOCK,
	KBD_KEYCODE_SCROLL_LOCK,
	KBD_KEYCODE_PAD_7,
	KBD_KEYCODE_PAD_8,
	KBD_KEYCODE_PAD_9,
	KBD_KEYCODE_PAD_SUBTRACT,
	KBD_KEYCODE_PAD_4,
	KBD_KEYCODE_PAD_5,
	KBD_KEYCODE_PAD_6,
	KBD_KEYCODE_PAD_ADD,
	KBD_KEYCODE_PAD_1,
	KBD_KEYCODE_PAD_2,
	KBD_KEYCODE_PAD_3,
	KBD_KEYCODE_PAD_0,
	KBD_KEYCODE_PAD_DEL,
	KBD_KEYCODE_EUROPEAN = 94,
	KBD_KEYCODE_F11,
	KBD_KEYCODE_F12,
	KBD_KEYCODE_HOME,
	KBD_KEYCODE_UP,
	KBD_KEYCODE_PAGE_UP,
	KBD_KEYCODE_LEFT,
	KBD_KEYCODE_RIGHT = 102,
	KBD_KEYCODE_END,
	KBD_KEYCODE_DOWN,
	KBD_KEYCODE_PAGE_DOWN,
	KBD_KEYCODE_INSERT,
	KBD_KEYCODE_DELETE,
	KBD_KEYCODE_PAD_ENTER,
	KBD_KEYCODE_R_CONTROL,
	KBD_KEYCODE_PAUSE,
	KBD_KEYCODE_PRINT,
	KBD_KEYCODE_PAD_DEVIDE,
	KBD_KEYCODE_R_ALT,
	KBD_KEYCODE_L_COMMAND = 115,
	KBD_KEYCODE_R_COMMAND,
	KBD_KEYCODE_MENU,
	KBD_KEYCODE_JAPANESE_HENKAN = 129,
	KBD_KEYCODE_JAPANESE_MUHENKAN = 131,
	KBD_KEYCODE_YEN = 133,
	KBD_KEYCODE_L_SHIFT = 0xA0,
	KBD_KEYCODE_JAPANESE_HIRAGANA_KATAKANA = 208,
	KBD_KEYCODE_HANGUL_HANJA,
	KBD_KEYCODE_HANGUL,
	KBD_KEYCODE_JAPANESE_BACKSLASH,
	KBD_KEYCODE_ESCAPE,
	KBD_KEYCODE_MINUS,
	KBD_KEYCODE_EQUAL,
	KBD_KEYCODE_L_BRACKET,
	KBD_KEYCODE_R_BRACKET,
	KBD_KEYCODE_L_CONTROL,
	KBD_KEYCODE_COMMA,
};

static RedKey keycode_map[256];

#define INIT_MAP                                                                    \
    KEYMAP(KEYCODE_ESCAPE, REDKEY_ESCAPE);                                          \
    KEYMAP(KEYCODE_1, REDKEY_1);                                                    \
    KEYMAP(KEYCODE_2, REDKEY_2);                                                    \
    KEYMAP(KEYCODE_3, REDKEY_3);                                                    \
    KEYMAP(KEYCODE_4, REDKEY_4);                                                    \
    KEYMAP(KEYCODE_5, REDKEY_5);                                                    \
    KEYMAP(KEYCODE_6, REDKEY_6);                                                    \
    KEYMAP(KEYCODE_7, REDKEY_7);                                                    \
    KEYMAP(KEYCODE_8, REDKEY_8);                                                    \
    KEYMAP(KEYCODE_9, REDKEY_9);                                                    \
    KEYMAP(KEYCODE_0, REDKEY_0);                                                    \
    KEYMAP(KEYCODE_MINUS, REDKEY_MINUS);                                            \
    KEYMAP(KEYCODE_EQUAL, REDKEY_EQUALS);                                           \
    KEYMAP(KEYCODE_BACK_SPACE, REDKEY_BACKSPACE);                                   \
    KEYMAP(KEYCODE_TAB, REDKEY_TAB);                                                \
    KEYMAP(KEYCODE_Q, REDKEY_Q);                                                    \
    KEYMAP(KEYCODE_W, REDKEY_W);                                                    \
    KEYMAP(KEYCODE_E, REDKEY_E);                                                    \
    KEYMAP(KEYCODE_R, REDKEY_R);                                                    \
    KEYMAP(KEYCODE_T, REDKEY_T);                                                    \
    KEYMAP(KEYCODE_Y, REDKEY_Y);                                                    \
    KEYMAP(KEYCODE_U, REDKEY_U);                                                    \
    KEYMAP(KEYCODE_I, REDKEY_I);                                                    \
    KEYMAP(KEYCODE_O, REDKEY_O);                                                    \
    KEYMAP(KEYCODE_P, REDKEY_P);                                                    \
    KEYMAP(KEYCODE_L_BRACKET, REDKEY_L_BRACKET);                                    \
    KEYMAP(KEYCODE_R_BRACKET, REDKEY_R_BRACKET);                                    \
    KEYMAP(KEYCODE_RETURN, REDKEY_ENTER);                                           \
    KEYMAP(KEYCODE_L_CONTROL, REDKEY_L_CTRL);                                       \
    KEYMAP(KEYCODE_A, REDKEY_A);                                                    \
    KEYMAP(KEYCODE_S, REDKEY_S);                                                    \
    KEYMAP(KEYCODE_D, REDKEY_D);                                                    \
    KEYMAP(KEYCODE_F, REDKEY_F);                                                    \
    KEYMAP(KEYCODE_G, REDKEY_G);                                                    \
    KEYMAP(KEYCODE_H, REDKEY_H);                                                    \
    KEYMAP(KEYCODE_J, REDKEY_J);                                                    \
    KEYMAP(KEYCODE_K, REDKEY_K);                                                    \
    KEYMAP(KEYCODE_L, REDKEY_L);                                                    \
    KEYMAP(KEYCODE_SEMICOLON, REDKEY_SEMICOLON);                                    \
    KEYMAP(KEYCODE_APOSTROPH, REDKEY_QUOTE);                                        \
    KEYMAP(KEYCODE_BACKQUAT, REDKEY_BACK_QUOTE);                                    \
    KEYMAP(KEYCODE_L_SHIFT, REDKEY_L_SHIFT);                                        \
    KEYMAP(KEYCODE_BACKSLASH, REDKEY_BACK_SLASH);                                   \
    KEYMAP(KEYCODE_Z, REDKEY_Z);                                                    \
    KEYMAP(KEYCODE_X, REDKEY_X);                                                    \
    KEYMAP(KEYCODE_C, REDKEY_C);                                                    \
    KEYMAP(KEYCODE_V, REDKEY_V);                                                    \
    KEYMAP(KEYCODE_B, REDKEY_B);                                                    \
    KEYMAP(KEYCODE_N, REDKEY_N);                                                    \
    KEYMAP(KEYCODE_M, REDKEY_M);                                                    \
    KEYMAP(KEYCODE_COMMA, REDKEY_COMMA);                                            \
    KEYMAP(KEYCODE_PERIOD, REDKEY_PERIOD);                                          \
    KEYMAP(KEYCODE_SLASH, REDKEY_SLASH);                                            \
    KEYMAP(KEYCODE_R_SHIFT, REDKEY_R_SHIFT);                                        \
    KEYMAP(KEYCODE_PAD_MULTIPLY, REDKEY_PAD_MULTIPLY);                              \
    KEYMAP(KEYCODE_L_ALT, REDKEY_L_ALT);                                            \
    KEYMAP(KEYCODE_SPACE, REDKEY_SPACE);                                            \
    KEYMAP(KEYCODE_CAPS_LOCK, REDKEY_CAPS_LOCK);                                    \
    KEYMAP(KEYCODE_F1, REDKEY_F1);                                                  \
    KEYMAP(KEYCODE_F2, REDKEY_F2);                                                  \
    KEYMAP(KEYCODE_F3, REDKEY_F3);                                                  \
    KEYMAP(KEYCODE_F4, REDKEY_F4);                                                  \
    KEYMAP(KEYCODE_F5, REDKEY_F5);                                                  \
    KEYMAP(KEYCODE_F6, REDKEY_F6);                                                  \
    KEYMAP(KEYCODE_F7, REDKEY_F7);                                                  \
    KEYMAP(KEYCODE_F8, REDKEY_F8);                                                  \
    KEYMAP(KEYCODE_F9, REDKEY_F9);                                                  \
    KEYMAP(KEYCODE_F10, REDKEY_F10);                                                \
    KEYMAP(KEYCODE_NUM_LOCK, REDKEY_NUM_LOCK);                                      \
    KEYMAP(KEYCODE_SCROLL_LOCK, REDKEY_SCROLL_LOCK);                                \
    KEYMAP(KEYCODE_PAD_7, REDKEY_PAD_7);                                            \
    KEYMAP(KEYCODE_PAD_8, REDKEY_PAD_8);                                            \
    KEYMAP(KEYCODE_PAD_9, REDKEY_PAD_9);                                            \
    KEYMAP(KEYCODE_PAD_SUBTRACT, REDKEY_PAD_MINUS);                                 \
    KEYMAP(KEYCODE_PAD_4, REDKEY_PAD_4);                                            \
    KEYMAP(KEYCODE_PAD_5, REDKEY_PAD_5);                                            \
    KEYMAP(KEYCODE_PAD_6, REDKEY_PAD_6);                                            \
    KEYMAP(KEYCODE_PAD_ADD, REDKEY_PAD_PLUS);                                       \
    KEYMAP(KEYCODE_PAD_1, REDKEY_PAD_1);                                            \
    KEYMAP(KEYCODE_PAD_2, REDKEY_PAD_2);                                            \
    KEYMAP(KEYCODE_PAD_3, REDKEY_PAD_3);                                            \
    KEYMAP(KEYCODE_PAD_0, REDKEY_PAD_0);                                            \
    KEYMAP(KEYCODE_PAD_DEL, REDKEY_PAD_POINT);                                      \
    KEYMAP(KEYCODE_EUROPEAN, REDKEY_EUROPEAN);                                      \
    KEYMAP(KEYCODE_F11, REDKEY_F11);                                                \
    KEYMAP(KEYCODE_F12, REDKEY_F12);                                                \
    KEYMAP(KEYCODE_JAPANESE_BACKSLASH, REDKEY_JAPANESE_BACKSLASH);                  \
    KEYMAP(KEYCODE_JAPANESE_HENKAN, REDKEY_JAPANESE_HENKAN);                        \
    KEYMAP(KEYCODE_JAPANESE_HIRAGANA_KATAKANA, REDKEY_JAPANESE_HIRAGANA_KATAKANA);  \
    KEYMAP(KEYCODE_JAPANESE_MUHENKAN, REDKEY_JAPANESE_MUHENKAN);                    \
    KEYMAP(KEYCODE_PAD_ENTER, REDKEY_PAD_ENTER);                                    \
    KEYMAP(KEYCODE_R_CONTROL, REDKEY_R_CTRL);                                       \
    KEYMAP(KEYCODE_PAD_DEVIDE, REDKEY_PAD_DIVIDE);                                  \
    KEYMAP(KEYCODE_PRINT, REDKEY_CTRL_PRINT_SCREEN);                                \
    KEYMAP(KEYCODE_R_ALT, REDKEY_R_ALT);                                            \
    KEYMAP(KEYCODE_HOME, REDKEY_HOME);                                              \
    KEYMAP(KEYCODE_UP, REDKEY_UP);                                                  \
    KEYMAP(KEYCODE_PAGE_UP, REDKEY_PAGEUP);                                         \
    KEYMAP(KEYCODE_LEFT, REDKEY_LEFT);                                              \
    KEYMAP(KEYCODE_RIGHT, REDKEY_RIGHT);                                            \
    KEYMAP(KEYCODE_END, REDKEY_END);                                                \
    KEYMAP(KEYCODE_DOWN, REDKEY_DOWN);                                              \
    KEYMAP(KEYCODE_PAGE_DOWN, REDKEY_PAGEDOWN);                                     \
    KEYMAP(KEYCODE_INSERT, REDKEY_INSERT);                                          \
    KEYMAP(KEYCODE_DELETE, REDKEY_DELETE);                                          \
    KEYMAP(KEYCODE_PAUSE, REDKEY_PAUSE);                                            \
                                                                                    \
    KEYMAP(KEYCODE_YEN, REDKEY_JAPANESE_YEN);                                       \
    KEYMAP(KEYCODE_L_COMMAND, REDKEY_LEFT_CMD);                                     \
    KEYMAP(KEYCODE_R_COMMAND, REDKEY_RIGHT_CMD);                                    \
    KEYMAP(KEYCODE_MENU, REDKEY_MENU);                                              \
    KEYMAP(KEYCODE_HANGUL, REDKEY_KOREAN_HANGUL);                                   \
    KEYMAP(KEYCODE_HANGUL_HANJA, REDKEY_KOREAN_HANGUL_HANJA);

static void init_kbd_map()
{
#define KEYMAP(key_code, red_key)  keycode_map[KBD_##key_code] = red_key
	INIT_MAP;
#undef KEYMAP
}

int main()
{
	init_kbd_map();
	printf("0x%02x 0x%02x\n", 'a', 'A');
	printf("A: %d\n", keycode_map['A']);
	printf("A: %d\n", keycode_map[65]);

	RedKey key = keycode_map['A'];
	if (key >= 'A' && key <= 'Z')
	{
		printf("hello world!\n");
	}
    return 0;
}

