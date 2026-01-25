package main

import (
	"encoding/hex"
	"fmt"
	"strings"
)

func hexToStr(data []byte, upper bool) string {
	s := hex.EncodeToString(data)
	if upper {
		return strings.ToUpper(s)
	}
	return s
}
func main() {
	fmt.Println(hexToStr([]byte{0xFF, 0xA0}, true))
}
