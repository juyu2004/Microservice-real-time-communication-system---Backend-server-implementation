# Microservice-real-time-communication-system---Backend-server-implementation
微服务及时通讯系统 - 后台服务器实现
开发阶段与功能介绍
聊天室后台服务器实现：
1. 功能需求确定阶段：
  1. 要做什么，实现什么项目
  2. 实现这个项目，需要内部拥有哪些功能
2. 设计阶段
  1. 概要框架设计
  2. 功能模块接口设计
3. 技术调研，搭建开发环境阶段
  1. 确定使用哪些技术框架/库，了解它们的基础使用
  2. 将开发环境搭建起来
4. 具体实现阶段
5. 单元测试阶段：确定每一个模块实现的没有问题
6. 系统联调阶段
功能需求确定阶段：
1. 用户注册
2. 用户登录
3. 个人信息获取
4. 个人信息修改：签名修改，绑定手机号修改，头像修改，昵称修改
5. 手机验证码获取
6. 手机号注册与登录
7. 用户搜索
8. 申请好友
9. 获取好友申请列表
10. 处理好友申请
11. 获取聊天会话列表
12. 发送新消息（文本消息，图片消息，语音消息，文件消息）
13. 获取历史消息-按时间
14. 获取最近消息-按条数
15. 关键字消息搜索
16. 文件的上传与下载
17. 语音转文字
18. 创建群聊
框架设计：
微服务框架 -- 将整体的业务进行子业务的拆分
[图片]
聊天室子服务拆分：
1. 网关子服务：负责与客户端进行通信交互
2. 用户管理子服务：负责提供个人信息相关操作的服务
  1. 用户的注册与登录
  2. 手机号的注册与登录
  3. 短信验证码的获取
  4. 个人信息的获取
  5. 个人信息的修改：昵称，签名，头像，手机号
3. 好友管理子服务：
  1. 用户的搜索
  2. 好友的申请
  3. 待处理申请列表的获取
  4. 申请的处理
  5. 好友的删除
  6. 聊天会话的创建
  7. 聊天会话列表的获取
  8. 会话成员的获取
  9. 好友列表的获取
[图片]
消息转发子服务：
告诉网关，当前消息应该转发给谁？
并不是提供进行消息的转发功能，提供的获取一条消息应该发送给哪些用户的功能
网关收到一条消息，需要对消息进行转发，网关询问消息转发子服务，获取转发的用户列表
消息存储子服务：
负责消息的持久化存储以及查询搜索功能
1. 消息存储：文本消息，图片消息，语音消息，文件消息
2. 消息获取：按时间区域获取，获取最近的N条消息
3. 消息的关键字搜索
语音识别子服务：
负责将语音消息转换为文字
文件管理子服务：
提供文件的存储与下载（应用于用户头像，消息内容的文件类型数据存储）
单文件上传
多文件上传
单文件下载
多文件下载
后台环境搭建
编辑器安装： 
sudo apt-get install vim
编译器安装： 
sudo apt-get install gcc g++
调试器安装 
sudo apt-get install gdb
项目构建工具安装： 
sudo apt-get install make cmake
传输工具安装： 
sudo apt-get install lrzsz
版本管理工具安装：
sudo apt-get install git
gflags 框架安装
 sudo apt-get install libgflags-dev
