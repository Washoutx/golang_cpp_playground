package main

import "fmt"

// this task is specific for C++, following code is just code snippet similar to task

type Scale int

const (
	Celcius Scale = iota
	Kelvin
	Fahrenheit
)

func (c Scale) String() string {
	switch c {
	case Celcius:
		return "Celcius"
	case Kelvin:
		return "Kelvin"
	case Fahrenheit:
		return "Fahrenheit"
	default:
		return "unknown"
	}
}

type Temperature struct {
	val   float32
	scale Scale
}

func (v *Temperature) String() string {
	return fmt.Sprintf("%f.2 %s", v.val, v.scale)
}

func (v *Temperature) convert(toScale Scale) {
	switch v.scale {
	case Celcius:
		if toScale == Fahrenheit {
			v.val = v.val*9.0/5.0 + 32.0
			v.scale = Fahrenheit
		} else if toScale == Kelvin {
			v.val = v.val + 273.15
			v.scale = Kelvin
		}
	case Fahrenheit:
		if toScale == Celcius {
			v.val = (v.val - 32.0) * 5.0 / 9.0
			v.scale = Celcius
		} else if toScale == Kelvin {
			v.val = (v.val-32.0)*5.0/9.0 + 273.15
			v.scale = Kelvin
		}
	case Kelvin:
		if toScale == Celcius {
			v.val = v.val - 273.15
			v.scale = Celcius
		} else if toScale == Fahrenheit {
			v.val = (v.val-273.15)*9.0/5.0 + 32.0
			v.scale = Fahrenheit
		}
	}
}

func main() {
	temp := Temperature{val: -10, scale: Celcius}
	temp.convert(Fahrenheit)
	fmt.Println(temp)

}
