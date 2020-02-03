.. FMLearn documentation master file, created by
   sphinx-quickstart on Mon Feb  3 17:51:08 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

欢迎使用 FMLearn !
===================================

FMLearn 是一款高性能的，易用的，并且可扩展的机器学习算法库。

快速开始
----------------------------------

安装 FMLearn
^^^^^^^^^^^^^


Python 样例
^^^^^^^^^^^^^^

.. code-block:: python

   import fmlearn as fl
   X, y = load_digits(n_class=2, return_X_y=True)
   y[y == 0] = -1
   X = normalize(X)

   X_train_, X_test_, y_train_, y_test_ = train_test_split(X, y, test_size=0.2, random_state=12)
   print(X_train_.shape)

   _, n_features = X.shape

   fl.FactorizationMachine.set_log_level(0)
   fm = fl.FactorizationMachine(1, n_features, 100,
                              0.0001, [0.1, 0.1, 0.1],
                              0.0, 0.1,
                              True, True)
   fm.fit(X_train_, y_train_, 1000)

目录
----
.. toctree::
   :maxdepth: 2

   install


* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
