

## 0.[官方源文档链接](https://docs.conda.io/projects/conda/en/latest/user-guide/getting-started.html)

## 1.管理conda

验证conda是否安装成功，在Windows : anaconda prompt终端或 Linux/Unix/Mac 的终端下输入:

 ```
 conda --version
 ```

conda显示你安装的版本号. 

举例: `conda 4.7.12`

更新当前conda版本. 输入以下命令:

 ```
 conda update conda
 ```

conda比较版本，然后显示出可以安装的版本。如果有新版本conda可用，输入 `y` 来更新:

 ```
 Proceed ([y]/n)? y
 ```

## 2.管理环境

conda允许你创建一个不会与其他环境有关的，包含文件、包和它们的依赖的分离式环境。

当你开始使用conda时，你已经有了一个名为base的默认环境。但是，当你不想要将程序放入你的基环境的话，可以创建一个使你的程序与其他程序相隔离的分离式环境。

1. 创建新环境并给它安装一个包。

   我们将创建一个名为`snwflakes`的新环境，然后安装`BioPython`包。在终端输入以下命令：

   ```
   conda create --name snowflakes biopython
   ```

   Conda检查查看BioPython需要哪些其他软件包（“依赖项”）,然后询问你是否继续:

   ```
   Proceed ([y]/n)? y
   ```

   键入`y`和回车继续

2. 为了激活和使用刚才安装的新环境, 输入以下内容:

   - Windows、macOS and Linux，Conda 4.6以上版本: 

    ```
    conda activate snowflakes
    ```

   **NOTE**: `conda activate` only works on conda 4.6 and later versions.

   现在你就处于 `snowflakes` 环境中了,任何你键入的conda命令都将作用于这个环境，直到你切换到其他环境（即deactivated snowflakes）

3. 为了看到你所有的环境列表，键入:

   ```
   conda info --envs
   ```

   环境列表与下方所列相似（3、4行 为不同系统所示）:

   ```
   # conda environments:
   #
   base           /home/username/Anaconda3
   snowflakes   * /home/username/Anaconda3/envs/snowflakes  （Linux）
   snowflakes   *  D:\anaconda\envs\snowflakes				 （Winodws）
   ```

   **Tip**：当前活跃环境是环境列表中带有`*`的

4. 关闭当前环境，切换至默认环境 (即base)，键入: `conda activate`

5. 删除环境

   如果当前位于snowflakes环境内，则先退出环境，输入：

   ```
   conda deactivate
   ```

   回到base环境后，输入删除snowflakes环境的命令：

   ```
   conda env remove -n snowflakes
   ```

## 3.管理Python

当你创建一个新环境时，conda安装的Python版本与你安装的anaconda软件的默认Python版本相同。如果你想要使用一个不同的Python版本，比如Python 3.5, 你可以在创建一个新的环境时，指定你想要的Python版本。 

1. 创建一个名为 "snakes"且包含Python 3.5的新环境:

   ```
   conda create --name snakes python=3.5
   ```

   当conda询问你是否继续时,键入 "y" 然后按回车键.

2. 激活新环境:

   - Windows、macOS and Linux，Conda 4.6以上版本: 
   ```
   conda activate snakes
   ```

3. 核实snakes环境已经被添加和激活:

   ```
   conda info --envs
   ```

   Conda 显示了所有的环境列表，然后在当前激活的环境前加了`*`号:

   ```
   # conda environments:
   #
   base                     /home/username/anaconda3
   snakes                *  /home/username/anaconda3/envs/snakes
   snowflakes               /home/username/anaconda3/envs/snowflakes
   ```

   当前激活的环境名称同样在你的终端命令行的`$`符号前用`()`括起来显示，像下面这样:

   ```
   (snakes) $
   ```

4. 确定你当前环境安装的Python版本:

   ```
   python --version
   ```

5. 关闭当前环境，回到默认环境 (即base): `conda activate`


## 4.管理包

在这一节，你可以检查你安装了哪些包、核实哪些是能用的、寻找确定的包然后安装它。

1. 为了寻找一个你已经安装的包，首先激活你要寻找这个包的环境. 如：

   ```
   conda activate snakes
   ```

2. 检查当前环境下有哪些包可用：

   ```
   conda list
   ```

3. 添加一些软件源（国外服务器网速太慢，使用一些国内镜像源，如：下面添加了两个源）

   ```
   conda config --add channels https://conda.anaconda.org/menpo
   conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
   ```

4. 查看当前源有哪些:

   ```
   conda config --show channels
   ```

5. 若要删除某些源：

   ```
   conda config --remove channels https://pypi.doubanio.com/simple/
   ```

6. 检查是否可以从Anaconda存储库中获得尚未安装的名为“opencv”的软件包（必须连接到Internet）:

   ```
   conda search opencv
   ```

   Conda在Anaconda存储库中显示具有该名称的所有软件包的列表，因此我们知道它可用。

7. 向当前环境中安装新包:

   ```
   conda install opencv
   ```

8. 在已安装的包列表里检查是否包安装成功:

   ```
   conda list
   ```