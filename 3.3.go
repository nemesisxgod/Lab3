package main

import (
	"fmt"
	"math"
)

type Coord struct {
	X float64
	Y float64
}

func cofe(Ts, T, kOst float64, t int) []Coord {
	cofeNow := make([]Coord, 0)

	for i := 0; i < t; i++ {
		cofeNow = append(cofeNow, Coord{float64(i), T})
		T -= kOst * (T - Ts)
	}

	return cofeNow
}

func aprox(cofeNow []Coord) (float64, float64) {
	var sumXY, sumX, sumY, sumSqrX float64
	n := float64(len(cofeNow))

	for _, koord := range cofeNow {
		x := koord.X
		y := koord.Y
		sumXY += x * y            // Σ xi*yi
		sumX += x                 // Σ xi
		sumY += y                 // Σ yi
		sumSqrX += math.Pow(x, 2) // (Σ xi)^2
	}

	a := (n*sumXY - sumX*sumY) / (n*sumSqrX - math.Pow(sumX, 2))
	b := (sumY - a*sumX) / n

	return a, b
}

func korrel(cofeNow []Coord) float64 {
	var mediumX, mediumY float64

	for _, koord := range cofeNow {
		x := koord.X
		y := koord.Y
		mediumX += x
		mediumY += y
	}

	mediumX /= float64(len(cofeNow))
	mediumY /= float64(len(cofeNow)) // Считаем средние икс и игрик

	var sumDxDy, sumSqrDx, sumSqrDy float64

	for _, koord := range cofeNow {
		x := koord.X
		y := koord.Y
		sumDxDy += (x - mediumX) * (y - mediumY)
		sumSqrDx += math.Pow(x-mediumX, 2)
		sumSqrDy += math.Pow(y-mediumY, 2)
	}

	return sumDxDy / math.Sqrt(sumSqrDx*sumSqrDy)
}

func main() {
	var Ts, T, kOst float64
	var t int
	fmt.Print("Введите Ts, T, kOst, t: ")
	fmt.Scan(&Ts, &T, &kOst, &t)

	cofeNow := cofe(Ts, T, kOst, t)
	a, b := aprox(cofeNow)
	k := korrel(cofeNow)

	fmt.Println("Время", "\t", "Температура кофе")
	for _, tempOtTime := range cofeNow {
		time := tempOtTime.X
		temperature := tempOtTime.Y
		fmt.Println(time, "\t", temperature)
	}

	fmt.Printf("\nЛиния аппроксимации: T = %.2f * t + %.2f\n", a, b)
	fmt.Printf("\nКоэффициент корреляции: %.2f\n", k)
}
