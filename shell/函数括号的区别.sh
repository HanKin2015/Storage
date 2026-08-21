hejian@android-PowerEdge-R920:~/hj$ sh l.sh
/home/hejian/hj

/tmp
hello
hejian@android-PowerEdge-R920:~/hj$ cat l.sh
#!/system/bin/sh

# 小括号（子shell）
func_paren() (
    cd /tmp
    LOCAL_VAR="world"
)

# 大括号（当前shell）
func_brace() {
    cd /tmp
    LOCAL_VAR="hello"
}

func_paren
pwd             # 输出原来的目录 (目录没变，因为cd是在子Shell里跑的)
echo $LOCAL_VAR # 输出空 (变量没保留，因为子Shell销毁了)

func_brace
pwd
echo $LOCAL_VAR