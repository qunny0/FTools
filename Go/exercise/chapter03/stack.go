package stack

// save data
type Stack struct {
	i    int
	data [10]int
}

// push
func (s *Stack) Push(k int) {
	s.data[s.i] = k
	s.i++
}

// pop
func (s *Stack) Pop() int {
	s.i--
	return s.data[s.i]
}
