#include <iostream>
#include "log.h"
#include "util.h"


int main(int argc, char** argv){
    lirui::Logger::ptr logger(new lirui::Logger);
    logger->addAppender(lirui::LogAppender::ptr(new lirui::StdoutLogAppender));

    lirui::LogAppender::ptr file_appender = std::make_shared<lirui::FileLogAppender>("./log/log.txt");
    lirui::LogFormatter::ptr fmt = std::make_shared<lirui::LogFormatter>("%d%T%m%n");
    file_appender->setFormatter(fmt);
    file_appender->setLevel(lirui::LogLevel::ERROR);

    logger->addAppender(file_appender);
    
    // lirui::LogEvent::ptr event(new lirui::LogEvent(logger, lirui::LogLevel::DEBUG,  __FILE__, __LINE__, 0, 
    //             lirui::GetThreadId(), lirui::GetFiberId(), time(0)));
    // event->getSS() << "this is log info";

    // logger->log(lirui::LogLevel::DEBUG, event); //放入 wrap 的析构函数

    LIRUI_LOG_DEBUG(logger) << "test my macro";
    LIRUI_LOG_WARN(logger) << "test my macro waring";
    LIRUI_LOG_ERROR(logger) << "test my macro error!";
    LIRUI_LOG_FATAL(logger) << "test my macro fatal!!!";


    auto l = lirui::LoggerMgr::GetInstance()->getLogger("xx");
    LIRUI_LOG_INFO(l) << "test logger manager find xx logger";

    std::cout << "hello lirui log" << std::endl;


    return 0;
}