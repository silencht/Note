## 系统安装

1、下载sdk
首先，在 NVDIA 官网上下载并安装 SDK Manager（需要注册一个 nvida 账号才能下载）下载地址：https://developer.nvidia.com/embedded/downloads

2、安装sdk

输入命令：

```shell
sudo apt install sdk*.deb(换成你下载的安装包路径)
```

3、启动sdk

```shell
sdkmanager
```

### 一、踩坑记录

#### 1、SDKManager无法登陆以及OOPS问题

使用移动、联通宽带均无法直接登陆sdkmanager账户，使用魔法上网，情况稍有改善，但仍无法进入STEP2界面，出现OOPS网络连接不通问题。

解决方法：

- 通过手动配置sdkmanager客户端右上角settings内的代理（与魔法上网参数一致），偶然成功刷机一次，但该方法第二天失效。具体成功原因暂时未知。
- 使用学校的10GB流量账号可流畅登陆下载运行。

#### 2、usb 1-4-port1:cannote enable. maybe the usb cable is bad？

<img src="https://silencht.oss-cn-beijing.aliyuncs.com/img/IMG_0530.JPG" alt="IMG_0530" style="zoom: 15%;" />

进入桌面后，测试板子上所有USB口都能正常工作。排除板子硬件问题后，发现USBHUB坏了，换个新的就警告了。

<img src="https://silencht.oss-cn-beijing.aliyuncs.com/img/5D467BEA4EF6CA3C9B0F0F5AA1DBCD42.png" alt="5D467BEA4EF6CA3C9B0F0F5AA1DBCD42" style="zoom:15%;" />

#### 3、cp: not writing through dangling symlink 'etc/resolv.conf'

etc/resolv.conf 是记录DNS服务参数的文件，手动修改8.8.4.4，114.114.114.114等DNS参数均无法解决。

#### 4、cgroup：cgroup2：unknown option “nsdelegate”

论坛说可能是系统内核版本与系统版本相差过大导致的问题，解决方法暂时不明。

#### 4、联想显示器无法成功启动问题

通过HDMI-VGA线连接联想显示器无法显示画面，只能使用HDMI-HMDI显示器才可成功启动，进入桌面界面。

联想显示器显示超出输入分辨率范围，随后显示无输入信号，猜测是显示信号分辨率输出太大，通过配置 /etc/X11/xorg.conf 文件，未能解决问题。

