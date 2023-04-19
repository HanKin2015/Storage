# sqlite3基本操作

SQLite3是一种轻量级的关系型数据库管理系统，它可以在本地文件中存储数据。以下是SQLite3的基本操作：

打开数据库：在终端中输入sqlite3命令，后跟数据库文件名，如sqlite3 test.db，即可打开名为test.db的数据库文件。

创建表格：使用CREATE TABLE语句创建表格，如CREATE TABLE students (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);，创建了一个名为students的表格，包含id、name和age三个字段。

插入数据：使用INSERT INTO语句插入数据，如INSERT INTO students (name, age) VALUES ('Tom', 18);，即可向students表格中插入一条数据，其中name为Tom，age为18。

查询数据：使用SELECT语句查询数据，如SELECT * FROM students;，即可查询students表格中的所有数据。

更新数据：使用UPDATE语句更新数据，如UPDATE students SET age = 19 WHERE name = 'Tom';，即可将students表格中name为Tom的数据的age字段更新为19。

删除数据：使用DELETE语句删除数据，如DELETE FROM students WHERE name = 'Tom';，即可删除students表格中name为Tom的数据。

关闭数据库：在终端中输入.exit命令，即可关闭数据库。

# 实战
```
sqlite3 example.db
.tables
.quit
INSERT INTO users (name, age) VALUES ('hejian', 65);
select * from users;
.header on
.mode column
```

# 在sqlite3中执行.mode column报错Error: mode should be one of: ascii column csv html insert line list quote tabs tcl
原因是column单词打错了，它的意思是后面的参数一定是这几个中的一个。






