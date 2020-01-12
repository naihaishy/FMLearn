# -*- coding:utf-8 -*-
# @Time : 2020/1/12 17:25
# @Author : naihai
import pandas as pd
from fmlearn import DMatrix

if __name__ == '__main__':
    data = pd.read_csv("E:\Scala\projects\Recommend\data\house_price_train.txt", sep='\t', header=None)
    X = data[data.columns[1:]]
    y = data[0].values

    data = DMatrix(data=X, label=y)

    print(data)
