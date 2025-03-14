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