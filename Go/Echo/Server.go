package main

import (
	"fmt"
	"net"
	"strconv"
	"time"
)

var ip = "127.0.0.1"
var port = 9999

var buff = make([]byte, 1024)

func main() {
	tcpAddr, er := net.ResolveTCPAddr("tcp", ip+":"+strconv.Itoa(port))
	if er != nil {
		fmt.Printf("Resolve TCP addr %s error : %s !", tcpAddr.String(), er.Error())
	}

	tcpListener, err := net.ListenTCP("tcp", tcpAddr)
	if err != nil {
		fmt.Printf("Listener error : %s \n", err)
	}

	defer tcpListener.Close()

	fmt.Printf("Listening : %s\n", tcpAddr.String())

	for {
		tcpConn, err := tcpListener.AcceptTCP()
		if err != nil {
			continue
		}
		fmt.Printf("A client connected : " + tcpConn.RemoteAddr().String() + "\n")
		go tcpPipe(tcpConn)
	}
}

func tcpPipe(conn *net.TCPConn) {
	ipStr := conn.RemoteAddr().String()
	defer func() {
		fmt.Println("disconnected : " + ipStr)
		conn.Close()
	}()

	for {
		n, err := conn.Read(buff)
		if err != nil {
			return
		}

		msg := time.Now().String() + ": " + string(buff[:n]) + "\n"
		fmt.Print(msg)

		b := []byte(string(buff[:n]))

		conn.Write(b)
	}
}
