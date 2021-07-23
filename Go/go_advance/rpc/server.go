package main

import (
	"io"
	"net/http"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type HelloService struct{}

func (p *HelloService) Hello(request string, reply *string) error {
	*reply = "hello: " + request
	return nil
}

//func main() {
//	//rpc.RegisterName("HelloService", new(HelloService))
//	RegisterHelloService(new (HelloService))
//
//
//	listener, err := net.Listen("tcp", ":1234")
//
//	if err != nil {
//		log.Fatal("Listen tcp error:", err)
//	}
//	for true {
//		conn, err := listener.Accept()
//		if err != nil {
//			log.Fatal("Accepet error:", err)
//		}
//		//rpc.ServeConn(conn)
//		go rpc.ServeCodec(jsonrpc.NewServerCodec(conn))
//	}
//
//
//
//}

func main() {
	rpc.RegisterName("HelloService", new(HelloService))

	http.HandleFunc("/jsonrpc", func(w http.ResponseWriter, r *http.Request) {
		var conn io.ReadWriteCloser = struct {
			io.Writer
			io.ReadCloser
		}{
			ReadCloser: r.Body,
			Writer:     w,
		}

		rpc.ServeRequest(jsonrpc.NewServerCodec(conn))
	})

	http.ListenAndServe(":1234", nil)
}