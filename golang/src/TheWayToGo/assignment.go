package main

import "fmt"

func main() {
    a := 100
    //a := 123  // 错误
    a = 123
    fmt.Println("a = ", a)
    fmt.Println("a =", a)   // 正确，在每个参数之间自动增加空格
}
