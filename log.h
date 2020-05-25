#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <ostream>
#include <sstream>
#include <fstream>

#include <time.h>

#include "singleton.h"

/**
 * @brief 使用流式方式将日志级别level的日志写入到logger
 */
#define LIRUI_LOG_LEVEL(logger,level) \
    if(logger->getLevel() <= level) \
        lirui::LogEventWrap(lirui::LogEvent::ptr(new lirui::LogEvent(logger,level, \
            __FILE__, __LINE__,0, lirui::GetThreadId(),\
            lirui::GetFiberId(), time(0)))).getSS()

#define LIRUI_LOG_DEBUG(logger) LIRUI_LOG_LEVEL(logger, lirui::LogLevel::DEBUG)
#define LIRUI_LOG_INFO(logger) LIRUI_LOG_LEVEL(logger, lirui::LogLevel::INFO)
#define LIRUI_LOG_WARN(logger) LIRUI_LOG_LEVEL(logger, lirui::LogLevel::WARN)
#define LIRUI_LOG_ERROR(logger) LIRUI_LOG_LEVEL(logger, lirui::LogLevel::ERROR)
#define LIRUI_LOG_FATAL(logger) LIRUI_LOG_LEVEL(logger, lirui::LogLevel::FATAL)


namespace lirui {

class Logger;

//2 日志级别
class LogLevel{
public:
    enum Level{
        UNKONW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5 //致命
    };

    static const char* ToString(LogLevel::Level level);

};

//1 日志事件
class LogEvent{
public:
    //typedef std::shared_ptr<LogEvent> ptr;
    using ptr = std::shared_ptr<LogEvent>;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t line, uint32_t elapse,
        uint32_t threadId, uint32_t fiberId, uint64_t time);
    ~LogEvent();
    
    const char* getFile() const {return m_file;}
    int32_t getLine() const {return m_line;}
    uint32_t getElapse() const {return m_elapse;}
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint64_t getTime() const {return m_time;}
    // const std::string& getContent() const {return m_ss.str();} //不能常量引用？？
    std::string getContent() const {return m_ss.str();}

    std::shared_ptr<Logger> getLogger() const { return m_logger; }
    LogLevel::Level getLevel() const {return m_level;}


    std::stringstream& getSS() {return m_ss;} // it is a deleted function

private:
    const char *m_file = nullptr;
    int32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint64_t m_time = 0;
    std::stringstream m_ss;

    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};

class LogEventWrap {
public:
    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();

    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;

};


//3 日志格式器, 20200523 不知道怎么写
//怎样才能定义一个灵活的日志输出格式
class LogFormatter{
public:
    using ptr = std::shared_ptr<LogFormatter>;
    LogFormatter(const std::string& pattern);//根据用户输入的pattern来format输出

    //%t %n %thread_id等等
    std::string format(std::shared_ptr<Logger> logger/*Logger::ptr logger*/, LogLevel::Level level, LogEvent::ptr event);
public:
    //日志解析子模块，20200524干嘛的
    class FormatItem{
    public:
        using ptr = std::shared_ptr<FormatItem>;
        //FormatItem(const std::string& fmt = "") {}
        virtual ~FormatItem() {}

        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };

    void init();//解析m_pattern
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
};

//4 日志输出地
class LogAppender{
public:
    using ptr = std::shared_ptr<LogAppender>;
    virtual ~LogAppender(){}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0; //纯虚函数
    void setFormatter(LogFormatter::ptr val){m_formatter = val;}
    LogFormatter::ptr getFormatter() {return m_formatter;}

    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val) {m_level = val;}
    

protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    LogFormatter::ptr m_formatter; //输出什么，以什么格式输出

};

//5 日志器
class Logger : public std::enable_shared_from_this<Logger>{
public:
    using ptr = std::shared_ptr<Logger>;

    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level level) {m_level = level;}

    const std::string& getName() const {return m_name;}

private:
    std::string m_name; //日志名称
    LogLevel::Level m_level;//满足日志级别的才输出,log函数
    std::list<LogAppender::ptr> m_appenders; //Appenders集合, 20200523 不懂这个是干啥的

    LogFormatter::ptr m_formatter;
};


//Appender子类
//输出到控制台的Appender
class StdoutLogAppender : public LogAppender{
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;
    virtual void log(Logger::ptr logger,LogLevel::Level level, LogEvent::ptr event) override;

};

class FileLogAppender : public LogAppender{
public:
    using ptr = std::shared_ptr<FileLogAppender>;
    FileLogAppender(const std::string& filename);
    virtual void log(Logger::ptr logger,LogLevel::Level level, LogEvent::ptr event) override;

    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};


//每次创建logger是麻烦的,创建管理器
class LoggerManager{
public:
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);
private:
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

using LoggerMgr = lirui::Singleton<LoggerManager>;

}

#endif