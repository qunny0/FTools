package main

import (
	"fmt"
	"log"
	"net"
	"os"
)

func handleConn(conn net.Conn) {
	ch := make(chan string)
	go clientWriter(conn, ch)
}

func broadcaster() {
	clients := make(map[client]bool) // all connected clients

	for {
		select {
		case msg := <-message:
			// Broadcast incoming message to all
			// clients` outgoing message channels
			for cli := range clients {
				cli <- msg
			}
		case cli := <-entering:
			clients[cli] = true
		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

func main() {
	listener, err := net.Listen("tcp", "0.0.0.0:8888")
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Printf(os.Stdout, "You got something wrong %v", err)
			continue
		}

		go handleConn(conn)
	}
}
