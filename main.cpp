#include <iostream>
#include "./src/log.h"


int main(int argc, char** argv){
    lirui::Logger::ptr logger(new lirui::Logger);
    logger->addAppender(lirui::LogAppender::ptr(new lirui::StdoutLogAppender));
    
    lirui::LogEvent::ptr event(new lirui::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));
    event->getSS() << "this is log info";

    logger->log(lirui::LogLevel::DEBUG, event);

    std::cout << "hello lirui log";

    return 0;
}