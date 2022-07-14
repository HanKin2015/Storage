#include <iomanip>
#include <unistd.h>
#include "log4cplus/logger.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/initializer.h"

using namespace std;
using namespace log4cplus;

#define FILE_APPENDER 				0
#define ROLLINGFILE_APPENDER 		1
#define DAILYROLLINGFILE_APPENDER 	0

int main(int argc, char **argv)
{
    log4cplus::Initializer initializer;
    
#if (FILE_APPENDER == 1)
    SharedAppenderPtr append_1(new FileAppender("test.log"));
#elif (ROLLINGFILE_APPENDER == 1)
    SharedAppenderPtr append_1(new RollingFileAppender("./log/test.log", 200*1024, 5, true, true));
#elif (DAILYROLLINGFILE_APPENDER == 1)
    SharedAppenderPtr append_1(new DailyRollingFileAppender("test.log", MINUTELY, true, 5));
#endif
    append_1->setName(LOG4CPLUS_TEXT("append_1"));

    log4cplus::tstring pattern =  LOG4CPLUS_TEXT("%D{%Y/%m/%d %H:%M:%S,%Q} [%t] %-5p - %m [%l]%n");
	append_1->setLayout(std::unique_ptr<Layout>(new PatternLayout(pattern)));
    
    Logger logger_1 = Logger::getInstance(LOG4CPLUS_TEXT("test1"));
    
    logger_1.addAppender(append_1);

    logger_1.setLogLevel(log4cplus::WARN_LOG_LEVEL);
    
    while(true){
        LOG4CPLUS_TRACE(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
        LOG4CPLUS_DEBUG(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
        LOG4CPLUS_INFO (logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
        LOG4CPLUS_WARN (logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
        LOG4CPLUS_ERROR(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
        LOG4CPLUS_FATAL(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
        usleep(100);
    }
    
	return 0;   
}
