import numpy as np

case_data = {'case_name': 'test_customerInfo_save', 'method': 'POST', 'data_type': 'FORM', 'args': '{"companyName": "测试接口","contactName": "test1", "districtId": "1412609444310224897","contactNumber": "158000000","type": "2", "machineTypeId": "250", "machineId": "aax003", "email": "","machineStatus": ""}', 'expect_res': '操作成功', '': '', '备注': 'machineId字段需要参数化否则会报重复'}

# 提取典中典并修改值
args = eval(case_data['args'])
args['machineTypeId'] = '100'

# 新值写回原位
case_data['args'] = str(args)

print(args)

print(case_data)

#case_data['args'].update({'machineTypeId': '123'})
#print(case_data)
print(eval(case_data['args'])['machineTypeId'])

eval(case_data['args']).update({'machineTypeId':'123'})

print(case_data)

args.update({'machineTypeId':'123'})
print(args)

#case_data.update({'args': eval(case_data['args']).update({'machineTypeId':'122222223'})})
#print(case_data)



import json
#json_data = json.loads(str(case_data))
#print(json_data)
user  = '{"name":"jim","sex":"male","age":"18"}'
print(json.loads(user))