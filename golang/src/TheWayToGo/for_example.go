package main

import "fmt"

func main() {
    for i := 0; i < 5; i++ {
        var v int
        fmt.Printf("%d ", v)
        v = 5
    }
    
    s := ""
    for ; s != "aaaaa"; {
        fmt.Println("Value of s:", s)
        s = s + "a"
    }
}