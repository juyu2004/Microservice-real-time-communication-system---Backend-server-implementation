# Microservice-real-time-communication-system---Backend-server-implementation
## 开发阶段与功能介绍

### 聊天室后台服务器实现：

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

#### 功能需求确定阶段：

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

#### 框架设计：

微服务框架 -- 将整体的业务进行子业务的拆分

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=YTA1MzUzZmY2ZDljNzU0ODQwZWYyZTRiMWE3ZTY0ODVfaTNmSEVzcXVNcDMxZWh6T3pQczJPWmMxVWNnbmRnbXNfVG9rZW46Q2RmbmJWNTJTbzA4cG14RU1IbWNkSG1vbjdnXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

#### 聊天室子服务拆分：

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

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=Yzk5Y2M5MDQ5MmI2ZDg5MzM5ZGIxYTYzN2YyMjYzOWJfZHpMa3UwRzRzU0c1ZGlscW5tNTdnMzNpdWM5Z2FxUU1fVG9rZW46UXlwaGIzdjRJb1EyREp4SE8xdGNCVkV0bjVmXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

#### 消息转发子服务：

告诉网关，当前消息应该转发给谁？

并不是提供进行消息的转发功能，提供的获取一条消息应该发送给哪些用户的功能

网关收到一条消息，需要对消息进行转发，网关询问消息转发子服务，获取转发的用户列表

#### 消息存储子服务：

负责消息的持久化存储以及查询搜索功能

1. 消息存储：文本消息，图片消息，语音消息，文件消息
2. 消息获取：按时间区域获取，获取最近的N条消息
3. 消息的关键字搜索

#### 语音识别子服务：

负责将语音消息转换为文字

#### 文件管理子服务：

提供文件的存储与下载（应用于用户头像，消息内容的文件类型数据存储）

单文件上传

多文件上传

单文件下载

多文件下载

## 后台环境搭建

### 编辑器安装： 

```Plain
sudo apt-get install vim
```

### 编译器安装： 

```Plain
sudo apt-get install gcc g++
```

### 调试器安装 

```Plain
sudo apt-get install gdb
```

### 项目构建工具安装： 

```Plain
sudo apt-get install make cmake
```

### 传输工具安装： 

```Plain
sudo apt-get install lrzsz
```

### 版本管理工具安装：

```Plain
sudo apt-get install git
```

### gflags 框架安装

```Plain
 sudo apt-get install libgflags-dev
```

#### gflags 介绍

gflags是Google 开发的一个开源库，用于C++ 应用程序中命令行参数的声明、定义和解析。gflags 库提供了一种简单的方式来添加、解析和文档化命令行标志（flags），使得程序可以根据不同的运行时配置进行调整。

它具有如下几个特点：

• **易于使用**：gflags 提供了一套简单直观的API 来定义和解析命令行标志，使得开发者可以轻松地为应用程序添加新的参数。

• **自动帮助和文档**：gflags 可以自动生成每个标志的帮助信息和文档，这有助于用户理解如何使用程序及其参数。

• **类型安全**：gflags 支持多种数据类型的标志，包括布尔值、整数、字符串等，并且提供了类型检查和转换。

• **多平台支持**：gflags 可以在多种操作系统上使用，包括Windows、Linux 和macOS。

• **可扩展性**：gflags 允许开发者自定义标志的注册和解析逻辑，提供了强大的扩展性。

官方文档： https://gflags.github.io/gflags/

代码仓库：https://github.com/gflags/gflags.git

#### gflags 使用

1. 包含头文件

使用gflags库来定义/解析命令行参数必须包含如下头文件

```Plain
#include <gflags/gflags.h>
```

1. 定义参数

利用gflag 提供的宏定义来定义参数。该宏的3 个参数分别为命令行参数名，参数默认值，参数的帮助信息。

```Plain
DEFINE_bool(reuse_addr, true, "是否开始网络地址重用选项"); 
DEFINE_int32(log_level, 1, "日志等级：1-DEBUG, 2-WARN, 3-ERROR"); 
DEFINE_string(log_file, "stdout", "日志输出位置设置，默认为标准输出");
```

gflags支持定义多种类型的宏函数：

```Plain
DEFINE_bool 
DEFINE_int32 
DEFINE_int64 
DEFINE_uint64 
DEFINE_double 
DEFINE_string
```

1. 访问参数

我们可以在程序中通过FLAGS_name 像正常变量一样访问标志参数。比如在上面的例子中，我们可以通过FLAGS_big_menu和FLAGS_languages 变量来访问命令行参数。

1. 不同文件访问参数

如果想再另外一个文件访问当前文件的参数，以参数FLAGS_big_menu为例，我们可以使用用宏DECLARE_bool(big_menu)来声明引入这个参数。

其实这个宏就相当于做了extern FLAGS_big_menu， 定义外部链接属性。

1. 初始化所有参数

当我们定义好参数后，需要告诉可执行程序去处理解析命令行传入的参数，使得FLAGS_*变量能得到正确赋值。我们需要在main函数中，调用下面的函数来解决命令行传入的所有参数。

