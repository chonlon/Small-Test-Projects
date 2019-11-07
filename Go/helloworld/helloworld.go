package main

import (
	"fmt"
)

func swap(x *int, y *int) {
	*x, *y = *y, *x
}

type test struct {
	title string
	width int
	height int
	PIXMAP int
}

type Info struct {
	address string
	phone string
}

//接收者是非指针
func (this Info) changeInfo() {
	this.address = "上海"
	this.phone = "10086"
	fmt.Println(this)
}

//接收者是指针
func (this *Info) changeInfo2() {
	this.address = "上海"
	this.phone = "10086"
	fmt.Println(this)
}

func Test_demo5() {
	info := &Info{"北京", "10086"}
	//指针调用，但接收者自动被转换成了非指针，changeInfo函数应用的是info的拷贝。
	info.changeInfo() // {上海 10086}
	fmt.Println(info) //&{北京 10086}

	info2 := Info{"北京", "10086"}
	//非指针调用，但接收者自动被转换成了指针，changeInfo函数应用的是真正的info实例。
	info2.changeInfo2() // &{上海 10086}
	fmt.Println(info2) //{上海 10086}
}

func say() {
	for true {
		fmt.Println("hello")
		fmt.Println("world")
	}
}

func main() {
	a, b := 1, 2
	var tt test
	tt.height = 10
	tt.PIXMAP = 19
	fmt.Println(tt.height, tt.PIXMAP)
	swap(&a, &b)
	fmt.Println(a, b)

	s := []int{1, 2, 3}
	fmt.Println(s, len(s), cap(s))
	for i, c := range "go" {
		fmt.Println(i, c)
	}
	go say()
	say()
}
