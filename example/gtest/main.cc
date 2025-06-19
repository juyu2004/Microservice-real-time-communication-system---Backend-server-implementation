#include <gtest/gtest.h>
#include <iostream>

int abs(int x)
{
    return x > 0 ? x : -x;
}

TEST(abs_test, test1)
{
    ASSERT_TRUE(abs(1) == 1) << "abs(1) = 1"; // 断言1等于1，如果为真，则测试通过，否则测试失败
    ASSERT_TRUE(abs(-1) == 1);                // 断言-1等于1，如果为真，则测试通过，否则测试失败
    ASSERT_FALSE(abs(-2) == -2);              // 断言-2不等于-2，如果为真，则测试通过，否则测试失败
    ASSERT_EQ(abs(1), abs(-1));               // 断言1和-1相等，如果为真，则测试通过，否则测试失败
    ASSERT_NE(abs(-1), 0);                    // 断言-1不等于0，如果为真，则测试通过，否则测试失败
    ASSERT_LT(abs(-1), 2);                    // 断言-1小于2，如果为真，则测试通过，否则测试失败
    ASSERT_GT(abs(-1), 0);                    // 断言-1大于0，如果为真，则测试通过，否则测试失败
    ASSERT_LE(abs(-1), 2);                    // 断言-1小于等于2，如果为真，则测试通过，否则测试失败
    ASSERT_GE(abs(-1), 1);                    // 断言-1大于等于1，如果为真，则测试通过，否则测试失败
}

int main(int argc, char *argv[])
{
    // 将命令行参数传递给gtest
    testing::InitGoogleTest(&argc, argv);
    // 运行所有测试用例
    return RUN_ALL_TESTS();
}