package main

import (
	"fmt"
	"net"
)

func main() {
	fmt.Println("Starting the server ...")
	listener, err := net.Listen("tcp", "localhost:22222")
	if err != nil {
		fmt.Println("Error listening", err.Error())
		return
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting", err.Error())
			return
		}
		go doServe(conn)
	}
}

func doServe(conn net.Conn) {
	for {
		buf := make([]byte, 512)
		rlen, rerr := conn.Read(buf)
		if rerr != nil {
			fmt.Println("read error", rerr.Error())
			break
		}
		fmt.Printf("Received data: %v\n", string(buf[:rlen]))
		_, werr := conn.Write(buf[:rlen])
		if werr != nil {
			fmt.Println("write error ", werr.Error())
		}
	}
}
