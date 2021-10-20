#include "log.h"
#include "util.h"
#include <iostream>

int main(int argc, char** argv){
    Tao::Logger::ptr logger(new Tao::Logger);
    logger->addAppender(Tao::LogAppender::ptr(new Tao::StdoutLogAppender));

    Tao::FileLogAppender::ptr fileAppender(new Tao::FileLogAppender("./log.txt"));
    Tao::LogFormatter::ptr fileLogFormat(new Tao::LogFormatter("%d%T[%p]%T%m%n"));
    fileAppender->setLogFormatter(fileLogFormat);
    fileAppender->setLevel(Tao::LogLevel::ERROR);
    logger->addAppender(fileAppender);

    TAO_LOG_LEVEL(logger, Tao::LogLevel::DEBUG) << "haha";
    TAO_LOG_INFO(logger) << "INFO";
    TAO_LOG_FATAL(logger) << "FATAL";
    TAO_LOG_FMT_ERROR(logger, "ERROR %s", "zt");

    auto i = Tao::LoggerMgr::getInstance()->getLogger("xx");
    TAO_LOG_WARN(i) << "SinglePtr";
    
    return 0;
}