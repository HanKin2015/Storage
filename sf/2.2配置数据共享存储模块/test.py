# -*- coding: utf-8 -*-
"""
Created on Sat Jul 11 16:51:52 2020

@author: hj159
"""
import client

if __name__=='__main__':
    client.help()
    
    cmd = "qry ('employees')"
    client.execute_cmd(cmd)
    client.execute_cmd("closeserver")