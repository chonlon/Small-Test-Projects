package main

import "net/rpc"

const HelloServiceName = "path/to/pkg.HelloService"
type HelloServiceInterface = interface {
	Hello(request string, reply* string) error
}

func RegisterHelloService(svc HelloServiceInterface) error {
	return rpc.RegisterName(HelloServiceName, svc)
}
