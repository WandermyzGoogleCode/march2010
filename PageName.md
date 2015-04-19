# Introduction #

They way to add a virtual partition in the file system.


# Details #

This is a way for you to add a virtual partition to the file system with default size.(The default value should be half of the entire physical memory. I think it's enough.)
  * You just need to add the following line into the file /etc/fstab, and restart your computer.
```
tmpfs /media/ramdisk tmpfs defaults,noatime,mode=1777 0 0
```
  * I don't know how to specific the partitions size currently...
  * The performance of the ramdisk partition is pretty good. Copying a 200MB file in hard disk spends about 8sec, but by ramdisk it spends no time.
  * No need to care about the main memory cost. The cost of the main memory is dynamic. For example, if there is no file in the partition, the cost of the main memory would be zero.