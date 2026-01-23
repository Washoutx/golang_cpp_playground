package main

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

func getArgsMinimum[T constraints.Integer | constraints.Float](args ...T) T {
	min := args[0]
	for i := 1; i < len(args); i++ {
		if args[i] < min {
			min = args[i]
		}
	}
	return min
}

type MyInt int

type MinInterface interface {
	~int | constraints.Float | string
}

func getArgsMinimumExtra[T MinInterface](args ...T) T {
	min := args[0]
	for i := 1; i < len(args); i++ {
		if args[i] < min {
			min = args[i]
		}
	}
	return min
}

type MyStruct struct {
	a, b int
	c    float32
}

func minimumComparator[T any](comp func(a, b T) bool, args ...T) T {
	min := args[0]
	for i := 1; i < len(args); i++ {
		if comp(args[i], min) {
			min = args[i]
		}
	}
	return min
}

func main() {
	fmt.Println(getArgsMinimum(3, 2, 1, 4))
	fmt.Println(getArgsMinimumExtra("123", "12", "1"))
	fmt.Println(getArgsMinimumExtra(MyInt(3), MyInt(2), MyInt(1)))

	data := []MyStruct{
		{a: 10, b: 20, c: 3}, {a: 10, b: 20, c: 2}, {a: 10, b: 20, c: 1},
	}
	min := minimumComparator(func(obj1, obj2 MyStruct) bool { return obj1.c < obj2.c }, data...)
	fmt.Println(min)
}
