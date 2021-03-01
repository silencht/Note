## 1. MNIST数据集

### introduction

The MNIST (Modified National Institute of Standards and Technology database) database of handwritten digits, has a training set of 60,000 examples, and a test set of 10,000 examples. It is a subset of a larger set available from NIST. The digits have been size-normalized and centered in a fixed-size image.

It is a good database for people who want to try learning techniques and pattern recognition methods on real-world data while spending minimal efforts on preprocessing and formatting.

Four files are available on this [site](http://yann.lecun.com/exdb/mnist/):

> [train-images-idx3-ubyte.gz](http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz): training set images (9912422 bytes) 每张图片28*28像素，单通道灰度图
>
> [train-labels-idx1-ubyte.gz](http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz): training set labels (28881 bytes)
>
> [t10k-images-idx3-ubyte.gz](http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz):  test set images (1648877 bytes) 每张图片28*28像素，单通道灰度图
>
> [t10k-labels-idx1-ubyte.gz](http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz):  test set labels (4542 bytes)

### file format

All the integers in the files are stored in the MSB first (high endian) format used by most non-Intel processors. Users of Intel processors and other low-endian machines must flip the bytes of the header.

The training set contains 60000 examples, and the test set 10000 examples.

The first 5000 examples of the test set are taken from the original NIST training set. The last 5000 are taken from the original NIST test set. The first 5000 are cleaner and easier than the last 5000.

以上四个文件解压后，可用visual studio code 并下载名称为 hexdump for VSCode 的插件，以16进制方式打开：

<img src="https://silencht.oss-cn-beijing.aliyuncs.com/img/image-20210301144148039.png" alt="image-20210301144148039" style="zoom: 25%;" />

####  train-labels-idx1-ubyte:

```
[offset] 	[type]     			[value]     		 [description]
  0000   32 bit integer 	0x00000801(2049) 	magic number (MSB first)
  0004   32 bit integer 		60000     			 number of items
  0008   unsigned byte  		  ??       				 label
  0009   unsigned byte  		  ??        			 label
........
  xxxx   unsigned byte  		  ??               	     label
```

The labels values are 0 to 9.

文件打开，头部如下图：

<img src="https://silencht.oss-cn-beijing.aliyuncs.com/img/image-20210301145239002.png" alt="image-20210301145239002" style="zoom: 80%;" />

> 这个文件里面包含了60000个标签内容，每一个标签的值为0到9之间的一个数。
>
> 先解析每一个属性的含义：说明书中的offset代表了字节偏移量（说明书中的 “偏移地址” 是包括了文件打开后视图的 “基地址+偏移地址” 的总地址）；type代表了这个属性的值的类型；value代表了这个属性的值是多少；description是对这个属性的说明；
>
> 例如：当采用 **说明书中** 偏移地址0041进行表达的时候，代表了上图的 00000040+01 = 00000041 总地址的数据（后四位相同）。
>
> 简要分析开头，从第0个字节开始有一个32位的整数，它的值是0x00000801，它是一个魔数；从第4个字节开始有一个32位的整数，它的值是60000（十六进制0x0000EA60），它代表了数据集的数量；从第8个字节开始有一个unsigned byte，它的值是05，说明第一张图片标签是数字5，下一张是数字0，再下一张是数字4（这样的标签数字有60000个，分别对应60000张图片）.....

#### train-images-idx3-ubyte:

```
[offset] 	[type]     			[value]     		  [description]
  0000   32 bit integer 	0x00000803(2051) 		magic number
  0004   32 bit integer 		60000      			number of images
  0008   32 bit integer 		  28        		number of rows
  0012   32 bit integer 		  28        		number of columns
  0016   unsigned byte  		  ??        			pixel
  0017   unsigned byte  		  ??        			pixel
........
  xxxx   unsigned byte  		  ??        			pixel
```

Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).

#### t10k-labels-idx1-ubyte:

```
[offset] 	[type]     			[value]     			[description]
  0000   32 bit integer 	0x00000801(2049) 		magic number (MSB first)
  0004   32 bit integer 		 10000      			number of items
  0008   unsigned byte  		  ??        				label
  0009   unsigned byte  		  ??        				label
........
  xxxx   unsigned byte  		  ??        				label
```

The labels values are 0 to 9.

#### t10k-images-idx3-ubyte:

```
[offset] 	[type]     			[value]     			[description]
  0000   32 bit integer 	0x00000803(2051) 			magic number
  0004   32 bit integer 		 10000      			number of images
  0008   32 bit integer 		  28        			number of rows
  0012   32 bit integer 		  28        			number of columns
  0016   unsigned byte  		  ??        			pixel
  0017   unsigned byte  		  ??        			pixel
........
  xxxx   unsigned byte  		  ??        			pixel
```

Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).

#### the idx file format

the IDX file format is a simple format for vectors and multidimensional matrices of various numerical types.

The basic format is

```
magic number
size in dimension 0
size in dimension 1
size in dimension 2
.....
size in dimension N
data
```

The magic number is an integer (MSB first). The first 2 bytes are always 0.

The third byte codes the type of the data:
0x08: unsigned byte
0x09: signed byte
0x0B: short (2 bytes)
0x0C: int (4 bytes)
0x0D: float (4 bytes)
0x0E: double (8 bytes)

The 4-th byte codes the number of dimensions of the vector/matrix: 1 for vectors, 2 for matrices....

The sizes in each dimension are 4-byte integers (MSB first, high endian, like in most non-Intel processors).

## 2.Code



## Reference

1. [THE MNIST DATABASE](http://yann.lecun.com/exdb/mnist/)

2. [MNIST数据集介绍](https://www.jianshu.com/p/050750a1bb5e)

3. [可跳过2，直接看3：MNIST数据集与IDX文件](https://blog.csdn.net/weixin_38118997/article/details/103670901)

