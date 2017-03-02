/*
    只有i++，没有++i
*/

package main

import (
  "fmt"
)

func f_q_1_1()  {
    for index := 0; index < 10; index++ {
        fmt.Println(index)
    }
    fmt.Println("")
}

func f_q_1_2()  {
    index := 0

    L: fmt.Println(index)

    if index < 9 {
        index += 1
        goto L
    }
}

func f_q_1_3()  {
    arr := [...]int{0,1,2,3,4,5,6,7,8,9}

    for index := 0; index < 10; index++ {
        fmt.Println(index, arr[index])
    }
}

func f_q_2()  {
    for idx := 1; idx <= 100; idx++ {
        if idx % 3 == 0 {
            fmt.Printf("Fizz")
        }
        if idx % 5 == 0 {
            fmt.Printf("Buzz")
        }
        if idx % 3 != 0 && idx % 5 != 0 {
            fmt.Print(idx)
        }

        fmt.Println("")
    }
}

func f_q_3()  {
    for i := 1; i <= 100; i++ {
        for j := 1; j <= i; j++ {
            fmt.Printf("A")
        }
        fmt.Println("")
    }
}

func main()  {
    f_q_3()
}
