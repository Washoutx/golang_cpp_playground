package main

import (
	"fmt"
	"regexp"
)

func main() {
	pattern := regexp.MustCompile(`(\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4})`)
	fmt.Println(pattern.ReplaceAllString("today is 01.12.2017!", `$5-$3-$1`))
}
