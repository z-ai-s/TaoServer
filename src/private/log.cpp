#include "log.h"
#include <iostream>
#include <time.h>

namespace Tao
{
//日志事件
LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            ,uint32_t threadId, uint32_t fiberId, uint64_t time)
    :m_file(file)
    ,m_line(line)
    ,m_elapse(elapse)
    ,m_threadId(threadId)
    ,m_fiberId(fiberId)
    ,m_time(time)
    ,m_logger(logger)
    ,m_level(level){

}

void LogEvent::format(const char *fmt, ...){
    va_list al;
    va_start(al, fmt);
    fomrat(fmt, al);
    va_end(al);
}

void LogEvent::fomrat(const char* fmt, va_list al){
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    if (len != -1){
        m_ss << std::string(buf, len);
        free(buf);
    }
}

LogEventWrap::LogEventWrap(LogEvent::ptr event)
    :m_logEvent(event){    
}

LogEventWrap::~LogEventWrap(){
    m_logEvent->getLogger()->log(m_logEvent->getLevel(), m_logEvent);
}

std::stringstream& LogEventWrap::getSS(){
    return m_logEvent->getSS();
}

LogEvent::ptr LogEventWrap::getEvent(){
    return m_logEvent;
}

//日志级别
const char* LogLevel::Tostring(LogLevel::Level level){
    switch (level) {
#define XX(name) \
    case LogLevel::name: \
        return #name;    \
        break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX   
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
}

//日志格式器
LogFormatter::LogFormatter(const std::string& pattern)
    :m_pattern(pattern){
    init();
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event){
    std::stringstream ss;
    for (auto formatItem:m_itemsVector){
        formatItem->format(ss, logger, level, event);
    }

    return ss.str();
}

class MessageFormatItem:public LogFormatter::FormatItem{
public:
    MessageFormatItem(const std::string& fmt = "") {}
    
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getContent();
    }
};

class LevelFormatItem:public LogFormatter::FormatItem{
public:
    LevelFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << LogLevel::Tostring(level);
    }
};

class ElapseFormatItem:public LogFormatter::FormatItem{
public:
    ElapseFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class LoggerNameFormatItem:public LogFormatter::FormatItem{
public:
    LoggerNameFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << logger->getName();
    }
};

class ThreadIdFormatItem:public LogFormatter::FormatItem{
public:
    ThreadIdFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

class FiberIdFormatItem:public LogFormatter::FormatItem{
public:
    FiberIdFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFiberId();
    }
};

class NewLineFormatItem:public LogFormatter::FormatItem{
public:
    NewLineFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << std::endl;
    }
};

class TabFormatItem:public LogFormatter::FormatItem{
public:
    TabFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << "\t";
    }
};

class StringFormatItem:public LogFormatter::FormatItem{
public:
    StringFormatItem(const std::string& str)
        :m_string(str) {

    }

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << m_string;
    }
private:
    std::string m_string;
};

class DataTimeFormatItem:public LogFormatter::FormatItem{
public:
    DataTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S")
        :m_format(format){
        if (m_format.empty()){
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }

private:
    std::string m_format;
};

class FilenameFormatItem:public LogFormatter::FormatItem{
public:
    FilenameFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFile();
    }
};