```Plain
google::ParseCommandLineFlags(&argc, &argv, true);
```

- argc 和 argv 就是 main 的入口参数
- 第三个参数被称为 remove_flags。如果它为 true, 表示 ParseCommandLineFlags 会从argv中移除标识和它们的参数，相应减少argc的值。如果它为false,ParseCommandLineFlags会保留argc不变，但将会重新调整它们的顺序，使得标识再前面。

1. 运行参数设置

gflags为我们提供了多种命令行设置参数的方式。

string和int设置参数

```Python
exec --log_file="./main.log" 
exec -log_file="./main.log" 
exec --log_file "./main.log" 
exec -log_file "./main.log"
```

bool设置参数

```Shell
Shell 
exec --reuse_addr 
exec --noreuse_addr 
exec --reuse_addr=true 
exec --reuse_addr=false
```

--将会终止标识的处理。比如在exec -f1 1 -- -f2 2中， f1被认为是一个标识，但f2不会

1. 配置文件使用

配置文件的使用，其实就是为了让程序的运行参数配置更加标准化，不需要每次运行的时候都手动收入每个参数的数值，而是通过配置文件，一次编写，永久使用。

需要注意的是，配置文件中选项名称必须与代码中定义的选项名称一致。

样例：

```Shell
-reuse_addr=true, 
-log_level=3 
-log_file=./log/main.log 
```

1. 特殊参数标识

gflags也默认为我们提供了几个特殊的标识。

```Shell
Shell --help # 显示文件中所有标识的帮助信息 
--helpfull # 和-help 一样, 帮助信息更全面一些 
--helpshort # 只显示当前执行文件里的标志 
--helpxml # 以 xml 方式打印，方便处理 
--version # 打印版本信息，由 google::SetVersionString()设定
--flagfile -flagfile=f #从文件 f 中读取命令行参数
```

#### 入门案例

编写样例代码： main.cc

```C++
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
```

配置文件

```Shell
-reuse_addr=true
-log_level=3
-log_file=./log/main.log
```

Makefile 编写

```Shell
main:main.cc
    g++ -std=c++17 $^ -o $@ -lgflags 
```

样例运行:

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDZhZjAzNjM5NjU4OTMyYTVhMmY3ZjVhOWJmN2M4ODJfQzdWRHg5RngyTXZqODl2UWlkUmw0WEUzUWlTTmtFZGlfVG9rZW46RVV2MGJ2SDU4b0xFSFB4RW9qNmNQN3Bqbk1jXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=NTY2N2I4NDZmY2JkYjMxY2Y1ZjUxMDk3NjI4NTQ4YWVfYTRPNmtuWnFVa280MTg5SGJvTHZ6QzlZaERMaXZZd1ZfVG9rZW46UEMxUGJreWpsb0NDemN4eHFSUGNnSENBbjVtXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGU5NGY1ZTc0ZjY0MGEzY2M3MjVhYWU1NTM5OTY1MDlfV0lMMmVMSmsxWnEzcXcwdmdES3ZmWERnQ0RCQk1qU0JfVG9rZW46WE9QTGJQajBxb1JPSGZ4aUFjM2NJOU1rblZkXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

### gtest 框架安装

#### 安装：

```Shell
sudo apt-get install libgtest-dev
```

#### 介绍：

GTest是一个跨平台的C++单元测试框架，由google公司发布。gtest是为了在不同平台上为编写C++单元测试而生成的。它提供了丰富的断言、致命和非致命判断、参数化等等测试所需的宏，以及全局测试，单元测试组件。

1. 头文件包含：

```Shell
#include <gtest/gtest.h>
```

1. 框架初始化接口：

```Shell
testing::InitGoogleTest(&argc, argv);
```

1. 调用测试样例：

```Shell
RUN_ALL_TESTS();
```

1. TEST宏

```Shell
//这里不需要双引号，且同测试下多个测试样例不能同名 
TEST(测试名称, 测试样例名称)
TEST_F(test_fixture,test_name)
```

- TEST：主要用来创建一个简单测试， 它定义了一个测试函数， 在这个函数中可以使用任何C++代码并且使用框架提供的断言进行检查
- TEST_F：主要用来进行多样测试，适用于多个测试场景如果需要相同的数据配置的情况， 即相同的数据测不同的行为

1. 断言宏

GTest中的断言的宏可以分为两类：

- ASSERT_系列：如果当前点检测失败则退出当前函数
- EXPECT_系列：如果当前点检测失败则继续往下执行

下面是经常使用的断言介绍

```SQL
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
```

1. 样例

```C++
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
```

Makefile：

```Shell
main:main.cc
    g++ -std=c++17 $^ -o $@ -lgtest -lgtest_main -pthread
```

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=NzdkY2JiOWQ0NmU3MTI3YTBiYmM2ZTQyZTEzNmZkMWJfMGo5ckV4M0VaTUM4N05zNUgxYk5WS2lna0h6b0tvekJfVG9rZW46UGJIbWI3Y0dJbzBEaFR4NVdaaGNwcWNTblhjXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

