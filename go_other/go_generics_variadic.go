package main

import "fmt"

func foo[T any](a T) T {
	return a
}

func goo[T int | string](a T) T {
	return a
}

func doo[A any, B int | rune](a A, b B) {
	fmt.Println(a, b)
}

type GenericStruct[T any] struct {
	a T
}

type Number interface {
	int | int64 | float64
}

type GenericStructNumber[T Number] struct {
	a T
}

type MyInt int

// allow underlying int type so MyInt is ok
func zoo[T ~int](a T) {
	fmt.Println(a)
}

func find_if[T any](f func(T), values ...T) {
	fmt.Println("find_if")
	for i, val := range values {
		fmt.Println(i)
		f(val)
	}

}

func main() {
	fmt.Println(foo[int](123))
	fmt.Println(foo(321))

	fmt.Println(goo("test"))
	fmt.Println(goo(123))
	// fmt.Println(goo(123.1)) compilation err

	doo("test", 1)
	zoo(MyInt(10))

	find_if(func(str string) {
		fmt.Println(str)
	}, []string{"test1", "test2"}...)

	find_if(func(str string) {
		fmt.Println(str)
	}, "str1", "str2", "str3")
}
