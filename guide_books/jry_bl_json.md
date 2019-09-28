# 蒟蒻云基础库-JSON部分用户手册
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)
有问题发issues

## 状态
随各模块保持跟进

## 基本信息

头文件:暂无

源文件:暂无

控制文件:暂无

类:暂无

强制依赖项:

1.jry_bl_string

可选依赖(及相关依赖函数):

暂无

## 控制字

暂无

##其他

这玩意甚至没有文件

分散在各个模块当中

使用*.from_json(jry_bl_string in)解压JSON

使用s1<<*.to_json();压缩JSON，注意这里必须要用<<，否则有内存泄露，详见jry_bl_string.md

