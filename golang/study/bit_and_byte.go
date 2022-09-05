/**
* 文 件 名: bit_and_byte.go
* 文件描述: 一个数字a究竟是怎么存在内存中的
* 作    者: HanKin
* 创建日期: 2022.09.05
* 修改日期：2022.09.05
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

package main

import (
    "fmt"
    "unsafe"
)

func main() {
    //定义一个 字符a
    var a = 'a'
    //定义一个 正 整数3
    var b uint8 = 3
    var c uint8 = 98
    fmt.Printf("值:%c,十进制:%d,类型:%T,二进制:%b,大小%v字节\n", a, a, a, a, unsafe.Sizeof(a)) // 4个字节
    fmt.Printf("值%d,十进制:%d,类型:%T,二进制%b,大小%v字节\n", b, b, b, b, unsafe.Sizeof(b))   //一个字节
    fmt.Printf("值%c,十进制,%d,类型:%T,二进制%b,大小%v字节\n", c, c, c, c,unsafe.Sizeof(c))      //一个字节
}