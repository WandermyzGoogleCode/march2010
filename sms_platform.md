

某些地方可能理解不到位，请大家指正！

# 客户端 #
单向用户可以在手机端发送一条短信到指定号码修改个人信息（状态）。由于该用户操作以通常发送短信的方式进行，因此我们的客户端不需要对发送功能进行专门处理，只需规定用户发送短信的格式即可。
  * 由于只需要更改状态，因此可以让用户直接以新的状态为短信内容发送到指定号码。(to extend?)
  * 用户发送后，若修改信息成功，用户收到短信提示“修改成功”，否则收到短信提示“修改失败”。
  * ?短信平台：移动／联通／小灵通 不兼容，短信平台号码不同

# 服务器端 #
  * 服务器端收到一条请求，并且判断该请求为修改状态
  * 检查该用户是否存在，若是则继续，否则发送广告，且不再次发送反馈信息
  * 检查是否是单向用户，若是，则继续，否则向客户端发送失败消息，且不再次发送反馈信息
  * 索引到该用户的信息，更改其状态字段为用户请求修改的内容
  * 更新状态更新时间
  * (需进一步明确)是否存在同步等问题？
  * 若修改成功，向客户端发送短信“修改成功”，否则向客户端发送短信“修改失败”（这个是否能做？）