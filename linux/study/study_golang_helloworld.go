/**
* 文 件 名: study_golang.go
* 文件描述: 学习golang语言: 简单入门
* 作    者: HanKin
* 创建日期: 2021.09.09
* 修改日期：2021.09.09
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
package main	// 同一个文件夹下的文件只能有一个包名

import "fmt"
import (
    "io"
    "math"
	"os"
	"strings"
)

// 常量即常变量 const var str = "hello world!"
const str = "hello world!"

// 函数名首字母小写即为 private
func add(x,y int) int {
    return x + y
}

// 函数名首字母大写即为 public
func Sub(x,y int) int {
    return x - y
}

// 学习fmt包
func study_fmt() {
	fmt.Print("a", "b", 1, 2, 3, "cd", "efg", "\n")	// 非字符串参数之间会添加空格，返回写入的字节数
    fmt.Println("a", "b", 1, 2, 3, "c", "d")		// 所有参数之间会添加空格，最后会添加一个换行符
    fmt.Printf("ab %d %d %d cd\n", 1, 2, 3)			// 格式字符串 format 的占位符中
    // ab1 2 3cdefg
    // a b 1 2 3 c d
    // ab 1 2 3 cd

    if err := percent(30, 70, 90, 160); err != nil {
        fmt.Println(err)
    }
    // 30%
    // 70%
    // 90%
    // 数值 160 超出范围（100）
}
func percent(i ...int) error {
    for _, n := range i {
        if n > 100 {
            return fmt.Errorf("数值 %d 超出范围（100）", n)
        }
        fmt.Print(n, "%\n")
    }
    return nil
}

func test() {
    fmt.Println(str)			// hello world!
	fmt.Println(math.Exp2(10))	// 1024
	fmt.Println(add(3, 5))		// 8
	fmt.Println(Sub(5, 3))		// 2
}

func study_io() {
	//io.Copy(os.Stdout, os.Stdin)	// 无限输入输出
    //fmt.Println("Got EOF -- bye")
	io.CopyN(os.Stdout, strings.NewReader("Go语言中文网"), 8)	// Go语言
	fmt.Println()	// 换行
}

func study_format_string() {
	// 格式化字符串: %d 表示整型数字，%s 表示字符串
    var stockcode=123
    var enddate="2020-12-31"
    var url="Code=%d&endDate=%s"
    var target_url=fmt.Sprintf(url,stockcode,enddate)
    fmt.Println(target_url)
}

func main() {	// { 不能在单独的行上
    // 1.无法分类的学习
    test()

    // 2.学习io库
    study_io()

    // 3.学习fmt库
    study_fmt()

    // 4.学习格式化字符串
    study_format_string()
}
