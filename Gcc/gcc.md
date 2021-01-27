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
  - 机器代码输出文件由`-o`选项指定，这个选项通常在最后给出；
  - 如果省略该选项，输出将被写入`a.out`的默认文件；
  - 如果一个与可执行文件同名的文件已经存在于当前目录中，它将被覆盖；
  - 选项`-Wall`打开所有最常用的编译器警告，建议始终使用此选项！
- 运行命令：`./hello`
- 输出结果：`Hello,world!`

### 2.2 在一个简单的程序中发现错误

- 源文件：bad.c

  ```c
  #include <stdio.h>
  int main (void)
  {
  	printf ("Two plus two is %f\n", 4);
  	return 0;
  }
  ```

- 编译命令：`gcc -Wall  bad.c -o bad`

- 编译警告：

  ```c
  bad.c: In function ‘main’:
  bad.c:4:27: warning: format ‘%f’ expects argument of type ‘double’, but argument 2 has type ‘int’ [-Wformat=]
    printf("Two plus two is %f\n",4);
                            ~^
                            %d
  ```

- 运行命令：`./bad`

- 输出结果：`Two plus two is 0.000000`（实际结果因平台与环境不同而不同）

### 2.3 编译多个源文件

- 源文件

  - 文件1：main.c

    ```c
    #include "hello.h"
    int main (void)
    {
    	hello ("world");
    	return 0;
    }
    ```

  - 文件2：hello.h

    ```c
    void hello (const char * name);
    ```

  - 文件3：hello_fn.c

    ```c 
    #include <stdio.h>
    #include "hello.h"
    void hello (const char * name)
    {
    	printf ("Hello, %s!\n", name);
    }
    ```

- 编译命令：`gcc -Wall main.c hello_fn.c -o newhello`

- NOTE：

  - 头文件‘hello.h’在命令行上的文件列表中没有指定。 源文件中的指令#include “hello.h”指示编译器在适当的位置自动包含它。
  - 啊

- 运行命令：`./newhello`

- 输出结果：`Hello,World!`

### 2.4 独立编译文件

- NOTE：
  - 当程序存储在独立的源文件中时，只有更改过的文件需要在修改源代码后重新编译。 在这种方法中，源文件先被单独编译，然后再连接在一起——这是一个分为两阶段的过程。
  - 在第一阶段，在不创建可执行文件的情况下编译文件。第一阶段的结果被称为**对象文件**，在使用GCC时使用扩展名`.o`表示。
  - 在第二阶段，**对象文件**由一个名为**链接器**的单独程序合并在一起。链接器将所有对象文件组合在一起，创建一个**可执行文件**。
  - 对象文件包含机器代码，代码中任何引用了其他文件中函数（或变量）的内存地址的地方都暂未定义（缺失）。 这就允许在不直接引用其他文件的情况下编译源文件。 链接器在生成可执行文件时填充这些缺失的地址。

#### 2.4.1 从源文件创建一个对象文件

- 编译命令：`gcc -Wall -c main,c`
  - `-c`选项指定一个源文件编译为对象文件，在这种情况下，不需要`-o`选项来指定输出文件的名称。当使用`-c`编译时，编译器会自动创建一个对象文件，其名称与源文件相同，使用`.o`而不是原始扩展名。
  - 这将生成一个对象文件main.o，其中包含主函数的机器代码。它包含对外部函数hello的引用，但在这个阶段，对象文件中留下了相应缺失的内存地址（稍后将通过**链接**来填写）。
- 编译命令：`gcc -Wall -c hello_fn.c`
  - 生成对象文件hello_fn.o

#### 2.4.2 从对象文件创建可执行文件

创建可执行文件的最后一步是使用gcc将对象文件**链接**在一起，并填写外部函数的缺失地址。 要将对象文件链接在一起，只需使用命令：

- 链接命令：`gcc main.o hello_fn.o -o hello`
- NOTE：
  - 不需要`-Wall`选项的原因之一是每个单个源文件已经成功编译为对象文件了。一旦成功编译了源文件，链接是一个明确的过程，它要么成功，要么失败（只有在有无法解决的引用时才会失败）。
  - 要执行链接步骤，gcc使用链接器ld，这是一个单独的程序。 在GNU系统上使用GNU链接器：GNU ld。 其他系统可以使用GNU linker with GCC，或它们自己的链接器。通过运行链接器，gcc从对象文件中创建可执行文件。

