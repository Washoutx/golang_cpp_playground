package main

import "fmt"

func contains[T comparable](slice []T, value T) bool {
	for _, elem := range slice {
		if elem == value {
			return true
		}
	}
	return false
}

func contains_any[T comparable](slice []T, value ...T) bool {
	for _, elem := range value {
		if contains(slice, elem) {
			return true
		}
	}
	return false
}

func contains_all[T comparable](slice []T, value ...T) bool {
	for _, elem := range value {
		if !contains(slice, elem) {
			return false
		}
	}
	return true
}

func contains_none[T comparable](slice []T, value ...T) bool {
	for _, elem := range value {
		if contains(slice, elem) {
			return false
		}
	}
	return true
}

func main() {
	arr1 := []int{1, 2, 3, 4}
	fmt.Println(contains_all(arr1, 1, 2, 3, 4))
	fmt.Println(contains_all(arr1, 5, 2, 3, 4))
	fmt.Println(contains_any(arr1, 9, 9, 9, 1, 9))
	fmt.Println(contains_any(arr1, 9, 9, 9, 9, 9))
	fmt.Println(contains_none(arr1, 8, 8, 8, 8))
	fmt.Println(contains_none(arr1, 1, 8, 8, 8))

	arr2 := [4]int{1, 2, 3, 4}
	fmt.Println(contains_all(arr2[:], 1, 2, 3, 4))
	fmt.Println(contains_all(arr2[:], 5, 2, 3, 4))
	fmt.Println(contains_any(arr2[:], 9, 9, 9, 1, 9))
	fmt.Println(contains_any(arr2[:], 9, 9, 9, 9, 9))
	fmt.Println(contains_none(arr2[:], 8, 8, 8, 8))
	fmt.Println(contains_none(arr2[:], 1, 8, 8, 8))
}
