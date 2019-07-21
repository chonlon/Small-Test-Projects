package main

import (
	"fmt"
	"time"
)

func sum(s []int, c chan int) {
	sum := 0

	for _, v := range s {
		sum += v
	}

	c <- sum
}
func sum2(s []int, c chan int) {
	sum := 0

	for _, v := range s {
		sum += v
	}
	time.Sleep(1000)
	c <- sum
}

func main() {
	s := []int {7, 2, 8, -9, 4, 0}

	c := make(chan int)

	go sum2(s[:len(s)/2], c)
	go sum(s[len(s)/2:], c)

	x, y := <-c, <-c
	fmt.Println(x, y, x+y)
}