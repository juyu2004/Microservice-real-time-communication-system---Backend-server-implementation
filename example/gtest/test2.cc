#include <iostream>
#include <gtest/gtest.h>

// TestSuite:测试套件/集合进行单元测试，即，将多个相关测试归入一组的方式进行测试
// 为这组测试用例进行环境配置和清理

// 概念：对一个功能的验证往往需要很多测试用例，测试套件就是针对一组相关测试用例进行环境配置的事件机制

// 用法：先定义环境类，继承于 testing::Test 基类，重写两个静态函数 SetUpTestCase/TearDownTestCase
// 进行环境配置和清理

class HashTestEnv1 : public testing::Test{
public:
    static void SetUpTestCase(){
        std::cout << "环境1 第一个 TEST 之前调用" << std::endl;
    }

    static void TearDownTestCase(){
        std::cout << "环境1 最后一个 TEST 之后调用" << std::endl;
    }
public:
    std::unordered_map<std::string, std::string> dict;
};

// 注意，测试套件使用的不是 TEST 了，而是 TEST_F, 而第一个参数名称就是测试套件环境类名称
// main 函数中不需要再注册环境了，而是在 TEST_F 中可以直接访问类的成员变量和成员函数
TEST_F(HashTestEnv1, insert_test){
    std::cout << "环境1, 中间insert测试" << std::endl;
    dict.insert(std::make_pair("Hello", "你好"));
    dict.insert(std::make_pair("hello", "你好"));
    dict.insert(std::make_pair("world", "世界"));
    auto it = dict.find("hello");
    ASSERT_NE(it, dict.end());
}

TEST_F(HashTestEnv1, sizeof){
    std::cout << "环境1, 中间size测试" << std::endl;
    ASSERT_GT(dict.size(), 0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

