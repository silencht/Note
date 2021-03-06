## 1. Code

### 4

[collections](../../Language/python/basic/collections.md)

### 60 values()

#### 描述

Python 字典 values() 方法返回一个迭代器，可以使用 list() 来转换为列表，列表为字典中的所有值。

#### 语法

values()方法语法：

```python
dict.values()
```

#### 参数

- NA。

#### 返回值

返回迭代器。

#### 实例

以下实例展示了 values() 方法的使用方法：

```python
#!/usr/bin/python3
 
dict = {'Sex': 'female', 'Age': 7, 'Name': 'Zara'}
print ("字典所有值为 : ",  list(dict.values()))
```

以上实例输出结果为：

```python
字典所有值为 :  ['female', 7, 'Zara']
```

```python
#供理解的实例
from collections import OrderedDict

class SimpleConvNet:
        def __init__(self):
        # 生成层
            self.x = 0
            self.layers = OrderedDict()
            self.layers['Conv1'] = Convolution1()
            self.layers['Conv2'] = Convolution2()

        def predict(self):
            print(self.layers.values())
            for layer in self.layers.values():
                print(layer)
                self.x = layer.conv()
                print(self.x)

class Convolution1():
    def conv(self):
        print("i am conv1!")
        return 1

class Convolution2():
    def conv(self):
        print("i am conv2!")
        return 2

sc = SimpleConvNet()
sc.predict()

#输出
odict_values([<__main__.Convolution1 object at 0x0000015E169E92E0>,<__main__.Convolution2 object at 0x0000015E16A123D0>])
<__main__.Convolution1 object at 0x0000015E169E92E0>
i am conv1!
1
<__main__.Convolution2 object at 0x0000015E16A123D0>
i am conv2!
2
```



## 2. Image

