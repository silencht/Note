## 1. Code

### 25

#### lower

##### 描述

[Python lower() 方法](https://www.runoob.com/python3/python3-string-lower.html)转换字符串中所有大写字符为小写。

##### 语法

lower()方法语法：

```python
str.lower()
```

##### 参数

- 无

##### 返回值

返回将字符串中所有大写字符转换为小写后生成的字符串。

##### 实例

以下实例展示了lower()的使用方法：

```python
#!/usr/bin/python3

str = "Runoob EXAMPLE....WOW!!!"

print( str.lower() )
```

以上实例输出结果如下：

```python
runoob example....wow!!!
```

#### **optimizer_param

[python函数的参数之调用函数时带星号](../../Language/python/basic/函数的参数.md)

## 2. [Comments](https://www.pythonf.cn/read/5014)

```python
# coding: utf-8

import numpy as np
from optimizer import *

class Trainer:
    """进行神经网络的训练的类
    """
    def __init__(self, network, x_train, t_train, x_test, t_test,
                 epochs=20, mini_batch_size=100,
                 optimizer='SGD', optimizer_param={'lr':0.01}, 
                 evaluate_sample_num_per_epoch=None, verbose=True):     #evaluate_sample_num_per_epoch是对于每个epoch，测试样本的数量，默认为整个数据集。verbose=True就打印出提示信息
				 
        self.network = network
        self.verbose = verbose
        self.x_train = x_train
        self.t_train = t_train
        self.x_test = x_test
        self.t_test = t_test
        self.epochs = epochs
        self.batch_size = mini_batch_size
        self.evaluate_sample_num_per_epoch = evaluate_sample_num_per_epoch

        # 确定优化器
        optimizer_class_dict = {'sgd':SGD, 'momentum':Momentum, 'nesterov':Nesterov,
                                'adagrad':AdaGrad, 'rmsprpo':RMSprop, 'adam':Adam}
        self.optimizer = optimizer_class_dict[optimizer.lower()](**optimizer_param)   # 这里利用了可变参数，实际上相当于self.optimizer = Adam(lr=0.01),见上文25行代码解释
        
        self.train_size = x_train.shape[0]  # 训练大小设为训练数据集总图片数
        self.iter_per_epoch = max(self.train_size / mini_batch_size, 1) # 求出每个epoch的训练次数
        self.max_iter = int(epochs * self.iter_per_epoch) # 求出总训练次数
        self.current_iter = 0  # 初始化当前训练次数和epoch数
        self.current_epoch = 0
        
        
        self.train_acc_list = [] # 初始化训练数据精度列表和测试数据精度列表，用于绘图
        self.test_acc_list = []

    def train_step(self): # 单次训练函数
	
        # 从训练数据中随机选择一份批数据	
        batch_mask = np.random.choice(self.train_size, self.batch_size)
        x_batch = self.x_train[batch_mask]
        t_batch = self.t_train[batch_mask]
        
        # 计算训练参数的梯度
        grads = self.network.gradient(x_batch, t_batch)
		
        # 根据梯度利用优化器更新训练参数
        self.optimizer.update(self.network.params, grads)
        
        if self.current_iter % self.iter_per_epoch == 0:  # 完成一个epoch，当前epoch数加1，计算并记录当前模型对训练数据和测试数据的识别精度
            self.current_epoch += 1
            
            x_train_sample, t_train_sample = self.x_train, self.t_train
            x_test_sample, t_test_sample = self.x_test, self.t_test
            if not self.evaluate_sample_num_per_epoch is None:
                t = self.evaluate_sample_num_per_epoch
                x_train_sample, t_train_sample = self.x_train[:t], self.t_train[:t]
                x_test_sample, t_test_sample = self.x_test[:t], self.t_test[:t]
                
            train_acc = self.network.accuracy(x_train_sample, t_train_sample)
            test_acc = self.network.accuracy(x_test_sample, t_test_sample)
            self.train_acc_list.append(train_acc)
            self.test_acc_list.append(test_acc)

            if self.verbose: print("=== epoch:" + str(self.current_epoch) + ", train acc:" + str(train_acc) + ", test acc:" + str(test_acc) + " ===")
			
			
        self.current_iter += 1 # 完成一次训练，当前训练次数加一

    def train(self):
        for i in range(self.max_iter):   # 依次完成所有训练
            self.train_step()
            print("完成训练",i)

        test_acc = self.network.accuracy(self.x_test, self.t_test)    # 完成所有训练后测试并打印出当前模型对测试数据的识别精度
        if self.verbose:
            print("=============== Final Test Accuracy ===============")
            print("test acc:" + str(test_acc))
```

