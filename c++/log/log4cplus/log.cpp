/**
 * @brief 使用的log4cplus版本为1.2.2其中使用了auto_ptr导致编译器warning
 */
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/mdc.h>
#pragma GCC diagnostic pop
#else
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/mdc.h>
#endif
#include <cstdio>

log4cplus::Logger g_logger_root;

#define LOG_CONF_PATH   "./log.config"

void log_init(void)
{
    try {
        log4cplus::initialize();
        log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(LOG_CONF_PATH));

        // 必须加临时变量，否则编译不过
        //log4cplus::Logger logger = log4cplus::Logger::getRoot();
        //g_logger_root = logger;
        g_logger_root = log4cplus::Logger::getRoot();
    } catch (std::exception &e) {
        printf("log init failed, %s", e.what());
    }
}

int main()
{
    (void)log_init();
    log4cplus::getMDC().put(LOG4CPLUS_TEXT("key"), LOG4CPLUS_TEXT("MDC value"));
    LOG4CPLUS_TRACE(g_logger_root, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_DEBUG(g_logger_root, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_INFO (g_logger_root, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_WARN (g_logger_root, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_ERROR(g_logger_root, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    LOG4CPLUS_FATAL(g_logger_root, LOG4CPLUS_TEXT("Hello, log4cplus!"));
    return 0;
}
