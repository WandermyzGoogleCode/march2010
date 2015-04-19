
---

新系统还没有deploy。此页面在新系统deploy之后才生效

---


# 情况说明 #
  * 对原有系统的数据表结构作了较大改动。
    * lives3\_groups: 用于存储私密群组。添加了OwnerMemberId字段。
    * lives3\_members: 用户的基础表，存储电话（作为登录凭据）、密码和姓名。
    * lives3\_membersextra：存储额外的用户信息。注意：并不是每一个用户都会在此表中有一个对应的记录（查询时应使用OUTTER JOIN）
    * lives3\_opengroups：开放群组（即以前的标签，tags.config.php）
    * lives3\_openinfo: 将部分字段移动到了lives3\_members中
    * lives3\_permissions: 权限表，记录用户和权限的对应关系（多对多）
    * lives3\_tags: 由记录PhoneNumber改为记录MemberId
    * lives3\_admininfo: 删除

# 用户系统API #
  * 用户系统API由Membership类的静态函数定义，具体用法请见函数注释，web\_register.inc.php, web\_editprofile.inc.php和web\_remove.inc.php也可以拿来参考。
  * Membership中的函数主要用于修改用户信息，用户信息的读取和显示仍然需要自己写SQL查询。注意，由于现在用户信息分开存在不同的表里，所以查询时需要注意使用INNER JOIN和OUTTER JOIN
  * common.inc.php中的$user变量有一定改动，请见LoginUser类的注释。（检查权限使用$user->checkPerm）

## 有关权限系统的说明 ##
  * 在目前的权限系统中，有三种权限：系统管理员、私密群组管理员和开放用户。每个用户可以拥有多个权限或没有任何权限，每个权限也可以有多个用户或没有用户。
    * 系统管理员：最高权限，可以进行任意管理操作以及管理任意用户的信息
    * 私密群组管理员：可以添加、删除私密群组及修改自己的群组成员
    * 开放用户：可以编辑自己的状态
    * 如果一个用户没有任何权限，那么他将不能对系统做出任何修改（包括修改自己的状态）。目前，所以由我们自己添加并维护的号码都设置成了没有权限，这样，我们只有通过系统管理员账号来修改该用户的信息。这可以避免有人猜出这些用户的密码并做非法修改。
  * 权限系统仅适用于开放用户及管理员账户（即网站上的那些用户），不适用于普通用户（即双向、加密用户）

# 群组系统API #
  * 群组系统API由GroupManager类的静态函数定义，具体用法请见函数注释。
  * 群组系统API包括操作开放群组和操作私密群组。私密群组API\*还没有实现