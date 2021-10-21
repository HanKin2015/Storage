/*
For-each range 循环

这种格式的循环可以对字符串、数组、切片等进行迭代输出元素。
*/

package main
import "fmt"

func test1() {
	strings := []string{"google", "runoob"}
	for i, s := range strings {
			fmt.Println(i, s)
	}


	numbers := [6]int{1, 2, 3, 5}
	for i,x:= range numbers {
			fmt.Printf("第 %d 位 x 的值 = %d\n", i,x)
	}  
}

// 使用标记和不使用标记的区别
/*
---- break ----
i: 1
i2: 11
i: 2
i2: 11
i: 3
i2: 11
---- break label ----
i: 1
i2: 11 
*/
func test2() {
    // 不使用标记
    fmt.Println("---- break ----")
    for i := 1; i <= 3; i++ {
        fmt.Printf("i: %d\n", i)
                for i2 := 11; i2 <= 13; i2++ {
                        fmt.Printf("i2: %d\n", i2)
                        break
                }
        }

    // 使用标记
    fmt.Println("---- break label ----")
    re:
        for i := 1; i <= 3; i++ {
            fmt.Printf("i: %d\n", i)
            for i2 := 11; i2 <= 13; i2++ {
                fmt.Printf("i2: %d\n", i2)
                break re
            }
        }
}

/*
欢迎进入成绩查询系统
1.进入成绩查询 2.退出程序
请输入序号选择:1

请输入一个学生的成绩:56
你考了56分,评价为D,成绩不合格

1.进入成绩查询 2.退出程序
请输入序号选择:2

exit status 1
*/
func test3() {
    var score int = 0
    var fenshu string = "A"
    fmt.Printf("欢迎进入成绩查询系统\n")
    ZHU: for true{
        var xuanzhe int = 0
        fmt.Println("1.进入成绩查询 2.退出程序")
        fmt.Printf("请输入序号选择:")
        fmt.Scanln(&xuanzhe)
        fmt.Printf("\n")
        if xuanzhe == 1{
             goto CHA
        }
        if xuanzhe == 2{
            os.Exit(1)
        }

    }

    CHA: for true {
        fmt.Printf("请输入一个学生的成绩:")
        fmt.Scanln(&score)

        switch {
            case score >= 90:fenshu = "A"

            case score >= 80&&score < 90:fenshu = "B"

            case score >= 60&&score < 80:fenshu = "C"

            default: fenshu = "D"
        }

        //fmt.Println(fenshu)
         var c string  = strconv.Itoa(score)
        switch{
            case fenshu == "A":
                fmt.Printf("你考了%s分,评价为%s,成绩优秀\n",c,fenshu)
            case fenshu == "B" || fenshu == "C":
                fmt.Printf("你考了%s分,评价为%s,成绩良好\n",c,fenshu)
            case fenshu == "D":
                fmt.Printf("你考了%s分,评价为%s,成绩不合格\n",c,fenshu)
        }
        fmt.Printf("\n")
        goto ZHU
}
    //fmt.Println(score)
}

func main() {
	test1()
	
	test2()
	
	test3()
}