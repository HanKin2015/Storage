// Go 语言中同时有函数和方法。一个方法就是一个包含了接受者的函数。
// 接受者可以是命名类型或者结构体类型的一个值或者是一个指针。所有给定类型的方法属于该类型的方法集。

package main

import (
   "fmt"  
)

/* 定义结构体 */
type Circle struct {
  radius float64
}

func main() {
  var c1 Circle
  c1.radius = 10.00
  fmt.Println("圆的面积 = ", c1.getArea())
  
  println("切片解决九九乘法表")
  var num []int   //定义切片
  for i:=1;i<10;i++{
     num = append(num, i) //将数据添加到切片中去
  }
  for i:=1;i<10 ;i++  {
   for j:=1;j<i+1 ;j++  {
        value:=num[j-1]*i //计算      
        fmt.Printf("%d*%d=%d\t",j,i,value,)
     }
     fmt.Println()
  }
}

//该 method 属于 Circle 类型对象中的方法
func (c Circle) getArea() float64 {
  //c.radius 即为 Circle 类型对象中的属性
  return 3.14 * c.radius * c.radius
}