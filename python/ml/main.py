# -*- coding: utf-8 -*-
"""
Created on Mon Jan 14 15:02:09 2019

@author: HanKin
"""

############ 1、导入依赖包 ############
import numpy as np            # ndarray数组
import pandas as pd           # DataFrame表格
from sklearn import datasets  # 自带的数据集
from sklearn.model_selection import train_test_split # 随机划分为训练子集和测试子集
from sklearn.model_selection import cross_val_score  # 模型评价：训练误差和测试误差
from sklearn.feature_selection import SelectFromModel, chi2, SelectPercentile # 特征选择(三种方法)
from sklearn.metrics import roc_auc_score            # 评价指标
from sklearn.metrics import f1_score 
#from sklearn.cross_validation import StratifiedKFold # K折交叉验证
from sklearn.model_selection import StratifiedKFold
from sklearn.model_selection import KFold

from sklearn.neighbors import KNeighborsClassifier   # KNN
from sklearn.linear_model import LogisticRegression  # 逻辑斯特回归LR
from sklearn.tree import DecisionTreeClassifier      # DT
from sklearn.ensemble import RandomForestClassifier  # RFC随机森林分类
from sklearn.ensemble import RandomForestRegressor   # RFR随机森林回归
from sklearn.ensemble import ExtraTreesClassifier    # ETC极端随机树分类
from sklearn.ensemble import ExtraTreesRegressor     # ETR极端随机树回归
from sklearn.naive_bayes import GaussianNB           # GNB朴素贝叶斯
from sklearn import svm                            # SVM支持向量机
import xgboost as xgb                                # XGB
import lightgbm as lgb                               # LGB
from scipy import sparse                           # 对稀疏数据进行标准化        
from sklearn.preprocessing import OneHotEncoder, LabelEncoder  # 独热编码、标签编码
from sklearn.feature_extraction.text import CountVectorizer   # 文本特征提取
import time
import datetime
import os   
import re     
from sklearn.metrics import mean_squared_error
from sklearn.metrics import log_loss 
from pandas.api.types import is_bool_dtype, is_string_dtype  # 字段类型判断

import matplotlib as mpl
import matplotlib.pyplot as plt      # 作图
import seaborn as sns                # 作图
plt.style.use("fivethirtyeight")
sns.set_style({'font.sans-serif':['simhei','Arial']})
from IPython.display import display  # 输出语句

import warnings                      # 消除警告
warnings.filterwarnings("ignore")

#%matplotlib inline  
#import mxnet                          # 深度学习框架
#import tensorflow as tf

from sys import version_info  # 检查Python版本
if version_info.major != 3:
    raise Exception('请使用 Python 3 来完成此项目')
	
############ 2、加载数据集 ############
if not os.path.exists('data'):
    raise Exception('请将数据集放在data文件夹里面')
path = os.path.dirname(os.path.realpath('__file__')) + '/data/'
train = pd.read_csv(path + 'jinnan_round1_train_20181227.csv', engine='python') # 默认engine不行
#test = pd.read_csv(path + 'jinnan_round1_testA_20181227.csv', engine='python')
test = pd.read_csv(path + 'jinnan_round1_testB_20190121.csv', engine='python')
submission = test[['样本id']]
#submission = pd.read_csv(path + 'jinnan_round1_submit_20181227.csv', engine='python', header=None)

# 删除离群点样本
train = train[train['收率']>0.85]

# 获取target
target = train['收率']  # 是label好还是target
#del train['收率']

# 合并训练集和测试集
train['dataType'] = 1
test['dataType'] = -1
test['收率'] = -1
data = pd.concat([train, test], axis=0, ignore_index=True)
data = data.reindex_axis(train.columns, axis=1)  # 合并后列名会按照字母序排列，复原

data['drop_count'] = data[['B9', 'B10', 'B11']].isnull().sum(axis=1)
data.drop(['B9','B10','B11'], axis=1, inplace=True)

# 缺失值填充
data = data.fillna(-1)

# 异常值修正
data[1486, 'A19'] = 300
data[1512, 'A19'] = 100
data[1304, 'A25'] = 70
data[523, 'B1'] = 350
data[1043, 'B6'] = 79
data[1443, 'B6'] = 79
data[1061, 'B12'] = 800
data[1433, 'B14'] = 385
data[597, 'B14'] = 400
data[1246, 'B14'] = 400

