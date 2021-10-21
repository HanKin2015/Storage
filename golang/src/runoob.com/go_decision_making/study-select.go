/*
select 会循环检测条件，如果有满足则执行并退出，否则一直循环检测。
每个 case 都必须是一个通信
所有 channel 表达式都会被求值
所有被发送的表达式都会被求值
如果任意某个通信可以进行，它就执行，其他被忽略。
如果有多个 case 都可以运行，Select 会随机公平地选出一个执行。其他不会执行。
否则：
	如果有 default 子句，则执行该语句。
	如果没有 default 子句，select 将阻塞，直到某个通信可以运行；Go 不会重新对 channel 或值进行求值。
*/

package main

import (
        "fmt"
        "time"
)

func Chann(ch chan int, stopCh chan bool) {
        var i int
        i = 10
        for j := 0; j < 10; j++ {
                ch <- i
                time.Sleep(time.Second)
        }
        stopCh <- true
}

func main() {

        ch := make(chan int)
        c := 0
        stopCh := make(chan bool)

        go Chann(ch, stopCh)

        for {
                select {
                case c = <-ch:
                        fmt.Println("Receive c =", c)
                case s := <-ch:
                        fmt.Println("Receive s =", s)
                case _ = <-stopCh:
                        goto end
                }
        }
end:
}
/*
运行结果:
Receive s = 10
Receive s = 10
Receive c = 10
Receive s = 10
Receive s = 10
Receive s = 10
Receive c = 10
Receive c = 10
Receive c = 10
Receive s = 10
*/
