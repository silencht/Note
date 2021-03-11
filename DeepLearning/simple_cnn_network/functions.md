## 1. Code

### 5 identity

恒等函数

### 9 step

阶跃函数（此为参数支持numpy数组版本）

```python
#最简单版本，但是x只能接受浮点数，不允许参数为numpy数组
def step_function(x):
    if x > 0:
        return 1
    else:
        return 0
#参数支持numpy数组版本
def step_function(x):
    y = x > 0
    return y.astype(np.int)
```

```python
>>> import numpy as np
x = np.array([-1.0,1.0,2.0])
>>>x
array([-1.,1.,2.])
>>>y = x > 0
>>>y
array([False,True,True],dtype=bool)
>>>y = y.astype(np.int)
>>>y
array([0,1,1])
```

### 13 sigmoid

激活函数，本函数通过广播特性支持numpy数组：
$$
\displaystyle S(t)={\frac {1}{1+e^{-t}}}
$$

### 14 relu

<img src="https://silencht.oss-cn-beijing.aliyuncs.com/img/Ramp_function.svg.png" alt="Ramp_function.svg" style="zoom: 10%;" />

### 31 softmax

此函数负责将输入转化为[0,1]区间概率形式的输出。

假设输出层共n个神经元，
$$
{\displaystyle y_{k} = {\frac {e^{a_{k}}}{\sum _{i=1}^{n}e^{a_{i}}}}}
$$

```python
#版本1，缺陷：指数值过大会发生溢出
def softmax(a):
    exp_a = np.exp(a)
    sum_exp_a = np.sum(exp_a)
    y = exp_a / sum_exp_a
    
    return y
```

根据如下公式改进：

<img src="https://silencht.oss-cn-beijing.aliyuncs.com/img/image-20210303143112164.png" alt="image-20210303143112164" style="zoom: 80%;" />

根据上式，分子分母同时加减某常数值，结果不变，因此分子分母同时减去输入信号中的最大值：

```python
#改良溢出缺陷版,但代码只适合一维
def softmax(a):
    c = np.max(a)
    exp_a = np.exp(a-c) #溢出对策
    sum_exp_a = np.sum(exp_a)
    y = exp_a / sum_exp_a
    
    return y
```

```python
#考虑到二维的最终版
def softmax(x):
    if x.ndim == 2:
        x = x.T
        x = x - np.max(x, axis=0)
        y = np.exp(x) / np.sum(np.exp(x), axis=0)
        return y.T 

    x = x - np.max(x) # 溢出对策
    return np.exp(x) / np.sum(np.exp(x))
```

```python
#帮助理解上述代码的实例：
b = np.array([[1,2,3],[4,5,6],[7,8,9]])
print(b)
print(np.max(b, axis=0))
b = b.T
print(b)
print(np.max(b, axis=0))
#输出
[[1 2 3]
 [4 5 6]
 [7 8 9]]
[7 8 9]
[[1 4 7]
 [2 5 8]
 [3 6 9]]
[3 6 9]
```



