package main

import (
	"fmt"
	"regexp"
	"strconv"
)

type URI struct {
	Protocol, Domain string
	Port             *int
	Path             *string
	Query            *string
	Fragment         *string
}

func parseURI(str string) (*URI, bool) {
	pattern := regexp.MustCompile(`^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$`)
	matches := pattern.FindStringSubmatch(str)

	if matches == nil {
		return nil, false
	}

	result := URI{
		Protocol: matches[1],
		Domain:   matches[2],
	}

	if matches[4] != "" {
		port, _ := strconv.Atoi(matches[4])
		result.Port = &port
	}
	if matches[5] != "" {
		result.Path = &matches[5]

	}
	if matches[7] != "" {
		result.Query = &matches[7]
	}
	if matches[9] != "" {
		result.Fragment = &matches[9]

	}
	return &result, true
}

func main() {
	p1, ok1 := parseURI("https://packt.com")
	fmt.Println(p1, ok1)

	p2, ok2 := parseURI("https://bbc.com:80/en/index.html?lite=true#ui")
	fmt.Println(p2, ok2)
}