#### Gtest 事件机制

GTest中的事件机制是指在测试前和测试后提供给用户自行添加操作的机制，而且该机制也可以让同一测试套件下的测试用例共享数据。

GTest框架中事件的结构层次：

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGY5MDhmMjRkNGY4NzU3Yjg5ZjRhOWUyOTYxYmZiNmJfY2JmZ2p3TzVnQnhhcE1MOTBTVjE4U2Z4b0dCNnZ6S1RfVG9rZW46RXhhNWJISUVMb1lYS1V4MVM5cGN6dFd6bjJnXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

- 测试程序：一个测试程序只有一个main函数，也可以说是一个可执行程序是一个测试程序。该级别的事件机制是在程序的开始和结束执行
- 测试套件：代表一个测试用例的集合体，该级别的事件机制是在整体的测试案例开始和结束执行
- 测试用例：该级别的事件机制是在每个测试用例开始和结束都执行

事件机制的最大好处就是能够为我们各个测试用例提前准备好测试环境，并在测试完毕后用于销毁环境，这样有个好处就是如果我们有一端代码需要进行多种不同方法的测试，则可以通过测试机制在每个测试用例进行之前初始化测试环境和数据，并在测试完毕后清理测试造成的影响。

GTest提供了三种常见的的事件：

1. 全局事件

针对整个测试程序。实现全局的事件机制，需要创建一个自己的类，然后继承testing::Environment类，然后分别实现成员函数SetUp 和 TearDown，同时在main函数内进行调用testing::AddGlobalTestEnvironment(new MyEnvironment);函数添加全局的事件机制

```C++
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
```

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=ZTIyYjUyZmUzZjAyMDY4ZWE2NGQyZTk4NTE4OTQyNjFfNTQycGxaZkJhdUtLSllQUUFRYU5BSkpkWm9vV0h3RUVfVG9rZW46T1lkYWIzSUVHb002MEF4eHBOV2M0ZmdXbjBjXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

1. TestSuite事件

针对一个个测试套件。测试套件的事件机制我们同样需要去创建一个类，继承自testing::Test，实现两个静态函数SetUpTestCase和TearDownTestCase，测试套件的事件机制不需要像全局事件机制一样在main注册，而是需要将我们平时使用的TEST宏改为TEST_F宏。

- SetUpTestCase() 函数是在测试套件第一个测试用例开始前执行
- TearDownTestCase() 函数是在测试套件最后一个测试用例结束后执行
- 需要注意TEST_F的第一个参数是我们创建的类名，也就是当前测试套件的名称，这样在TEST_F宏的测试套件中就可以访问类中的成员了。

```C++
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
```

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=OGE3N2Q3OTA0ODRiOWVlZDU3Y2JiNzc1MDczNTQ4OTBfbHZsVzkxMmpXNkpLRTRUV25NaWJaWURsMkdDUTVkSE1fVG9rZW46WXRaeWJncjdob1hsdDh4d1hhSmNqbTZkbjJmXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

能够看到在上例中，有一个好处，就是将数据与测试结合到同一个测试环境类中了，这样与外界的耦合度更低，代码也更清晰。

但是同样的，我们发现在两个测试用例中第二个测试用例失败了，这是为什么呢？这就涉及到了TestCase事件的机制。

1. TestCase事件

针对一个个测试用例。测试用例的事件机制的创建和测试套件的基本一样，不同地方在于测试用例实现的两个函数分别是SetUp和TearDown, 这两个函数也不是静态函数

- SetUp()函数是在一个测试用例的开始前执行
- TearDown()函数是在一个测试用例的结束后执行

也就是说，在TestSuite/TestCase事件中，每个测试用例，虽然它们同用同一个事件环境类，可以访问其中的资源，但是本质上每个测试用例的环境都是独立的，这样我们就不用担心不同的测试用例之间会有数据上的影响了，保证所有的测试用例都使用相同的测试环境进行测试。

```C++
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
```

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=ZmQ1ODFiMWZmYzljZGQyOWJiYjFjODMxNmY0ODhhZTRfNU95TE1yOUh6RlZIaVgxVEFQRE1FcVBiVDdqN29qd0pfVG9rZW46TGNVNWJpRG5mb1pHZjd4ZldUNGNXdmVZbmRjXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

### spdlog 框架安装

#### 介绍:

spdlog 是一个高性能、超快速、零配置的C++ 日志库，它旨在提供简洁的API 和丰富的功能，同时保持高性能日志记录。它支持多种输出目标、格式化选项、线程安全以及异步日志记录。以下是对spdlog 的详细介绍和使用方法。

github链接：https://github.com/gabime/spdlog

特点

- 高性能：spdlog 专为速度而设计，即使在高负载情况下也能保持良好的性能。
- 零配置：无需复杂的配置，只需包含头文件即可在项目中使用。
- 异步日志：支持异步日志记录，减少对主线程的影响。
- 格式化：支持自定义日志消息的格式化，包括时间戳、线程ID、日志级别等。
- 多平台：跨平台兼容，支持Windows、Linux、macOS 等操作系统。
- 丰富的 API：提供丰富的日志级别和操作符重载，方便记录各种类型的日志。

