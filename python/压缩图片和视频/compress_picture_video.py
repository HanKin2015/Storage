# -*- coding: utf-8 -*-
"""
文 件 名: compress_picture_video.py
文件描述: python压缩图片和视频
作    者: HanKin
创建日期: 2022.03.13
修改日期：2022.03.13

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
import os
import zlib
import threading
import platform
from PIL import Image

class Compress_Pic_or_Video(object):

    def __init__(self, filePath, inputName, outName=""):
        self.filePath  = filePath   #文件地址
        self.inputName = inputName  #输入的文件名字
        self.outName   = outName    #输出的文件名字
        self.system_   = platform.platform().split("-",1)[0]
        
        if self.system_ ==  "Windows":
            self.filePath = (self.filePath + "\\") if self.filePath.rsplit("\\",1)[-1] else self.filePath
        elif self.system_ == "Linux":
            self.filePath = (self.filePath + "/") if self.filePath.rsplit("/",1)[-1] else self.filePath
            
        self.fileInputPath = self.filePath + inputName
        self.fileOutPath   = self.filePath + outName

    @property
    def is_picture(self):
        picSuffixSet = {"BMP", "GIF", "JPEG", "TIFF", "PNG", "SVG", "PCX", "WMF", "EMF", "LIC", "EPS", "TGA", "JPG"}
        suffix = self.fileInputPath.rsplit(".", 1)[-1].upper()
        if suffix in picSuffixSet:
            return True
        else:
            return False

    @property
    def is_video(self):
        videoSuffixSet = {"WMV", "ASF", "ASX", "RM", "RMVB", "MP4", "3GP", "MOV", "M4V", "AVI", "DAT", "MKV", "FIV", "VOB"}
        suffix = self.fileInputPath.rsplit(".", 1)[-1].upper()
        if suffix in videoSuffixSet:
            return True
        else:
            return False

    def SavePic(self):
        fpsize = os.path.getsize(self.fileInputPath) / 1024  # 获得图片多少K   os.path.getsize(self.picPath)返回的是字节
        if fpsize >= 50.0:                      # 是否大于50K
            im = Image.open(self.fileInputPath) # 打开图片
            imBytes = im.tobytes()              # 把图片转换成bytes流
            imBytes = zlib.compress(imBytes, 5) # 对图像字节串进行压缩
            im2 = Image.frombytes('RGB', im.size, zlib.decompress(imBytes))  # 压缩成新的图片
            if self.outName:
                im2.save(self.fileOutPath)      #不覆盖原图
                return (self.fileOutPath,os.path.getsize(self.fileOutPath))
            else:
                im2.save(self.fileInputPath)    #覆盖原图
                return (self.fileInputPath,os.path.getsize(self.fileInputPath))
        else:
            return True

    def SaveVideo(self):
        fpsize = os.path.getsize(self.fileInputPath) / 1024
        if fpsize >= 150.0: #大于150KB的视频需要压缩
            if self.outName:
                compress = "ffmpeg -i {} -r 10 -pix_fmt yuv420p -vcodec libx264 -preset veryslow -profile:v baseline  -crf 23 -acodec aac -b:a 32k -strict -5 {}".format(self.fileInputPath,self.fileOutPath)
                isRun = os.system(compress)
            else:
                compress = "ffmpeg -i {} -r 10 -pix_fmt yuv420p -vcodec libx264 -preset veryslow -profile:v baseline  -crf 23 -acodec aac -b:a 32k -strict -5 {}".format(self.fileInputPath, self.fileInputPath)
                isRun = os.system(compress)
            if isRun != 0:
                return (isRun,"没有安装ffmpeg")
            return True
        else:
            return True

    def Compress_Picture(self):
        #异步保存打开下面的代码，注释同步保存的代码
        thr = threading.Thread(target=self.SavePic)
        thr.start()
        #下面为同步保存
        # fpsize = os.path.getsize(self.fileInputPath) / 1024  # 获得图片多少K   os.path.getsize(self.picPath)返回的是字节
        # if fpsize >= 50.0:  # 是否大于50K
        #     im = Image.open(self.fileInputPath)  # 打开图片
        #     imBytes = im.tobytes()  # 把图片转换成bytes流
        #     imBytes = zlib.compress(imBytes, 5)  # 对图像字节串进行压缩
        #     im2 = Image.frombytes('RGB', im.size, zlib.decompress(imBytes))  # 压缩成新的图片
        #     if self.outName:
        #         im2.save(self.fileOutPath)  # 不覆盖原图
        #         return (self.fileOutPath, os.path.getsize(self.fileOutPath) / 1024)
        #     else:
        #         im2.save(self.fileInputPath)  # 覆盖原图
        #         return (self.fileInputPath, os.path.getsize(self.fileInputPath) / 1024)
        # else:
        #     return True

    def Compress_Video(self):
        # 异步保存打开下面的代码，注释同步保存的代码
        thr = threading.Thread(target=self.SaveVideo)
        thr.start()
        #下面为同步代码
        # fpsize = os.path.getsize(self.fileInputPath) / 1024
        # if fpsize >= 150.0:  # 大于150KB的视频需要压缩
        #     compress = "ffmpeg -i {} -r 10 -pix_fmt yuv420p -vcodec libx264 -preset veryslow -profile:v baseline  -crf 23 -acodec aac -b:a 32k -strict -5 {}".format(
        #         self.fileInputPath, self.fileOutPath)
        #     isRun = os.system(compress)
        #     if isRun != 0:
        #         return (isRun, "没有安装ffmpeg")
        #     return True
        # else:
        #     return True

if __name__ == "__main__":
    b = sys.argv[1:]    #测试压缩
    savepic = Compress_Pic_or_Video(b[0], b[1], b[2])
    print(savepic.Compress_Picture())
