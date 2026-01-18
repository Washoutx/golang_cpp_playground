package main

import "fmt"

func main() {
	// buffer 3
	ch := make(chan string, 3)

	go func() {
		ch <- "hello from goroutine"
	}()

	ch <- "test1"
	ch <- "test2"
	ch <- "test3"

	for msg := range ch {
		fmt.Println(msg)
	}
}
