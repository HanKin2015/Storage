package main

import "fmt"

var isActive bool                   // 全局变量声明
var enabled, disabled = true, false // 忽略类型的声明
func test_bool() {
	var available bool // 一般声明
	valid := false     // 简短声明
	available = true   // 赋值操作
	fmt.Println(valid, available)
}

func main() {
	var a bool = true
	var b int = 123
	var c int8 = 1
	var d int16 = 2
	var e int32 = 3
	var f int64 = 4
	var uc uint8 = 1
	var ud uint16 = 2
	var ue uint32 = 3
	var uf uint64 = 4
	var g float32 = 1.23
	var h float64 = 2.34

	// go 1.9版本对于数字类型，无需定义int及float32、float64，系统会自动识别
	var k = 1.2
	var l = 3
	fmt.Println(a, b, c, d, e, f, uc, ud, ue, uf, g, h, k, l)

	test_bool()
}
