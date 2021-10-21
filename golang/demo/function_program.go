// 区分一个语言是不是支持函数式编程，一个很重要的特点就是：函数是“一等公民”，可以赋值给一个变量，也可以作为另一个函数的参数或者返回值。

// case 1
add = func(a, b int) int {
	return a + b 
}
add(1, 2)

// case 2
values := []int32{42, 9, 101, 95, 27, 25}
sort.Slice(values, func(i, j int) bool {
	return values[i] < values[j]
})

// case 3
func Hello1(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("hello1"))
}

func Hello2(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("hello2"))
}

func timeMiddleware(next http.Handler) http.Handler {
	return func(w http.ResponseWriter, r *http.Request){
		timeStart := time.Now()
		
		// next handler
        next.ServeHTTP(wr, r)
        
        log.Println(time.Since(timeStart))
	}
}

func main() {
    http.HandleFunc("/hello1", timeMiddleware(hello1))
    http.HandleFunc("/hello2", timeMiddleware(hello2))
    err := http.ListenAndServe(":8080", nil)
    ...
}