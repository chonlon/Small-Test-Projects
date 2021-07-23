package main

import (
	"fmt"
	"net"
	"strconv"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:22222")

	if err != nil {
		fmt.Println("Error dialing", err.Error())
		return
	}

	for i := 1; i <= 100; i++ {
		_, err := conn.Write([]byte("message" + strconv.Itoa(i)))
		if err != nil {
			fmt.Println("Error write",err.Error())
			break
		}
		buf := make([]byte, 512)
		len, read_err := conn.Read(buf)
		if read_err != nil {
			fmt.Println("Error write", err.Error())
			break
		}
		fmt.Printf("got message back: %v\n", string(buf[:len]))
	}
	conn.Close()
}