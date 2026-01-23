package main

// This task doesn't have many sense in GO, GO handle most of things by default

import "fmt"

type Array2D[T any] [][]T
type ClassArray2D[T any] struct {
	arr [][]T
}

func (a Array2D[T]) Size() int {
	size := 0
	for _, row := range a {
		size += len(row)
	}
	return size
}

func main() {
	arr1 := Array2D[int]{{1,2,3}, {3,2,1}}
	arr1 = append(arr1, []int{1,2,3})
	arr2 := ClassArray2D[int]{ arr : [][]int{{1,2,3}, {3,2,1}}}
	fmt.Println(arr1, arr2.arr)
	fmt.Println(arr1.Size())
}
