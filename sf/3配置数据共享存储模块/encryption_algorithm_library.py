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
import hashlib
import hmac
from Crypto import Random
from Crypto.Hash import SHA
from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
from Crypto.Signature import PKCS1_v1_5 as Signature_pkcs1_v1_5
from Crypto.PublicKey import RSA
import rsa
import os

# URL编码
def url_encode(data):
    encode_data = parse.quote(data)
    return encode_data
def url_decode(data):    
    decode_data = parse.unquote(data)
    return decode_data
    
# base64编码:要么是ASCII包含的字符,要么是二进制数据,即不支持中文
def base64_encode(data):
    encode_data = base64.b64encode(data)
    return encode_data
def base64_decode(data):    
    decode_data = base64.b64decode(data)
    return decode_data    

# HASH:md5加密是不可逆的，只能加密，不能解密，加密时只能传二进制类型的（字符串加encode()就能变成byte类型）。
# 无论多长的字符串，加密出来都是32位的。
def hash_encode(data):
    # 可选择md5,sha1
    hash_obj = hashlib.new("md5")
    hash_obj.update(data.encode(encoding='utf-8'))
    return hash_obj.hexdigest()

# HMAC
def hmac_encode(data):
    hmac_obj = hmac.new('key', digestmod=hashlib.md5)
    hmac_obj.update(data.encode(encoding='utf-8'))
    return hmac_obj.hexdigest()
 
def save_key():
    """
    新建公钥和私钥并保存到本地
    :return:
    """
    if os.path.exists('./data/public.pem'):
        return True
    pubkey, privkey = rsa.newkeys(1024)
    pub = pubkey.save_pkcs1() #以pem格式保存pubkey
    pri = privkey.save_pkcs1() #以pem格式保存privkey
    with open('./data/public.pem','w+') as f:
        f.write(pub.decode('utf8'))
    with open('./data/private.pem','w+') as f:
        f.write(pri.decode('utf8'))

def rsa_encode(data): 
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
def rsa_decode(data):
    '''
    私钥解密
    :return:
    '''
    #读取本地私钥
    save_key()
    with open('./data/private.pem', 'r') as f:
        p = f.read()
    privkey = rsa.PrivateKey.load_pkcs1(p.encode('utf8'))  #pem格式加载私钥
    
    # base64解码
    crypto_msg = base64.decodebytes(data.encode('utf8'))

    decrypto_msg = rsa.decrypt(crypto_msg,privkey)  #私钥解密
    decrypto_msg = decrypto_msg.decode('utf8')  #utf8解码
    #print(decrypto_msg)
    return decrypto_msg

 
 
def test_enc_alg_lib():
    data = u"南北abc"
    ret = url_encode(data)
    print(ret)
    ret = url_decode(ret)
    print(ret)
    
    #注意:用于base64编码的,要么是ASCII包含的字符,要么是二进制数据
    data = b"gasds"
    ret = base64_encode(data)
    print(ret)
    ret = base64_decode(ret)
    print(ret)
    
    data = u"何健"
    ret = hash_encode(data)
    print(ret)
    
    data = "q ('employees')"
    ret = rsa_encode(data)
    print(ret)
    ret = rsa_decode(ret)
    print(ret)
  
   
if __name__=='__main__':
    test_enc_alg_lib() 
    