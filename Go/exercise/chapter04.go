package main

import (
	"fmt"
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

func main() {
	m := []e{1, 2, 3, 4}
	s := []e{"a", "b", "c", "d"}
	mf := q18(m, mult2)
	sf := q18(s, mult2)

	fmt.Printf("%v\n", mf)
	fmt.Printf("%v\n", sf)
}
