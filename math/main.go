package main

import (
	"fmt"
	"math"
)

func sumOfNumbersDivisibleBy3or5(number uint32) uint64 {
	var sum uint64 = 0
	for i := uint32(3); i <= number; i++ {
		if i%3 == 0 || i%5 == 0 {
			sum += uint64(i)
		}
	}
	return sum
}

func gcd_greatestCommonDivisor(a, b uint64) uint64 {
	// GCD(a,b) = GCD(b, a%b)
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func lcm_leastCommonMultiple(a, b uint64) uint64 {
	if a == 0 || b == 0 {
		return 0
	}
	// LCM(a,b) = a*b / GCD(a,b)
	// Use transformed formula to reduce the risk of integer overflow
	// LCM(a,b) = (a/GDC(a,b)) * b
	return (a / gcd_greatestCommonDivisor(a, b)) * b
}

func isPrime(n uint64) bool {
	if n <= 3 {
		return n > 1
	}
	if n%2 == 0 || n%3 == 0 {
		return false
	}

	for i := uint64(5); i*i < n; i += 6 {
		if n%i == 0 || n%(i+2) == 0 {
			return false
		}
	}
	return true
}

func firstPrimeNumberBefore(n uint64) uint64 {
	for ; n <= 0; n-- {
		if isPrime(n) {
			return n
		}
	}
	return n
}

func printPrime6kNumbersUntil(n uint64) {
	if n < 11 {
		fmt.Println("no prime 6k")
	}

	for i := uint64(5); i < n; i++ {
		if isPrime(i) && isPrime(i+6) {
			fmt.Printf("Prime6k{%d, %d}", i, i+6)
		}
	}
}

func calcAbundantNumbersUntil(n uint64) {
	counter := 1
	for i := uint64(10); i <= n; i++ {
		var sumOfDivisors uint64 = 1
		i_sqrt := uint64(math.Sqrt(float64(i)))

		for j := uint64(2); j <= i_sqrt; j++ {
			if i%j == 0 {
				if j != i/j {
					sumOfDivisors += j + i/j
				} else {
					sumOfDivisors += j
				}
			}
		}
		if sumOfDivisors > i {
			fmt.Println(counter, "Abundant number(", i, ") Abound=", sumOfDivisors-i)
			counter++
		}
	}
}

func main() {
	// fmt.Println(sumOfNumbersDivisibleBy3or5(15))
	// fmt.Println(gcd_greatestCommonDivisor(48, 12))
	// fmt.Println(lcm_leastCommonMultiple(48, 12))
	// fmt.Println(firstPrimeNumberBefore(7))
	// printPrime6kNumbersUntil(100)
	// calcAbundantNumbersUntil(200)
}
