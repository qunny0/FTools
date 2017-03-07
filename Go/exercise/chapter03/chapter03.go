package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var st = new(Stack)

type Stack struct {
	i    int
	data [10]int
}

func (s *Stack) Push(k int) {
	s.data[s.i] = k
	s.i++
}

func (s *Stack) Pop() int {
	s.i--
	return s.data[s.i]
}

func main() {
	for {
		s, err := reader.ReadString('\n')

		fmt.Printf("-----====%v", s)

		var token string
		if err != nil {
			return
		}

		for _, c := range s {
			switch {
			case c >= '0' && c <= '9':
				token = token + string(c)
			case c == ' ':
				r, _ := strconv.Atoi(token)
				st.Push(r)
				token = ""
			case c == '+':
				fmt.Printf("%d\n", st.Pop()+st.Pop())
			case c == '*':
				fmt.Printf("%d\n", st.Pop()*st.Pop())
			case c == '-':
				p := st.Pop()
				q := st.Pop()
				fmt.Printf("%d\n", q-p)
			case c == 'q':
				return
			default:
				// error
			}
		}
	}
}