![](https://silencht.oss-cn-beijing.aliyuncs.com/img/20200210175417839.png)

## 3. [Comments](https://www.pythonf.cn/read/5014)

```python
import sys,os
sys.path.append(os.pardir)
import numpy as np
from layers import *   # 导入加权和层类Affine、激活函数层类ReLU、卷积层类Convolution、池化层类Pooling
from collections import OrderedDict  # 导入有序字典类OrderedDict


# 三层卷积神经网络的实现
class SimpleConvNet:
	# 初始化函数，入口参数为输入数据的各维度值、滤波器参数（W1）、隐藏层2的神经元数目、输出层的神经元数目、初始化时权重的标准差
	def __init__(self,input_dim=(1,28,28),conv_param={'filter_num':30,'filter_size':5,'pad':0,'stride':1},hidden_size=100,output_size=10,weight_init_std=0.01):
		 
		# 第一步 将卷积层的超参数提取出来（方便后面使用），然后计算卷积层的输出大小
		filter_num = conv_param['filter_num']    # 滤波器个数30
		filter_size = conv_param['filter_size']  # 滤波器大小5*5
		filter_pad = conv_param['pad']           # 滤波器填充0
		filter_stride = conv_param['stride']     # 滤波器步幅1

		input_size = input_dim[1] # 输入数据的大小28
		conv_output_size = (input_size - filter_size + 2*filter_pad) / filter_stride +1 # 根据公式计算卷积层输出数据大小
		pool_output_size = int(filter_num*(conv_output_size/2)*(conv_output_size/2))    # 根据公式计算池化层输出数据大小
		
		# 第二步 初始化各层权重
		self.params = {}                          # 定义实例变量params为字典型变量
		self.params['W1'] = weight_init_std * np.random.randn(filter_num,input_dim[0],filter_size,filter_size) # 第一层权重W1初始化为（滤波器个数*通道数*滤波器高度*滤波器宽度）形状的高斯分布
		self.params['b1'] = np.zeros(filter_num)  # 第一层偏置b1初始化为长度为卷积层输出数据通道数的一维全0数组
		
		self.params['W2'] = weight_init_std * np.random.randn(pool_output_size,hidden_size) # 第二层权重W2初始化为（池化层输出数据大小*隐藏层2神经元数目）形状的高斯分布
		self.params['b2'] = np.zeros(hidden_size) # 第二层偏置b2初始化为长度为隐藏层2神经元数目的一维全0数组
		
		self.params['W3'] = weight_init_std * np.random.randn(hidden_size,output_size) # 第三层权重W3初始化为（隐藏层2神经元数目*输出层神经元数目）形状的高斯分布
		self.params['b3'] = np.zeros(output_size) # 第三层偏置b3初始化为长度为输出层神经元数目的一维全0数组
		
		# 第三步 生成搭建神经网络的层
		self.layers = OrderedDict() # 定义实例变量layers为有序字典型变量
		# 隐藏层1
		self.layers['Conv1'] = Convolution(self.params['W1'],self.params['b1'],conv_param['stride'],conv_param['pad']) # 创建卷积层1
		self.layers['Relu1'] = ReLU() # 创建激活函数ReLU层1
		self.layers['Pool1'] = Pooling(pool_h=2,pool_w=2,stride=2) # 创建池化层1
		# 隐藏层2
		self.layers['Affine1'] = Affine(self.params['W2'],self.params['b2']) # 创建加权和层1
		self.layers['Relu2'] = ReLU()  # 创建激活函数ReLU层2
		# 输出层
		self.layers['Affine2'] = Affine(self.params['W3'],self.params['b3']) # 创建加权和层2
		self.last_layer = SoftmaxWithLoss() # 创建softmaxwithloss层
	
	# 推理函数，入口参数为输入数据
	def predict(self,x):
		for layer in self.layers.values(): # 依次取实例变量layers中的每一层
			x = layer.forward(x)           # 将前一层的输出作为后一层的输入，进行正向传播，最后得到推理结果y的加权和形式
		return x
	
	# 损失函数，入口参数为输入图像数据和正确解标签
	def loss(self,x,t):    
		y = self.predict(x)                # 调用推理函数得到推理结果的加权和形式
		return self.last_layer.forward(y,t)# 进一步调用最后一层SoftmaxWithLoss的前向函数，得到推理结果的概率形式和损失函数值，这里只返回损失函数值
	
    # 梯度函数，入口参数同loss	
	def gradient(self,x,t):
		# 正向传播
		self.loss(x,t)  # 得到反向传播所需的各个中间变量
		
		# 反向传播
		dout = 1
		dout = self.last_layer.backward(dout)
		
		layers = list(self.layers.values())
		layers.reverse()
		for layer in layers:
			dout = layer.backward(dout)
		
		# 设定梯度
		grads = {}
		grads['W1'] = self.layers['Conv1'].dW
		grads['b1'] = self.layers['Conv1'].db
		grads['W2'] = self.layers['Affine1'].dW
		grads['b2'] = self.layers['Affine1'].db
		grads['W3'] = self.layers['Affine2'].dW
		grads['b3'] = self.layers['Affine2'].db
		
		return grads
	# 精度函数，入口参数比loss多了batch_size(批数量大小)
	def accuracy(self, x, t, batch_size=100):
		if t.ndim != 1 : t = np.argmax(t, axis=1) # 如果正确解标签是one-hot形式，就将其改为简单解形式
        
		acc = 0.0 # 识别正确数的初始值设为0.0
        
		for i in range(int(x.shape[0] / batch_size)): # 对总共600份批数据，一份一份求识别正确的数目，并求和
			tx = x[i*batch_size:(i+1)*batch_size]
			tt = t[i*batch_size:(i+1)*batch_size]
			y = self.predict(tx)
			y = np.argmax(y, axis=1)
			acc += np.sum(y == tt) 
        
		return acc / x.shape[0]   # 识别正确数/数据总数，返回识别精度
	
```