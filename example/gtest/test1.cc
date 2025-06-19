#include <iostream>
#include <gtest/gtest.h>

// 全局事件：针对整个测试程序，提供全局事件机制，能够在测试之前配置测试环境数据，测试完毕后清理数据
// 先定义环境类，通过继承testing::Environment的派生类来完成
// 重写虚函数接口 SetUp() 会在测试之前调用，TearDown() 会在测试之后调用 

std::unordered_map<std::string, std::string> dict;

class HashTestEnv : public testing::Environment{
public:
    virtual void SetUp() override{
        std::cout << "测试前：提前准备数据！" << std::endl;
        dict.insert(std::make_pair("hello", "你好"));
        dict.insert(std::make_pair("hello", "你好"));
        dict.insert(std::make_pair("world", "世界"));
    }
    virtual void TearDown() override{
        std::cout << "测试后：清理数据！" << std::endl;
        dict.clear();
    }
};

TEST(hash_case_test, find_test){
    auto it = dict.find("hello");
    ASSERT_NE(it, dict.end()); // 断言it不等于dict.end()，如果为真，则测试通过，否则测试失败
}
TEST(hash_case_test, size_test){
    ASSERT_GT(dict.size(), 0);
}

int main(int argc, char *argv[])
{
    testing::AddGlobalTestEnvironment(new HashTestEnv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}