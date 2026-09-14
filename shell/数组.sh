[10356856@LIN-EB1ACC025D1 hj]$ cat l.sh
#!/bin/bash

# 定义一个测试数组

fruit=("an apple" "a banana" "pig|orange")

# 1. 遍历数组的「值」（常规写法）

echo "遍历数组的值："
for val in "\({fruit[@]}"; do
    echo "值：\)val"
done

# 2. 遍历数组的「索引」（你的目标语法）

echo -e "\n 遍历数组的索引："
for i in "\({!fruit[@]}"; do
    echo "索引：\)i → 对应值：\({fruit[\)i]}"
done

# 稀疏数组：索引 0、2、5 有值

sparse_arr=([0]="a" [2]="c" [5]="f")
for i in "${!sparse_arr [@]}"; do
echo " 索引 $i → \({sparse_arr[\)i]}"
done

# 输出：

# 索引 0 → a

# 索引 2 → c

# 索引 5 → f

[10356856@LIN-EB1ACC025D1 hj]$ sh l.sh
遍历数组的值：
值：an apple
值：a banana
值：pig|orange
遍历数组的索引：
索引：0 → 对应值：an apple
索引：1 → 对应值：a banana
索引：2 → 对应值：pig|orange
索引 0 → a
索引 2 → c
索引 5 → f