'''
共有18个Object类型特征，其中A25里都是数值直接转换
另外10个时间戳，6个时间段，1个样本id
'''
# 转换A25，有一条异常值
#del data['A25'][1298]
data['A25'][1298] = -1
data['A25'] = data['A25'].astype('float')

# 样本id去掉前面的sample字符转化为数值特征使用
data['样本id'] = data['样本id'].apply(lambda x: int(x.split('_')[1]))

addFeatures = []
data['B14/A1_A3_A4_A19_B1_B12'] = data['B14']/(data['A1']+data['A3']+data['A4']+data['A19']+data['B1']+data['B12'])
data['A6/B14'] = data['A6'] / data['B14']
data['B6/B14'] = data['B6'] / data['B14']
data['B14/A1'] = data['B14'] / data['A1']
addFeatures.append('B14/A1_A3_A4_A19_B1_B12') 
addFeatures.append('A6/B14')
addFeatures.append('B6/B14')
addFeatures.append('B14/A1')
    
data['sumTemperature'] = 0
for i in [6, 8, 10, 12, 15, 17, 21, 25, 27]:
    feat = 'A' + str(i)
    data['sumTemperature'] += data[feat]
addFeatures.append('sumTemperature')
    
data['minB14'] = data['B14'].map(data[data.dataType!=-1].groupby('B14')['收率'].min())
data['maxB14'] = data['B14'].map(data[data.dataType!=-1].groupby('B14')['收率'].max())
data['stdB14'] = data['B14'].map(data[data.dataType!=-1].groupby('B14')['收率'].std())
addFeatures.append('minB14')
addFeatures.append('maxB14')
addFeatures.append('stdB14')
    
# id 分桶
data['idCut10']  = pd.cut(data['样本id'], 10 , labels=False)
data['idCut30']  = pd.cut(data['样本id'], 30 , labels=False)
data['idCut50']  = pd.cut(data['样本id'], 50 , labels=False)
data['idCut100'] = pd.cut(data['样本id'], 100, labels=False)

# id分桶与B14交互
for feat in ['idCut10','idCut30','idCut50','idCut100']:
    data[feat + '/B14'] = data[feat] / data['B14']
    addFeatures.append(feat + '/B14')


data['id//16'] = (data['样本id']) // 16
num = len(data)

features = ['A10', 'B2', 'B14', 'B14/A1']   
data['features_id//16'] = data[features + ['id//16']].apply(lambda x: hash(str(x.tolist())), raw=True, axis=1)
data['newTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].mean())
data['minTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].min())
data['maxTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].max())
data['diffTarget'] = data['maxTarget'] - data['minTarget']
    
windowSliding = pd.DataFrame()
windowSliding['sumTarget'] = np.zeros(num)
windowSliding['sumMinTarget'] = np.zeros(num)
windowSliding['sumMaxTarget'] = np.zeros(num)
for i in range(1,9):
    data['temp'] = (data['样本id'] + i) // 16
    data['features_temp'] = data[features + ['temp']].apply(lambda x: hash(str(x.tolist())), raw=True, axis=1)
    windowSliding['mean'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].mean())
    windowSliding['min'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].min())
    windowSliding['max'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].max())
        
    windowSliding['sumTarget'] += windowSliding['mean']
    windowSliding['sumMinTarget'] += windowSliding['min']
    windowSliding['sumMaxTarget'] += windowSliding['max']
        
data['newTarget'] = (data['newTarget'] + windowSliding['sumTarget'] / i) / 2
data['diffTarget'] = (data['diffTarget'] + (windowSliding['sumMaxTarget'] - windowSliding['sumMinTarget']) / i) / 2

newTarget1 = data.loc[data.dataType == 1 ,'newTarget']
data.drop(['features_id//16','temp','newTarget','minTarget','maxTarget', 'features_temp'], axis=1, inplace=True)

features = ['A10','B2','B14']
data['features_id//16'] = data[features + ['id//16']].apply(lambda x: hash(str(x.tolist())), raw=True, axis=1)
data['newTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].mean())
data['minTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].min())
data['maxTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].max())
data['diffTarget'] = data['maxTarget'] - data['minTarget']
    
    
windowSliding = pd.DataFrame()
windowSliding['sumTarget'] = np.zeros(num)
windowSliding['sumMinTarget'] = np.zeros(num)
windowSliding['sumMaxTarget'] = np.zeros(num)
for i in range(1,9):
    data['temp'] = (data['样本id'] + i) // 16
    data['features_temp'] = data[features + ['temp']].apply(lambda x: hash(str(x.tolist())), raw=True, axis=1)
    windowSliding['mean'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].mean())
    windowSliding['min'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].min())
    windowSliding['max'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].max())
        
    windowSliding['sumTarget'] += windowSliding['mean']
    windowSliding['sumMinTarget'] += windowSliding['min']
    windowSliding['sumMaxTarget'] += windowSliding['max']
        
