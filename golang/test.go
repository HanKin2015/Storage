import (
	"testing"
	"unsafe"
	"math"
	"fmt"
)

func TestIntSize(t *testing.T) {
	fmt.Println("不同int类型占用的字节数大小：")
	var i1 int = 1
	var i2 int8 = 2
	var i3 int16 = 3
	var i4 int32 = 4
	var i5 int64 = 5
	fmt.Printf("int    : %v\n", unsafe.Sizeof(i1))
	fmt.Printf("int8   : %v\n", unsafe.Sizeof(i2))
	fmt.Printf("int16  : %v\n", unsafe.Sizeof(i3))
	fmt.Printf("int32  : %v\n", unsafe.Sizeof(i4))
	fmt.Printf("int64  : %v\n", unsafe.Sizeof(i5))
}

https://blog.csdn.net/u011582922/article/details/121732193