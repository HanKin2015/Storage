package main

import "fmt"

func main() {
    s := "你好，世界！"
    // 转换为rune切片
    runes := []rune(s)
    fmt.Println(len(s))             // 输出18，这是字节的数量
    fmt.Println(len(runes))         // 输出6，这是字符的数量
    fmt.Println(string(runes[0]))   // 输出"你"
    fmt.Println(string(runes[0:2])) // 输出"你好"
    
    // 遍历字符串中rune
    for i, r := range s {
        fmt.Printf("索引位置 %d 处的字符是 %c，码点是 U+%X\n", i, r, r)
    }
    
    // rune字面量
    r1 := 'A'       // 普通ASCII字符
    r2 := '世'      // 中文字符
    r3 := '\u4e16'  // 使用Unicode转义序列
    r4 := '\U0001F600' // emoji表情
    fmt.Printf("%T %d %c\n", r1, r1, r1) // 输出 int32 65 A
    fmt.Printf("%T %d %c\n", r2, r2, r2)
    fmt.Printf("%T %d %c\n", r3, r3, r3)
    fmt.Printf("%T %d %c\n", r4, r4, r4)
}