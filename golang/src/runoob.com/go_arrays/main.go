package main

import "fmt"

// 数组和切片
func test() {
	// 数组
	b := [...]int{2, 3, 5, 7, 11, 13}

	func boo(tt [6]int) {
		tt[0], tt[len(tt)-1] = tt[len(tt)-1], tt[0]
	}

	boo(b)
	fmt.Println(b) // [2 3 5 7 11 13]
	// 切片
	p := []int{2, 3, 5, 7, 11, 13}

	func poo(tt []int) {
		tt[0], tt[len(tt)-1] = tt[len(tt)-1], tt[0]
	}
	poo(p)
	fmt.Println(p)  // [13 3 5 7 11 2]
}

/*
value[0][0]=1      value[0][1]=2      [1 2]
value[1][0]=3      value[1][1]=4      [3 4]
value[2][0]=5      value[2][1]=6      [5 6]
*/
func T() {
    // 二维数组   
    var value = [3][2]int{{1, 2}, {3, 4}, {5, 6}}  
    // 遍历二维数组的其他方法，使用 range  
    // 其实，这里的 i, j 表示行游标和列游标  
    // v2 就是具体的每一个元素  
    // v  就是每一行的所有元素 
    for i, v := range value {
        for j, v2 := range v {            
            fmt.Printf("value[%v][%v]=%v \t ", i, j, v2)        
        }        
        fmt.Print(v)        
        fmt.Println()    
    }
}

func main() {
    // Step 1: 创建数组
    values := [][]int{}

    // Step 2: 使用 appped() 函数向空的二维数组添加两行一维数组
    row1 := []int{1, 2, 3}
    row2 := []int{4, 5, 6}
    values = append(values, row1)
    values = append(values, row2)

    // Step 3: 显示两行数据
    fmt.Println("Row 1")
    fmt.Println(values[0])
    fmt.Println("Row 2")
    fmt.Println(values[1])

    // Step 4: 访问第一个元素
    fmt.Println("第一个元素为：")
    fmt.Println(values[0][0])
}
/*
Row 1
[1 2 3]
Row 2
[4 5 6]
第一个元素为：
1

多维数组可通过大括号来初始值。以下实例为一个 3 行 4 列的二维数组：

a := [3][4]int{  
 {0, 1, 2, 3} ,   /*  第一行索引为 0 */
 {4, 5, 6, 7} ,   /*  第二行索引为 1 */
 {8, 9, 10, 11},   /* 第三行索引为 2 */
}
注意：以上代码中倒数第二行的 } 必须要有逗号，因为最后一行的 } 不能单独一行，也可以写成这样：
a := [3][4]int{  
 {0, 1, 2, 3} ,   /*  第一行索引为 0 */
 {4, 5, 6, 7} ,   /*  第二行索引为 1 */
 {8, 9, 10, 11}}   /* 第三行索引为 2 */
*/