- 运行命令：`./hello`
- 输出结果：`Hello,World!`

#### 2.4.3 对象文件的链接顺序

在类Unix系统中，编译器和链接器的一般行为是在命令行指定的对象文件中从左到右搜索外部函数。**这意味着包含某函数定义的对象文件应该出现在调用该函数的任何文件之后。**

因此，2.4.2节编译命令中，hello_fn.o应该放在main.o后面。

大多数当前编译器和链接器将搜索所有对象文件，而不管顺序如何，但由于并非所有编译器都这样做，所以最好遵循从左到右排序对象文件的约定。

### 2.5 重新编译和重新链接

- 源文件：main.c
  ```c
  #include "hello.h"
  int main (void)
  {
  	hello ("everyone"); /* changed from "world" */
  	return 0;
  }
  ```

- 重新编译命令：`gcc -Wall -c main.c`

- 重新链接命令：`gcc main.o hello_fn.o -o hello`
- NOTE：
  - 产生新的main.o文件后，没有必要为hello_fn.c编译一个新的对象文件，因为该文件和它所依赖的相关文件，如头文件，都没有发生更改。
  - 如果文件hello_fn.c被修改，我们可以重新编译hello_fn.c来创建一个新的对象文件hello_fn.o，并将其与现有文件main.o重新链接【但如果函数的原型发生了变化，就有必要修改和重新编译使用它的所有其他源文件】。
  - 一般来说，链接比编译更快——在具有许多源文件的大型项目中，只重新编译已修改的文件可以节省大量时间。

- 运行命令：`./hello`
- 输出结果：`Hello,everyone!`

### 2.6 链接外部库（静态库）

库是可以链接到程序中的预编译对象文件的集合。 库最常用的是提供系统函数，比如C数学库中找到的平方根函数sqrt。

库通常存储在具有扩展名`.a`的特殊存档文件中，称为**静态库**。它们是用一个单独的工具GNU archiver (ar)从对象文件中创建的，链接器在编译时用它们解析对函数的引用。

- NOTE：

  标准系统库通常存储在'/usr/lib'、'/usr/lib64'、'/lib'或'/lib64'中。如C数学库一般存储在'/usr/lib/libm.a'（腾讯云服务器-Ubuntu18.04系统中，该文件位于'/usr/lib/x86_64-linux-gnu'目录下），相应的原型声明存储在'/usr/include/math.h'

- 源文件：calc.c

  ```c
  #include <math.h>
  #include <stdio.h>
  int main (void)
  {
  	double x = sqrt (2.0);
  	printf ("The square root of 2.0 is %f\n", x);
  	return 0;
  }
  ```

- （书中编译器）**编译命令**：`gcc -Wall calc.c -o calc`

  （实际测试可以顺利编译通过，可能是新版本编译器已经智能的为我们寻找到库并隐式链接好了）

- 编译警告：

  ```
  /tmp/ccbR6Ojm.o: In function ‘main’:
  /tmp/ccbR6Ojm.o(.text+0x19): undefined reference to ‘sqrt’
  ```

- NOTE：
  - 书中：出现编译错误的原因是，没有链接外部数学库libm.a，对sqrt函数的引用就无法解决。 函数sqrt在程序源代码和默认库libc.a（如printf就在这个库中）中没有定义，除非显式选择它，否则编译器不会链接到文件libm.a（实际我的gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0可以顺利编译通过）。
- 一个比较麻烦的链接编译命令：`gcc -Wall calc.c /usr/lib/x86_64-linux-gnu/libm.a -o calc`