class LineFormatItem:public LogFormatter::FormatItem{
public:
    LineFormatItem(const std::string& fmt = "") {}

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

//%%  %xxx  %xxx{xxx} 三种
void LogFormatter::init(){
    std::vector<std::tuple<std::string, std::string, int> > vec; //保存str format type 
    std::string nstr;

    for (size_t i = 0; i < m_pattern.size(); i++){
        //普通字符
        if (m_pattern[i] != '%'){
            nstr.append(1, m_pattern[i]);
            continue;
        }
        //格式字符

        //%%
        if (m_pattern[i+1] == '%' && (i+1) < m_pattern.size()){
            nstr.append(1, '%');
            i++;        //for 循环中有一个++
            continue;
        }

        size_t n = i + 1;
        size_t fmt_beigin = 0;
        int fmt_status = 0;
        std::string str;
        std::string format;
        //其他两种情况
        while (n < m_pattern.size()){
            if (!fmt_status &&
                !isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}'){
                str = m_pattern.substr(i+1, n-i-1);
                break;
            }
                

            if (fmt_status == 0){
                if (m_pattern[n] == '{'){
                    str = m_pattern.substr(i+1, n-i-1);
                    fmt_status = 1;
                    fmt_beigin = n;
                    n++;
                    continue;
                }
            }

            if (fmt_status == 1){
                if (m_pattern[n] == '}'){
                    format = m_pattern.substr(fmt_beigin+1, n-fmt_beigin-1);
                    fmt_status = 0;
                    n++;
                    break;
                }
            }
            n++;

            if (n == m_pattern.size() && str.empty()){
                str = m_pattern.substr(i + 1);
            }
        }
        
        if (fmt_status == 0){
            if (!nstr.empty()){
                vec.push_back(std::make_tuple(nstr, "", 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, format, 1));
            i = n - 1;
        } else if (fmt_status == 1){
            std::cout << "pattern parse error!" << m_pattern << " - " << m_pattern.substr(i) << std::endl;
            vec.push_back(std::make_tuple("<<error-type>>", format, 0));
        }
    }

    if (!nstr.empty()){
        vec.push_back(std::make_tuple(nstr, "", 0));
        nstr.clear();
    }

    static std::map<std::string, std::function<FormatItem::ptr(const std::string& fmt)> > s_format_items = {
#define XX(str, type) \
        {str, [](const std::string& fmt) {return FormatItem::ptr(new type(fmt) );} }

        XX("m", MessageFormatItem),         //%m -- 消息体
        XX("p", LevelFormatItem),           //%p -- level
        XX("r", ElapseFormatItem),          //%r -- 启动后的时间
        XX("c", LoggerNameFormatItem),      //%c -- 日志名称
        XX("t", ThreadIdFormatItem),        //%t -- 线程id
        XX("n", NewLineFormatItem),         //%n -- 回车换行
        XX("T", TabFormatItem),             // \t
        XX("d", DataTimeFormatItem),        //%d -- 时间
        XX("f", FilenameFormatItem),        //%f -- 文件名
        XX("l", LineFormatItem),            //%l -- 行号
        XX("F", FiberIdFormatItem)          //%F -- 协程id
#undef XX
    };

    for (auto& i : vec){
        if (std::get<2>(i) == 0) {
            m_itemsVector.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i) )));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if (it == s_format_items.end()) {
                m_itemsVector.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>") ));
            } else {
                m_itemsVector.push_back(it->second(std::get<1>(i)) );
            }
        }

    }
}

//输出到控制台的Appender
void StdoutLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event){
    if (level >= m_level){
        std::cout << m_logFormatter->format(logger, level, event);
    }
}

//输出到文件的Appender
FileLogAppender::FileLogAppender(const std::string &filename)
    :m_filename(filename){
        if (!reopen()){
            std::cout << "open file failed!" << std::endl;
        }
}

void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level){
        m_fileStream << m_logFormatter->format(logger, level, event);
    }
}

bool FileLogAppender::reopen(){
    if (m_fileStream){
        m_fileStream.close();
    }
    m_fileStream.open(m_filename, std::ios::app);

    return !!m_fileStream;
}

//日志器
Logger::Logger(const std::string& name)
    :m_name(name)
    ,m_level(LogLevel::DEBUG) {         //默认是最低级别
    m_logFormatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if (level >= m_level){
        auto self = shared_from_this();
        for (auto& appender:m_appenderList){
            appender->log(self, level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event){
    log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event){
    log(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);
}

void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);
}

void Logger::addAppender(LogAppender::ptr appender){
    if (!appender->getLogFormatter()){          //如果appender没有自己的格式则将logger的格式给它
        appender->setLogFormatter(m_logFormatter);
    }
    m_appenderList.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender){
    for(auto ite = m_appenderList.begin();
             ite != m_appenderList.end(); 
             ite++){
        if(*ite == appender){
            m_appenderList.erase(ite);
            break;
        }         
    }
}

LoggerManage::LoggerManage(){
    m_loggerRoot.reset(new Logger);
    m_loggerRoot->addAppender(LogAppender::ptr(new StdoutLogAppender));
}

Logger::ptr LoggerManage::getLogger(const std::string& name){
    auto it = m_loggers.find(name);
    return it == m_loggers.end() ? m_loggerRoot : it->second;
}

void LoggerManage::init(){

}

}
