package main

import "fmt"

func rec() {
	if r := recover(); r != nil {
		fmt.Println("Recover from panic:", r)
	}
}

func panicFun() {
	defer rec()
	panic("panic called")
}

func main() {
	panicFun()
}
