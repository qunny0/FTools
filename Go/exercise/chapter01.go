/*
   只有i++，没有++i
*/

package main

import (
	"fmt"
)

func f_q_1_1() {
	for index := 0; index < 10; index++ {
		fmt.Println(index)
	}
	fmt.Println("")
}

func f_q_1_2() {
	index := 0

L:
	fmt.Println(index)

	if index < 9 {
		index += 1
		goto L
	}
}

func f_q_1_3() {
	arr := [...]int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

	fmt.Printf("%v\n", arr)
	// for index := 0; index < 10; index++ {
	// 	fmt.Println(index, arr[index])
	// }
}

func f_q_2() {
	const (
		FIZZ = 3
		BUZZ = 5
	)

	for idx := 1; idx <= 100; idx++ {
		if idx%3 == 0 {
			fmt.Printf("Fizz")
		}
		if idx%5 == 0 {
			fmt.Printf("Buzz")
		}
		if idx%3 != 0 && idx%5 != 0 {
			fmt.Print(idx)
		}

		fmt.Println("")
	}
}

func f_q_3_1() {
	for i := 1; i <= 100; i++ {
		for j := 1; j <= i; j++ {
			fmt.Printf("A")
		}
		fmt.Println("")
	}
}

func f_q_3_2(str string) {
	lenstr := len(str)
	str_arr := []rune(str)
	charNum := 0
	for idx := 0; idx < lenstr; idx++ {
		if str_arr[idx] >= 'a' && str_arr[idx] <= 'z' {
			charNum += 1
		} else if str_arr[idx] >= 'A' && str_arr[idx] <= 'Z' {
			charNum += 1
		}
	}

	fmt.Println(charNum, lenstr)

	// return charNum, lenstr
}

func f_q_3_3(str string) {
	// lenstr := len(str)
	// str_arr := []rune(str)
	//
	// if lenstr < begin+3 {
	// 	return
	// }
	//
	// str_arr[begin+0] = 'a'
	// str_arr[begin+1] = 'b'
	// str_arr[begin+2] = 'c'
	//
	// s2 := string(str_arr)
	//

	arr := []rune(str)
	copy(arr[4:4+3], []rune("abc"))

	fmt.Printf("Before %s\n", str)
	fmt.Println(string(arr))
}

func f_q_3_4(str string) {
	strArr := []rune(str)

	for i, j := 0, len(str)-1; i < j; i, j = i+1, j-1 {
		strArr[i], strArr[j] = strArr[j], strArr[i]
	}

	s2 := string(strArr)

	fmt.Println(s2)
}

func f_q_4() {
	a := [...]float64{1, 2, 3, 4, 5}
	s1 := a[0:len(a)]

	var sum float64
	sum = 0
	for _, v := range s1 {
		sum += v
	}

	average := sum / float64(len(a))

	fmt.Println(average)
}

func main() {
	f_q_3_3("hhhh aaa bb ff dd")
}
