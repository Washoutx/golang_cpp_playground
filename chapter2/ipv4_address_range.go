package main

import (
	"encoding/binary"
	"fmt"
	"strconv"
	"strings"
)

type IP_V4 struct {
	octets [4]uint8
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
		ip.octets[i] = uint8(octet)
	}
	return ip, nil
}

func (ip IP_V4) to_uint32_t() uint32 {
	data := binary.BigEndian.Uint32(ip.octets[:])
	return data
}

func (ip *IP_V4) Inc() {
	temp := ip.to_uint32_t()
	temp++
	binary.BigEndian.PutUint32(ip.octets[:], temp)
	fmt.Println(ip.octets)
}

func (ip IP_V4) CompareLE(other IP_V4) bool {
	return ip.to_uint32_t() <= other.to_uint32_t()
}

func main() {
	var input1, input2 string
	fmt.Scan(&input1)
	fmt.Scan(&input2)
	ip1, err := ParseIP(input1)
	if err == nil {
		fmt.Println(ip1)
	} else {
		fmt.Print(err)
	}
	ip2, err := ParseIP(input2)
	if err == nil {
		fmt.Println(ip2)
	} else {
		fmt.Print(err)
	}

	fmt.Println(ip1.CompareLE(ip2))
	for ip1.CompareLE(ip2) {
		fmt.Println(ip1)
		ip1.Inc()
	}
}
