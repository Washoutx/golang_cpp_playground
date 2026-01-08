package main

import (
	"fmt"
	"math"
	mrand "math/rand"
	"sort"
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

func sumOfDivisors(i uint64) uint64 {
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
	return sumOfDivisors
}

func calcAbundantNumbersUntil(n uint64) {
	counter := 1
	for i := uint64(10); i <= n; i++ {
		sumOfDivisors := sumOfDivisors(i)
		if sumOfDivisors > i {
			fmt.Println(counter, "Abundant number(", i, ") Abound=", sumOfDivisors-i)
			counter++
		}
	}
}

type Pair struct {
	first, second uint64
}

func makeOrderPair(a, b uint64) Pair {
	if a > b {
		return Pair{first: b, second: a}
	}
	return Pair{first: a, second: b}
}

func printAmicableUntil(limit uint64) {
	set := make(map[Pair]struct{})
	for i := uint64(4); i < limit; i++ {
		sum1 := sumOfDivisors(i)
		if sum1 < limit {
			sum2 := sumOfDivisors(sum1)
			if sum2 == i && sum1 != i {
				set[makeOrderPair(i, sum1)] = struct{}{}
			}
		}
	}
	fmt.Println("Amount=", len(set))
	var keys = make([]uint64, 0, len(set))
	for v := range set {
		keys = append(keys, v.first)
		// fmt.Printf("%d and %d are friend numbers\n", v.first, v.second)
	}
	sort.Slice(keys, func(i, j int) bool {
		return keys[i] < keys[j]
	})
	for _, v := range keys {
		fmt.Printf("%d are friend\n", v)
	}
}

func checkIfArmstrongNum(n uint64) {
	temp := n
	digits := 0
	for temp > 0 {
		temp /= 10
		digits++
	}

	sum := float64(0)
	temp = n
	for i := 0; i < digits; i++ {
		digit := temp % 10
		sum += math.Pow(float64(digit), float64(digits))
		temp /= 10
	}

	if uint64(sum) == n {
		fmt.Println(n, "is Armstrong number")
	}
}

func printPrimeFactors(n uint64) {
	vec := []uint64{}
	for n%2 == 0 {
		vec = append(vec, 2)
		n /= 2
	}
	for i := uint64(3); i <= uint64(math.Sqrt(float64(n))); i += 2 {
		for n%i == 0 {
			vec = append(vec, i)
			n /= i
		}
	}

	if n > 2 {
		vec = append(vec, n)
	}

	for _, i := range vec {
		fmt.Println(i)
	}
}

func decToBin(n uint64) []byte {
	bin := []byte{}
	for n > 0 {
		bin = append(bin, byte(n%2))
		n /= 2
	}
	return bin
}

func gray_encode(n uint64) uint64 {
	bin := decToBin(n)
	grayEncoded := uint64(n ^ (n >> 1))
	binGray := decToBin(grayEncoded)
	fmt.Print("Value: ")
	for i := len(bin) - 1; i > 0; i-- {
		fmt.Print(bin[i])
	}

	fmt.Println()

	fmt.Print("Gray encoded: ")
	for i := len(binGray) - 1; i > 0; i-- {
		fmt.Print(binGray[i])
	}
	fmt.Println()
	return grayEncoded
}

func gray_decode(n uint64) uint64 {
	decoded := uint64(0)
	for i := n; i != 0; i >>= 1 {
		decoded ^= i
	}
	bin := decToBin(decoded)

	fmt.Print("Gray decoded: ")
	for i := len(bin) - 1; i > 0; i-- {
		fmt.Print(bin[i])
	}
	fmt.Println()
	return decoded
}

func convertToRoman(n uint64) {
	result := []string{}
	roman := []struct {
		idx   uint64
		value string
	}{
		{1000, "M"},
		{900, "CM"},
		{500, "D"},
		{400, "CD"},
		{100, "C"},
		{90, "XC"},
		{50, "L"},
		{40, "XL"},
		{10, "X"},
		{9, "IX"},
		{5, "V"},
		{4, "IV"},
		{1, "I"},
	}

	for _, el := range roman {
		for n >= el.idx {
			result = append(result, el.value)
			n -= el.idx
		}
	}

	for _, str := range result {
		fmt.Print(str)
	}
}

func longestCollatzSequence(bound uint64) {
	global_sequence := []uint64{}
	for n := uint64(1); n <= bound; n++ {
		sequence := []uint64{n}
		i := n
		for i != 1 {
			if i%2 == 0 {
				i /= 2
			} else {
				i = 3*i + 1
			}
			sequence = append(sequence, i)
		}
		if len(sequence) > len(global_sequence) {
			global_sequence = append([]uint64(nil), sequence...)
		}
	}

	fmt.Println("Size =", len(global_sequence))
	for _, v := range global_sequence {
		fmt.Print(v, " ")
	}
}

func PiMonteCarlo(samples float64) float64 {
	inside := float64(0)
	for i := float64(0); i < samples; i++ {
		x := mrand.Float64()
		y := mrand.Float64()
		if (math.Pow(x, 2) + math.Pow(y, 2)) <= 1 {
			inside++
		}
	}
	return 4.0 * inside / samples
}

func isValidISBN10(isbn string) bool {
	digits := make([]rune, 0, 10)
	for _, ch := range isbn {
		if ch >= '0' && ch <= '9' {
			digits = append(digits, ch)
		}
	}
	fmt.Println(string(digits))
	if len(digits) < 10 || len(digits) > 10 {
		return false
	}

	checksum := digits[9]
	calc_checksum := 0
	for i := 0; i < 9; i++ {
		calc_checksum += (i + 1) * int(digits[i]-'0')
	}

	if int(checksum-'0') == calc_checksum%11 {
		fmt.Println("Valid ISBN")
		return true
	}
	return false
}

func main() {
	// fmt.Println(sumOfNumbersDivisibleBy3or5(15))
	// fmt.Println(gcd_greatestCommonDivisor(48, 12))
	// fmt.Println(lcm_leastCommonMultiple(48, 12))
	// fmt.Println(firstPrimeNumberBefore(7))
	// printPrime6kNumbersUntil(100)
	// calcAbundantNumbersUntil(200)
	// printAmicableUntil(1000000)
	// for i := uint64(0); i < 1000000; i++ {
	// 	checkIfArmstrongNum(i)
	// }
	// printPrimeFactors(420)
	// gray_decode(gray_encode(4200))
	// convertToRoman(10)
	// longestCollatzSequence(100)
	// fmt.Println(PiMonteCarlo(1000000))
	isValidISBN10("0-306-40615-2")
}
