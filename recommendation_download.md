为了能够使得群组推荐列表被动态更新（推荐列表即目前S60客户端下载群组时可供用户直接选择，而不用输入具体的下载口令（标签）的一个群组列表），我们决定将第一类群组下载协议（下载开放用户的协议）做一个小的修改：

在原有的返回结果后面直接加上一个推荐列表。推荐列表第一行为一个整数list\_size，表示推荐列表中有list\_size个群组。接下来list\_size行，每行两个字符串：name\_base64\_encoded以及token。其中name\_base64\_encoded是该群组的中文名的base64编码，token则是英文的下载口令。注意，token不要base64编码！
```
			/**
			 * The new list is transfered in the following format:
			 * ------
			 * line1: list_size
			 * line2: name1_base64_encoded token1
			 * line3: name2_base64_encoded token2
			 * ...
			 * ------
			 * Note that only name should be base64 encoded. Token should not be encoded.
			 */
```
接下来给一个完整的第一类群组下载协议的返回样例：

---

```
4
979500
979501
979502
979503
2
[推荐群组1的Base64编码] token1
[推荐群组2的Base64编码] token2
```

---

上面的样例中，一开始是下载的开放群组的信息：有4个开放用户，号码从979500到979503。后面的三行描述了一个有两个群组的推荐列表。