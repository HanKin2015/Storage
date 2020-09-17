# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 00:52:45 2020

@author: hj159

对称加密:指数据加密和解密使用相同的密钥[数据的机密性] --	DES, AES
非对称加密	也叫公钥加密:指数据加密和解密使用不同的密钥,即密钥对儿[身份验证] --	DSA，RSA
单向加密:指只能加密数据,而不能解密数据[数据的完整性] -- MD5，SHA系列算法
"""
from urllib import parse
import base64
import datetime
import argparse #命令行参数获取模块
import hashlib
import hmac
from Crypto import Random
from Crypto.Hash import SHA
from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
from Crypto.Signature import PKCS1_v1_5 as Signature_pkcs1_v1_5
from Crypto.PublicKey import RSA
import rsa

def Findmd5(args):
    md=args.hashvalue
    starttime=datetime.datetime.now()
    for i in open(args.file):
        md5=hashlib.md5()   #获取一个md5加密算法对象
        rs=i.strip()    #去掉行尾的换行符
        md5.update(rs.encode('utf-8'))  #指定需要加密的字符串
        newmd5=md5.hexdigest()  #获取加密后的16进制字符串
        #print newmd5
        if newmd5==md:
            print('明文是：'+rs)    #打印出明文字符串
            break
        else:
            pass

    endtime=datetime.datetime.now()
    print(endtime-starttime)	#计算用时，非必须


#URL编码
def UrlEncode(data):
    encode_data = parse.quote(data)
    return encode_data
def UrlDecode(data):    
    decode_data = parse.unquote(data)
    return decode_data
    
#base64编码:要么是ASCII包含的字符,要么是二进制数据,即不支持中文
def Base64Encode(data):
    encode_data = base64.b64encode(data)
    return encode_data
def Base64Decode(data):    
    decode_data = base64.b64decode(data)
    return decode_data    

#HASH:md5加密是不可逆的，只能加密，不能解密，加密时只能传二进制类型的（字符串加encode()就能变成byte类型）。
#无论多长的字符串，加密出来都是32位的。
def HashEncode(data):
    #可选择md5,sha1
    hash_obj = hashlib.new("md5")
    hash_obj.update(data.encode(encoding='utf-8'))
    return hash_obj.hexdigest()

#HMAC
def HmacEncode(data):
    hmac_obj = hmac.new('key', digestmod=hashlib.md5)
    hmac_obj.update(data.encode(encoding='utf-8'))
    return hmac_obj.hexdigest()

#RSA加密解密
global random_generator
def GenPem():
    # 伪随机数生成器
    global random_generator
    random_generator = Random.new().read
    # rsa算法生成实例
    rsa = RSA.generate(1024, random_generator)
      
    # Server的秘钥对的生成
    private_pem = rsa.exportKey()
    #print(private_pem)
    with open("private.pem", "wb") as f:
      f.write(private_pem)
      
    public_pem = rsa.publickey().exportKey()
    with open("public.pem", "wb") as f:
        #print(type(public_pem))
        f.write(public_pem)
     

#使用公钥对内容进行rsa加密
def RsaEncode1(data): 
    with open("public.pem", "rb") as f:
        key = f.read()
        #print(type(key))
        rsa_key = RSA.importKey(key)
        cipher = Cipher_pkcs1_v1_5.new(rsa_key)
        cipher_text = base64.b64encode(cipher.encrypt(data.encode('utf-8')))
        #print(cipher_text.decode('utf-8'))
        return cipher_text.decode('utf-8')

#使用私钥对内容进行rsa解密
def RsaDecode1(data):
    with open("private.pem", "rb") as f:
        key = f.read()
        rsakey = RSA.importKey(key)
        cipher = Cipher_pkcs1_v1_5.new(rsakey)
        text = cipher.decrypt(base64.b64decode(data), random_generator)
        #print(text.decode('utf-8'))
        return text.decode('utf-8')
 
def SaveKey():
    """
    新建公钥和私钥并保存到本地
    :return:
    """
    pubkey, privkey = rsa.newkeys(1024)
    pub = pubkey.save_pkcs1() #以pem格式保存pubkey
    pri = privkey.save_pkcs1() #以pem格式保存privkey
    with open('./data/public.pem','w+') as f:
        f.write(pub.decode('utf8'))
    with open('./data/private.pem','w+') as f:
        f.write(pri.decode('utf8'))

def RsaEncode(data): 
    '''
    用公钥加密
    :return:
    '''
    with open('./data/public.pem', 'r') as f:
        p = f.read()
    pubkey = rsa.PublicKey.load_pkcs1(p.encode('utf8'))  #pem格式加载公钥,返回pkcs
    crypto = rsa.encrypt(data.encode('utf8'),pub_key=pubkey) # 使用PKCS加密给定的消息,返回类型bytes

    #对于保存，网络传输，打印不乱码，需要通base64编码进行转换；
    # base64编解码能把一些无法直接用文件本信息编码的二进制数据，转换成常规的二进制数据。
    crypto_msg = base64.encodebytes(crypto).decode('utf8')  #加密后的文本信息msg
    #print("加密后:{}".format(crypto_msg))
    return crypto_msg
       
#使用私钥对内容进行rsa解密
def RsaDecode(data):
    '''
    私钥解密
    :return:
    '''
    #读取本地私钥
    with open('./data/private.pem', 'r') as f:
        p = f.read()
    privkey = rsa.PrivateKey.load_pkcs1(p.encode('utf8'))  #pem格式加载私钥
    
    # base64解码
    crypto_msg = base64.decodebytes(data.encode('utf8'))

    decrypto_msg = rsa.decrypt(crypto_msg,privkey)  #私钥解密
    decrypto_msg = decrypto_msg.decode('utf8')  #utf8解码
    #print(decrypto_msg)
    return decrypto_msg

 
 
def TestEncAlgLib():
    data = u"南北abc"
    ret = UrlEncode(data)
    print(ret)
    ret = UrlDecode(ret)
    print(ret)
    
    #注意:用于base64编码的,要么是ASCII包含的字符,要么是二进制数据
    data = b"gasds"
    ret = Base64Encode(data)
    print(ret)
    ret = Base64Decode(ret)
    print(ret)
    
    data = u"何健"
    ret = HashEncode(data)
    print(ret)
    
    GenPem()
    data = "q ('employees')"
    ret = RsaEncode(data)
    print(ret)
    ret = RsaDecode(ret)
    print(ret)
    
def TestScript():
    parser=argparse.ArgumentParser(usage='Usage:./findmd5.py -l 密码文件路径 -i 哈希值 ',description='help info.')   #创建一个新的解析对象
    parser.add_argument("-l", default='wordlist.txt', help="密码文件.", dest="file")    #向该对象中添加使用到的命令行选项和参数
    parser.add_argument("-i", dest="hashvalue",help="要解密的哈希值.")

    args = parser.parse_args()  #解析命令行
    Findmd5(args)    
   
if __name__=='__main__':
    #TestEncAlgLib()    
    #TestScript()
    #SaveKey()
    data = "q ('employees')"
    ret = RsaEncode(data)
    print(ret)
    ret = RsaDecode(ret)
    print(ret)