# 域名备案信息查询

输入一批域名，返回这批域名备案信息中的主办单位名称

比如，对于域名“www.sina.com”，返回“北京新浪互联信息服务有限公司”

可以通过第三方API来查询www.sina.com备案信息，如：
http://icp.chinaz.com/www.sina.com
https://www.beian88.com/sina.com
http://www.beianbeian.com/search/www.sina.com.html

第三方API可能不稳定，可能返回错误，可能返回输入验证码，你的代码需要尝试从多个第三方API获取信息来保证程序的输出。

其它要求：
1. 尽可能考虑过程中可能出现的异常
2. 合理地记录日志
3. 使用多线程来优化性能
4. 需单元测试



# 1、输入
- 以文件格式读入，当前目录下urls.txt文件
- 手动输入(未设计，不方便大量输入)

# 2、日志打印
- 使用logging，并且使用concurrent_log_handler日志自动以5k大小备份，当前目录log.txt文件

# 3、使用python爬虫技术获取主办单位名称
- 使用requests+bs4方式进行爬虫
- 三个域名备案网站dom结构不同，设置不同的爬取规则
- 反爬虫机制，超时未获取则使用代理ip爬取
- 并发爬虫解析，使用ThreadPoolExecutor线程池

# 3、单元测试
- 使用unittest框架

# 4、保存到本地文件
- 结果保存到当前目录results.csv文件





























