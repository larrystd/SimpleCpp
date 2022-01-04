package main

import (
	"fmt"
	"time"

	"golang.org/x/sys/unix"
)

func numbers() {
	fmt.Println("numbers(): pid", unix.Getpid())
	fmt.Println("numbers(): tid", unix.Gettid())
	time.Sleep(3000 * time.Second)
}
func alphabets() {
	fmt.Println("alphabets(): pid", unix.Getpid())
	fmt.Println("alphabets(): tid", unix.Gettid())
	time.Sleep(3000 * time.Second)
}
func main() {
	go numbers()
	go alphabets()
	fmt.Println("main(): pid", unix.Getpid())
	fmt.Println("main(): tid", unix.Gettid())
	time.Sleep(3000 * time.Second)
	fmt.Println("main terminated")
}
