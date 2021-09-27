

import subprocess

cmd = r"./ls.sh"
cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
result = cmd_result.stdout.read()
print(result)
