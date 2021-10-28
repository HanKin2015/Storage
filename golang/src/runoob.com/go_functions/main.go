package main

import (
   "fmt"
   "math"
)

// Go 语言可以很灵活的创建函数，并作为另外一个函数的实参，函数定义后可作为另外一个函数的实参数传入
func test1() {
   /* 声明函数变量 */
   getSquareRoot := func(x float64) float64 {
      return math.Sqrt(x)
   }

   /* 使用函数 */
   fmt.Println(getSquareRoot(9))
}

/*
我是回调，x：1
我是回调，x：2
*/
// 声明一个函数类型
type cb func(int) int
func test2() {
	testCallBack(1, callBack)
    testCallBack(2, func(x int) int {
        fmt.Printf("我是回调，x：%d\n", x)
        return x
    })
}
func testCallBack(x int, f cb) {
    f(x)
}

func callBack(x int) int {
    fmt.Printf("我是回调，x：%d\n", x)
    return x
}

// 闭包是匿名函数，可在动态编程中使用
// Go 语言支持匿名函数，可作为闭包。匿名函数是一个"内联"语句或表达式。匿名函数的优越性在于可以直接使用函数内的变量，不必申明。
// 以下实例中，我们创建了函数 getSequence() ，返回另外一个函数。该函数的目的是在闭包中递增 i 变量。
func test3() {
   /* nextNumber 为一个函数，函数 i 为 0 */
   nextNumber := getSequence()  

   /* 调用 nextNumber 函数，i 变量自增 1 并返回 */
   fmt.Println(nextNumber())	// 1
   fmt.Println(nextNumber())	// 2
   fmt.Println(nextNumber())	// 3
   
   /* 创建新的函数 nextNumber1，并查看结果 */
   nextNumber1 := getSequence()  
   fmt.Println(nextNumber1())	// 1
   fmt.Println(nextNumber1())	// 2
}
func getSequence() func() int {
   i:=0
   return func() int {
      i+=1
     return i  
   }
}

// 带参数的闭包函数调用
func test4() {
    add_func := add(1,2)
    fmt.Println(add_func(1,1))	// 1 3 2
    fmt.Println(add_func(0,0))	// 2 3 0
    fmt.Println(add_func(2,2))	// 3 3 4
	
	sub_func := sub(9, 6)
	fmt.Println(sub_func(3, 1))	// 1 3 2
	fmt.Println(sub_func(7, 1))	// 2 3 6
	fmt.Println(sub_func(9, 1))	// 3 3 8
}
// 闭包使用方法
func add(x1, x2 int) func(x3 int, x4 int)(int, int, int)  {
    i := 0
    return func(x3 int,x4 int) (int,int,int){ 
       i++
       return i, x1 + x2, x3 + x4
    }
}
// 闭包使用方法，函数声明中的返回值(闭包函数)不用写具体的形参名称
func sub(x1, x2 int) func(int, int) (int, int, int) {
  i := 0
  return func(x3, x4 int) (int, int, int) {
    i += 1
    return i, x1 - x2, x3 - x4
  }
}

func main(){
	test1()

	test2()
	
	test3()
	
	test4()
}