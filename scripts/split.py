# -*- coding:utf-8 -*-
# @Time : 2020/2/23 17:34
# @Author : naihai

import pandas as pd
from sklearn.model_selection import train_test_split

if __name__ == '__main__':
    df = pd.read_csv("E:\\Projects\\CLion\\Projects\\FMLearn\\python-package\\fmlearn\\house_price_train.txt", sep='\t')

    train, valid = train_test_split(df, test_size=0.2)

    train_df = pd.DataFrame(train)
    valid_df = pd.DataFrame(valid)

    train_df.to_csv("house_price_train.txt", sep='\t', header=False, index=False)
    valid_df.to_csv("house_price_valid.txt", sep='\t', header=False, index=False)
