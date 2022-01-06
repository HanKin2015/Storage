import requests
from bs4 import BeautifulSoup
from concurrent.futures import ThreadPoolExecutor
import logging
import time
from logging.handlers import RotatingFileHandler
logger = logging.getLogger(__name__)
logger.setLevel(level = logging.INFO)
#定义一个RotatingFileHandler，最多备份3个日志文件，每个日志文件最大1K
rHandler = RotatingFileHandler("log.txt",maxBytes = 1*1024,backupCount = 3)
rHandler.setLevel(logging.INFO)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
rHandler.setFormatter(formatter)
 
#console = logging.StreamHandler()
#console.setLevel(logging.INFO)
#console.setFormatter(formatter)
 
logger.addHandler(rHandler)
logging.basicConfig(format="[%(asctime)s-%(levelname)s]: %(message)s", level=logging.INFO)
THREAD_NUM = 4


def input_data(data_file):
    """
    加载待查询域名
    :param data_file: 待查询域名输入文件 每一行一个域名
    :return: 包含所有待查询域名的list
    """
    logging.info("loading data file: {} ".format(data_file))
    data = []
    with open(data_file) as rf:
        for line in rf:
            data.append(line.strip())
    logging.info("data file: {} loaded".format(data_file))
    return data


def load_domain_seacher(api_file):
    """"
    加载查询域名的站点和规则
    :param api_file: 配置域名查询站点和规则的配置文件
    :return: 包含查询站点和查询规则的list
    """
    logging.info("loading api file: {} ".format(api_file))
    api_list = []
    with open(api_file, encoding='utf-8') as rf:
        for line in rf:
            if line.startswith('#'):
                continue
            api_url, selector, idx = line.strip().split(',')
            api_list.append((api_url, selector, int(idx)))
    if len(api_list) == 0:
        logging.warning("api file {} is not contain valid api".format(api_file))
    logger.info("api file: {} loaded".format(api_file))
    return api_list


def search_domain(domain, api_list):
    """
    轮询查询站点, 查询一个域名的信息
    :param domain: 一个待查询域名
    :param api_list: 查询站点和查询规则
    :return: tuple (待查询域名, 域名信息)
    """
    logging.info("search {} begin".format(domain))
    for api_url, selector, idx in api_list:
        url = api_url.format(domain)
        resp = None
        try:
            resp = requests.get(url, timeout=3)
        except Exception as e:
            logging.error("api url {} get error".format(api_url))
            logging.exception(e)
        if resp is not None:
            soup = BeautifulSoup(resp.text, "html.parser")
            tags = soup.select(selector)
            if tags is not None and len(tags) >= idx+1:
                text = tags[idx].string
                if text is None or len(text) > 0:
                    return domain, text
    return domain, 'No domain info'


def main():
    data = input_data('data')
    api_list = load_domain_seacher('api.csv')
    res_list = []
    begin = time.time()
    with ThreadPoolExecutor(THREAD_NUM) as pool:
        for domain in data:
            res = pool.submit(search_domain, domain, api_list)
            res_list.append(res)
    for res in res_list:
        print(res.result())
    end = time.time()
    logging.info("total time cost {}s".format(round(end-begin, 3)))


if __name__ == "__main__":
    main()
