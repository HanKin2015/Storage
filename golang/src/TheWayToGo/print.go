package main

import "fmt"

func main() {
    // 使用 print（不推荐）
    num := 42
    str := "hello"
    print("num=", num, " str=", str, "\n") // 输出可能不规范

    // 使用 fmt.Print
    fmt.Print("num=", num, " str=", str, "\n") // 标准输出
    fmt.Printf("num=%d str=%s\n", num, str)    // 格式化输出
    fmt.Println("num=", num, "str=", str)      // 自动换行
    
    var ch1 byte = 65
    var ch2 byte = '\x41'
    print(ch1, ch2)
}