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