# SLAM REVIEW



## 1. SLAM是什么

**同时定位与地图构建**（英语：Simultaneous localization and mapping，一般直接称SLAM）是一种概念：希望机器人从未知环境的未知地点出发，在运动过程中通过重复观测到的地图特征（比如，墙角，柱子等）定位自身位置和姿态，再根据自身位置增量式的构建地图，从而达到同时定位和地图构建的目的。

### 1.1 SLAM适用场景

> SLAM finds applications in all scenarios in which a prior map is not available and needs to be built.

那些没有办法构建先验地图且需要构建地图的所有场景。

### 1.2 SLAM不适用场景

> SLAM may not be required if localization can be done reliably with respect to the known landmarks.

那些能依靠已知地标进行有效定位的场景。

### 1.3 SLAM的兴起

> The popularity of the SLAM problem is connected with the emergence of indoor applications of mobile robotics.

与室内移动机器人的兴起息息相关。

>  The popularity of SLAM in the last 30 years is not surprising if one thinks about the manifold aspects that SLAM involves. 
>
> At the lower level (called the *front-end* ) SLAM naturally intersects other research fifields such as computer vision and signal processing;
>
> At the higher level (that we later call the *back-end* ), SLAM is an appealing mix of geometry, graph theory, optimization, and probabilistic estimation.

如果考虑到SLAM涉及的多方面问题，那么它在这三十年的流行也就不足为奇。

从低层次，即SLAM前端来说，它与计算机视觉和信号处理等领域很自然的交叉作用；从高层次，即SLAM后端来说，它是一个吸引人的几何、图论、优化和概率估计的组合。

### 1.4 两个重要问题

#### 1.4.1 自动机器人需要SLAM吗？

> > SLAM aims at building a globally consistent representation of the environment, leveraging both ego-motion measurements and loop closures. The keyword here is “**loop closure**”: if we sacrififice loop closures, SLAM reduces to **odometry**. In early applications, odometry was obtained by integrating wheel encoders. The pose estimate obtained from wheel odometry quickly **drifts**, making the estimate unusable after few meters.
>
> SLAM旨在利用自我运动测量和回路闭合来构建整体一致的环境表示。这里的关键词是“回路闭合”：如果我们丢弃回路闭合，那么SLAM将会退化为里程测量 / 里程计。在早期的应用中，可以通过积分车轮编码器来获得里程。然而，从车轮里程测量所获得的姿态估计快速**漂移**，使得估计数在短短几米之内就不可用。
>
> - A. Kelly. Mobile Robotics: Mathematics, Models, and Methods . Cambridge University Press, 2013.
>
> > this was one of the main thrusts behind the development of SLAM: the observation of external landmarks is useful to reduce the trajectory drift and possibly correct it.
>
> 这个是SLAM发展背后的主要推动力之一：对于外部地标的观测有助于减少轨迹漂移并可能纠正之。
>
> - P. Newman, J. J. Leonard, J. D. Tardos, and J. Neira. Explore and Return: Experimental Validation of Real-Time Concurrent Mapping and Localization. In *Proceedings of the IEEE International Conferenceon Robotics and Automation (ICRA)*, pages 1802–1809. IEEE, 2002.
>
> >  However, more recent odometry algorithms are based on visual and inertial information, and have very small drift (*<* 0*.*5% of the trajectory length).
>
> 然而，很多最近的基于视觉和惯性信息的测速方法漂移越来越小。
>
> - C. Forster, L. Carlone, F. Dellaert, and D. Scaramuzza. On-Manifold Preintegration for Real-Time Visual–Inertial Odometry. *IEEE Transactions on Robotics (TRO)*, PP(99):1–21, 2016.
>
> 那么问题来了，
>
> **我们真的还需要SLAM这个算法吗？**
>
> **答案有三方面**

##### 1.4.1.1

​	首先，在过去十年的SLAM发展中，研究本身就产生了基于视觉-惰性测量算法，这种算法目前代表了最先进的水平[163,175]。在这种意义上，视觉-惯性导航（visual-inertial navigation）就是SLAM：**VIN可以被看作一个简化版SLAM系统，只不过这个系统的回路闭合（loop closure）或者位置识别（place recongnition）模块没有开启**。

​	更一般的，SLAM直接导致了在相比以前文献（如航空航天工程中的[惰性导航](./relative_note/visual-inertial navigation.md)）更有挑战性的设置下（如没有GPS,低质量传感器等）关于传感器融合的研究。

##### 1.4.1.2

 	第二个回答是关于环境的真实拓扑结构（true topology）的。一个只运行里程计（odometry）而关闭回路闭合（loop closure）的机器人会将世界解释为一个“无限走廊（infinite corridor）”，在这个“走廊”里，机器人一直保持着探索未定义的新区域。





#### 1.4.2 SLAM在学术上已经被解决了吗？

## 2. SLAM的发展阶段

### 2.1 1986—2004：classical age（古典时期）

#### 2.1.1 研究内容

> the introduction of **the main probabilistic formulations** for SLAM , including approaches based on **Extended Kalman Filters**, **Rao-Blackwellised Particle Filters**, and **maximum likelihood estimation**.

引入了SLAM主要的概率公式，其中包括 扩展卡尔曼滤波、粒子滤波 和 最大似然估计

#### 2.1.2 论文

> A thorough historical review of the first 20 years of the SLAM problem

详细论述SLAM发展前二十年的review

- H. F. Durrant-Whyte and T. Bailey. Simultaneous Localisation and Mapping (SLAM): Part I. *IEEE Robotics and Automation Magazine*, 13(2):99–110, 2006.
- T. Bailey and H. F. Durrant-Whyte. Simultaneous Localisation and Mapping (SLAM): Part II. *Robotics and Autonomous Systems (RAS)*, 13(3):108–117, 2006.

> Two other excellent references describing the **three main SLAM formulations** of the classical age

描述三大SLAM主要公式的论文

- S. Thrun, W. Burgard, and D. Fox. Probabilistic Robotics. MIT Press,2005.
- C. Stachniss, S. Thrun, and J. J. Leonard. Simultaneous Localization and Mapping. In B. Siciliano and O. Khatib, editors, Springer Handbook of Robotics, chapter 46, pages 1153–1176. Springer, 2nd edition, 2016.  

#### 2.1.3 挑战

> the basic challenges connected to efficiency and robust data association.

效率和鲁棒的数据关联的挑战 。

### 2.2 2004—2015：algorithmic-analysis age（算法分析时期）

#### 2.2.1 研究内容

> the study of fundamental properties of SLAM, including observability, convergence, and consistency. In this period, the key role of **sparsity** towards effificient SLAM solvers was also understood, and the main open-source SLAM libraries were developed.

研究SLAM的基本特性，包括可观测性、收敛性和一致性。在这一时期，（人们）理解了对SLAM的高效率解决器？起到关键作用的**稀疏性**，并开发了主要的开源SLAM库。

#### 2.2.2 论文

> partially covered

覆盖部分该时期内容的review

- G. Dissanayake, S. Huang, Z. Wang, and R. Ranasinghe. A review of recent developments in Simultaneous Localization and Mapping. In International Conference on Industrial and Information Systems*, pages 477–482. IEEE, 2011.





## 0.1 英文名词翻译/解释

- metric 度量
- semantic 语义 Semantic is used to describe things that deal with the meanings of words and sentences.
- pose 姿态，这里一般指机器人的位置和姿势 position and orientation

