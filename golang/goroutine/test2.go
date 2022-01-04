package main

import (
	"fmt"
	"runtime"
	"time"
)

func hello() {
	fmt.Println("Hello world goroutine")
}
func main() {
	runtime.GOMAXPROCS(1)
	for i := 0; i < 10; i++ {
		go func() {
			println(i)
			//fmt.Println("numbers(): tid", unix.Gettid())
		}()
	}
	runtime.Gosched()
	time.Sleep(time.Second)
}