#### 安装:

```Shell
sudo apt-get install libspdlog-dev
```

#### 使用:

1. 包含头文件：

在你的C++ 源文件中包含spdlog 的头文件：

```Shell
#include <spdlog/spdlog.h>
```

1. 日志输出等级枚举

```C++
namespace level
{
    enum level_enum : int
    {
        trace = SPDLOG_LEVEL_TRACE,
        debug = SPDLOG_LEVEL_DEBUG,
        info = SPDLOG_LEVEL_INFO,
        warn = SPDLOG_LEVEL_WARN,
        err = SPDLOG_LEVEL_ERROR,
        critical = SPDLOG_LEVEL_CRITICAL,
        off = SPDLOG_LEVEL_OFF,
        n_levels
    };
}
```

1. 日志输出格式自定义：

可以自定义日志消息的格式:

```C++
logger->set_pattern("%Y-%m-%d %H:%M:%S [%t] [%-7l] %v"); 
%t - 线程ID（Thread ID）。 
%n - 日志器名称（Logger name）。 
%l - 日志级别名称（Level name），如 INFO, DEBUG, ERROR 等。 
%v - 日志内容（message）。
%Y - 年（Year）。 
%m - 月（Month）。 
%d - 日（Day）。 
%H - 小时（24-hour format）。 
%M - 分钟（Minute）。 
%S - 秒（Second）。
```

1. 日志记录器类：

创建一个基本的日志记录器，并设置日志级别和输出模式：

```C++
namespace spdlog
{
    class logger
    {
        logger(std::string name); 
        logger(std::string name, sink_ptr single_sink);
        logger(std::string name, sinks_init_list sinks); 
        void set_level(level::level_enum log_level);
        void set_formatter(std::unique_ptr<formatter> f);
        template <typename... Args>
        void trace(fmt::format_string<Args...> fmt, Args &&...args){}
        template <typename... Args>
        void debug(fmt::format_string<Args...> fmt, Args &&...args){}
        template <typename... Args>
        void info(fmt::format_string<Args...> fmt, Args &&...args){} 
        template <typename... Args>
        void warn(fmt::format_string<Args...> fmt, Args &&...args){}
        template <typename... Args>
        void error(fmt::format_string<Args...> fmt, Args &&...args){} 
        template <typename... Args>
        void critical(fmt::format_string<Args...> fmt, Args &&...args){} 
        void flush(); // 刷新日志 
        //策略刷新--触发指定等级日志的时候立即刷新日志的输出 
        void flush_on(level::level_enum log_level); 
    };
}
```

1. 异步日志记录类：

```C++
class async_logger final : public logger
{
    async_logger(std::string logger_name,
                 sinks_init_list sinks_list,
                 std::weak_ptr<details::thread_pool> tp,
                 async_overflow_policy overflow_policy = async_overflow_policy::block);

    async_logger(std::string logger_name,
                 sink_ptr single_sink,
                 std::weak_ptr<details::thread_pool> tp,
                 async_overflow_policy overflow_policy = async_overflow_policy::block);
    // 异步日志输出需要异步工作线程的支持，这里是线程池类
    class SPDLOG_API thread_pool
    {
        thread_pool(size_t q_max_items,
                    size_t threads_n,
                    std::function<void()> on_thread_start,
                    std::function<void()> on_thread_stop);
        thread_pool(size_t q_max_items, size_t threads_n,
                    std::function<void()> on_thread_start);
        thread_pool(size_t q_max_items, size_t threads_n);
    };
};

std::shared_ptr<spdlog::details::thread_pool> thread_pool(){
    return details::registry::instance().get_tp();
}
// 默认线程池的初始化接口
inline void init_thread_pool(size_t q_size, size_t thread_count) 

auto async_logger = spdlog::async_logger_mt("async_logger", "logs/async_log.txt");

async_logger->info("This is an asynchronous info message");
```

1. 日志记录器工厂类：

```C++
using async_factory = async_factory_impl<async_overflow_policy::block>;
template <typename Sink, typename... SinkArgs>
inline std::shared_ptr<spdlog::logger> create_async(
    std::string logger_name, 
    SinkArgs &&...sink_args) 
    
// 创建一个彩色输出到标准输出的日志记录器，默认工厂创建同步日志记录器 
template<typename Factory = spdlog::synchronous_factory> 
std::shared_ptr<logger> stdout_color_mt( 
    const std::string &logger_name, 
    color_mode mode = color_mode::automatic); 
//标准错误 
template<typename Factory = spdlog::synchronous_factory> 
    std::shared_ptr<logger> stderr_color_mt( 
        const std::string &logger_name, 
        color_mode mode = color_mode::automatic); 
//指定文件 
template<typename Factory = spdlog::synchronous_factory> 
std::shared_ptr<logger> basic_logger_mt( 
    const std::string &logger_name, 
    const filename_t &filename, 
    bool truncate = false, 
    const file_event_handlers &event_handlers = {}) 
//循环文件 
template<typename Factory = spdlog::synchronous_factory> 
std::shared_ptr<logger> rotating_logger_mt( 
    const std::string &logger_name, 
    const filename_t &filename, 
    size_t max_file_size, 
    size_t max_files, 
    bool rotate_on_open = false) 
    ...
```

