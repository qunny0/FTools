package main

import (
	"fmt"
	"net"
	"strconv"
)

var ip = "127.0.0.1"
var port = 8888

func checkError(err error, info string) (res bool) {
	if err != nil {
		fmt.Println(info + " " + err.Error())
		return false
	}
	return true
}

///////////////////////////////////////////////
//
// 服务器发送数据的线程
// 参数：
//      连接字典    conns
//      数据通道    messages
///////////////////////////////////////////////
func echoHandler(conns *map[string]net.Conn, messages chan string) {
	for {
		msg := <-messages
		fmt.Println(msg)

		for key, value := range *conns {
			fmt.Println("connection is connected from ...", key)
			_, err := value.Write([]byte(msg))
			if err != nil {
				fmt.Println(err.Error())
				delete(*conns, key)
			}
		}
	}
}

///////////////////////////////////////////////
//
// 服务器接收数据线程
// 参数：
//      数据连接    conn
//      通讯通道    messages
///////////////////////////////////////////////
func handler(conn net.Conn, messages chan string) {
	fmt.Println("connection is connected from ...", conn.RemoteAddr().String())

	buf := make([]byte, 1024)
	for {
		length, err := conn.Read(buf)
		if checkError(err, "Connection") == false {
			conn.Close()
			break
		}

		if length > 0 {
			buf[length] = 0
		}

		reciveStr := string(buf[0:length])
		messages <- reciveStr
	}
}

func startServer() {
	service := ":" + strconv.Itoa(port)
	tcpAddr, err := net.ResolveTCPAddr("tcp", service)
	checkError(err, "ResolveTCPAddr")

	l, err := net.Listen("tcp", tcpAddr.String())
	checkError(err, "ListenTCP")
	conns := make(map[string]net.Conn)
	messages := make(chan string, 10)

	// 启动服务器广播线程
	go echoHandler(&conns, messages)

	for {
		fmt.Println("Listening ... ")
		conn, err := l.Accept()
		checkError(err, "Accept")
		fmt.Println("Accepting...")
		conns[conn.RemoteAddr().String()] = conn
		// lanuch a thread
		go handler(conn, messages)
	}
}

func main() {
	startServer()
}
