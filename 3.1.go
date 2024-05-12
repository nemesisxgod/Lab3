package main

import (
	"fmt"
	"math"
	"os"
)

func firstFragm(x float64) float64 {
	res := -math.Sqrt(9 - (x+6)*(x+6))
	if math.Abs(res) < 0.000001 {
		res = 0.0
	}
	return res
}

func secondFragm(x float64) float64 {
	res := x + 3
	return res
}

func thirdFragm(x float64) float64 {
	res := math.Sqrt(9 - x*x)
	if math.Abs(res) < 0.000001 {
		res = 0.0
	}
	return res
}

func fourthFragm(x float64) float64 {
	res := -x + 3
	return res
}

func fifthFragm(x float64) float64 {
	res := x/2.0 - 3.0/2.0
	return res
}

func main() {
	xStart := -9.0
	xEnd := 9.0
	dx := 1.0

	file, err := os.Create("test_go.txt")
	if err != nil {
		fmt.Println("При открытии файла произошла ошибка")
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "%10s %10s\n", "x", "y")
	for x := xStart; x <= xEnd; x += dx {
		if math.Abs(x) < 0.000001 {
			x = 0.0
		}
		if x >= -9.0 && x < -6.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, firstFragm(x))
		}
		if x >= -6.0 && x < -3.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, secondFragm(x))
		}
		if x >= -3.0 && x < 0.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, thirdFragm(x))
		}
		if x >= 0.0 && x < 3.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, fourthFragm(x))
		}
		if x >= 3.0 && x <= 9.0 {
			fmt.Fprintf(file, "%10.2f %10.2f\n", x, fifthFragm(x))
		}
	}
}