1. 日志落地类

```C++
namespace spdlog
{
    namespace sinks
    {
        class SPDLOG_API sink
        {
        public:
            virtual ~sink() = default;
            virtual void log(const details::log_msg &msg) = 0;
            virtual void flush() = 0;
            virtual void set_pattern(const std::string &pattern) = 0;
            virtual void set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) = 0;
            void set_level(level::level_enum log_level);
        };
        using stderr_color_sink_mt;
        using stderr_sink_mt;
        using stdout_color_sink_mt;
        using stdout_sink_mt;
        // 滚动日志文件-超过一定大小则自动重新创建新的日志文件
        sink_ptr rotating_file_sink(filename_t base_filename,
                                    std::size_t max_size,
                                    std::size_t max_files,
                                    bool rotate_on_open = false,
                                    const file_event_handlers &event_handlers = {});
        using rotating_file_sink_mt = rotating_file_sink<std::mutex>;
        // 普通的文件落地对啊ing
        sink_ptr basic_file_sink(const filename_t &filename,
                                 bool truncate = false,
                                 const file_event_handlers &event_handlers = {});
        using basic_file_sink_mt = basic_file_sink<std::mutex>;
        using kafka_sink_mt = kafka_sink<std::mutex>;
        using mongo_sink_mt = mongo_sink<std::mutex>;
        using tcp_sink_mt = tcp_sink<std::mutex>;
        using udp_sink_mt = udp_sink<std::mutex>;
        .....
        //*_st：单线程版本，不用加锁，效率更高。
        //*_mt：多线程版本，用于多线程程序是线程安全的。
    }
}
```

1. 全局接口

```C++
//输出等级设置接口 
void set_level(level::level_enum log_level);
//日志刷新策略-每隔N秒刷新一次 
void flush_every(std::chrono::seconds interval)
//日志刷新策略-触发指定等级立即刷新 
void flush_on(level::level_enum log_level);
```

1. 记录日志：

使用日志记录器记录不同级别的日志：

```Shell
logger->trace("This is a trace message"); 
logger->debug("This is a debug message"); 
logger->info("This is an info message"); 
logger->warn("This is a warning message"); 
logger->error("This is an error message"); 
logger->critical("This is a critical message");
```

1. 使用样例:

```C++
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>

void multi_sink_example(){
    // 创建一个标准输出的落地方向对象
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    // 该方向仅允许warn等级以上的日志输出
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example][%^%l%$] %v");
    // 创建一个文件输出的落地方向
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt, true");
    // 该方向允许trace等级以上的日志输出
    file_sink->set_level(spdlog::level::trace);
    // 构造一个日志器对象,用于输出日志
    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    // 每个日志器都可以设置初步过滤等级,其次内部每个sink也可以设置自己独立的过滤等级
    logger.set_level(spdlog::level::debug);
    logger.set_pattern("%Y-%m-%d %H:%M:%S [%l] %v");
    logger.warn("this message should not appear in the console, only in the file");
}

void async_example(){
    // void init_thread_pool(size_t q_size, size_t thread_count);
    spdlog::init_thread_pool(32768, 1); // 设置默认线程池属性信息
    // 通过工厂模式创建异步日志记录器的同时,会在内部创建默认线程池作为异步线程
    auto async_logger = spdlog::basic_logger_mt<spdlog::async_factory>(
        "async_file_logger", "logs/async_log.text"
    );
    async_logger->set_pattern("%Y-%m-%d %H:%M:%S [%l] %v");
    for(int i = 1; i < 101; ++i){
        // 需要注意的是,在多参数的时候,spdlog并非使用 %s %d 这种通配符来匹配参数
        // 而是使用 {}, spdlog 可以自己识别数据类型
        async_logger->info("Async message #{} {}", i, "hello");
    }
}

int main()
{
    multi_sink_example();
    // async_example();
    return 0;
}
```

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=OWU1NjM0NzU2ZmIyYjUyYjZhNGMwM2ExYTc3NGMxYjJfbnhZYkNmQ2VvVXpuUHVWWTZXM1cxSk1FMDZlY0R3NG1fVG9rZW46QTNYNmJmcHVlbzg5bzJ4Y1MwRGNpNDdEbjhjXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=OGM1NjkxODUwMzkzZDIyMTQyM2VjMWJjYTdlZWE0NGJfYks2SG9TUEcyaUhVa282cW5YamFTbWhreWpaN2hKRDNfVG9rZW46TG1iZmJla1cxb3Q4VUx4bmR0M2MxRFlRblFoXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

#### 二次封装:

