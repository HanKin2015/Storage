/**
 * index.go
 * 
 * author: hj
 * created at 2021-01-27
 */

// 包名,说明本文件里面含有main函数
package main

// 引入其他包
import (
	"fmt"
	"./myMath"
)

type Ustr string

func (us Ustr) String() string {
    return strings.ToUpper(string(us))
}

func (us Ustr) GoString() string {
    return `"` + strings.ToUpper(string(us)) + `"`
}

func (u Ustr) Format(f fmt.State, c rune) {
    write := func(s string) {
        f.Write([]byte(s))
    }
    switch c {
    case 'm', 'M':
        write("旗标：[")
        for s := "+- 0#"; len(s) > 0; s = s[1:] {
            if f.Flag(int(s[0])) {
                write(s[:1])
            }
        }
        write("]")
        if v, ok := f.Width(); ok {
            write(" | 宽度：" + strconv.FormatInt(int64(v), 10))
        }
        if v, ok := f.Precision(); ok {
            write(" | 精度：" + strconv.FormatInt(int64(v), 10))
        }
    case 's', 'v': // 如果使用 Format 函数，则必须自己处理所有格式，包括 %#v
        if c == 'v' && f.Flag('#') {
            write(u.GoString())
        } else {
            write(u.String())
        }
    default: // 如果使用 Format 函数，则必须自己处理默认输出
        write("无效格式：" + string(c))
    }
}

// https://www.runoob.com/go/go-basic-syntax.html笔记中内容有点多

// 主函数
func main() {
    fmt.Println("Hello World!")
    fmt.Println(mathClass.Add(1, 1))
    fmt.Println(mathClass.Sub(1, 1))
	// Hello World!
	// 2
	// 0

	fmt.Print("a", "b", 1, 2, 3, "c", "d", "\n")
    fmt.Println("a", "b", 1, 2, 3, "c", "d")
    fmt.Printf("ab %d %d %d cd\n", 1, 2, 3)
    // ab1 2 3cd
    // a b 1 2 3 c d
    // ab 1 2 3 cd

    if err := percent(30, 70, 90, 160); err != nil {
        fmt.Println(err)
    }
    // 30%
    // 70%
    // 90%
    // 数值 160 超出范围（100）
	
	u := Ustr("Hello World!")
    // "-" 标记和 "0" 标记不能同时存在
    fmt.Printf("%-+ 0#8.5m\n", u) // 旗标：[+- #] | 宽度：8 | 精度：5
    fmt.Printf("%+ 0#8.5M\n", u)  // 旗标：[+ 0#] | 宽度：8 | 精度：5
    fmt.Println(u)                // HELLO WORLD!
    fmt.Printf("%s\n", u)         // HELLO WORLD!
    fmt.Printf("%#v\n", u)        // "HELLO WORLD!"
    fmt.Printf("%d\n", u)         // 无效格式：d
}

func percent(i ...int) error {
    for _, n := range i {
        if n > 100 {
            return fmt.Errorf("数值 %d 超出范围（100）", n)
        }
        fmt.Print(n, "%\n")
    }
    return nil
}

