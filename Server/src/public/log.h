#ifndef __TAO_LOG_H__
#define __TAO_LOG_H__

#include <string>
#include <stdint.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <map>

#include "singleton.h"

#define TAO_LOG_LEVEL(logger, level) \
    if (logger->getLevel() <= level) \
        Tao::LogEventWrap(\
            Tao::LogEvent::ptr(\
                new Tao::LogEvent(logger, level, __FILE__, __LINE__, 0, \
                                Tao::getThreadId(), Tao::getFiberId(), time(0)) ) ).getSS()

#define TAO_LOG_DEBUG(logger) TAO_LOG_LEVEL(logger, Tao::LogLevel::DEBUG)
#define TAO_LOG_INFO(logger) TAO_LOG_LEVEL(logger, Tao::LogLevel::INFO)
#define TAO_LOG_WARN(logger) TAO_LOG_LEVEL(logger, Tao::LogLevel::WARN)
#define TAO_LOG_ERROR(logger) TAO_LOG_LEVEL(logger, Tao::LogLevel::ERROR)
#define TAO_LOG_FATAL(logger) TAO_LOG_LEVEL(logger, Tao::LogLevel::FATAL)

#define TAO_LOG_FMT_LEVEL(logger, level, fmt, ...)\
    if (logger->getLevel() <= level) \
        Tao::LogEventWrap(\
            Tao::LogEvent::ptr(\
                new Tao::LogEvent(logger, level, __FILE__, __LINE__, 0, \
                                Tao::getThreadId(), Tao::getFiberId(), time(0)) ) ).getEvent()->format(fmt, __VA_ARGS__)

#define TAO_LOG_FMT_DEBUG(logger, fmt, ...) TAO_LOG_FMT_LEVEL(logger, Tao::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define TAO_LOG_FMT_INFO(logger, fmt, ...) TAO_LOG_FMT_LEVEL(logger, Tao::LogLevel::INFO, fmt, __VA_ARGS__)
#define TAO_LOG_FMT_WARN(logger, fmt, ...) TAO_LOG_FMT_LEVEL(logger, Tao::LogLevel::WARN, fmt, __VA_ARGS__)
#define TAO_LOG_FMT_ERROR(logger, fmt, ...) TAO_LOG_FMT_LEVEL(logger, Tao::LogLevel::ERROR, fmt, __VA_ARGS__)
#define TAO_LOG_FMT_FATAL(logger, fmt, ...) TAO_LOG_FMT_LEVEL(logger, Tao::LogLevel::FATAL, fmt, __VA_ARGS__)

namespace Tao{
class Logger;

//日志级别
class LogLevel{
public:
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* Tostring(LogLevel::Level level);
};

//日志事件
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            ,uint32_t threadId, uint32_t fiberId, uint64_t time);

    const char* getFile() const { return m_file; } 
    int32_t getLine() const { return m_line; }
    uint32_t getElapse() const { return m_elapse; }
    uint32_t getThreadId() const { return m_threadId; }
    uint32_t getFiberId() const { return m_fiberId; }
    uint64_t getTime() const { return m_time; }
    std::string getContent() const { return m_ss.str(); }
    std::stringstream& getSS() {return m_ss;}
    void format(const char* fmt, ...);
    void fomrat(const char* fmt, va_list al);

    std::shared_ptr<Logger> getLogger() const { return m_logger;}
    LogLevel::Level getLevel() const {return m_level;}
private:
    const char* m_file = nullptr;   //文件名
    int32_t m_line = 0;             //行号
    uint32_t m_elapse = 0;          //程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;        //线程ID
    uint32_t m_fiberId = 0;         //协程ID
    uint64_t m_time = 0;            //时间戳
    std::stringstream m_ss;         

    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};

//配合宏函数简化操作的日志事件包装类
class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr event);
    ~LogEventWrap();
    std::stringstream& getSS();
    LogEvent::ptr getEvent();
private:
    LogEvent::ptr m_logEvent;
};

//日志格式器
    //格式：
        //%m -- 消息体
        //%p -- level
        //%r -- 启动后的时间
        //%c -- 日志名称
        //%t -- 线程id
        //%n -- 回车换行
        // \t
        //%d -- 时间
        //%f -- 文件名
        //%l -- 行号
        //%F -- 协程id
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    class FormatItem{
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem() {}
        
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };

private:
    void init();

    std::string m_pattern;
    std::vector<FormatItem::ptr> m_itemsVector;

};

//日志输出器
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender() {}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

    LogFormatter::ptr getLogFormatter() const { return m_logFormatter; }
    void setLogFormatter(LogFormatter::ptr logFormatter) { m_logFormatter = logFormatter; }

    LogLevel::Level getLevel() const { return m_level;}
    void setLevel(LogLevel::Level level) { m_level = level; }
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    LogFormatter::ptr m_logFormatter;
};

//输出到控制台的Appender
class StdoutLogAppender:public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    
    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;

};

//输出到文件的Appender
class FileLogAppender:public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);

    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_fileStream;

};

//日志器
class Logger:public std::enable_shared_from_this<Logger>{
public:

    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name = "defualt");

    void log(LogLevel::Level level, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    const std::string getName() const { return m_name; }

    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level& level) { m_level = level; } 
    
    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
private:
    std::string m_name;                     //日志名称
    LogLevel::Level m_level;                //日志级别
    std::list<LogAppender::ptr> m_appenderList;      //Appender集合
    LogFormatter::ptr m_logFormatter;
    
};

class LoggerManage{
public:
    LoggerManage();
    Logger::ptr getLogger(const std::string& name);

private:
    void init();

    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_loggerRoot;
};

typedef Tao::SingletonPtr<LoggerManage> LoggerMgr;

}

#endif