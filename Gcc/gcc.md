## 2 编译一个C程序

### 2.1 编译一个简单的C程序

- 源文件：hello.c

  ```c
  #include<stdio.h>
  
  int main(void)
  {
          printf("Hello,world!\n");
          return 0;
  }
  ```

- 编译命令：`gcc -Wall hello.c -o hello`

- NOTE：
  - 机器代码输出文件由`-o`选项指定，这个选项通常在最后给出
  - 如果省略该选项，输出将被写入`a.out`的默认文件
  - 如果一个与可执行文件同名的文件已经存在于当前目录中，它将被覆盖
  - 选项`-Wall`打开所有最常用的编译器警告，建议始终使用此选项！
- 输出命令：`./hello`
- 输出结果：`Hello,world!`

### 2.2 在一个简单的程序中发现错误

