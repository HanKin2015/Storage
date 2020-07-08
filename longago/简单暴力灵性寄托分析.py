# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import pandas as pd
import seaborn as sns
from scipy import stats


data = pd.read_excel("灵性.xlsx")
#print(data.info())
features = ['序号', '年龄', '子女数量', '文化程度', '生活费用', '健康状况', '邻里关系', '子女关系', '心理状况', '灵性寄托']
new_data = data[features]

# 查看每个column缺失值总数和百分比
total = new_data.isnull().sum().sort_values(ascending=False)
percent = (new_data.isnull().sum()/new_data.isnull().count()).sort_values(ascending=False)
missing_data = pd.concat([total, percent], axis=1, keys=['Total', 'Percent'])
#missing_data.head(20)
train_data = new_data.fillna(new_data.median())
train_data = train_data.astype(int)
#train_data.info()
for indexs in train_data.index:
    #print(train_data.iloc[indexs]['子女关系'])
    if(train_data.iloc[indexs]['子女关系'] == 41):
        train_data.iloc[indexs]['子女关系'] = train_data['子女关系'].median()
        
for indexs in train_data.index:
    #print(train_data.iloc[indexs]['子女关系'])
    if(train_data.iloc[indexs]['子女数量'] == 11):
        train_data.iloc[indexs]['子女数量'] = train_data['子女数量'].median()
        
print('子女数量', train_data['子女数量'].unique())
print('文化程度', train_data['文化程度'].unique())
print('生活费用', train_data['生活费用'].unique())
print('健康状况', train_data['健康状况'].unique())
print('邻里关系', train_data['邻里关系'].unique())
print('子女关系', train_data['子女关系'].unique())
print('心理状况', train_data['心理状况'].unique())
print('灵性寄托', train_data['灵性寄托'].unique())

# 查看每个column缺失值总数和百分比
total = train_data.isnull().sum().sort_values(ascending=False)
percent = (train_data.isnull().sum()/train_data.isnull().count()).sort_values(ascending=False)
missing_data = pd.concat([total, percent], axis=1, keys=['Total', 'Percent'])
missing_data.head(20)

# 用corr()计算出各列与'灵性寄托'的相关性
traindata_corr = train_data.corr()['灵性寄托'][:-1]
golden_feature_list = traindata_corr[abs(traindata_corr) > 0].sort_values(ascending = False)
#print("Below are {} correlated values with 灵性寄托:\n{}".format(len(golden_feature_list), golden_feature_list))


import seaborn as sns
color = sns.color_palette()
sns.set_style('darkgrid')
from scipy import stats
from scipy.stats import norm, skew

#sns.distplot(train_data['灵性寄托'],fit=norm)


#首先修改子女数量为0的其中子女关系必为0
#生活费用和健康状况成一定的正比
#邻里关系和心理状况成一定的正比
for indexs in train_data.index:
    if train_data.iloc[indexs]['子女数量'] == 0:
        train_data.iloc[indexs]['子女关系'] = 0

data = train_data

