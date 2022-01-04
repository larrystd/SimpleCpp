package calc //必须放在文件首位
var Age = 20 //公有变量
var age = 10 //私有变量
func Add(x, y int) int { //首字母大写是公有方法, 可以给其他package使用
	return x + y
}
func Sub(x, y int) int {
	return x - y

}
func add(x, y int) int { //首字母小写是私有方法，只能自己包内访问
	return x + y
}
