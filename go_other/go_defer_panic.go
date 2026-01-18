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

type DeferObj struct {
}

func (o DeferObj) close() {
	fmt.Println("close")
}

func (o DeferObj) init() {
	fmt.Println("init")
}

func main() {
	panicFun()

	obj := DeferObj{}
	defer obj.close()
	obj.init()
}
