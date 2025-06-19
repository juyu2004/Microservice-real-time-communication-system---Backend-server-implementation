#include <iostream>
#include <gtest/gtest.h>

// TestCase:测试用例的单元测试,及针对每一个测试用例都使用独立的测试环境数据进行测试
// 概念:它是针对测试用例进行环境配置的一种事情机制
// 用法:先定义环境类,继承于 testing::Test 基类,在环境类内重写 SetUp/TearDown 接口

class HashTestEnv2 : public testing::Test{
public:
    static void SetUpTestCase(){
        std::cout << "环境2 第一个TEST之前被调用,进行总体环境配置" << std::endl;
    }
    static void TearDownTestCase(){
        std::cout << "环境2 最后一个TEST之后被调用,进行总体环境清理" << std::endl;
    }
    virtual void SetUp() override{
        std::cout << "环境2 测试前:提前准备数据!" << std::endl;
        dict.insert(std::make_pair("bye", "再见"));
        dict.insert(std::make_pair("see you", "再见"));
    }
    virtual void TearDown() override{
        std::cout << "环境2 测试结束后:清理数据!!" << std::endl;
        dict.clear();
    }
public:
    std::unordered_map<std::string, std::string> dict;
};

TEST_F(HashTestEnv2, insert_test){
    std::cout << "环境2,中间测试" << std::endl;
    dict.insert(std::make_pair("hello", "你好"));
    ASSERT_EQ(dict.size(), 3);
}

TEST_F(HashTestEnv2, size_test){
    std::cout << "环境2, 中间size测试" << std::endl;
    auto it = dict.find("Hello");
    ASSERT_EQ(it, dict.end());
    ASSERT_EQ(dict.size(), 2);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}