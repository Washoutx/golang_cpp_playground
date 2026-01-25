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

func strToHex(str string) ([]byte, error) {
	s := strings.TrimSpace(str)

	return hex.DecodeString(s)
}

func main() {
	hex := []byte{0xFF, 0xA0}
	str := hexToStr(hex, true)
	fmt.Println(str)
	hex2, _ := strToHex(str)
	fmt.Printf("%X\n", hex2)
}
