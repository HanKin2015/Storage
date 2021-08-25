#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <unistd.h>

#define min(x,y) ({ \
 typeof(x) _x = (x); \
 typeof(y) _y = (y); \
 (void) (&_x == &_y); \
 _x < _y ? _x : _y; })

#define max(x,y) ({ \
 typeof(x) _x = (x); \
 typeof(y) _y = (y); \
 (void) (&_x == &_y); \
 _x > _y ? _x : _y; })

void RaiseVolume(uint8_t *buffer, uint32_t length, int factor)
{
    signed short MIN = -0x8000;
    signed short MAX = 0x7FFF;
    signed short low = 0, high = 0, data = 0, maxData = 0, minData = 0;
    //获取一个音频帧中的最大值`max`和最小值`min`
    for (int i = 0; i < length; i+=2) {
        low = buffer[i];
        high = buffer[i+1];
        data = low+(high<<8);
        maxData = maxData > data ? maxData : data;
        minData = minData < data ? minData : data;
    }
  //根据获取到的最大值和最小值分别计算出在不失真的情况下，允许的放大倍数`maxfactor`和`minfactor`
    signed short maxfactor =  maxData != 0 ? MAX/maxData : 1;
    signed short minfactor =  minData != 0 ? MIN/minData : 1;
    if (minfactor == 1 || maxfactor == 1) {
        return;
    }
    //取其最小值为允许的放大倍数`allowfactor`
    signed short allowfactor = min(maxfactor, minfactor);
    //根据经验系数`factor`，选择合适的系数
    factor = factor > allowfactor ? allowfactor : factor;
    if (factor <= 1) {
        return;
    }
    //对PCM数据放大
    signed long newData = 0;
    for (int i = 0; i < length; i+=2) {
        low = buffer[i];
        high = buffer[i+1];
        data = low+(high<<8);
        newData = data*factor;
        //边界值溢出处理
        if (newData < MIN) {
            newData = MIN;
        }else if (newData > MAX) {
            newData = MAX;
        }
        data = newData&0xffff;
        buffer[i] = data&0x00ff;
        buffer[i+1] = (data&0xff00)>>8;
    }
}

int main()
{
	const char *c = "6543654243243244234";
	uint8_t *buffer = (uint8_t *)c;
	
	uint32_t length = 20;
	RaiseVolume(buffer, length, 2);
	return 0;
}