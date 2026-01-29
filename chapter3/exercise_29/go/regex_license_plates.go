package main

import (
	"fmt"
	"regexp"
)

func main() {
	pattern := regexp.MustCompile(`^[A-Za-z]{3}-[A-Za-z]{2} \d{3,4}$`)
	strings := []string{
		"ABC-DE 123",
		"XYZ-QW 1234",
		"AB-DE 123",
	}
	patternAll := regexp.MustCompile(`[A-Za-z]{3}-[A-Za-z]{2} \d{3,4}`)

	for _, str := range strings {
		fmt.Println(pattern.MatchString(str))
	}

	str := "ABD-DE 123 test test AB-DE 123 XYZ-QW 1234"
	const ALL_MATCHES = -1
	matches := patternAll.FindAllString(str, ALL_MATCHES)

	for _, match := range matches {
		fmt.Println(match)
	}
}