因为spdlog的日志输出对文件名和行号并不是很友好（也有可能是调研不到位...），以及因为spdlog本身实现了线程安全，如果使用默认日志器每次进行单例获取，效率会有降低，因此进行二次封装，简化使用。

- 日志的初始化封装接口
- 日志的输出接口封装宏

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=Yjg4OTE1YmE4ZjA5YmEyZDk1ZDVlNjBjODY0MGFhOWZfYVV6bVZVYjJiNmRHU0d3d2g3RnRRRjBjQXROVldhOTdfVG9rZW46RVFSeWJ5bThTb3FSOHp4SWhlbGNyMkIwbmdlXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

```C++
#include <spdlog/spdlog.h>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>

// 全局日志器
std::shared_ptr<spdlog::logger> g_default_logger;

// mode - 运行模式 true-发布模式 false-调试模式
void init_logger(bool mode, const std::string &file, int32_t level)
{
    if(mode == false){
        // 如果是调试模式，则创建标准输出日志器，输出等级为最低
        g_default_logger = spdlog::stdout_color_mt("default-logger");
        g_default_logger->set_level(spdlog::level::level_enum::trace);
        g_default_logger->flush_on(spdlog::level::level_enum::trace);
    }else{
        // 如果是发布模式，则创建文件日志器，输出等级为最低
        g_default_logger = spdlog::basic_logger_mt("default-logger", file);
        g_default_logger->set_level(spdlog::level::level_enum::trace); 
        g_default_logger->flush_on(spdlog::level::level_enum::trace);
    }
    g_default_logger->set_pattern("[%n][%H:%M:%S][%t][%-8l] %v");
}

#define LOG_TRACE(format,...) g_default_logger->trace(std::string("[{}:{}]") + format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_DEBUG(format,...) g_default_logger->debug(std::string("[{}:{}]") + format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_INFO(format,...) g_default_logger->info(std::string("[{}:{}]") + format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_WARN(format,...) g_default_logger->warn(std::string("[{}:{}]") + format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ERROR(format,...) g_default_logger->error(std::string("[{}:{}]") + format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_CRITICAL(format,...) g_default_logger->critical(std::string("[{}:{}]") + format,__FILE__,__LINE__,##__VA_ARGS__)
```

### brpc 框架安装

### etcd 框架安装

#### 介绍:

Etcd是一个golang编写的分布式、高可用的一致性键值存储系统，用于配置共享和服务发现等。它使用Raft一致性算法来保持集群数据的一致性，且客户端通过长连接watch功能，能够及时收到数据变化通知，相较于Zookeeper框架更加轻量化。以下是关于etcd的安装与使用方法的详细介绍。

#### 安装:

首先，需要在你的系统中安装Etcd。Etcd是一个分布式键值存储，通常用于服务发现和配置管理。以下是在Linux系统上安装Etcd的基本步骤:

1. 安装etcd:

```C++
sudo apt-get install etcd
```

1. 启动etcd服务:

```C++
sudo systemctl start etcd
```

1. 设置Etcd开机自启：

```C++
sudo systemctl enable etcd
```

1. 运行验证

```C++
etcdctl put mykey "this is awesome"
```

如果出现报错：

```C++
dev@bite:~/workspace$ etcdctl put mykey "this is awesome" No help topic for 'put'
```

则sudo vi /etc/profile 在末尾声明环境变量 ETCDCTL_API=3以确定etcd版本。

```C++
export ETCDCTL_API=3
```

完毕后，加载配置文件，并重新执行测试指令:

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=MzI1MDJjOTkzNzhjODRhN2NiNDExMGQ1NGVmYzkxYTRfZWhHd0dDdVhhU2dOTXhrNWJ5U1RhREtQM2hBajJoOHFfVG9rZW46REtBTWI1MVdvb0VTNGd4dTVpQWN5clNNbkNlXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

#### 搭建服务注册发现中心

使用Etcd作为服务注册发现中心,你需要定义服务的注册和发现逻辑.这通常涉及到以下几个操作:

1. 服务注册:服务器启动时,向 Etcd 注册自己的地址和端口.
2. 服务发现:客户端通过Etcd获取服务的地址和端口,用于远程调用.
3. 健康检查:服务定期向Etcd发送心跳,以维持其注册信息的有效性.

etcd 采用golang 编写，v3版本通信采用grpc API，即(HTTP2+protobuf);

官方只维护了go语言版本的client库, 因此需要找到C/C++ 非官方的client 开发库：

etcd-cpp-apiv3

etcd-cpp-apiv3是一个etcd的C++版本客户端API。它依赖于mipsasm, boost, protobuf, gRPC, cpprestsdk等库。

etcd-cpp-apiv3的GitHub地址是：https://github.com/etcd-cpp-apiv3/etcd-cpp-apiv3

依赖安装：

```C++
sudo apt-get install libboost-all-dev 
libssl-dev sudo apt-get install libprotobuf-dev protobuf-compiler-grpc 
sudo apt-get install libgrpc-dev libgrpc++-dev 
sudo apt-get install libcpprest-dev 
```

