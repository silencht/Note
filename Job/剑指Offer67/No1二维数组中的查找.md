

[牛客网原题链接](https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&&tqId=11154&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)

#### **题目描述**

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

```
[
 [1,2,8,9],
 [2,4,9,12],
 [4,7,10,13],
 [6,8,11,15]
]
```

给定 target = 7，返回 true。

给定 target = 3，返回 false。

##### **示例1**

```
输入：7,[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
```

```
返回值：true
```

**说明**

```
存在7，返回true
```

##### **示例2**

```
输入：3,[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
返回值：false
```

**说明**

```
不存在3，返回false
```

#### **1、第一种方法**

右上角逐渐逼近左下角

-   如果当前位置元素比target小，则row++（注：row为行，col为列）
-   如果当前位置元素比target大，则col--
-   如果相等，返回true
-   如果越界了还没找到，说明不存在，返回false

首先判断数组的列`array[0].empty`和行`array.empty()`是否为空，然后取得列值col和行值row，接着将坐标定位到右上角，最后开始循环判断，从右向左，从上向下。

```c++
class Solution {
  public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.empty() || array[0].empty())return false;
        int row = array[0].size(), col = array.size();
        int weight = col - 1, height = 0;
        while (weight >= 0 && height < col) {
            if (array[height][weight] > target) --weight;
            else if(array[height][weight] < target) ++height;
            else return true;
        }
        return false;
    }
};
```
