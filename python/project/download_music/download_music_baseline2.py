import time
import requests
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By

headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.83 Safari/537.36'
    }
options = webdriver.ChromeOptions()
service = Service(executable_path=r"C:\Program Files\Google\Chrome\Application\chromedriver.exe")
driver = webdriver.Chrome(service=service, options=options)
driver.implicitly_wait(10)
driver.get('http://tool.liumingye.cn/music/?page=searchPage', headers=headers)
driver.find_element(By.CSS_SELECTOR, '#input').send_keys('张杰')
driver.find_element(By.CSS_SELECTOR, '#search  button:nth-child(2) i').click()

"""保存歌曲数据"""
def download(name, url):
    return
    filename = '音乐\\' + name + '.mp3'
    response = requests.get(url=url)
    with open(filename, mode='wb') as f:
        f.write(response.content)

"""模拟人去滚动鼠标向下浏览页面"""
def drop_down():
    for x in range(1, 20, 10):
        time.sleep(0.5)
        j = x / 10
        js = 'document.documentElement.scrollTop = document.documentElement.scrollHeight * %f' % j
        driver.execute_script(js)


"""解析网站数据获取歌曲名字以及歌曲下载地址"""
lis = driver.find_elements_by_css_selector('#player li')
f = 0
for li in lis:
    f += 1
    time.sleep(1)
    name = li.find_element_by_css_selector('.aplayer-list-title').text
    li.find_element_by_css_selector('.aplayer-list-download').click()
    time.sleep(1)
    down_url = driver.find_element_by_css_selector('#m-download > div > div > div.modal-body > div:nth-child(6) > div.input-group-append > a.btn.btn-outline-secondary.download').get_attribute('href')
    time.sleep(1)
    driver.find_element_by_css_selector('#m-download > div > div > div.modal-header > button').click()
    # time.sleep(1)
    download(name, down_url)
    print(name, down_url)
    if f % 10 == 0:
        drop_down()