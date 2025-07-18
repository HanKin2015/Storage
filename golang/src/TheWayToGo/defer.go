package main
import "fmt"

func main() {
    function1()
    
    // 当有多个 defer 行为被注册时，它们会以逆序执行（类似栈，即后进先出）
    for i := 0; i < 5; i++ {
        defer fmt.Printf("%d ", i)
    }
}

func function1() {
    fmt.Printf("In function1 at the top\n")
    defer function2()
    fmt.Printf("In function1 at the bottom!\n")
}

func function2() {
    fmt.Printf("function2: Deferred until the end of the calling function!")
}