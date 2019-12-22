package main

import "fmt"

func main() {
	LABEL1:
	for i:=0; i < 10; i++{
		for j := 1; j < 10;j++ {
			fmt.Println(i, j)
			if 2 * i * j == i*i + j*j{
				fmt.Println("--------")
				break LABEL1
			}
		}
	}

}
