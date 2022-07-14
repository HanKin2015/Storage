#include <iomanip>
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/initializer.h"
#include "log4cplus/configurator.h"

using namespace std;
using namespace log4cplus;

int main(int argc, char **argv)
{
    log4cplus::Initializer initializer;   
    
    Logger root = Logger::getRoot();
	Logger logger_1 = Logger::getInstance(LOG4CPLUS_TEXT("test1"));
    
	/* 使用配置文件进行设置 */
   	log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./log4cplus.properties"));

    LOG4CPLUS_TRACE(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_DEBUG(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_INFO (logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_WARN (logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_ERROR(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_FATAL(logger_1, LOG4CPLUS_TEXT("Hello, log4cplus!"));

	return 0;   
}