api框架安装

```Bash
git clone https://github.com/etcd-cpp-apiv3/etcd-cpp-apiv3.git 
cd etcd-cpp-apiv3 
mkdir build && cd build 

cmake .. -DCMAKE_INSTALL_PREFIX=/usr 
make -j$(nproc) && sudo make install
```

**服务注册**

主要是在etcd服务器上存储一个租期ns的保活键值对，表示所能提供指定服务的节点主机，比如/service/user/instance-1的key，且对应的val为提供服务的主机节点地址：

<key, val> -- < /service/user/instance-1, 127.0.0.1:9000>

- /service是主目录，其下会有不同服务的键值对存储
- /user是服务名称，表示该键值对是一个用户服务的节点
- /instance-1是节点实例名称，提供用户服务可能会有很多节点，每个节点都应该有自己独立且唯一的实例名称

当这个键值对注册之后，服务发现方可以基于目录进行键值对的发现。

且一旦注册节点退出，保活失败，则3s后租约失效，键值对被删除，etcd会通知发现方数据的失效，进而实现服务下线通知的功能。

**服务发现**

服务发现分为两个过程：

- 刚启动客户端的时候，进行ls 目录浏览，进行/service路径下所有键值对的获取
- 对关心的服务进行watcher观测，一旦数值发生变化（新增/删除），收到通知进行节点的管理

如果ls 的路径为/service，则会获取到/service/user, /service/firend, ...等其路径下的所有能够提供服务的实例节点数据。 

如果ls 的路径为/service/user， 则会获取到 /service/user/instancd-1, /service/user/instance-2,....等所有提供用户服务的实例节点数据。

客户端可以将发现的所有<实例 - 地址>管理起来，以便于进行节点的管理：

- 收到新增数据通知，则向本地管理添加新增的节点地址-- 服务上线
- 收到删除数据通知，则从本地管理删除对应的节点地址-- 服务下线

因为管理了所有的能够提供服务的节点主机的地址，因此当需要进行rpc调用的时候，则根据服务名称，获取一个能够提供服务的主机节点地址进行访问就可以了，而这里的获取策略，我们采用RR轮转策略。

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=MGYxMjhmNDRiNzFkNWMxMzM0YTk1NzNiNmNlYzk1ZTBfOG5Kd0Zvc0NyNkxIQVV6QzRFTUhMUEx2TDNqOEE3RDdfVG9rZW46WlBMY2J0OWxDb2M0a2J4SUs0dmNua2ZlbnJoXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

**封装思想：**

将etcd的操作全部封装起来，也不需要管理数据，只需要向外四个基础操作接口：

- 进行服务注册，也就是向etcd添加 <服务-主机地址>的数据
- 进行服务发现，获取当前所有能提供服务的信息
- 设置服务上线的处理回调接口
- 设置服务下线的处理回调接口

这样封装之后，外部的rpc调用模块，可以先获取所有的当前服务信息，建立通信连接进行rpc调用，也能在有新服务上线的时候新增连接，以及下线的时候移除连接。

```C++
#pragma once
#include <etcd/Client.hpp>
#include <etcd/KeepAlive.hpp>
#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>
#include <etcd/Value.hpp>
#include <functional>
#include "logger.hpp"

namespace bite_im
{
    // 服务注册客户端类
    class Registry
    {
    public:
        using ptr = std::shared_ptr<Registry>;
        Registry(const std::string &host) : _client(std::make_shared<etcd::Client>(host)),
                                            _keep_alive(_client->leasekeepalive(3).get()),
                                            _lease_id(_keep_alive->Lease()) {}
        ~Registry() { _keep_alive->Cancel(); }
        bool registry(const std::string &key, const std::string &val)
        {
            auto resp = _client->put(key, val, _lease_id).get();
            if (resp.is_ok() == false)
            {
                LOG_ERROR("注册数据失败：{}", resp.error_message());
                return false;
            }
            return true;
        }

    private:
        std::shared_ptr<etcd::Client> _client;
        std::shared_ptr<etcd::KeepAlive> _keep_alive;
        uint64_t _lease_id;
    };

    // 服务发现客户端类
    class Discovery
    {
    public:
        using ptr = std::shared_ptr<Discovery>;
        using NotifyCallback = std::function<void(std::string, std::string)>;
        Discovery(const std::string &host,
                  const std::string &basedir,
                  const NotifyCallback &put_cb,
                  const NotifyCallback &del_cb) : _client(std::make_shared<etcd::Client>(host)),
                                                  _put_cb(put_cb), _del_cb(del_cb)
        {
            // 先进行服务发现,先获取到当前已有的数据
            auto resp = _client->ls(basedir).get();
            if (resp.is_ok() == false)
            {
                LOG_ERROR("获取服务信息数据失败：{}", resp.error_message());
            }
            int sz = resp.keys().size();
            for (int i = 0; i < sz; ++i)
            {
                if (_put_cb)
                    _put_cb(resp.key(i), resp.value(i).as_string());
            }
            // 然后进行事件监控，监控数据发生的改变并调用回调进行处理
            _watcher = std::make_shared<etcd::Watcher>(*_client.get(), basedir,
                                                       std::bind(&Discovery::callback, this, std::placeholders::_1), true);
        }
        ~Discovery()
        {
            _watcher->Cancel();
        }

    private:
        void callback(const etcd::Response &resp)
        {
            if (resp.is_ok() == false)
            {
                LOG_ERROR("收到一个错误的事件通知: {}", resp.error_message());
                return;
            }
            for (auto const &ev : resp.events())
            {
                if (ev.event_type() == etcd::Event::EventType::PUT)
                {
                    if (_put_cb)
                        _put_cb(ev.kv().key(), ev.kv().as_string());
                    LOG_DEBUG("新增服务：{}-{}", ev.kv().key(), ev.kv().as_string());
                }
                else if (ev.event_type() == etcd::Event::EventType::DELETE_)
                {
                    if (_del_cb)
                        _del_cb(ev.prev_kv().key(), ev.prev_kv().as_string());
                    LOG_DEBUG("下线服务：{}-{}", ev.prev_kv().key(), ev.prev_kv().as_string());
                }
            }
        }

    private:
        NotifyCallback _put_cb;
        NotifyCallback _del_cb;
        std::shared_ptr<etcd::Client> _client;
        std::shared_ptr<etcd::Watcher> _watcher;
    };
}
```