data['newTarget'] = (data['newTarget'] + windowSliding['sumTarget'] / i) / 2
data['diffTarget'] = (data['diffTarget'] + (windowSliding['sumMaxTarget'] - windowSliding['sumMinTarget']) / i) / 2

newTarget2 = data.loc[data.dataType == 1 ,'newTarget']
data.drop(['features_id//16','temp','newTarget','minTarget','maxTarget', 'features_temp'], axis=1, inplace=True)

features = ['A8','A10','B2','B12','B14']
data['features_id//16'] = data[features + ['id//16']].apply(lambda x: hash(str(x.tolist())), raw=True, axis=1)
data['newTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].mean())
data['minTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].min())
data['maxTarget'] = data['features_id//16'].map(data[data.dataType!=-1].groupby('features_id//16')['收率'].max())
data['diffTarget'] = data['maxTarget'] - data['minTarget']
    
windowSliding = pd.DataFrame()
windowSliding['sumTarget'] = np.zeros(num)
windowSliding['sumMinTarget'] = np.zeros(num)
windowSliding['sumMaxTarget'] = np.zeros(num)
for i in range(1,9):
    data['temp'] = (data['样本id'] + i) // 16
    data['features_temp'] = data[features + ['temp']].apply(lambda x: hash(str(x.tolist())), raw=True, axis=1)
    windowSliding['mean'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].mean())
    windowSliding['min'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].min())
    windowSliding['max'] = data['features_temp'].map(data[data.dataType!=-1].groupby('features_temp')['收率'].max())
        
    windowSliding['sumTarget'] += windowSliding['mean']
    windowSliding['sumMinTarget'] += windowSliding['min']
    windowSliding['sumMaxTarget'] += windowSliding['max']
        
data['newTarget'] = (data['newTarget'] + windowSliding['sumTarget'] / i) / 2
data['diffTarget'] = (data['diffTarget'] + (windowSliding['sumMaxTarget'] - windowSliding['sumMinTarget']) / i) / 2

newTarget3 = data.loc[data.dataType == 1 ,'newTarget']
data.drop(['id//16','features_id//16','temp','newTarget','minTarget','maxTarget', 'features_temp'], axis=1, inplace=True)

newTarget = (newTarget1 + newTarget2 + newTarget3) / 3


# 构造label残差，让模型拟合残差
def GetMeanTarget(x1, x2, x3, x4):
    if x1== -1 and x2 != None:
        x1 = x2
    elif x1== -1 and x2 == None and x3 != None:
        x1 = x3
    elif x1== -1 and x2 == None and x3 == None: 
        x1 = x4
    else:
        x1 = x1
    return x1

print('构造target残差...')
data['B12_B14'] = data['B12'].astype('str') + '_' + data['B14'].astype('str')
data['mean_B12_B14'] = data['B12_B14'].map(data[data.dataType!=-1].groupby('B12_B14')['收率'].mean()).fillna(-1)
data['meanB12'] = data['B12'].map(data[data.dataType!=-1].groupby('B12')['收率'].mean())
data['meanB14'] = data['B14'].map(data[data.dataType!=-1].groupby('B14')['收率'].mean())
train_mean = data[data.dataType!=-1].apply(lambda row:GetMeanTarget(row['mean_B12_B14'],row['meanB12'],row['meanB14'],np.mean(train['收率'])),axis=1)
test_mean = data[data.dataType==-1].apply(lambda row:GetMeanTarget(row['mean_B12_B14'],row['meanB12'],row['meanB14'],np.mean(train['收率'])),axis=1)
newTarget = newTarget.values - train_mean.values
data.drop(['B12_B14','mean_B12_B14','meanB12','meanB14'], axis=1, inplace=True)

# 删除部分的特征
data.drop(['A5','A9','A11','A14','A16','A20','A24','A26','A28','B4', 'B5','B7', '收率','dataType'], axis=1, inplace=True)

# 删除类别占比过大特征
good_features = list(data.columns)
for feat in data.columns:   # 这里可以进行调节
    rate = data[feat].value_counts(normalize=True, dropna=False).values[0]
    if rate > 0.85:
        good_features.remove(feat)
        print(feat)  
        
