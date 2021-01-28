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

- **编译命令**（书中编译器）：`gcc -Wall calc.c -o calc`

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

这些路径上的目录是按顺序搜索的，在上面的两个列表中从前到后搜索。默认的搜索路径还可能包括附加的系统相关目录或特定站点（site- specific）的目录，以及 gcc 本身的安装目录。 例如，在64位平台上，默认情况下还可以搜索附加的 'lib64' 目录。例如，在`/usr/local/include`中找到的头文件优先于在`/usr/include`中具有相同名称的文件’。 类似地，在`/usr/local/lib`中找到的库优先于在`/usr/lib`中同名的库。

当在其他目录中安装其他库时，需要扩展搜索路径，以便找到库。 

**编译器选项`-I`和`-L`分别在包含路径和库搜索路径的开头添加新目录。**

#### 3.1.1 搜索路径示例

下面的示例程序使用一个库，该库可以作为系统上的附加包安装——GNU数据库管理库(GDBM)。 GDBM库将**键-值**对存储在DBM文件中——这是一种数据文件类型，允许通过**键**（任意字符序列)存储和索引**值**。

- 源文件：dbmain.c

  ```c
  #include <stdio.h>
  #include <gdbm.h>
  int	main (void)
  {
  	GDBM_FILE dbf;
  	datum key = { "testkey", 7 }; /* key, length */
  	datum value = { "testvalue", 9 }; /* value, length */
  	printf ("Storing key-value pair... ");
  	dbf = gdbm_open ("test", 0, GDBM_NEWDB, 0644, 0);
  	gdbm_store (dbf, key, value, GDBM_INSERT);
  	gdbm_close (dbf);
  	printf ("done.\n");
  	return 0;
  }
  ```

- NOTE：

  程序使用头文件gdbm.h和库libgdbm.a。 如果库已安装在‘/usr/local/lib’的默认位置，头文件在‘/usr/local/include’中，则可以使用以下简单命令编译程序：

- 编译命令：`gcc -Wall dbmain.c -lgdbm`

- NOTE：

  如果GDBM的头文件和库所在的两个目录都是默认的 gcc **包含路径**和**链接路径**的一部分，那么上面的命令可以成功编译。

  但是，如果GDBM已经安装在不同的位置，尝试编译程序将会产生以下错误：`dbmain.c:1: gdbm.h: No such file or directory`。

  例如，如果GDBM包的1.8.3版本安装在目录‘/opt/gdbm-1.8.3’下，则头文件的位置将是'/opt/gdbm-1.8.3/include/gdbm.h'。这不是默认的 gcc **包含路径**的一部分。 

  此时，使用命令行选项`-I`将适当的目录添加到**包含路径**允许编译程序，但不链接的话：

- 编译命令：`gcc -Wall -I/opt/gdbm-1.8.3/include dbmain.c -lgdbm`

- 编译警告：

  ```shell
  /usr/bin/ld: cannot find -lgdbm 
  collect2: ld returned 1 exit status
  ```

- NOTE：

  包含库的目录在**链接路径**中仍然缺失。可以使用以下选项添加到链接路径中：`-L/opt/gdbm-1.8.3/lib/`

- 编译命令：`gcc -Wall -I/opt/gdbm-1.8.3/include -L/opt/gdbm-1.8.3/lib dbmain.c -lgdbm`

- NOTE：

  请注意，不要将头文件的**绝对路径**放在源代码中的#include语句中，因为这可能会影响源程序在其他系统上编译。 应该始终使用`-I`选项或`INCLUDE_PATH`环境变量来设置头文件的**包含路径**。

#### 3.1.2 环境变量

头文件和库的搜索路径也可以通过shell中的**环境变量**来控制。 

其他目录可以使用环境变量`C_INCLUDE_PATH`(对于C头文件)或`CPLUS_INCLUDE_PATH`(对于C头文件)将其添加到**包含路径**中。 例如，下面的命令将在编译C程序时向**包含路径**添加‘/opt/gdbm-1.8.3/include'

- 向环境变量添加包含路径命令：

  ```shell
  $ C_INCLUDE_PATH=/opt/gdbm-1.8.3/include
  $ export C_INCLUDE_PATH
  ```

