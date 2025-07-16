package main

import (
    "fmt"
    //"math"
)

func main() {
    var c1 complex64 = 5 + 10i
    fmt.Printf("The value is: %v\n", c1) // 输出： 5 + 10i
    
    var c2 = complex(1 ,2)
    fmt.Printf("The value is: %v\n", c2)
}