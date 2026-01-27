package main

import (
	"fmt"
	"strings"
)

func join_string(strings []string, separator string) string {
	result := strings[0] 
	for idx := 1; idx < len(strings); idx++{
		result += separator + strings[idx] 
	}
	return result
}

func main() {
	fmt.Println(join_string([]string{"one", "two", "three"}, ":sep:"))
	fmt.Println(strings.Join([]string{"one", "two", "three"}, ":sep:"))
}
