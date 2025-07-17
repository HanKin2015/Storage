package main
func main() {
    var p *int = nil
    //*p = 0
    var x int = 100
    p = &x
    *p = x
    *p = 1234
    *p = 0
}
// in Windows: stops only with: <exit code="-1073741819" msg="process crashed"/>
// runtime error: invalid memory address or nil pointer dereference