gflags 介绍
gflags是Google 开发的一个开源库，用于C++ 应用程序中命令行参数的声明、定义和解析。gflags 库提供了一种简单的方式来添加、解析和文档化命令行标志（flags），使得程序可以根据不同的运行时配置进行调整。
它具有如下几个特点：
• 易于使用：gflags 提供了一套简单直观的API 来定义和解析命令行标志，使得开发者可以轻松地为应用程序添加新的参数。
• 自动帮助和文档：gflags 可以自动生成每个标志的帮助信息和文档，这有助于用户理解如何使用程序及其参数。
• 类型安全：gflags 支持多种数据类型的标志，包括布尔值、整数、字符串等，并且提供了类型检查和转换。
• 多平台支持：gflags 可以在多种操作系统上使用，包括Windows、Linux 和macOS。
• 可扩展性：gflags 允许开发者自定义标志的注册和解析逻辑，提供了强大的扩展性。
官方文档： https://gflags.github.io/gflags/
代码仓库：https://github.com/gflags/gflags.git
gflags 使用
1. 包含头文件
使用gflags库来定义/解析命令行参数必须包含如下头文件
#include <gflags/gflags.h>
2. 定义参数
利用gflag 提供的宏定义来定义参数。该宏的3 个参数分别为命令行参数名，参数默认值，参数的帮助信息。
DEFINE_bool(reuse_addr, true, "是否开始网络地址重用选项"); 
DEFINE_int32(log_level, 1, "日志等级：1-DEBUG, 2-WARN, 3-ERROR"); 
DEFINE_string(log_file, "stdout", "日志输出位置设置，默认为标准输出");
gflags支持定义多种类型的宏函数：
DEFINE_bool 
DEFINE_int32 
DEFINE_int64 
DEFINE_uint64 
DEFINE_double 
DEFINE_string
3. 访问参数
我们可以在程序中通过FLAGS_name 像正常变量一样访问标志参数。比如在上面的例子中，我们可以通过FLAGS_big_menu和FLAGS_languages 变量来访问命令行参数。
4. 不同文件访问参数
如果想再另外一个文件访问当前文件的参数，以参数FLAGS_big_menu为例，我们可以使用用宏DECLARE_bool(big_menu)来声明引入这个参数。
其实这个宏就相当于做了extern FLAGS_big_menu， 定义外部链接属性。
5. 初始化所有参数
当我们定义好参数后，需要告诉可执行程序去处理解析命令行传入的参数，使得FLAGS_*变量能得到正确赋值。我们需要在main函数中，调用下面的函数来解决命令行传入的所有参数。
google::ParseCommandLineFlags(&argc, &argv, true);
- argc 和 argv 就是 main 的入口参数
- 第三个参数被称为 remove_flags。如果它为 true, 表示 ParseCommandLineFlags 会从argv中移除标识和它们的参数，相应减少argc的值。如果它为false,ParseCommandLineFlags会保留argc不变，但将会重新调整它们的顺序，使得标识再前面。
6. 运行参数设置
gflags为我们提供了多种命令行设置参数的方式。
string和int设置参数
exec --log_file="./main.log" 
exec -log_file="./main.log" 
exec --log_file "./main.log" 
exec -log_file "./main.log"
bool设置参数
Shell 
exec --reuse_addr 
exec --noreuse_addr 
exec --reuse_addr=true 
exec --reuse_addr=false
--将会终止标识的处理。比如在exec -f1 1 -- -f2 2中， f1被认为是一个标识，但f2不会
7. 配置文件使用
配置文件的使用，其实就是为了让程序的运行参数配置更加标准化，不需要每次运行的时候都手动收入每个参数的数值，而是通过配置文件，一次编写，永久使用。
需要注意的是，配置文件中选项名称必须与代码中定义的选项名称一致。
样例：
-reuse_addr=true, 
-log_level=3 
-log_file=./log/main.log 
8. 特殊参数标识
gflags也默认为我们提供了几个特殊的标识。
Shell --help # 显示文件中所有标识的帮助信息 
--helpfull # 和-help 一样, 帮助信息更全面一些 
--helpshort # 只显示当前执行文件里的标志 
--helpxml # 以 xml 方式打印，方便处理 
--version # 打印版本信息，由 google::SetVersionString()设定
--flagfile -flagfile=f #从文件 f 中读取命令行参数
入门案例
编写样例代码： main.cc
#include <gflags/gflags.h>
#include <iostream>

DEFINE_bool(reuse_addr, true, "是否开启网络地址重用选项");
DEFINE_int32(log_level, 1, "日志等级：1-DEBUG, 2-WARN, 3-ERROR");
DEFINE_string(log_file, "stdout", "日志输出位置设置，默认为标准输出");

int main(int argc, char *argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "reuse_addr: " << FLAGS_reuse_addr << std::endl;
    std::cout << "log_level: " << FLAGS_log_level << std::endl;
    std::cout << "log_file: " << FLAGS_log_file << std::endl;
    return 0;
}
配置文件
-reuse_addr=true
-log_level=3
-log_file=./log/main.log
Makefile 编写
main:main.cc
    g++ -std=c++17 $^ -o $@ -lgflags 
