#define DEF_CTOR(func) __attribute__((constructor)) static void func(void)

typedef void (*fn_run)(void);
typedef void (*fn_setup)(void);
typedef void (*fn_teardown)(void);
typedef unsigned int U32;

#ifdef __cplusplus
extern "C" {
#endif

//  注册一个testcase到suite中
void ut_register_case(const char *suite_name, const char *case_name, fn_run pfn);
//  注册一个suite到suites中，该suite的所有testcase由pfn生成
void ut_register_suite(const char *suite_name);
//  改变当前测试套件的setup函数
void ut_register_setup(const char *suite_name, fn_setup pfn);
//  改变当前测试套件的tearDown函数
void ut_register_teardown(const char *suite_name, fn_teardown pfn);
//  抛出一个单元测试错误，中断当前测试案例执行
void ut_throw_err(const char *fname, int line, const char *fmt, ...);
//  通过命令行参数方式启动单元测试
void ut_run(void);

#ifdef __cplusplus
}
#endif

/**
 *  @brief 定义一个单元测试套
 */
#define UT_SUITE(suite_)                                                    \
    static const char *s_ut_suite_name = #suite_;                           \
    DEF_CTOR(ut_ctor_suite_##suite_)                                        \
    {                                                                       \
        ut_register_suite(#suite_);                                         \
    }                                                                       \

/**
 *  @brief 定义单元测试案例
 */
#define UT_CASE(case_)                                                      \
    static void test_##case_(void);                                         \
    DEF_CTOR(ut_ctor_case_##case_)                                          \
    {                                                                       \
        ut_register_case(s_ut_suite_name, #case_, test_##case_);            \
    }                                                                       \
    static void test_##case_(void)

/**
 *  @brief 定义测试套件的setup函数（该函数可用来为一系列测试案例打桩）
 */
#define UT_SETUP()                                                          \
    static void setup(void);                                                \
    DEF_CTOR(ut_ctor_setup)                                                 \
    {                                                                       \
        ut_register_setup(s_ut_suite_name, setup);                          \
    }                                                                       \
    static void setup(void)

/**
 *  @brief 定义测试套件的teardown函数（用于恢复setup改变的系统环境）
 */
#define UT_TEARDOWN()                                                       \
    static void teardown(void);                                             \
    DEF_CTOR(ut_ctor_teardown)                                              \
    {                                                                       \
        ut_register_teardown(s_ut_suite_name, teardown);                    \
    }                                                                       \
    static void teardown(void)
/**
 *  @brief  报告测试失败
 */
#define UT_FAIL(s_)             ut_throw_err(__FILE__, __LINE__, "%s", s_)

/**
 *  @brief 报告测试在某处失败
 */
#define UT_FAIL_AT(f_, l_, s_)  ut_throw_err(f_, l_, "%s", s_)

/**
 *  @brief 断言-表达式为真
 */
#define UT_ASSERT(expr_)                                                    \
    do {                                                                    \
        if (!(expr_)) {                                                     \
            ut_throw_err(__FILE__, __LINE__, "assert failed: %s", #expr_);  \
        }                                                                   \
    } while (0)

/**
 *  @brief 断言返回值大于等于0－表达式的返回值是HRET类型
 */
#define UT_SUCCEED(expr_)                                                   \
    do {                                                                    \
        HRET hret_ = (expr_);                                               \
        if (hret_ < 0) {                                                    \
            ut_throw_err(__FILE__, __LINE__,                                \
                "hret: %08x, express: %s", hret_, #expr_);                  \
        }                                                                   \
    } while (0)

/**
 *  @brief 断言-表达式expr_的值和expect_相等
 */
#define UT_EXPECT(expect_, expr_)                                           \
    do {                                                                    \
        int actual_ = (int)(expr_);                                         \
        if ((expect_) != (actual_)) {                                       \
            ut_throw_err(__FILE__, __LINE__,                                \
                "\nexpress: %s\nexpect: %s;\nactual: %d(%08x);",            \
                #expr_, #expect_, (int)actual_, (U32)actual_);              \
        }                                                                   \
    } while (0)

/**
 *  @brief 断言-表达式expr_的值等于字符串expect_
 */
#define UT_EXPECT_STR(expect_, expr_)                                       \
    do {                                                                    \
        const char *actual_ = (const char *)(expr_);                        \
        if (strcmp(expect_, actual_) != 0) {                                \
            ut_throw_err(__FILE__, __LINE__,                                \
                "\nexpress: %s\nexpect: %s;\nactual: %s;",                  \
                #expr_, expect_, actual_);                                  \
        }                                                                   \
    } while (0)
#include <string.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

typedef struct test_t       test_t;
typedef void (*fn_test_run)(test_t *test);
typedef void (*fn_free)(void *p);

typedef struct test_vtbl_t {
    const char *type;       //"case", "suite", "func"
    fn_test_run run;        //运行本测试(testcase_run or testsuite_run or testfunc_run)
} test_vtbl_t;
/**
 *  测试
 */
struct test_t {
    const char *name;       //测试名字

    test_t     *parent;     //测试树上的父节点
    test_t     *child_head; //孩子节点链表表头
    test_t     *child_tail; //孩子节点链表表头
    test_t     *next;       //链表的后继

    test_vtbl_t *vtbl;      //该测试的函数集
    union {
        fn_run  run_case;
        struct {
            fn_setup setup;
            fn_teardown teardown;
        } suite;
    } fn;
};

static test_vtbl_t s_root_vtbl = {
    "root",
    NULL,
};
/**
 *  所有的testcase的根；
 */
static test_t s_root = {
    "",                 //name
    NULL,               //parent
    NULL,               //child_head
    NULL,               //child_tail
    NULL,               //next
    &s_root_vtbl,       //vtbl
    {NULL},             //run_case or suite
};
static int          s_run_round;        //案例运行的轮次
static int          s_error_cnt;        //出错的单测个数
static jmp_buf      s_jmp_env;          //出错跳转的环境

#ifndef _DEBUG
#define fprintf dummy_fprintf
int dummy_fprintf(FILE *fp, const char *fmt, ...)
{
    return 0;
}
#endif
/**
 *  @brief 删除所有子测试
 */
static void test_clear(test_t *test)
{
    test_t *p = NULL;

    assert(test);
    p = test->child_head;
    while (test->child_head) {
        p = test->child_head;
        test->child_head = test->child_head->next;
        test_clear(p);
        free(p);
    }
}
/**
 *  @brief 为一个测试添加子测试
 */
void test_add_child(test_t *test, test_t *child)
{
    assert(test);
    assert(child);
    assert(child != test);
    assert(child->parent == NULL);

    child->next = NULL;
    child->parent = test;

    if (!test->child_tail) {
        test->child_tail = child;
        test->child_head = test->child_tail;
    } else {
        test->child_tail->next = child;
        test->child_tail = child;
    }
}
/**
 *  @brief 中断测试，抛出一个异常，并记录异常信息
 */
void ut_throw_err(const char *fname, int line, const char *fmt, ...)
{
    va_list ap;
    char buf[1024];

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    fprintf(stderr, "\n%s(%d): %s\n", fname, line, buf);

    longjmp(s_jmp_env, -1);
}

/**
 *  @brief 运行整个测试案例
 *  @param  test    待运行的测试案例
 */
static void testcase_run(test_t *test)
{
    assert(test);
    assert(test->parent);
    assert(test->fn.run_case);

    if (setjmp(s_jmp_env) == 0) {
        fprintf(stderr, "[RUNNING] - %s\n", test->name);
        if (test->parent->fn.suite.setup)
            test->parent->fn.suite.setup();
        test->fn.run_case();
        if (test->parent->fn.suite.teardown)
            test->parent->fn.suite.teardown();
        fprintf(stderr, "[  OK   ] - %s\n", test->name);
    } else {
        ++s_error_cnt;
        fprintf(stderr, "[FAILED ] - %s\n", test->name);
    }
}

static test_vtbl_t s_case_vtbl = {
    "case",
    testcase_run,
};

/**
 *  @brief 运行所有子测试
 *  @param  test 待运行的测试套
 */
static void testsuite_run(test_t *test)
{
    test_t *p = NULL;

    assert(test);

    fprintf(stderr, "[-------] begin %s ...\n", test->name);
    for (p = test->child_head; p; p = p->next) {
        p->vtbl->run(p);
    }
    fprintf(stderr, "[-------] end %s\n", test->name);
}

static test_vtbl_t s_suite_vtbl = {
    "suite",
    testsuite_run,
};
/**
 *  @brief 取得名字为suite_name的测试套
 */
static test_t *ut_gen_suite(const char *suite_name)
{
    test_t *suite = NULL;
    test_t *suites = &s_root;

    for (suite = suites->child_head; suite; suite = suite->next) {
        if (strcmp(suite->name, suite_name) == 0)
            return suite;
    }
    suite = (test_t *)calloc(1, sizeof(test_t));
    suite->name = suite_name;
    suite->vtbl = &s_suite_vtbl;

    test_add_child(suites, suite);
    return suite;
}
/**
 *  @brief 注册一个名字为suite_name的测试套
 *  @param  suite_name 测试套的名字
 */
void ut_register_suite(const char *suite_name)
{
    (void)ut_gen_suite(suite_name);
}
/**
 *  @brief 改变当前测试套件的setup函数
 *  @param  suite_name 测试套的名字
 *  @param [in] pfn     setup函数指针
 */
void ut_register_setup(const char *suite_name, fn_setup pfn)
{
    test_t *suite = ut_gen_suite(suite_name);

    assert(pfn);
    assert(suite);

    suite->fn.suite.setup = pfn;
}
/**
 *  @brief 改变当前测试套件的tearDown函数
 *  @param [in] suite_name 测试套的名字
 *  @param [in] pfn     tearDown函数指针
 */
void ut_register_teardown(const char *suite_name, fn_teardown pfn)
{
    test_t *suite = ut_gen_suite(suite_name);

    assert(pfn);
    assert(suite);

    suite->fn.suite.teardown = pfn;
}

/**
 *  @brief 注册一个名字为case_name的testcase到名字为suite_name的测试套中
 *  @param suite_name    testcase所在的测试套的名字
 *  @param case_name     testcase的注册名字
 *  @param pfn      执行测试的函数
 */
void ut_register_case(const char *suite_name, const char *case_name, fn_run pfn)
{
    test_t *test = NULL;
    test_t *suite = ut_gen_suite(suite_name);

    assert(suite);
    assert(case_name);
    assert(pfn);

    test = (test_t *)calloc(1, sizeof(test_t));
    test->name = case_name;
    test->vtbl = &s_case_vtbl;
    test->fn.run_case = pfn;

    test_add_child(suite, test);
}
/**
 *  @brief 根据命令行指定的参数运行单元测试
 */
void ut_run(void)
{
    test_t *child = NULL;

    s_error_cnt = 0;
    for (child = s_root.child_head; child; child = child->next) {
        child->vtbl->run(child);
    }
    if (s_error_cnt > 0) {
        printf("FAILED\n");
    } else {
        printf("OK\n");
    }
    ++s_run_round;
}
const char *range_substr(const char *pb, const char *pe, const char *sub)
{
    const char *cp = NULL;

    assert(pb && sub);
    assert(!pe || pe >= pb);

    if (!pe)
        return strstr(pb, sub);
    if (!*sub)
        return pb;

    cp = pb;
    while (*cp) {
        const char *s1 = cp;
        const char *s2 = sub;

        while (s1 < pe && *s2 && !(*s1-*s2)) {
            s1++;
            s2++;
        }

        if (!*s2)
            return cp;

        cp++;
    }
    return NULL;
}

#define OJ_RUN_ROUND_NUM 1
