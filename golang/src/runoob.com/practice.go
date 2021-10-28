// 练习作业：手写一个杨辉三角形、九九乘法表、菱形

package main

import "fmt"

func YangHuiTriangle1(line int) {
    //arr := [line][line]int{}
    //arr := [...][...]int{}
    arr := [100][100]int{}
    //arr := [100][line]int{}
    //arr := [][]int{}
    //arr := [][]int

    for i := 1; i <= line; i++ {
        for j := 1; j <= i; j++ {
            if j == 1 || j == i {
                arr[i-1][j-1] = 1
                fmt.Print(arr[i-1][j-1])
            } else {
                arr[i-1][j-1] = arr[i-2][j-1] + arr[i-2][j-2]
                fmt.Print(arr[i-1][j-1])
            }
            fmt.Print(" ")
        }
        fmt.Print("\n")
    }
}

func YangHuiTriangle2(line int) {
    arr := [100][100]int{}

    for i := 1; i <= line; i++ {
        for j := 1; j <= line-i; j++ {
            fmt.Print(" ")
        }
        for j := 1; j <= i; j++ {
            if j == 1 || j == i {
                arr[i-1][j-1] = 1
                fmt.Print(arr[i-1][j-1])
            } else {
                arr[i-1][j-1] = arr[i-2][j-1] + arr[i-2][j-2]
                fmt.Print(arr[i-1][j-1])
            }
            fmt.Print(" ")
        }
        fmt.Print("\n")
    }
}

func main() {
    YangHuiTriangle1(10)
    YangHuiTriangle2(10)
}