此目录将在命令行上指定的选项`-I`和标准默认目录'/usr/local/include'和'/usr/include'之前搜索。需要shell命令 export 导出来使环境变量可用于shell本身之外的程序——例如编译器。

类似地，可以使用环境变量`LIBRARY_PATH`将附加目录添加到**链接路径**中。 例如，下面的命令将向**链接路径**添加‘/opt/gdbm-1.8.3/lib'

- 向环境变量添加链接路径命令：

  ```shell
  $ LIBRARY_PATH=/opt/gdbm-1.8.3/lib
  $ export LIBRARY_PATH
  ```

此目录将在命令行中指定的选项`-L`和标准默认目录‘/usr/local/lib’和‘/usr/lib’之前进行搜索。

如果使用上面给出的环境变量设置，程序dbmain.c可以在没有`-I`和`-L`选项的情况下成功编译：

`gcc -Wall dbmain.c -lgdbm`

因为默认路径现在已经包含了环境变量`C_INCLUDE_PATH`和`LIBRARY_PATH`中指定的目录。

#### 3.1.3 扩展搜索路径

按照标准的Unix搜索路径约定，可以在环境变量中将几个目录利用冒号分隔列表一起指定：

````
DIR1:DIR2:DIR3:...
````

然后按从左到右的顺序搜索目录。 可以使用单个点`.`来指定当前目录（还可以使用空路径元素指定当前目录，例如`.:DIR:DIR2`等价于`:DIR:DIR2`）。

例如，下面的设置分别为各自安装在当前目录`.`和位于`/opt/gdbm-1.8.3`和`/net`的 include 和 lib 目录创建默认**包含路径**和**链接路径**：

```shell
$ C_INCLUDE_PATH=.:/opt/gdbm-1.8.3/include:/net/include
$ LIBRARY_PATH=.:/opt/gdbm-1.8.3/lib:/net/lib
```

若要在命令行上指定多个搜索路径目录，可以重复选项`-I`和`-L`。 例如下面的命令与上面的效果一样：

```shell
$ gcc -I. -I/opt/gdbm-1.8.3/include -I/net/include -L. -L/opt/gdbm-1.8.3/lib -L/net/lib
```

当环境变量和命令行选项一起使用时，编译器按以下顺序搜索目录：

1. 命令行选项`-I`和`-L`，从左到右;
2. 由环境变量指定的目录，例如`C_INCLUDE_PATH`和`LIBRARY_PATH`;
3. 默认系统目录;

### 3.2 共享库（动态库）和静态库

虽然上面的示例程序已经成功地编译和链接，但在能够加载和运行可执行文件之前需要最后一步。如果尝试直接启动可执行文件，那么大多数系统都会出现以下错误：

```shell
$ ./a.out
./a.out: error while loading shared libraries:
libgdbm.so.3: cannot open shared object file: No such file or directory
```

这是因为GDBM包提供了一个**共享库**。 这种类型的库需要特殊处理——它必须在可执行文件运行之前从磁盘加载。

外部库通常以两种形式提供：**静态库**和**共享库**。 

- **静态库**是前面看到的`.a`文件。 当程序与静态库链接时，程序使用任何外部函数的对象文件中的机器代码将从库复制到最终的可执行文件中。

- **共享库**使用更高级的链接形式处理，这使得可执行文件更小。 它使用扩展名`.so`，它代表共享对象。与共享库链接的可执行文件只包含它所需要的函数的一个小表，而不是来自外部函数的对象文件的完整机器代码。 在可执行文件开始运行之前，操作系统将外部函数的机器代码从磁盘上的共享库文件复制到内存中——这个过程被称为**动态链接**。

------

因为一个库的一个副本可以在多个程序之间共享，所以**动态链接**使可执行文件更小，并节省磁盘空间。 大多数操作系统还提供一种虚拟内存机制，允许所有运行的程序使用物理内存中的共享库的一份副本，从而节省内存和磁盘空间。

此外，**共享库**可以在不重新编译使用它的程序的情况下更新库（前提是库的接口不会更改）。

由于这些优点，gcc 编译程序在大多数系统中默认使用**共享库**（如果它们是可用的话）。 每当**静态库 **'lib*Name*.a’ 用选项`-lName`链接时，编译器首先检查是否具有相同名称和`.so`扩展的替代**共享库**。

在这种情况下，当编译器在链接路径中搜索'libgdbm'库时，如果它在目录‘/opt/gdbm-1.8.3/lib’中同时找到以下两个文件：

