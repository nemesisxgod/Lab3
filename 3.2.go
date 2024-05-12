package main

import (
	"fmt"
	"math"
	"math/big"
	"math/rand"
	"time"
)

func getBitLength(number int64) int64 {
	if number == 0 {
		return 0
	}
	x := int64(math.Ceil((math.Log2(float64(number))+1)/8) * 8)
	return int64(math.Ceil((math.Log2(float64(number))+1)/8) * 8)
}

// Функция для построения таблицы простых чисел с помощью решета Эратосфена
func sieveOfEratosthenes(n int) []int64 {
	isPrime := make([]bool, n+1)
	primes := make([]int64, 0)

	for p := 2; p*p <= n; p++ {
		if isPrime[p] == false {
			for i := p * p; i <= n; i += p {
				isPrime[i] = true
			}
		}
	}

	for p := 2; p <= n; p++ {
		if !isPrime[p] {
			primes = append(primes, int64(p))
		}
	}

	return primes
}

// Генерация случайных чисел
func randomNum(a, b int64) int64 {
	min, max := minMax(a, b)

	rand.Seed(time.Now().UnixNano())
	return rand.Int63n(max-min+1) + min
}

func minMax(a, b int64) (int64, int64) {
	if a < b {
		return a, b
	}
	return b, a
}

// Функция для нахождения наибольшего общего делителя двух чисел
func NOD(a, b int64) int64 {
	for b != 0 {
		temp := b
		b = a % b
		a = temp
	}
	return a
}

// Функция для вычисления a^b mod n
func powMod(a, b, n int64) int64 {
	result := int64(1)
	a = a % n

	for b > 0 {
		if b%2 == 1 {
			result = (result * a) % n
		}
		b /= 2
		a = (a * a) % n
	}

	return result
}

func testVer(n, k int64) bool {
	if n == 2 {
		return true
	}

	if n%2 == 0 || n < 2 {
		return false
	}

	t := n - 1
	s := int64(0)

	for t%2 == 0 {
		t /= 2
		s++
	}

	for i := int64(0); i < k; i++ {
		a := randomNum(2, n-2)
		x := powMod(a, t, n)

		if x == 1 || x == n-1 {
			continue
		}

		for j := int64(0); j < s-1; j++ {
			x = powMod(x, 2, n)

			if x == 1 {
				return false
			}

			if x == n-1 {
				break
			}
		}
	}

	return true
}

func generatePrimeMiller(bitLength int64, primes []int64, t int64) (int64, int64) {
	count := int64(0)
	var prime int64
	for prime == 0 {
		var m int64
		for m == 0 {
			m = 1
			for i := int64(0); i < t; i++ {
				q := primes[randomNum(0, int64(len(primes))-1)]
				a := randomNum(1, 3)

				poweredPrime := big.NewInt(1)
				poweredPrime.Exp(big.NewInt(q), big.NewInt(a), nil)

				m *= poweredPrime.Int64()
			}
			if getBitLength(m) == (bitLength - 1) {
				break
			}
		}

		n := 2*m + 1
		d := n - 1

		if millerTest(n, d, primes, t) {
			prime = n
		} else if testVer(n, 5) {
			count++
		}
	}
	return prime, count
}

func millerTest(n, d int64, primes []int64, t int64) bool {
	aj := make([]int64, 0)
	for i := int64(0); i < t; i++ {
		a := randomNum(2, n-2)
		aj = append(aj, a)
		x := powMod(a, d, n)
		if x != 1 {
			return false
		}
	}
	for _, prime := range primes {
		for _, i := range aj {
			z := d / prime
			if powMod(i, z, n) != 1 {
				continue
			} else {
				return false
			}
		}
	}

	return true
}

func generatePrimePoklington(bitLength int64, primes []int64, t int64) int64 {
	bitLengthF := int64(48)
	var F int64
	for {
		F = 1
		for i := int64(0); i < t; i++ {
			q := primes[randomNum(0, int64(len(primes))-1)]
			a := randomNum(1, 3)

			poweredPrime := big.NewInt(1)
			poweredPrime.Exp(big.NewInt(q), big.NewInt(a), nil)

			F *= poweredPrime.Int64()
		}
		if getBitLength(F) == bitLengthF {
			break
		}
	}

	var R int64
	for {
		R = randomNum(2, F)
		if R%2 == 0 && getBitLength(R) == (bitLengthF-1) {
			break
		}
	}

	n := F*R + 1

	if poklingtonTest(n, F, R, primes, t) {
		return n
	}
	return 0
}

func poklingtonTest(n, F, R int64, primes []int64, t int64) bool {
	for i := int64(0); i < t; i++ {
		a := randomNum(2, n-2)
		x := powMod(a, n-1, n)
		if x != 1 {
			return false
		}
	}

	for _, prime := range primes {
		if NOD(prime, F) == 1 {
			z := (n - 1) / prime
			conditionMet := false
			for i := int64(0); i < t; i++ {
				a := randomNum(2, n-2)
				res := powMod(a, z, n)
				if res == 1 {
					conditionMet = true
					break
				}
			}
			if !conditionMet {
				return false
			}
		}
	}

	return true
}

func GOST(bitLength int, primes []int64) int64 {
	prime := primes[randomNum(0, int64(len(primes))-1)]
	common := math.Pow(2.0, float64(bitLength-1)) / float64(prime)
	N := int64(math.Ceil(common)) + int64(common*float64(randomNum(0, rand.Max))/float64(rand.Max))
	if N%2 != 0 {
		N++
	}
	for u := int64(0); ; u += 2 {
		p := (N + u) * prime

		if p > int64(math.Pow(2, float64(bitLength))) {
			break
		}

		if powMod(2, p-1, p) == 1 && powMod(2, N+u, p) != 1 {
			return p
		}
	}
}

func main() {
	limit := 500
	primes := sieveOfEratosthenes(limit)
	k := int64(0)
	bitLength := int64(25)
	t := int64(3)
	fmt.Printf("%8s%16s%20s\n", "Число", "ВерТест", "Число отвергнутых")
	fmt.Println("---------------------------------------------")
	for i := 0; i < 10; i++ {
		prime, count := generatePrimeMiller(bitLength, primes, t)
		k = count

		testProbRes := "+"
		if !testVer(prime, t) {
			testProbRes = "-"
		}
		fmt.Printf("%8d%13s%16d\n", prime, testProbRes, k)
	}
}
