package main

import "unsafe"

// 字符串类型在 go 里是个结构, 包含指向底层数组的指针和长度,这两部分每部分都是 8 个字节，所以字符串类型大小为 16 个字节。
const (
    a = "abc"
    b = len(a)
    c = unsafe.Sizeof(a)
)

// iota 只是在同一个 const 常量组内递增，每当有新的 const 关键字时，iota 计数会重新开始。
const (
    d = iota
    e = iota
    f = iota
)

// 在定义常量组时，如果不提供初始值，则表示将使用上行的表达式。
// iota根据行自增
const (
    g = iota
    h
    i
)

func main(){
	// 这样也是可以输出的
    println(a, b, c, d, e, f, g, h, i)
}