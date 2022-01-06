
x = 10
h

def fun():
	print(x)

def p():
	x = 12345

def t():
	x += 1000

j = set()
j.add('a')

def k():
	j.add('b')

x += 100

if __name__ == '__main__':
	p()
	t()
	k()
	print(j)