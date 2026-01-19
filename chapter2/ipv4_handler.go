package main

import (
	"fmt"
	"strconv"
	"strings"
)

type OCTET uint8
type IP_V4 struct {
	octets[4]OCTET
}

func (ip IP_V4) String() string {
	return fmt.Sprintf("%d.%d.%d.%d", ip.octets[0], ip.octets[1], ip.octets[2], ip.octets[3])
}

func ParseIP(s string) (IP_V4, error) {
	var ip IP_V4
	octets := strings.Split(s, ".")
	if len(octets) < 4 {
		return IP_V4{}, fmt.Errorf("Invalid IP")
	}

	for i, octet_str := range octets {
		octet, err := strconv.Atoi(octet_str)
		if err != nil && octet < 0 || octet > 255 {
			return IP_V4{}, err
		}
		ip.octets[i] = OCTET(octet)
	}
	return ip, nil
}

func main() {
	var input string
	fmt.Scan(&input)
	ip, err := ParseIP(input)
	if err == nil {
		fmt.Println(ip)
	} else {
		fmt.Print(err)
	}
}
