Linux系统下编译安装方法：

直接执行 build.sh，或采用以下步骤

首先需要把所有源代码后缀由.cpp改为.c（apxs2的限制）：
cp mod_esp.cpp mod_esp.c
cp espserverapi_impl.cpp espserverapi_impl.c
cp utils.cpp utils.c

然后调用apxs2编译：
sudo apxs2 -c -i -S CC=g++ mod_esp.c espserverapi_impl.c utils.c -I. -L../lib -lesp-core -L/usr/local/apr/lib -lapr-1 -laprutil-1

如果编译成功，通常在 /usr/lib/apache2/modules 目录内生成文件 mod_esp.so 。

然后修改Apache配置文件 /etc/apache2/apache2.conf 增加一行：
LoadModule esp_module /usr/lib/apache2/modules/mod_esp.so

然后重启Apache：sudo apache2ctl restart （start/stop/restart）

如果没有找到apxs2命令，需先安装apache2-threaded-dev，参考：
https://plus.google.com/105597640837742873343/posts/2sNwB8fF7Lb
http://hi.baidu.com/zhangsilly/item/383ab80823f141123b53eedd
http://www.fuzhijie.me/?p=122

如果没有apr和aprutil库，也需要自己下载源代码编译安装（apt-get source apr）。
必要时需修改上面编译命令行内apr库文件路径。


by Liigo, 2013-1-8.
