package main

import (
	"fmt"
	"net"
)

var quitSemaphore chan bool

const BUFF_SIZE = 1024

var input = make([]byte, BUFF_SIZE)

func main() {
	tcpAddr, err := net.ResolveTCPAddr("tcp", "127.0.0.1:9999")
	if err != nil {
		fmt.Printf("resolve tcp address %s failed.\n", err.Error())
		return
	}

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		fmt.Printf("connect %s failed.\n", err.Error())
		return
	}

	defer conn.Close()
	fmt.Println("connected!")

	go onMessageRecived(conn)

	var msg string
	for {
		fmt.Scanf("%s\n", &msg)
		bytes := []byte(msg)

		if msg == "" {
			continue
		}
		msg = ""

		conn.Write(bytes)

		if msg == "quit" {
			break
		}
	}

	<-quitSemaphore
}

func onMessageRecived(conn *net.TCPConn) {
	for {
		n, err := conn.Read(input)
		if err != nil {
			fmt.Printf("onMessageRecived error : %s\n", err.Error())
			return
		}

		if n > 0 {
			inputstr := input[:n]
			fmt.Println("get message from server : " + string(inputstr))
		}
	}
}