![img](https://in4zh9vdv3.feishu.cn/space/api/box/stream/download/asynccode/?code=OGQ0OGE2NTliZjRkM2M5Y2UzYWE5YTk5YWU5ZGQ4OTFfVVRPdVJjRUl2TEIxdGlwZDhTM21TWEc3V3d5M1lxNVlfVG9rZW46WlhWSmJvZXdGb0NDSmV4dElQMWNSQWJsbkdjXzE3NTAzNTI2NTg6MTc1MDM1NjI1OF9WNA)

#### 测试样例:

```C++
#include <etcd/Client.hpp>
#include <etcd/Response.hpp>
#include <etcd/KeepAlive.hpp>
#include <thread>

int main(int argc, char *argv[])
{
    std::string etcd_host = "http://127.0.0.1:2379";
    // 实例化一个etcd客户端对象
    etcd::Client client(etcd_host);

    // 获取租约保活对象 -- 伴随着创建一个指定有效时长的租约
    auto keep_alive = client.leasekeepalive(3).get();

    // 获取租约ID
    auto lease_id = keep_alive->Lease();

    // 向etcd新增数据
    auto resp1 = client.put("/service/user", "127.0.0.1:8080", lease_id).get();
    if(resp1.is_ok() == false){
        std::cout << "新增数据失败：" << resp1.error_message() << std::endl;
        return -1;
    }
    auto resp2 = client.put("/service/user", "127.0.0.1:9090", lease_id).get();
    if(resp2.is_ok() == false){
        std::cout << "新增数据失败：" << resp2.error_message() << std::endl;
        return -1;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
#include <etcd/Client.hpp>
#include <etcd/KeepAlive.hpp>
#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>
#include <etcd/Value.hpp>
#include <thread>

void callback(const etcd::Response &resp){
    if(resp.is_ok() == false){
        std::cout << "获取指定键值对信息失败：" << resp.error_message() << std::endl;
        return;
    }
    for(auto const& ev : resp.events()){
        if(ev.event_type() == etcd::Event::EventType::PUT){
            std::cout << "服务列表发生变化，新增服务：" << std::endl;
            std::cout << "当前的值：" << ev.kv().key() << "-" << ev.kv().as_string() << std::endl;
            std::cout << "原来的值：" << ev.prev_kv().key() << "-" << ev.prev_kv().as_string() << std::endl;
        }
        else if(ev.event_type() == etcd::Event::EventType::DELETE_){
            std::cout << "服务列表发生变化，删除服务：" << std::endl;
            std::cout << "当前的值：" << ev.kv().key() << "-" << ev.kv().as_string() << std::endl;
            std::cout << "原来的值：" << ev.prev_kv().key() << "-" << ev.prev_kv().as_string() << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    std::string etcd_host = "http://127.0.0.1:2379";
    // 实例化一个etcd客户端对象
    etcd::Client client(etcd_host);

    // 获取指定的键值对信息
    auto resp = client.ls("/service").get();
    if(resp.is_ok() == false){
        std::cout << "获取指定键值对信息失败：" << resp.error_message() << std::endl;
        return -1;
    }

    int sz = resp.keys().size();
    for(int i = 0; i < sz; i++){
        std::cout << resp.value(i).as_string() << "可以提供" << resp.key(i) << "服务" << std::endl;
    }

    //实例化一个键值对事件监控对象
    auto watcher = etcd::Watcher(client, "/service", callback, true);
    watcher.Wait();
    return 0;
}
```

### elasticsearch 框架安装：

### cpp-httplib 框架安装：

### websocketpp 框架安装：

### redis 安装

### ODB 安装

### RabbbitMQ 安装