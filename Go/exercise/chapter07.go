// 好的沟通就像是一杯刺激的浓咖啡，然后就难以入睡
//
//
//

package main

import (
	"bufio"
	"errors"
	"flag"
	"fmt"
	"io/ioutil"
	"net"
	"os"
	"os/exec"
	"os/user"
	"sort"
	"strconv"
	"strings"
)

func ex1() {
	buf := make([]byte, 1024)
	f, _ := os.Open("/etc/passwd")

	defer f.Close()

	for {
		n, _ := f.Read(buf)
		if n == 0 {
			break
		}
		os.Stdout.Write(buf[:n])
	}
}

func ex2() {
	buf := make([]byte, 1024)
	f, _ := os.Open("/etc/passwd")
	defer f.Close()

	r := bufio.NewReader(f)
	w := bufio.NewWriter(os.Stdout)

	defer w.Flush()

	for {
		n, _ := r.Read(buf)
		if n == 0 {
			break
		}
		w.Write(buf[0:n])
	}
}

// dnssec := flag.Bool("dnssec", false, "Request DNSSEC records")
// port := flag.String("port", "53", "Set the query port")
//
// flag.Usage = func ()  {
// 	fmt.Fprintf(os.Stderr, "Usage: %s [OPTATIONS] [name ...]\n", os.Args[0])
// 	flag.PrintDefaults()
// }
//
// flag.Parse()

func q28() {
	cmd := exec.Command("/bin/ps", "-e", "-opid,ppid,comm")
	buf, err := cmd.Output()

	if err != nil {
		fmt.Printf("error -- : %s\n", err.Error())
		return
	}

	child := make(map[int][]int)
	for i, s := range strings.Split(string(buf), "\n") {
		if i == 0 {
			continue
		}
		if len(s) == 0 {
			continue
		}

		f := strings.Fields(s)
		fpp, _ := strconv.Atoi(f[1])
		fp, _ := strconv.Atoi(f[0])
		child[fpp] = append(child[fpp], fp)
	}

	schild := make([]int, len(child))
	i := 0
	for k, _ := range child {
		schild[i] = k
		i++
	}

	sort.Ints(schild)

	for _, ppid := range schild {
		fmt.Printf("Pid %d has %d child", ppid, len(child[ppid]))
		if len(child[ppid]) == 1 {
			fmt.Printf(": %v\n", child[ppid])
			continue
		}
		fmt.Printf("ren: %v\n", child[ppid])
	}

	// fmt.Printf("%s\n", strBuf)
}

func q29() {
	var chars, words, lines int

	r := bufio.NewReader(os.Stdin)

	for {
		switch s, ok := r.ReadString('\n'); true {
		case ok != nil:
			fmt.Printf("%d %d %d\n", chars, words, lines)
			return
		default:
			chars += len(s)
			words += len(strings.Fields(s))
			lines++
		}
	}
}

func q30() {
	list := []string{"a", "b", "a", "a", "c", "d", "e", "f"}
	first := list[0]

	fmt.Printf("%s ", first)

	for _, v := range list[1:] {
		if first != v {
			fmt.Printf("%s ", v)
			first = v
		}
	}
	fmt.Println()
}

func q31() {
	var q = ` /* Go quine */
		package main
		import (
			"fmt"
		)
		func main() {
			print("")
		}
	`

	fmt.Printf("%s%c%s%c\n", q, 0x60, q, 0x60)
}

func q32() {
	l, err := net.Listen("tcp", "127.0.0.1:8053")
	if err != nil {
		fmt.Printf("Failure to listen: %s\n", err.Error())
	} else {
		fmt.Printf("Success listen %s\n", "127.0.0.1:8053")
	}

	for {
		if c, err := l.Accept(); err == nil {
			Echo(c)
		}
	}
}

func Echo(c net.Conn) {
	defer c.Close()

	fmt.Println("----173----")

	line, err := bufio.NewReader(c).ReadString('\n')
	if err != nil {
		fmt.Printf("Failure to read: %s\n", err.Error())
		return
	}

	_, err = c.Write([]byte(line))
	if err != nil {
		fmt.Printf("Failure to write: %s\n", err.Error())
		return
	}
}

func q34() {
	flag.Parse()
	ln, err := net.Listen("tcp", ":79")

	if err != nil {
		panic(err)
	}

	for {
		conn, err := ln.Accept()
		if err != nil {
			continue
		}
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer conn.Close()

	reader := bufio.NewReader(conn)
	usr, _, _ := reader.ReadLine()

	if info, err := getUserInfo(string(usr)); err != nil {
		conn.Write([]byte(err.Error()))
	} else {
		conn.Write(info)
	}
}

func getUserInfo(usr string) ([]byte, error) {
	u, e := user.Lookup(usr)

	if e != nil {
		return nil, e
	}

	data, err := ioutil.ReadFile(u.HomeDir + ".plan")
	if err != nil {
		return data, errors.New("User doesn`t have a .plan file!\n")
	}
	return data, nil
}

func main() {
	// cmd := exec.Command("/bin/ls", "-l")
	// buf, err := cmd.Output()
	//
	// if err == nil {
	// 	fmt.Printf("%s", buf)
	// }
	//

	q34()
}
