package main

func main() {
    var a int
    var b int64  // 不管是32还是64，都无法完成int转int64/int32
    a = 15
    b = a + a    // 编译错误
    b = b + 5    // 因为 5 是常量，所以可以通过编译
}