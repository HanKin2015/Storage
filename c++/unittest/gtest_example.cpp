#include<iostream>
using namespace std; 
#include<gtest/gtest.h>
 
class MyClass{
public:
    int add(int a,int b){
        return a+b;
    }
    int del(int a,int b){
        return a-b;
    }
 
};
//class MyClassTest: public testing::Test{}
class MyClassTest: public testing::TestWithParam<int>{
public:
    static void SetUpTestCase()
    {
        cout<<"SetUpTestCase"<<endl;
    }
    static void TearDownTestCase()
    {
        cout<<"TearDownTestCase"<<endl;
    }
    virtual void SetUp()   //TEST跑之前会执行SetUp
    {
        cout<<"SetUp"<<endl;
    }
    virtual void TearDown() //TEST跑完之后会执行TearDown
    {
        cout<<"TearDown"<<endl;
    }
    MyClass myClass;
 
};
 
INSTANTIATE_TEST_SUITE_P(PARAM,MyClassTest,testing::Values(3,5,7,9));
 
int Abs(int x)
{
     return x > 0 ? x : -x;
}
 
TEST(IsAbsTest,MyTest)
{
    ASSERT_TRUE(Abs(1) == 1) << "Abs(1)=1";  //ASSERT_TRUE期待结果是true,operator<<输出一些自定义的信息
    ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
    ASSERT_FALSE(Abs(-2) == -2);  //期待结果是false
    ASSERT_EQ(Abs(1),Abs(-1));
    ASSERT_NE(Abs(-1),0);
    ASSERT_LT(Abs(-1),2);
    ASSERT_GT(Abs(-1),0);
    ASSERT_LE(Abs(-1),2);
    ASSERT_GE(Abs(-1),0);
}
 
//此时使用的是TEST_P宏
TEST_P(MyClassTest,AddTest)
{
    auto out= myClass.add(1,2);
    //ASSERT_NE(out,3);
    int n = GetParam();
    ASSERT_EQ(out,3);
    ASSERT_EQ(out,n);
}
//此时使用的是TEST_F宏
TEST_F(MyClassTest,Add)
{
    auto out= myClass.add(1,2);
    ASSERT_EQ(out,3);
}
TEST_F(MyClassTest,del)
{
    ASSERT_EQ(myClass.del(4,3),1);
}
 
int main(int argc,char *argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}