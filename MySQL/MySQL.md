

## 1.安装mysql

### 1.1 WINDOWS环境

参考微信读书《MySQL8从零开始学》

### 1.2 LINUX环境 5.7

```bash
sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev
```

安装过程中会提示设置密码什么的，记住密码不要忘。

- 第三条命令出现 正在读取软件包列表... 完成 正在分析软件包的依赖关系树        正在读取状态信息... 完成        有一些软件包无法被安装。如果您用的是 unstable 发行版，这也许是 因为系统无法达到您要求的状态造成的。该版本中可能会有一些您需要的软件 包尚未被创建……错误，根据博客解决之，网址为：https://www.cnblogs.com/mliudong/p/4217945.html

安装完成之后可以使用如下命令来检查是否安装成功：



```bash
sudo netstat -tap | grep mysql
```



- 检查命令出现“sudo: netstat：找不到命令”，查找博客https://blog.csdn.net/weixin_41931602/article/details/83211455，输入命令:sudo apt-get install net-tools 后解决问题。

### 1.3 LINUX环境 8.0

https://blog.csdn.net/iehadoop/article/details/82961264

### 1.4 MySQL常用命令

#### 1.4.1 登陆：

```bash
mysql -u root -p 
root用户本地登陆

mysql –u用户名 [–h主机名或者服务器IP地址] –p;
输入密码;
一般用户远程登陆
```

#### 1.4.2 MySQL命令：

```mysql
SHOW DATABASES;
列出 MySQL 数据库管理系统的数据库列表。

USE 数据库名 ;
选择要操作的Mysql数据库，使用该命令后所有Mysql命令都只针对该数据库。

SHOW TABLES;
显示指定数据库的所有表，使用该命令前需要使用 use 命令来选择要操作的数据库。

SHOW COLUMNS FROM 数据表;
显示数据表的属性，属性类型，主键信息 ，是否为 NULL，默认值等其他信息。

select * from 数据表;
获取该数据表的所有记录的数据。
```

## 2.创建数据库

```bash
CREATE DATABASE 数据库名;
```

## 3.创建用户

创建可以访问数据库gesture的yoloyolo用户，密码为silencht

```mysql
GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP
ON gesture.*
TO 'yoloyolo'@'192.168.1.%'
IDENTIFIED BY 'silencht';
```

## 4.创建数据表

```mysql
CREATE TABLE gesture_tbl(
gesture_id INT UNSIGNED AUTO_INCREMENT,
c1 INT,
p1 FLOAT,
c2 INT,
p2 FLOAT,
fps FLOAT,
PRIMARY KEY (gesture_id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
```

## 5.插入原始的3行初始化数据

```mysql
INSERT INTO gesture_tbl(c1,p1,c2,p2,fps)
VALUES
 ('2','98.654874','6','46.544648','26.7684');

INSERT INTO gesture_tbl(c1,p1,c2,p2,fps)
VALUES
 ('18','96.4564534','9','0','19.6574');

INSERT INTO gesture_tbl(c1,p1,c2,p2,fps)
VALUES
 ('9','83.65546564','20','36.456464','24.4864');

```

## 6.（示例）命令行更新表格第二行数据

```mysql
UPDATE gesture_tbl SET c1 = "6", p1 = "96.8586", c2 ="18", p2 ="16.67452", fps = "21.4186"  WHERE gesture_id = 2;
```

## 7. C语言调用MySQL的接口，进行增删改查操作

代码位于此仓库：https://github.com/silencht/Use-C-language-to-call-Mysql