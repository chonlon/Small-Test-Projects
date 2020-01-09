package main

import "fmt"


// 疑问： go语言中的而所有长度不同的数组是不同的类型， 那个是否写一些函数的时候会很麻烦呢？
func main() {
	a := [3]int{1, 2, 3}
	b := [...]int{0:1, 3:2, 11:3}
	fmt.Println(a[0], a[1], a[2])
	fmt.Println(b)
}
