package main

import "fmt"

func main() {
	a := 3
	p := &a
	var pp *int
	pp = &a
	fmt.Println(*p, *pp)
}
