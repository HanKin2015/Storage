// 而在强类型语言中，变量的数据类型具有严格限制，不允许不同数据类型的变量直接相互操作
// 我们可以通过“go fmt”命令来按照官方的规范格式化代码。

// case 1  --ok
var a = 1.0

// case 2  --ok
var b int32 = 1.0

// case 3  --ok
var c float32 = 1.0

// case 4
var d float64 = 1.0

// case 5  --error:cannot use b (type int32) as type float32 in assignment
c = b 

// case 6  --ok
d = a

// case 7  --error:cannot use d (type float64) as type float32 in assignment
c = d

// case 8  --ok
b = int32(a)

fmt.Println(a, b, c, d)