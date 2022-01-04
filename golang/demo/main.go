package main

import (
	"demo/calc"
	"fmt"
)

func main() {
	sum := calc.Add(1, 2) //3
	mul := calc.Mul(5, 4) //20
	fmt.Println(sum)
	fmt.Println(mul)
	calc.PrintInfo() //你调用tools包方法
}
