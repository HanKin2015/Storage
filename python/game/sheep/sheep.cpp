/**
* 文 件 名: sheep.cpp
* 文件描述: 探究读写文件速度效率
* 作    者: HanKin
* 创建日期: 2022.06.30
* 修改日期：2022.06.30
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include "stdafx.h"
#include <easyx.h>
#include <graphics.h>		// 引用 EasyX 绘图库头文件
#include <conio.h>
#include <stdio.h>
const int WIDTH = 400;
const int HEIGHT = 760;
const int INTERVAL = 48;

IMAGE img_bk;
IMAGE img_item[3];

LPCTSTR change(const char *ch)
{
	int nLen = MultiByteToWideChar(CP_ACP, NULL, ch, -1, NULL, 0);
	wchar_t *pwstr = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, NULL, ch, -1, pwstr, nLen);
	return pwstr;
}

void loadImg()
{
	loadimage(&img_bk, change("images/back.png"), WIDTH, HEIGHT);
	loadimage(img_item + 0, change("images/tile1.png"), 48, 48);
	loadimage(img_item + 1, change("images/tile2.png"), 48, 48);
	loadimage(img_item + 2, change("images/tile5.png"), 48, 48);
}

int main()
{
	initgraph(WIDTH, HEIGHT,EW_SHOWCONSOLE);
	loadImg();

	int map[3][3] = {0};
	//初始化地图
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = r+1;	//1 2 3
		}
	}
	//打乱数组
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			int r1 = rand() % 3;
			int c1 = rand() % 3;
			int t = map[r1][c1];
			map[r1][c1] = map[r][c];
			map[r][c] = t;
		}
	}

	int store[7] = { 0 };

	int offsetX = (WIDTH - (2 * (48 + INTERVAL) + 48)) / 2;
	int offsetY = (HEIGHT - (2 * (48 + INTERVAL) + 48)) / 2;
	while (true)
	{
		BeginBatchDraw();
		//绘制地图
		putimage(0, 0, &img_bk);
		//输出图片
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if(map[r][c])
					putimage(offsetX + c * (48 + INTERVAL), offsetY + r * (48 + INTERVAL), img_item + (map[r][c]-1));
			}
		}
		//绘制下面
		for (int i = 0; i < 7; i++)
		{
			if (store[i])
				putimage((i * 50)+26, 620, img_item + (store[i]-1));
		}

		EndBatchDraw();
		ExMessage msg = { 0 };
		if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
		{
			//鼠标坐标判断
			for (int r = 0; r < 3; r++)
			{
				for (int c = 0; c < 3; c++)
				{
					int x = offsetX + c * (48 + INTERVAL);
					int y = offsetY + r * (48 + INTERVAL);
					//printf("pos(%d,%d)\n", x, y);
					//判断鼠标是否点击了图片
					if (msg.x > x && msg.x < x + 48 && msg.y>y && msg.y < y + 48)
					{
						//求出点击的图片对应的数组下标
						int col = (msg.x - offsetX)  /  (48 + INTERVAL);
						int row = (msg.y - offsetY)  / (48 + INTERVAL);
						//printf("row:%d col:%d\n", row, col);
						//把点击的图片添加到下面
						for (int i = 0; i < 7; i++)
						{
							if (store[i] == 0)
							{
								store[i] = map[row][col];
								break;
							}
						}

						//如果下面有三个一样的就消除
						int cnt = 0;
						for (int i = 0; i < 7; i++)
						{
							if (store[i] == map[row][col])
							{
								cnt++;
							}
						}
						if (cnt == 3)
						{
							for (int i = 0; i < 7; i++)
							{
								if (store[i] == map[row][col])
								{
									store[i] = 0;
								}
							}
						}

						//把点击的图片从map中删除
						map[row][col] = 0;					
					}
				}
			}
		}
	}

	while (1);
	return 0;
}
