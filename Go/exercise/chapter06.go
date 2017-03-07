// 并行是关于性能的
// 并行是关于程序设计的
//
package main

import (
	"fmt"
	"time"
)

var c chan int

func ready(w string, sec int) {
	time.Sleep(time.Duration(sec) * time.Second)
	fmt.Println(w, " is ready!")
	c <- 1
}

func cp6() {
	c = make(chan int)
	go ready("Tea", 2)
	go ready("Coffee", 1)

	fmt.Println("I`m waiting, but not too long.")

	i := 0
L:
	for {
		select {
		case <-c:
			i++
			if i > 1 {
				break L
			}
		}
	}

	// i := <-c
	// j := <-c
	//
	fmt.Println(i)
}

func q26() {
	ch := make(chan int)
	go shower(ch)

	for i := 0; i < 10; i++ {
		ch <- i
	}
}

func shower(c chan int) {
	for {
		j := <-c
		fmt.Println(j)
	}
}

func q26_2() {
	ch := make(chan int)
	quit := make(chan bool)

	go shower2(ch, quit)

	for i := 0; i < 10; i++ {
		ch <- i
	}
	quit <- true
}

func shower2(ch chan int, quit chan bool) {
	for {
		select {
		case j := <-c:
			fmt.Println(j)
		case <-quit:
			break
		}
	}
}

func dup3(in <-chan int) (<-chan int, <-chan int, <-chan int) {
	a, b, c := make(chan int, 2), make(chan int, 2), make(chan int, 2)

	go func() {
		for {
			x := <-in
			a <- x
			b <- x
			c <- x
		}
	}()

	return a, b, c
}

func fib() <-chan int {
	x := make(chan int, 2)
	a, b, out := dup3(x)

	go func() {
		x <- 0
		x <- 1
		<-a
		for {
			x <- <-a + <-b
		}
	}()

	return out
}

func main() {
	x := fib()
	for i := 0; i < 10; i++ {
		fmt.Println(<-x)
	}
}
