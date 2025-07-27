package main
import "fmt"

func main() {
    var arrAge = [5]int{18, 20, 15, 22, 16}
    fmt.Printf("%d\n", len(arrAge));
    var arrLazy1 = [...]int{5, 6, 7, 8, 22}
    fmt.Printf("%d\n", len(arrLazy1));
    var arrLazy2 = []int{5, 6, 7, 8, 22}
    fmt.Printf("%d\n", len(arrLazy2));
    var arrKeyValue1 = [5]string{3: "Chris", 4: "Ron"}  // 指的是下标3和4
    fmt.Printf("%d\n", len(arrKeyValue1));
    var arrKeyValue2 = []string{3: "Chris", 4: "Ron"}
    fmt.Printf("%d\n", len(arrKeyValue2));

    for i:=0; i < len(arrKeyValue1); i++ {
        fmt.Printf("Person at %d is %s\n", i, arrKeyValue1[i])
    }
}