print(len(good_features))
data = data[good_features]

categorical_columns = [f for f in data.columns if f not in ['样本id', 'diffTarget']]
categorical_columns = [f for f in categorical_columns if f not in addFeatures]
numerical_columns = [f for f in data.columns if f not in categorical_columns]

# LabelEncoder标签编码
for feat in categorical_columns:
    data[feat] = data[feat].map(dict(zip(data[feat].unique(), range(0, data[feat].nunique()))))
# 分离训练集和测试集
train = data[:train.shape[0]]
test  = data[train.shape[0]:]


def GetMeanFeature(train, test, mean_columns):
    # 逻辑有问题的mean
    train['target'] = list(newTarget)
    train['intTarget'] = pd.cut(train['target'], 5, labels=False)
    train = pd.get_dummies(train, columns=['intTarget'])
    li = train.columns[-5:].tolist()
    for f1 in categorical_columns:
        cate_rate = train[f1].value_counts(normalize=True, dropna=False).values[0]
        if cate_rate < 0.70:
            for f2 in li:
                col_name = 'B14_to_'+f1+"_"+f2+'_mean'
                mean_columns.append(col_name)
                order_label = train.groupby([f1])[f2].mean()
                train[col_name] = train['B14'].map(order_label)
                miss_rate = train[col_name].isnull().sum() * 100 / train[col_name].shape[0]
                if miss_rate > 0:
                    train = train.drop([col_name], axis=1)
                    mean_columns.remove(col_name)
                else:
                    test[col_name] = test['B14'].map(order_label)    
    train.drop(li+['target'], axis=1, inplace=True)
    return train, test, mean_columns

mean_columns = []
train, test, mean_columns = GetMeanFeature(train, test, mean_columns)

print(train.shape)
print(test.shape)
print('--------------')

X_train = train[mean_columns+numerical_columns].values  # 数值类型数据不需要编码
X_test = test[mean_columns+numerical_columns].values

print('分界线', data.shape)
print(data.columns)
print(X_train.shape, X_test.shape)
print(len(numerical_columns))
print(len(categorical_columns))

# OneHotEncoder独热编码：只是想让机器区分它们，并无大小比较之意。
enc = OneHotEncoder()
for f in categorical_columns:
    enc.fit(data[f].values.reshape(-1, 1))
    X_train = sparse.hstack((X_train, enc.transform(train[f].values.reshape(-1, 1))), 'csr')  # 添加离散型数据
    X_test = sparse.hstack((X_test, enc.transform(test[f].values.reshape(-1, 1))), 'csr')

y_train = newTarget

print(X_train.shape)
print(X_test.shape)
print('--------------')

xgb_params = {'eta': 0.05, 'max_depth': 10, 'subsample': 0.8, 'colsample_bytree': 0.8,
              'objective': 'reg:linear', 'eval_metric': 'rmse', 'silent': True, 'nthread': 4}

folds = KFold(n_splits=10, shuffle=True, random_state=2018)
oof_xgb = np.zeros(len(train))
predictions_xgb = np.zeros(len(test))

for fold_, (trn_idx, val_idx) in enumerate(folds.split(X_train, y_train)):
    print("fold n°{}".format(fold_+1))
    trn_data = xgb.DMatrix(X_train[trn_idx], y_train[trn_idx])
    val_data = xgb.DMatrix(X_train[val_idx], y_train[val_idx])

    watchlist = [(trn_data, 'train'), (val_data, 'valid_data')]
    clf = xgb.train(dtrain=trn_data, num_boost_round=20000, evals=watchlist, 
                    early_stopping_rounds=200, verbose_eval=False, params=xgb_params)
    oof_xgb[val_idx] = clf.predict(xgb.DMatrix(X_train[val_idx]), ntree_limit=clf.best_ntree_limit)
    predictions_xgb += (clf.predict(xgb.DMatrix(X_test), ntree_limit=clf.best_ntree_limit)+test_mean.values) / folds.n_splits

print("拟合残差 CV score: {:<8.8f}".format(mean_squared_error(oof_xgb + train_mean, target)))

############ 6、保存结果 ############# 
now = datetime.datetime.now()
now = now.strftime('%m-%d-%H-%M')
if not os.path.exists('result'):
    os.mkdir('result')
submission['收率'] = predictions_xgb
submission['收率'] = submission['收率'].apply(lambda x:round(x, 5))
submission.to_csv("./result/hankin_xgb_%s.csv" % now, index=False, header=None)
print('done!')
