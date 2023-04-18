import sqlite3

# 连接到数据库
conn = sqlite3.connect('example.db')

# 创建一个表
conn.execute('''CREATE TABLE IF NOT EXISTS users
             (id INTEGER PRIMARY KEY AUTOINCREMENT,
             name TEXT NOT NULL,
             age INTEGER NOT NULL);''')

# 插入数据
conn.execute("INSERT INTO users (name, age) VALUES (?, ?)", ('Alice', 25))
conn.execute("INSERT INTO users (name, age) VALUES (?, ?)", ('Bob', 30))

# 查询数据
cursor = conn.execute("SELECT id, name, age from users")
for row in cursor:
    print("ID = {}, NAME = {}, AGE = {}".format(row[0], row[1], row[2]))

# 提交更改并关闭连接
conn.commit()
conn.close()
