// file check_test.go

// 单元测试
func TestCheckSession(t *testing.T) {

	rsp, err := client.CheckSession(context.Background(),
		&api.CheckSessionReq{SessionID: "ABCDEFG1234"})
	if err != nil {
		t.Fatal(err)
	}
	t.Log(rsp)
	if rsp.IsValid != true {
		t.Fail()
	}
}

// 性能测试
func BenchmarkCheckSession(b *testing.B) {

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		client.CheckSession(context.Background(),
			&api.CheckSessionReq{SessionID: "ABCDEFG1234"})
	}
}
