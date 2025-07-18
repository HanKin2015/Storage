package main

import "fmt"

func main() {
    fmt.Printf("fib(5) = %d\n", fibonacci(5))   // 1 1 2 3 5 8
}

func fibonacci(n int) (ret int) {
    if n <= 1 {
        return 1
    }
    return fibonacci(n - 1) + fibonacci(n - 2)
}