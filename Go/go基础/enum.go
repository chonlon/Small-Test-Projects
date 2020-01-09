package main

import "fmt"

const (
	B int64 = 1 << (10 * iota)
	KB
	MB
	GB
	TB
)

func main() {
	fmt.Printf("B:%d\nKB:%d\nMB:%d\nGB:%d\nTB:%d\n", B, KB, MB, GB, TB)
}