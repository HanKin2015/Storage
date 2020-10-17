# -*- coding: utf-8 -*-
"""
Created on Sat Oct 17 11:02:28 2020

@author: hankin
"""

import subprocess

cmd = r"./ls.sh"
cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
result = cmd_result.stdout.read()
print(result)
