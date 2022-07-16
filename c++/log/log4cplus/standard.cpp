/*
 * 标准使用，严格实现步骤1-6。
 */

#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/loggingmacros.h>
#include <unistd.h>

using namespace log4cplus;
using namespace log4cplus::helpers;

int main()
{
    /* step 1: Instantiate an appender object */
    SharedObjectPtr<Appender> _append(new ConsoleAppender());
    _append->setName("append for  test");

    /* step 2: Instantiate a layout object */
    std::string pattern = "%d{%m/%d/%y  %H:%M:%S}  - %m [%l]%n";
    Layout *_layout(new PatternLayout(pattern));

    /* step 3: Attach the layout object to the appender */
    _append->setLayout(std::unique_ptr<Layout>(_layout));

    /* step 4:  Instantiate a logger object */
    Logger _logger = Logger::getInstance("test");

    /* step 5: Attach the appender object to the  logger  */
    _logger.addAppender(_append);

    /* step 6: Set a priority for the logger  */
    _logger.setLogLevel(ALL_LOG_LEVEL);

    /* log activity */
    LOG4CPLUS_DEBUG(_logger, "This is the  FIRST log message...");
    sleep(1);
    LOG4CPLUS_WARN(_logger, "This is the  SECOND log message...");
    return 0;
}