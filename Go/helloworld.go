package main

import "fmt"

/* Print something */

func main()  {
    fmt.Printf("Hello, wold; or 你好，世界.\n")

    const (
      a = iota
      b = iota
    )

    // fmt.Print(a, b)
    // fmt.Println()

    s := "Hello"
    c := []rune(s)
    c[0] = 'c'
    s2 := string(c)
    fmt.Printf("%s\n", s2)
}
