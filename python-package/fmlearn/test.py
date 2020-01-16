# -*- coding:utf-8 -*-
# @Time : 2020/1/12 17:25
# @Author : naihai
import pandas as pd
from fmlearn import DMatrix, FactorizationMachine

if __name__ == '__main__':
    data = pd.read_csv("house_price_train.txt", sep='\t', header=None)
    X = data[data.columns[1:]]
    y = data[0].values

    _, n_features = X.shape

    fm = FactorizationMachine(0, n_features, 100, 0.1, [0.1, 0.1, 0.1])
    fm.fit(X, y, 100)


