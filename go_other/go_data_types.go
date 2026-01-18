package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

type A struct {
	a, b int
}

type AliasInt int

func functionWithError(isError bool) (bool, error) {
	if isError {
		return false, fmt.Errorf("err msg")
	}
	return true, nil
}

func main() {
	alias_test := AliasInt(10)
	fmt.Printf("%#v\n", alias_test)
	obj := A{a: 1, b: 2}
	t := reflect.TypeOf(obj)
	fmt.Println(t)
	fmt.Println(t.Kind())

	var ptr_test uintptr
	// useful only for interaction w C/C++ ptrs because GC can change go ptrs
	ptr_test = uintptr(unsafe.Pointer(&obj))
	fmt.Println(ptr_test)

	const FLAG1 bool = false
	var FLAG2 bool = false
	FLAG3 := false
	fmt.Println(FLAG1, FLAG2, FLAG3)

	var str string = "TEST"
	var ch rune = 'c' // 32 int alias
	var b byte = 255  // 8 uint alias
	fmt.Println(str, ch, b)

	tab1 := []int{1, 2, 3}
	fmt.Println(tab1)
	tab2 := [][]int{{1, 2, 3}, {1, 2, 3}}
	fmt.Println(tab2)

	mp := map[int]string{1: "test1", 2: "test2"}
	fmt.Println(mp)
	ptr := &mp
	fmt.Printf("%p -> %v -> %#v\n", ptr, *ptr, *ptr)

	ret, err := functionWithError(true)
	if err != nil {
		fmt.Println(err, ret)
	}
	var a []A = nil
	fmt.Println(a)
	var x struct{}
	fmt.Printf("%p\n", &x)
	fmt.Println(unsafe.Sizeof(x))

	go_set := map[int]struct{}{2: {}, 3: {}, 1: {}}
	fmt.Println(go_set)
	a1, a2 := go_set[2]
	fmt.Println(a1, a2)
	if _, exists := go_set[3]; exists {
		fmt.Println("exists")
	}

	var map_var_no_init map[int]string
	if map_var_no_init == nil {
		fmt.Println("map_var_no_init == nil")
	}
	if _, ok := map_var_no_init[10]; !ok {
		fmt.Println("check nil map")
	}
	map_init := make(map[int]string)
	if map_init != nil {
		fmt.Println("map_init != nil")
	}

	// slice is dynamic table
	static_array := [2]int{1, 2}
	dynamic_array := []int{1, 2, 3}
	fmt.Println(static_array, dynamic_array)
	// dynamic_array[10] = 10 // panic
	dynamic_array = append(dynamic_array, 10)
	for v := range dynamic_array {
		fmt.Println(v)
	}

	// map, adding by index
	var mmap map[int]string
	// mmap[10] = "test" // panic, map is nil
	mmap = make(map[int]string)
	mmap[10] = "test"
	mmap[10] = "test"
	mmap[12] = "test"
	fmt.Println(mmap)
	delete(mmap, 12)
	fmt.Println(mmap)

	// deleting in slices is impossible, only re-append
	my_slice := make([]int, 0, 0)
	my_slice = append(my_slice, 0, 1, 2, 3, 4, 5)
	fmt.Println(my_slice, "size=", len(my_slice), "cap=", cap(my_slice))
	my_slice = append(my_slice[2:3], my_slice[4])
	fmt.Println(my_slice)
	my_slice = append(my_slice[2:3], my_slice[1:2]...)
	fmt.Println(my_slice)

	// unused var
	var _ = int(10)

	// any
	var _any any = "test"
	fmt.Println(_any)

	pseudo_tuple := []any{1, 1.1, 'a', "test"}
	fmt.Println(pseudo_tuple...)
}
