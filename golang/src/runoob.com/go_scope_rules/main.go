package main

import "fmt"

func main(){
  var a int = 0
  fmt.Println("for start")
  for a:=0; a < 10; a++ {
  //for a = 0; a < 10; a++ { 注意区别
    fmt.Println(a)
  }
  fmt.Println("for end")

  fmt.Println(a)
}