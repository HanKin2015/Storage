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