![](https://silencht.oss-cn-beijing.aliyuncs.com/img/gcc.png)

​		libm.a库包含所有数学函数的对象文件，如sin、cos、exp、log和sqrt。 链接器通过搜索找到包含sqrt函数的对象文件。一旦找到了sqrt函数的对象文件，就可以链接主程序并生成完整的可执行文件。

​		为了避免在命令行上指定长路径的需要，编译器提供了一个用于连接库的捷径选项`-l`。 例如，下面的命令：

- 便捷链接编译命令：`gcc -Wall calc.c -lm -o calc`
  - 一般来说，编译器选项 ' -l *NAME* ' 将尝试将对象文件与标准库目录中的库文件 lib*NAME*.a 链接起来。

#### 2.6.1 库的链接顺序

库的链接顺序与对象文件链接顺序遵循相同的规则：**从左到右搜索它们——包含某函数定义的库应该出现在使用它的任何源文件或对象文件之后**。 这包括用快捷键‘-l’选项指定的库，如下面的命令所示：

- 编译命令：` gcc -Wall calc.c -lm -o calc `（正确的顺序）

- 编译命令：` gcc -Wall -lm calc.c -o calc`（错误的顺序，但是我的环境中，编译器不会编译错误）

  - ```
    main.o: In function ‘main’:
    main.o(.text+0xf): undefined reference to ‘sqrt’
    ```

- NOTE：
  - 当使用多个库时，应该对库本身遵循相同的约定：调用另一个库中定义的外部函数的库应出现在包含该函数的库之前。
  - 至于对象文件，大多数当前编译器将搜索所有库，而不管顺序如何。 然而，由于并非所有编译器都这样做，所以最好遵循从左到右排序库的惯例

### 2.7 使用库的头文件

在使用库时，必须包含适当的头文件，以便声明函数参数并返回具有正确类型的值。

- 源文件：badpow.c

  ```c
  #include <stdio.h>
  int main (void)
  {
  	double x = pow (2.0, 3.0);
  	printf ("Two cubed is %f\n", x);
  	return 0;
  }
  ```
  - 该文件缺乏 #include <math.h> 语句

- 编译命令：`gcc badpow.c -lm`

- 运行命令：`./a.out`

- 输出结果：`Two cubed is 2.851120`（根据特定的平台和环境，显示的实际输出可能会有所不同 ）

  - 结果错误，正确应为8。因为调用pow的参数和返回值是用不正确的类型传递的

- 编译命令：`gcc -Wall badpow.c -lm`

- 编译警告：

  ```
  badpow.c: In function ‘main’:
  badpow.c:5: warning: implicit declaration of function ‘pow’
  ```

## 3 编译选项

本章描述GCC中可用的其他常用编译器选项。 这些选项控制诸如：定位库和文件的搜索路径、使用附加警告和诊断、预处理器宏和特定版本的C语言的特性。

### 3.1 设置搜索路径

在上一章中，我们看到了如何使用快捷选项`-lm`和头文件math.h 链接C标准数学库libm.a中带有函数的程序。

而使用库头文件编译程序时常见的问题是：

```
FILE.h: No such file or directory
```

如果该头文件不存在于gcc使用的标准头文件目录中，则会发生上述情况。 库也会出现类似的问题：

```
/usr/bin/ld: cannot find library
```

同样的，如果用于链接的库不存在于gcc使用的标准库目录中，则会发生上述情况。

默认情况下，gcc搜索以下目录的头文件：

```
/usr/local/include/
/usr/include/
```

以及以下目录的库文件：

```
/usr/local/lib/
/usr/lib/
```

头文件的目录列表通常被称为**包含路径**，库的目录列表被称为**库搜索路径**或**链接路径**。

这些路径上的目录是按顺序搜索的，在上面的两个列表中从前到后搜索。默认的搜索路径还可能包括附加的系统相关目录或特定站点（site- specific）的目录，以及GCC本身的安装目录。 例如，在64位平台上，默认情况下还可以搜索附加的 'lib64' 目录。例如，在`/usr/local/include`中找到的头文件优先于在`/usr/include`中具有相同名称的文件’。 类似地，在`/usr/local/lib`中找到的库优先于在`/usr/lib`中同名的库。

当在其他目录中安装其他库时，需要扩展搜索路径，以便找到库。 

**编译器选项`-I`和`-L`分别在包含路径和库搜索路径的开头添加新目录。**

#### 3.1.1 搜索路径示例



