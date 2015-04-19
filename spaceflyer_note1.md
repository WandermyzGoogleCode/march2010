# SOLVED PROBLEMS #
  * CONE 36是emulator的BUG
  * USER 47是由于tbufctochar时tbufc长度为0造成的
  * Signal Exception 0 received: A data abort exception has occurred是由于堆栈溢出造成的。原来S60的堆栈就8K，随便开个几千长度的字符串缓存就溢了。

# Appearance #
  * 用TITLE显示用户的名字，以体现当前有没有设定用户
  * 用大ICON来表现目前的操作情况（比如正在获取信息什么的）。当然小的文字说明还是要的，这个只是给个更好的体验。

# Candies #
  * [4](4.md)我们可能需要让用户通讯录里面不同联系人不能拥有相同的号码。考虑做一个原来合并功能的小工具，用户应该也会比较喜欢。
  * [2](2.md)通讯录人的个数远远大于一个屏幕能显示下的个数，但是联系人就像内存一样，有时间局部性和空间局部性（空间比较难挖掘）。一个屏幕的显示量就等于CACHE的大小，嘿嘿，这个CACHE如何做替换是不是很有意义呢？比如来电去电记录基本上就是一个LRU算法，而且只是针对来电的。我感觉我用通讯录的时候非常大的概率是直接使用这个LRU算法得到的CACHE的。因此，一个好的替换算法是不是很有用呢？That's a very sweet candy!
  * [3](3.md)既然大家讨厌骚扰电话，我们不如在系统里面做一个骚扰号码的数据库吧，我每次收到恶心号码电话或短信的第一反应就是去找找看这个号码到底是不是恶心号码，以免漏了重要电话。可以考虑和"http://www.soudianhua.com/Reports-6281.aspx"合作。
  * [1](1.md)我觉得我们很重要的一个优势就是信息的非易失性和及其方便的随时获取，这样对于清华各种张贴海报的人来说都是非常绝佳的信息传播平台，我觉得我们可以进一步扩大我们的恒星体系。
  * [1](1.md)可以打包下载一类手机号码到手机里面，比如餐饮，电影，协会等。感觉这个东西对于新生比较有用。而且这个东西应该也是商业之利器吧。

# 某公司的方向 #

B2B平台：

手机点击量分析统计平台：基于互联网搭建一个B2B（大型wap网站和手机软件商）/C2C（个人开发者）平台，实现对指定手机网站和手机软件（网站或软件所有者注册后提供相关链接信息）的流量统计与分析，用户行为分析。类似于www.admob.com



B2C平台：

手机搜索：图片搜索引擎&LBS服务（比如手机拍个照片 把照片里边东西认出来 再根据手机位置把你当期位置和照片东西关联）



主流智能手机平台（symbian，WM，android，iphone）上的技术研究：

高速手机下载技术（P2P或其他）

适合手机的视频，音频编解码技术

手机上的定位技术（GPS,LBS）

手机系统的优化技术（杀毒，内存整理，磁盘空间整理，进程监控）

手机上的flash技术研究

手机浏览器技术

手机信息的采集技术（通信录备份）

手机软件管理（手机软件版本，动态更新）

# NOKIA PROPOSAL #
## 内容 ##
  * PROPOSAL
  * 计划
  * 需要的支持
## 注意 ##
  * 创意，没有特定格式，看看官网（http://www.nokia.com.cn/find-products/happenings/innovationjourney）
  * 按文档“此次大赛将设立创业奖金、金奖、优胜奖、入围奖等数十余项奖项。”
## 现有的资料 ##
  * 刘洋的PROPOSAL，包含整个PhoneMe的4步走计划和产品简介，技术实现和推广计划。
## 问题 ##
  * PROPOSE整个计划还是初期第一步的计划。
  * 侧重点？场景/技术(感知、安全、挖掘)/可行/应用/创新/简单/强大/安全……
## 文档结构 ##
> ?

# 硬件 #

4个条件(还有一个？)
  1. FPGA能做出来
  1. 和PC的通信、LINUX下的驱动能有现成的很方便的支持
  1. 我们做出来可以用，并且做的好的话有人会帮我们10月份前烧出真正的芯片
  1. 能够长期稳定的运行


# 用户安全 #
为了保证用户不被伪造，可以利用手机序列号和短信验证码的帮定。另外传输时SSL之类的东西还是必要的，防止中间窃听和伪造信息。

# REFERENCE NOTE #
  1. C.E. Shannon, "A Mathematical Theory of Communication", Bell System Technical Journal, vol. 27, pp. 379-423, 623-656, July, October, 1948
  1. Theresa M. Korn; Korn, Granino Arthur. Mathematical Handbook for Scientists and Engineers: Definitions, Theorems, and Formulas for Reference and Review. New York: Dover Publications. pp. 613–614. ISBN 0-486-41147-8. (Conditional Entropy)
  1. C. Arndt (2001). Information Measures: Information and its description in Science and Engineering). Berlin: Springer. pp. 370–373. ISBN 3-540-41633-1. (Conditional Entropy)
  1. Entropic Security and the Encryption of High Entropy Messages
  1. Entropy measures and unconditional security in cryptography
  1. Secure applications of low-entropy keys
  1. Deterministic and Eﬃciently Searchable Encryption
  1. Perfectly-Secure Key Distribution for Dynamic Conferences