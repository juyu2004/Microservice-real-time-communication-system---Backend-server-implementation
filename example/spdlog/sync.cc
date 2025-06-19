#include "spdlog/spdlog.h"
#include <iostream>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
int main()
{
    // 设置全局的刷新策略
    // 每秒刷新
    spdlog::flush_every(std::chrono::seconds(1));

    // 遇到debug以上日志立即刷新
    spdlog::flush_on(spdlog::level::level_enum::debug);

    // 设置全局的日志输出等级 -- 无所谓 -- 每个日志器可以独立进行设置
    spdlog::set_level(spdlog::level::level_enum::debug);

    // 创建一个同步日志器（标准输出/文件）-- 工厂接口默认创建的就是同步日志器
    // auto logger = spdlog::stdout_color_mt("default-logger");
    auto logger = spdlog::basic_logger_mt("default-logger", "sync.log");

    // 设置日志输出格式
    logger->set_pattern("[%n][%H:%M:%S][%t][%-8l] %v");

    // 进行简单的日志输出
    logger->trace("你好！{}","小明");
    logger->debug("你好!{}","小明");
    logger->info("你好!{}","小明");
    logger->warn("你好!{}","小明");
    logger->error("你好!{}","小明");
    logger->critical("你好!{}","小明");

    return 0;
}