样例运行:
[图片]
[图片]
[图片]
gtest 框架安装
安装：
sudo apt-get install libgtest-dev
介绍：
GTest是一个跨平台的C++单元测试框架，由google公司发布。gtest是为了在不同平台上为编写C++单元测试而生成的。它提供了丰富的断言、致命和非致命判断、参数化等等测试所需的宏，以及全局测试，单元测试组件。
1. 头文件包含：
#include <gtest/gtest.h>
2. 框架初始化接口：
testing::InitGoogleTest(&argc, argv);
3. 调用测试样例：
RUN_ALL_TESTS();
4. TEST宏
//这里不需要双引号，且同测试下多个测试样例不能同名 
TEST(测试名称, 测试样例名称)
TEST_F(test_fixture,test_name)
- TEST：主要用来创建一个简单测试， 它定义了一个测试函数， 在这个函数中可以使用任何C++代码并且使用框架提供的断言进行检查
- TEST_F：主要用来进行多样测试，适用于多个测试场景如果需要相同的数据配置的情况， 即相同的数据测不同的行为
5. 断言宏
GTest中的断言的宏可以分为两类：
- ASSERT_系列：如果当前点检测失败则退出当前函数
- EXPECT_系列：如果当前点检测失败则继续往下执行
下面是经常使用的断言介绍
C++ 
// bool值检查 
ASSERT_TRUE(参数)，期待结果是true 
ASSERT_FALSE(参数)，期待结果是false 

//数值型数据检查 
ASSERT_EQ(参数1，参数2)，传入的是需要比较的两个数 equal 
ASSERT_NE(参数1，参数2)，not equal，不等于才返回true 
ASSERT_LT(参数1，参数2)，less than，小于才返回true 
ASSERT_GT(参数1，参数2)，greater than，大于才返回true 
ASSERT_LE(参数1，参数2)，less equal，小于等于才返回true 
ASSERT_GE(参数1，参数2)，greater equal，大于等于才返回true
6. 样例
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
Makefile：
main:main.cc
    g++ -std=c++17 $^ -o $@ -lgtest -lgtest_main -pthread
[图片]
Gtest 事件机制
GTest中的事件机制是指在测试前和测试后提供给用户自行添加操作的机制，而且该机制也可以让同一测试套件下的测试用例共享数据。
GTest框架中事件的结构层次：
[图片]
- 测试程序：一个测试程序只有一个main函数，也可以说是一个可执行程序是一个测试程序。该级别的事件机制是在程序的开始和结束执行
- 测试套件：代表一个测试用例的集合体，该级别的事件机制是在整体的测试案例开始和结束执行
- 测试用例：该级别的事件机制是在每个测试用例开始和结束都执行
事件机制的最大好处就是能够为我们各个测试用例提前准备好测试环境，并在测试完毕后用于销毁环境，这样有个好处就是如果我们有一端代码需要进行多种不同方法的测试，则可以通过测试机制在每个测试用例进行之前初始化测试环境和数据，并在测试完毕后清理测试造成的影响。
GTest提供了三种常见的的事件：
1. 全局事件
针对整个测试程序。实现全局的事件机制，需要创建一个自己的类，然后继承testing::Environment类，然后分别实现成员函数SetUp 和 TearDown，同时在main函数内进行调用testing::AddGlobalTestEnvironment(new MyEnvironment);函数添加全局的事件机制
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
[图片]
2. TestSuite事件
针对一个个测试套件。测试套件的事件机制我们同样需要去创建一个类，继承自testing::Test，实现两个静态函数SetUpTestCase和TearDownTestCase，测试套件的事件机制不需要像全局事件机制一样在main注册，而是需要将我们平时使用的TEST宏改为TEST_F宏。
- SetUpTestCase() 函数是在测试套件第一个测试用例开始前执行
- TearDownTestCase() 函数是在测试套件最后一个测试用例结束后执行
- 需要注意TEST_F的第一个参数是我们创建的类名，也就是当前测试套件的名称，这样在TEST_F宏的测试套件中就可以访问类中的成员了。
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
[图片]
能够看到在上例中，有一个好处，就是将数据与测试结合到同一个测试环境类中了，这样与外界的耦合度更低，代码也更清晰。
但是同样的，我们发现在两个测试用例中第二个测试用例失败了，这是为什么呢？这就涉及到了TestCase事件的机制。
3. TestCase事件
针对一个个测试用例。测试用例的事件机制的创建和测试套件的基本一样，不同地方在于测试用例实现的两个函数分别是SetUp和TearDown, 这两个函数也不是静态函数
- SetUp()函数是在一个测试用例的开始前执行
- TearDown()函数是在一个测试用例的结束后执行
也就是说，在TestSuite/TestCase事件中，每个测试用例，虽然它们同用同一个事件环境类，可以访问其中的资源，但是本质上每个测试用例的环境都是独立的，这样我们就不用担心不同的测试用例之间会有数据上的影响了，保证所有的测试用例都使用相同的测试环境进行测试。
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
[图片]
spdlog 框架安装
brpc 框架安装
etcd 框架安装
elasticsearch 框架安装：
cpp-httplib 框架安装：
websocketpp 框架安装：
redis 安装
ODB 安装
RabbbitMQ 安装