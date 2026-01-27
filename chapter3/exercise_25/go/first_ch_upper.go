package main

import (
	"fmt"
	"unicode"
)

func first_ch_upper(str string) string {
	result := []rune{}
	newWord := true

	for _, ch := range str {
		newWord = newWord || unicode.IsPunct(ch) || unicode.IsSpace(ch)

		if unicode.IsLetter(ch) {
			if newWord {
				result = append(result, unicode.ToUpper(ch))
				newWord = false
			} else {
				result = append(result, unicode.ToLower(ch))
			}
		} else {
			result = append(result, ch)
		}
	}
	return string(result)
}

func main() {
	text := "THIS IS an ExamplE, should wORk!"
	expected := "This Is An Example, Should Work!"

	if first_ch_upper(text) == expected {
		fmt.Println(expected)
	}
}
