[牛客网原题链接](https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&&tqId=11155&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)

#### **题目描述**

请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

#### **1、首先统计出长度，然后从后向前替换**

由于函数返回为void，说明此题不能另外开辟数组，需要in-place操作。我们知道字符串的遍历无非是从左到右和从右到左两种。
1）如果从左到右，会发现如果遇到空格，会将原来的字符覆盖。于是，此方法不行。
2）那么就考虑从右向左，遇到空格，就填充“02%“，否则将原字符移动应该呆的位置。

首先获取空格个数，然后计算替换后的字符串总长度（=原字符串长度+空格个数*2），接下来从后向前判断是否为空格，若不为空格就原样填充，若为空格就反向填充20%。

```c++
void replaceSpace(char *str,int length) {//int length是指当前的长度
    if (str == nullptr || length <= 0) return; // 养成良好习惯，判空操作
    int spaceCount = 0;
    int totalLen = length;
    for(int i = 0; i < length; ++i){
        if(str[i] == ' ') spaceCount++;
    }
    if (!cnt) return; // 没有空格，直接返回
    totalLen += spaceCount*2;
    
    for(int i = length-1; i>=0 &&totalLen != i; --i){//当 i = totalLen的时候说明前面已经
        //都没有空格了，可以节约一部分时间，而不是一直赋值下去
        if(str[i] != ' ') str[--totalLen] = str[i];
        else{
            str[--totalLen] = '0';
            str[--totalLen] = '2';
            str[--totalLen] = '%';                
        }

    }
}
```
