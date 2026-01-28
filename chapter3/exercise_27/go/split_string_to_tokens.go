package main

import (
	"fmt"
	"strings"
)

func split_string_to_tokens(text string, separator string) []string {
	results := []string{}

	prevPos := 0
	for idx, ch := range text {
		if strings.Contains(separator, string(ch)) {
			// fix conrner case when separators are next to each other
			if prevPos == idx {
				prevPos++
				continue
			}
			results = append(results, text[prevPos:idx])
			prevPos = idx + 1
		}
	}

	if prevPos < len(text) {
		results = append(results, text[prevPos:])
	}
	return results; 
}

func main() {
	fmt.Println(strings.Split(string("one two   three"), " "))
	fmt.Println(split_string_to_tokens("one:two:!three  four", ":! ,"))
}
