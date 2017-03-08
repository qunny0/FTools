package main

import (
	"bufio"
	"container/list"
	"errors"
	"flag"
	"fmt"
	"io"
	"os"
)

// q17
// 1. 这仅能工作于指向数字（int，unit）的指针值
// 2. ++仅仅定义在数学类型上，同时由于在Go中没有运算符重载，所以会在其他类型上失败（编译错误）。

// define the empty interface as a type
type e interface{}

func mult2(f e) e {
	switch f.(type) {
	case int:
		return f.(int) * 2
	case string:
		return f.(string) + f.(string) + f.(string) + f.(string)
	}
	return f
}

// m := []e{1, 2, 3, 4}
// s := []e{"a", "b", "c", "d"}
// mf := q18(m, mult2)
// sf := q18(s, mult2)
//
// fmt.Printf("%v\n", mf)
// fmt.Printf("%v\n", sf)
func q18(n []e, f func(e) e) []e {
	m := make([]e, len(n))
	for k, v := range n {
		m[k] = f(v)
	}

	return m
}

// q19-1
// var p1 Person        - 分配Person值给p1。p1的类型是Person
// p2 := new(Person)    - 分配内存并且将指针赋值给p2。p2类型是*Person
// q19-2
// func Set(t *T) { x = t}
// func Set(t T) {x = &t}
// 在第二个函数中，x指向一个新的(堆上分配的)变量t，其包含了实际参数值的副本。
// 在第一个函数中，x 指向了 t 指向的内容，也就是实际上的参数指向的内容。 因此在第二个函数，我们有了 “额外” 的变量存储了相关值的副本。
//

func q19() {
	l := list.New()

	l.PushBack(1)
	l.PushBack(2)
	l.PushBack(4)
	l.PushFront(3)

	for v := l.Front(); v != nil; v = v.Next() {
		fmt.Println(v.Value)
	}

	// for v := l.Back(); v != nil; v = v.Prev() {
	// 	fmt.Println(v.Value)
	// }
}

// q20
type Value int

type Node struct {
	Value
	prev, next *Node
}

type List struct {
	head, trail *Node
}

func (l *List) Front() *Node {
	return l.head
}

func (l *List) Back() *Node {
	return l.trail
}

func (n *Node) Next() *Node {
	return n.next
}

func (n *Node) Prev() *Node {
	return n.prev
}

func (l *List) Push(v Value) *List {
	n := &Node{Value: v}

	if l.head == nil {
		l.head = n
	} else {
		l.trail.next = n
		n.prev = l.trail
	}
	l.trail = n

	return l
}

var errEmpty = errors.New("List is empty")

func (l *List) Pop() (v Value, err error) {
	if l.trail == nil {
		err = errEmpty
	} else {
		v = l.trail.Value

		l.trail = l.trail.prev
		if l.trail == nil {
			l.head = nil
		}
	}

	return v, err
}

func q20() {
	l := new(List)

	l.Push(1)
	l.Push(3)
	l.Push(5)

	for v := l.Front(); v != nil; v = v.Next() {
		fmt.Println(v.Value)
	}

	fmt.Println()

	for v, err := l.Pop(); err == nil; v, err = l.Pop() {
		fmt.Println(v)
	}
}

// q20

var numberFlag = flag.Bool("n", false, "number each line")

// q21

func cat(r *bufio.Reader) {
	i := 1

	for {
		buf, e := r.ReadBytes('\n')
		if e == io.EOF {
			break
		}

		if *numberFlag {
			fmt.Fprintf(os.Stdout, "%5d %s", i, buf)
			i++
		} else {
			fmt.Fprintf(os.Stdout, "%s", buf)
		}
	}

	return
}

func q21() {
	flag.Parse()

	if flag.NArg() == 0 {
		cat(bufio.NewReader(os.Stdin))
	}

	for i := 0; i < flag.NArg(); i++ {
		f, e := os.Open(flag.Arg(i))

		if e != nil {
			fmt.Fprintf(os.Stderr, "%s: error reading from %s: %s\n", os.Args[0], flag.Arg(i), e.Error())
			continue
		}

		cat(bufio.NewReader(f))
	}
}

// q21

func main() {
	m := []e{1, 2, 3, 4}
	s := []e{"a", "b", "c", "d"}
	mf := q18(m, mult2)
	sf := q18(s, mult2)

	fmt.Printf("%v\n", mf)
	fmt.Printf("%v\n", sf)
}
