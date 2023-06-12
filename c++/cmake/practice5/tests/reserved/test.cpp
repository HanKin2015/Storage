#include "gtest/gtest.h"

/**
 * 当前测试用例是用于解决低版本gcc配合gcovr时，
 * 未覆盖到的文件，无法显示在覆盖率报告中的问题。
 * 
 * 官方对于该问题的解释：（官方建议使用新版本gcc）
 * https://gcovr.com/en/master/faq.html#why-are-uncovered-files-not-reported
 */

TEST(ReservedTest, foo)
{
}
