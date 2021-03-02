### numpy.frombuffer

#### [菜鸟教程](https://www.runoob.com/numpy/numpy-array-from-existing-data.html)

numpy.frombuffer 用于实现动态数组。

numpy.frombuffer 接受 buffer 输入参数，以流的形式读入转化成 ndarray 对象。

```python
numpy.frombuffer(buffer, dtype = float, count = -1, offset = 0)
```

> **注意：**buffer 是字符串的时候，Python3 默认 str 是 Unicode 类型，所以要转成 bytestring 在原 str 前加上 b。

参数说明：

|  参数  | 描述                                     |
| :----: | :--------------------------------------- |
| buffer | 可以是任意对象，会以流的形式读入。       |
| dtype  | 返回数组的数据类型，可选                 |
| count  | 读取的数据数量，默认为-1，读取所有数据。 |
| offset | 读取的起始位置，默认为0。                |

##### Python3.x 实例

```python
import numpy as np 

s =  b'Hello World' 
a = np.frombuffer(s, dtype =  'S1')  
print (a)
```

输出结果为：

```python
[b'H' b'e' b'l' b'l' b'o' b' ' b'W' b'o' b'r' b'l' b'd']
```

#### [NumPy官方](https://numpy.org/doc/stable/reference/generated/numpy.frombuffer.html)

```python
numpy.frombuffer(buffer, dtype = float, count = -1, offset = 0)
```

**Interpret a buffer as a 1-dimensional array.**

- Parameters

  **buffer**：**buffer_like**

  ​				An object that exposes the buffer interface.

  **dtype**： **data-type, optional**

  ​				optionalData-type of the returned array; default: float.

  **count**：**int, optional**

  ​				Number of items to read. `-1` means all data in the buffer.

  **offset**：**int, optional**

  ​				Start reading the buffer from this offset (in bytes); default: 0.