[某论坛](https://www.taodudu.cc/news/show-627002.html)称：“ **坑1**：请使用HDMI接口的显示器或者HDMI转DVI，HDMI转VGA无法通过开机自检，开机后可以更换HDMI转VGA接头显示成功。”

解决方法：

- HDMI-HDMI接口显示器（成功）
- VNC或SSH方式（暂未尝试）

#### 5、英伟达板子中文输入法
搜狗输入法只支持amd架构，而英伟达板子是arm架构，因此搜狗输入法很难安装。谷歌拼音输入法可以安装，但是xavier板子上有不会出现字的候选框的bug，知乎某答主说是安装了fcitx-qimpanel-configtool的原因。所以我使用自带的ibus拼音输入法。
[原文](https://blog.csdn.net/qq_34213260/article/details/106226831)
1. 安装文件 ibus-pinyin

   ibus是系统已经安装，直接输入ibus会显示如下内容：

   ```
   ibus
   ```

   用法：ibus 命令 [选项...]
   命令：
     engine          设定或获取引擎
     exit            退出 ibus-daemon
     ……略
     emoji           将面板中的 emoji 保存到剪贴板 
     help            显示本信息
   
2. 安装ibus-pinyin

```
sudo apt-get install ibus-pinyin
```

3. 系统设置
    打开右上角系统设置，进入语言支持（language support），点击“install / remove language…”，选择简体中文，输入密码，此时系统会进行更新，大约几分钟；
    将菜单和窗口的语言栏中“汉语（中国）”拖到最上方，键盘输入法系统选择IBus，最后选择应用到整个系统按钮；

4. ibus设置
    终端下输入：

  ```
  ibus-setup
  ```

  弹出一个窗口，切换到输入法选项卡，点击添加按钮，选择汉语，选择Pinyin选项，确定；
  输入下述命令，重新启动ibus：

  ```
  ibus restart
  ```

5. 重启电脑

  ```
  reboot
  ```

6. 开机切换输入法
右上角图标栏选择文本输入设置，找到“+”号，找到汉语（pinyin）（ibus）选项，添加，确定；
切换到下一个源，使用这里是如何切换输入法，可自行选择，推荐ctrl+space

#### 6、风扇自启动

[此方法原文链接](https://blog.csdn.net/weixin_38693938/article/details/108059540)

不要搞rc.local的启动脚本！！一大堆毛病，还搞不出来！！

直接安装 jetson-stats！

```bash
sudo apt install python3-pip
sudo -H pip3 install jetson-stats
sudo jtop
#按数字键5进入CTRL界面
#按S和E，设置jetson_clocks Running和boot Enable
#然后按q推出当前界面，重启设备，看看风扇是否开机自动启动
```
### 二、ORB-SLAM3安装
#### 7、安装Opencv
[方法原网址](https://www.jetsonhacks.com/2018/11/08/build-opencv-3-4-on-nvidia-jetson-agx-xavier-developer-kit/)
- 注意！Opencv的安装需要至少13GB硬盘空间，否则中途会编译安装失败！
```bash
#安装命令
$ git clone https://github.com/jetsonhacks/buildOpenCVXavier.git
$ cd buildOpenCVXavier
$ git checkout v1.0
$ ./buildOpenCV.sh
#安装完毕后删除源程序
$ ./removeOpenCVSources.sh
```
- 确认安装成功的两个方法
1. 命令行运行jtop命令，按数字6进入info选项卡，查看Opencv版本号
2. 命令行运行 pkg-config opencv --modversion 命令，直接输出Opencv版本号

- 使用OpenCV打开摄像头：

```python
import time
import cv2

cap = cv2.VideoCapture(0)
start_time = time.time()
counter = 0
# 获取视频宽度、高度
frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
# 视频平均帧率
fps = cap.get(cv2.CAP_PROP_FPS) 
while (True):
    ret, frame = cap.read()
    # 键盘输入空格暂停，输入q退出
    key = cv2.waitKey(1) & 0xff
    if key == ord(" "):
        cv2.waitKey(0)
    if key == ord("q"):
        break
    counter += 1  # 计算帧数
    if (time.time() - start_time) != 0:  # 实时显示帧数
        cv2.putText(frame, "FPS {0}".format(float('%.1f' % (counter / (time.time() - start_time)))), (500, 50),cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255),3)
        src = cv2.resize(frame, (frame_width // 3, frame_height // 3), interpolation=cv2.INTER_CUBIC)  # 窗口大小
        cv2.imshow('frame', src)
        print("FPS: ", counter / (time.time() - start_time))
        counter = 0
        start_time = time.time()
    time.sleep(1 / fps)  # 按原帧率播放
cap.release()
cv2.destroyAllWindows()
```



#### 8、安装Pangolin库
[pangolin库github网址](https://github.com/stevenlovegrove/Pangolin)
```bash
#Required Dependencies
sudo apt install libgl1-mesa-dev
sudo apt install libglew-dev
sudo apt install cmake
#download and build
git clone https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin
mkdir build
cd build
cmake ..
cmake --build .
```
#### 9、安装Eigen库

```bash
#Eigen3头文件默认位置在/usr/include/eigen3/中
#不确定是否安装的话，可以先查找一下
whereis eigen3
#若没有安装，输入以下命令安装
sudo apt-get install libeigen3-dev
```

#### 10、DBoW2 and g2o 

​	Already Included in ORB_SLAM3/Thirdparty folder.

#### 11、安装编译ORB-SLAM3

```bash
#clone this repository
git clone https://github.com/UZ-SLAMLab/ORB_SLAM3.git ORB_SLAM3
#They provide a script build.sh to build the Thirdparty libraries and ORB-SLAM3.
#Please make sure you have installed all required dependencies (see 7-10).
cd ORB_SLAM3
chmod +x build.sh
./build.sh
```

#### 12、编译期间若遇到如下编译错误

##### 一、boost_serialization

```bash
fatal error: boost/serialization/serialization.hpp:没有那个文件或目录
或……
/usr/bin/ld:cannot find -lboost_serialization
collect2:error:ld returned 1 exit status
……
```

- [解决方法](https://blog.csdn.net/a922922737/article/details/109697291)：

  这个错误的意思是找不到boost_serialization共享库，这个库的文件名应该为“libboost_serializatio.so”，其命名规则是：lib+库名(即xxx)+.so

  1. 方法一

     ```bash
     #安装locate库
     sudo apt-get install locate
     #定位缺失库位置
     locate libboost_serialization.so
     #若可定位到（如定位结果为/usr/local/ahuasdk/libXXX.so）进行软链接，定位不到见方法二
     sudo ln -s /usr/local/ahuasdk/libXXX.so /usr/lib/libXXX.so
     ```

  2. 方法二

     ```bash
     sudo apt-get install apt-file
     sudo apt-file update
     apt-file search libboost_serialization.so
     #apt-file 将列出所有包含libXXX.so文件的apt包，
     #选择相应的包用apt-get安装即可，通常请选择带dev的包安装。输出举例如下
     libboost_serializatio1.65-dev: /usr/lib/aarch64-linux-gnu/libboost_serialization.so
     #安装缺失库
     sudo apt-get install libboost-serializatio1.65-dev
     #注意，可能为
     sudo apt-get install libboost-serializatio1.65-dev
     ```
     
  3.  或者尝试安装

     ```bash
     sudo apt-get install libboost-dev
     ```

  ##### 二、openssl/md5.h

  ```
  fatal error : openssl/md5.h:没有那个文件或目录
  ```

- [解决方法](https://www.cnblogs.com/wangjq19920210/p/10698146.html)

  ```bash
  #首先得安装openssl：
  sudo apt-get install openssl 
  #其次，如果有#include<openssl/ssl.h>编译报错：openssl/ssl.h：没有那个文件或目录，解决办法为
  sudo apt-get install libssl-dev
  #安装上边的依赖就好了。
  ```

  三、v0.4beta中`no match for ‘operator/‘`的错误

  ```cpp
  ORB_SLAM3/src/LocalMapping.cc:628:49: error: no match for ‘operator/’ (operand types are ‘cv::Matx<float, 3, 1>’ and ‘float’)
  x3D = x3D_h.get_minor<3,1>(0,0) / x3D_h(3);
  ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~
  ```

  [解决办法]():

  ```c++
  //You can add below code to KannalaBrandt8.h. and LocalMapping.h
  
  namespace cv
  {
  	template<typename _Tp, int m, int n> static inline
  	Matx<_Tp, m, n> operator / (const Matx<_Tp, m, n>& a, float alpha)
  	{
  		return Matx<_Tp, m, n>(a, 1.f / alpha, Matx_ScaleOp());
  	}
  }
  
  //It will works for all same problems
  //继续出现编译错误，暂时放弃该版本，建议更换0.3beta版本
  git checkout -f ef97841
  ```

  