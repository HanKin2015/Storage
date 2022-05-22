1.根据用户名时间段统计 
git log --author="username" --since=2018-01-01 --until=2019-12-31 --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -

2.查看提交者排名前N位
git log --pretty='%aN' | sort | uniq -c | sort -k1 -n -r | head -n 5

3.提交数统计
git log --oneline | wc -l

4.根据用户名统计
git log --author="username" --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -
这个是6的子集，6也实现了这个功能

5.根据时间段统计 
git log --since=2018-01-01 --until=2018-12-31 --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }'

6.统计每个人的增删行数
git log --format='%aN' | sort -u | while read name; do echo -en "$name\t"; git log --author="$name" --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s \n", add, subs, loc }' -; done

7.贡献者统计
git log --pretty='%aN' | sort -u | wc -l
输出每个提交的贡献者信息，sort去重排序，wc统计数量




