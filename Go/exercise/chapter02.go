package main

import (
	"fmt"
	"strconv"
)

func f() (ret int) {
	defer func() {
		ret++
	}()

	return 0
}

// v := q_0(1.1, 2.2, 3.3, 4.4, 5.5)
func q5(args ...float64) (average float64) {
	var sum float64
	sum = 0
	for _, v := range args {
		sum += v
	}

	average = sum / float64(len(args))

	return
}

func a5(xs []float64) (avg float64) {
	sum := 0.0
	switch len(xs) {
	case 0:
		avg = 0
	default:
		for _, v := range xs {
			sum += v
		}
		avg = sum / float64(len(xs))
	}

	return
}

// f(2, 7)
// f(7, 2)
func q6(a, b int) (ra, rb int) {
	if a > b {
		ra, rb = b, a
	} else {
		ra, rb = a, b
	}

	return
}

// q7 - line 9. i is out of range

// q8
var gStackInt [256]int
var gStackCursor int

// gPush(1)
// gPush(3)
// gPush(5)
// a := gPop()
// a = gPop()
func gPush(a int) {
	gStackInt[gStackCursor] = a
	gStackCursor++
}

func gPop() (ret int) {
	gStackCursor--
	ret = gStackInt[gStackCursor]

	return
}

func gPrint() {

}

type stack struct {
	cursor int
	data   [256]int
}

func (s *stack) push(k int) {
	if s.cursor > 255 {
		return
	}

	s.data[s.cursor] = k
	s.cursor++
}

func (s *stack) pop() int {
	s.cursor--
	return s.data[s.cursor]
}

// 注意这里不是指针
func (s stack) String() string {
	var str string
	for i := 0; i < s.cursor; i++ {
		str = str + "[" + strconv.Itoa(i) + ":" + strconv.Itoa(s.data[i]) + "]"
	}

	return str
}

func q9(args ...int) {
	for _, v := range args {
		fmt.Println(v)
	}
}

// q10(7) = 13
func q10(level int) (ret int) {
	if level == 1 || level == 2 {
		ret = 1
		return
	}

	ret = q10(level-1) + q10(level-2)

	return ret
}

func fibonacci(value int) []int {
	x := make([]int, value)

	x[0], x[1] = 1, 1
	for n := 2; n < value; n++ {
		x[n] = x[n-1] + x[n-2]
	}

	return x
}

// 什么是列表
func q11(f func(int) int, l []int) []int {
	j := make([]int, len(l))

	for k, v := range l {
		j[k] = f(v)
	}

	return j
}

func q12Min(a, b int) (ret int) {
	if a > b {
		ret = b
	} else {
		ret = a
	}
	return
}

func q12Max(a, b int) (ret int) {
	if a > b {
		ret = a
	} else {
		ret = b
	}
	return
}

// q12(q12Min, 1, 2, 3, 4, 7, 6, 100, 2)
func q12(f func(int, int) int, arr ...int) (ret int) {
	ret = arr[0]
	for i := 1; i < len(arr); i++ {
		ret = f(ret, arr[i])
	}

	return
}

// q13(1, 2, 3, 4, 7, 6, 100, 2)
func q13(arr ...int) {
OUT:
	for i := 1; i < len(arr); i++ {
		swap := false
		for j := 0; j < len(arr)-i; j++ {
			if arr[j] < arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
				swap = true
			}
		}
		if !swap {
			break OUT
		}
	}

	for _, v := range arr {
		fmt.Println(v)
	}
}

func q14() (f func(a int) (ret int)) {
	f = func(a int) (ret int) {
		ret = a + 2
		return
	}
	return
}

func q14_2(x int) (f func(a int) (ret int)) {
	f = func(a int) (ret int) {
		ret = a + x
		return
	}
	return
}

func main() {
	var s stack
	s.push(4)
	s.push(2)
	// s.push(1)
	//
	// s.pop()
	// s.pop()
	// a := s.pop()

	fmt.Println(s.cursor)
	fmt.Printf("stack %v\n", s)
}
