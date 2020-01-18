# -*- coding:utf-8 -*-
# @Time : 2020/1/12 17:25
# @Author : naihai
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from fmlearn import DMatrix, FactorizationMachine

if __name__ == '__main__':
    data = pd.read_csv("house_price_train.txt", sep='\t', header=None)
    X = data[data.columns[1:]]
    y = data[0].values

    X_train_, X_test_, y_train_, y_test_ = train_test_split(X, y, test_size=0.2, random_state=12)
    print(X_train_.shape)

    # 预处理
    scaler = StandardScaler()
    scaler.fit(X)
    X_train_ = scaler.transform(X_train_)
    X_test_ = scaler.transform(X_test_)

    _, n_features = X.shape

    fm = FactorizationMachine(0, n_features, 100, 0.0000001, [0.1, 0.1, 0.1])
    fm.fit(X_train_, y_train_, 100)


