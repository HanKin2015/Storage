package main

import ("time"; "fmt")

func main() {
    // var 和:= 不能混用，:= 已经包含了变量声明
    var start = time.Now()
    var end = time.Now()
    var delta = end.Sub(start)
    fmt.Printf("运行时间是 %v\n", delta)
    fmt.Println("运行时间是", delta)
}