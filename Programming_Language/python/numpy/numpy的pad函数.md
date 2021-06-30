### numpy.pad

##### 例：二维数组填充

```python
import numpy as np
Matrix = np.arange(1,7).reshape(2,3)    #原始输入数组A
np.pad(Matrix,((1,1),(1,2)),'constant',constant_values = (0,0)) 
```

![1](https://silencht.oss-cn-beijing.aliyuncs.com/img/1.png)

`np.pad(Matrix,((1,1),(1,2)),'constant',constant_values = (0,0))` 表示：在二维数组Matrix的边缘填充constant_values指定的数值。

- （1,1）表示在Matrix的第[0]轴填充（二维数组中，0轴表示行），即在0轴前面填充1个宽度的0，比如数组Matrix中的1,2,3两个元素前面各填充了一行0，在4,5,6下面填充了一行0。
- （1,2）表示在Matrix的第[1]轴填充（二维数组中，1轴表示列），即在1轴前面填充1个宽度的0，后面填充2个宽度的0。
-    constant_values表示填充值，且(axis0，axis1)的填充值等于（0,0）

[原文链接](https://blog.csdn.net/Tan_HandSome/article/details/80296827)

##### 例：官方某实例代码

```python
a = [[1, 2], [3, 4]]
np.pad(a, ((3, 2), (2, 3)), 'minimum')
array([[1, 1, 1, 2, 1, 1, 1],
       [1, 1, 1, 2, 1, 1, 1],
       [1, 1, 1, 2, 1, 1, 1],
       [1, 1, 1, 2, 1, 1, 1],
       [3, 3, 3, 4, 3, 3, 3],
       [1, 1, 1, 2, 1, 1, 1],
       [1, 1, 1, 2, 1, 1, 1]])
```

[官方代码链接](https://numpy.org/doc/stable/reference/generated/numpy.pad.html)