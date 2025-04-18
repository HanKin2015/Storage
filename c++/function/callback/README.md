# 回调函数进一步理解


class QueryStudentDatabase;
void 回调函数func()

void test()
{
    func();
}


class Teacher;
void GetStudentNameList()
{
   
}

void GetStudentScore()
{
}

QueryStudentDatabase.func = GetStudentNameList()

QueryStudentDatabase.func = GetStudentScore()


回调函数的本质是异步。
tl：给代码内容的前提是先完成设计

me：我想写代码（但不知道内容需要tl给我，因此我无法偷摸着写），但是需要先完成设计

还有个前提是tl先执行，然后执行me，串行执行则行不通，因此需要异步操作，tl需要把代码内容在他退出之前交给我，但是我不能打开。我完成设计后再打开
因此：先输出完成设计，再输出代码内容


