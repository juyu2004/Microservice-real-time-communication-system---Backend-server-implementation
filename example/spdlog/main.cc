#include "logger.hpp"
#include <gflags/gflags.h>

DEFINE_bool(mode, false, "运行模式 true-发布模式 false-调试模式");
DEFINE_string(file, "main.log", "日志文件名");
DEFINE_int32(level, 0, "日志等级");

int main(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    init_logger(FLAGS_mode, FLAGS_file, FLAGS_level);
    
    LOG_TRACE("你好！{}","小明");
    LOG_DEBUG("你好!{}","小明");
    LOG_INFO("你好!{}","小明");
    LOG_WARN("你好!{}","小明");
    LOG_ERROR("你好!{}","小明");
    LOG_CRITICAL("你好!{}","小明");
    LOG_DEBUG("这是一个测试！");
    return -1;
}