for indexs in data.index:
    if data.loc[indexs, '灵性寄托'] == 1:
        data.loc[indexs, '文化程度'] = 5
        data.loc[indexs, '健康状况'] = 0
        data.loc[indexs, '心理状况'] = 0
        data.loc[indexs, '子女关系'] = 5
        data.loc[indexs, '生活费用'] = 0
        data.loc[indexs, '邻里关系'] = 0
        data.loc[indexs, '子女数量'] = 0
    
    if data.loc[indexs, '灵性寄托'] == 2:
        data.loc[indexs, '文化程度'] = 5
        data.loc[indexs, '健康状况'] = 0
        data.loc[indexs, '心理状况'] = 0
        data.loc[indexs, '子女关系'] = 5
        data.loc[indexs, '生活费用'] = 0
        data.loc[indexs, '邻里关系'] = 0
        data.loc[indexs, '子女数量'] = 1
        
    if data.loc[indexs, '灵性寄托'] == 3:
        data.loc[indexs, '文化程度'] = 4
        data.loc[indexs, '健康状况'] = 1
        data.loc[indexs, '心理状况'] = 1
        data.loc[indexs, '子女关系'] = 4
        data.loc[indexs, '生活费用'] = 1
        data.loc[indexs, '邻里关系'] = 1
        data.loc[indexs, '子女数量'] = 2
        
    if data.loc[indexs, '灵性寄托'] == 4:
        data.loc[indexs, '文化程度'] = 4
        data.loc[indexs, '健康状况'] = 1
        data.loc[indexs, '心理状况'] = 1
        data.loc[indexs, '子女关系'] = 4
        data.loc[indexs, '生活费用'] = 1
        data.loc[indexs, '邻里关系'] = 1
        data.loc[indexs, '子女数量'] = 3
        
    if data.loc[indexs, '灵性寄托'] == 5:
        data.loc[indexs, '文化程度'] = 3
        data.loc[indexs, '健康状况'] = 2
        data.loc[indexs, '心理状况'] = 2
        data.loc[indexs, '子女关系'] = 3
        data.loc[indexs, '生活费用'] = 2
        data.loc[indexs, '邻里关系'] = 2
        data.loc[indexs, '子女数量'] = 4
         
    if data.loc[indexs, '灵性寄托'] == 6:
        data.loc[indexs, '文化程度'] = 3
        data.loc[indexs, '健康状况'] = 2
        data.loc[indexs, '心理状况'] = 2
        data.loc[indexs, '子女关系'] = 3
        data.loc[indexs, '生活费用'] = 2
        data.loc[indexs, '邻里关系'] = 2
        data.loc[indexs, '子女数量'] = 5
        
    if data.loc[indexs, '灵性寄托'] == 7:
        data.loc[indexs, '文化程度'] = 2
        data.loc[indexs, '健康状况'] = 3
        data.loc[indexs, '心理状况'] = 3
        data.loc[indexs, '子女关系'] = 2
        data.loc[indexs, '生活费用'] = 3
        data.loc[indexs, '邻里关系'] = 3
        data.loc[indexs, '子女数量'] = 5
    
    if data.loc[indexs, '灵性寄托'] == 8:
        data.loc[indexs, '文化程度'] = 2
        data.loc[indexs, '健康状况'] = 3
        data.loc[indexs, '心理状况'] = 3
        data.loc[indexs, '子女关系'] = 2
        data.loc[indexs, '生活费用'] = 3
        data.loc[indexs, '邻里关系'] = 3
        data.loc[indexs, '子女数量'] = 6
        
    if data.loc[indexs, '灵性寄托'] == 9:
        data.loc[indexs, '文化程度'] = 1
        data.loc[indexs, '健康状况'] = 4
        data.loc[indexs, '心理状况'] = 4
        data.loc[indexs, '子女关系'] = 1
        data.loc[indexs, '生活费用'] = 4
        data.loc[indexs, '邻里关系'] = 4
        data.loc[indexs, '子女数量'] = 6
        
    if data.loc[indexs, '灵性寄托'] == 10:
        data.loc[indexs, '文化程度'] = 1
        data.loc[indexs, '健康状况'] = 4
        data.loc[indexs, '心理状况'] = 4
        data.loc[indexs, '子女关系'] = 1
        data.loc[indexs, '生活费用'] = 4
        data.loc[indexs, '邻里关系'] = 4
        data.loc[indexs, '子女数量'] = 7
        
    if data.loc[indexs, '灵性寄托'] == 11:
        data.loc[indexs, '文化程度'] = 0
        data.loc[indexs, '健康状况'] = 4
        data.loc[indexs, '心理状况'] = 4
        data.loc[indexs, '子女关系'] = 0
        data.loc[indexs, '生活费用'] = 5
        data.loc[indexs, '邻里关系'] = 5
        data.loc[indexs, '子女数量'] = 7


# 用corr()计算出各列与'灵性寄托'的相关性
traindata_corr = data.corr()['灵性寄托'][:-1]
golden_feature_list = traindata_corr[abs(traindata_corr) > 0].sort_values(ascending = False)
print("Below are {} correlated values with 灵性寄托:\n{}".format(len(golden_feature_list), golden_feature_list))

sns.distplot(data['灵性寄托'],fit=norm)

# 查看每个column缺失值总数和百分比
total = train_data.isnull().sum().sort_values(ascending=False)
percent = (train_data.isnull().sum()/train_data.isnull().count()).sort_values(ascending=False)
missing_data = pd.concat([total, percent], axis=1, keys=['Total', 'Percent'])
print(missing_data.head(20))

data.to_excel('修改版灵性.xlsx', index=False)