```shell
$ cd /opt/gdbm-1.8.3/lib
$ ls libgdbm.*
libgdbm.a libgdbm.so
```

此时，它使用共享对象文件而不是**静态库**。

------

然而，当可执行文件启动时，它加载使用了**共享库**的程序函数时必须找到**共享库**才能将其加载到内存中。默认情况下，加载程序只在预定义的系统目录集中搜索**共享库**，例如‘/usr/local/lib’和‘/usr/lib’。因此，如果**共享库**不位于预定义的目录中，则必须将其添加到**加载路径**（Load Path）中。

（*请注意，原则上，包含共享库的目录可以使用链接器选项 `-rpath`在可执行文件本身中存储（“硬编码”），但通常不会这样做，因为如果移动库或将可执行文件复制到另一个系统，则会产生问题*）。

设置**加载路径**最简单的方法是通过环境变量`LD_LIBRARY_PATH`。 例如，下面的命令将加载路径设置为‘/opt/gdbm-1.8.3/lib’，以便于找到**动态库**‘libgdbm.so'：

```shell
$ LD_LIBRARY_PATH=/opt/gdbm-1.8.3/lib
$ export LD_LIBRARY_PATH
$ ./a.out
Storing key-value pair... done.
```

可执行文件现在运行成功，打印它的消息并创建一个名为'test'的DBM文件，其中包含**键-值**对'testkey'和'testvalue'。

------

同样的，可以将几个共享库目录一起放置在**加载路径**中，冒号分离列表`DIR1：DIR2：DIR3：…：DIRN`。例如：

```shell
$ LD_LIBRARY_PATH=/opt/gdbm-1.8.3/lib:/opt/gtk-1.4/lib
$ export LD_LIBRARY_PATH
```

如果加载路径已经存在某些目录，可以通过这种语法来追加新的目录：`LD_LIBRARY_PATH=NEWDIRS:$LD_LIBRARY_PATH`。例如：

```shell
$ LD_LIBRARY_PATH=/opt/gsl-1.5/lib:$LD_LIBRARY_PATH
$ echo $LD_LIBRARY_PATH
/opt/gsl-1.5/lib:/opt/gdbm-1.8.3/lib:/opt/gtk-1.4/lib
```

系统管理员可以为所有用户设置`LD_LIBRARY_PATH`变量，将其添加到默认登录脚本中，例如‘/etc/profile’。

------

或者，静态链接可以强制使用 gcc 的`-static`选项，以避免使用共享库。例如：

```shell
$ gcc -Wall -static -I/opt/gdbm-1.8.3/include/ -L/opt/gdbm-1.8.3/lib/ dbmain.c -lgdbm
```

上行代码创建了一个与静态库'libgdbm.a'链接的可执行文件，可以在不设置`LD_LIBRARY_PATH`环境变量或将共享库放入默认目录的情况下运行。

如前所述，还可以通过指定命令行上的库的完整路径直接链接到单个库文件。例如，下面的命令将直接链接到**静态库**'libgdbm.a’：

```shell
$ gcc -Wall -I/opt/gdbm-1.8.3/include dbmain.c /opt/gdbm-1.8.3/lib/libgdbm.a
```

下面的命令将链接到**动态库**文件'libgdbm.so’：

```shell
$ gcc -Wall -I/opt/gdbm-1.8.3/include dbmain.c /opt/gdbm-1.8.3/lib/libgdbm.so
```

在这种链接共享库的情况下，仍然需要在运行可执行文件时设置库**加载路径**。

### 3.3 C语言标准

有几个选项可以控制gcc使用的C语言。 最常用的选项是`-ansi`和`-pedantic`。 每个标准的C语言的特定方言(dialect)也可以用`-std`选项选择。

#### 3.3.1 ANSI/ISO

`-ansi`

#### 3.3.2 Strict ANSI/ISO

`-pedantic`

#### 3.3.3 Selecting specifific standards

`-std=c89` 、`-std=iso9899:1990`、`-std=gnu89` ...

### 3.4 内部警告选项 `-Wall`

`-Wall`包括： `-Wcomment`、`-Wformat`、`-Wunused`、`-Wimplicit` ...

### 3.5 其他警告选项

略

## 4 使用预处理器



