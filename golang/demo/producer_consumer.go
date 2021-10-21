package main

import (
	"fmt"
	"math/rand"
	"time"
)

func runConsumer(ch chan int) {
	for {
		goods := <-ch
		fmt.Println("Consumer consume...", goods)
	}
}

func runProducer(ch chan int) {

	for {
		ch <- rand.Intn(100)
		ch <- rand.Intn(100)
		ch <- rand.Intn(100)
		fmt.Println("Producer produce...")
		time.Sleep(time.Second)
	}
}

func main() {
    
	ch := make(chan int)
	
    go runConsumer(ch)
    
	go runProducer(ch, exit)	// undefined: exit暂时无法理解如何解决这错误
	go runProducer(ch)

	<-exit
}