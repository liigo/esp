Linuxϵͳ�±��밲װ������

ֱ��ִ�� build.sh����������²���

������Ҫ������Դ�����׺��.cpp��Ϊ.c��apxs2�����ƣ���
cp mod_esp.cpp mod_esp.c
cp espserverapi_impl.cpp espserverapi_impl.c
cp utils.cpp utils.c

Ȼ�����apxs2���룺
sudo apxs2 -c -i -S CC=g++ mod_esp.c espserverapi_impl.c utils.c -I. -L../lib -lesp-core -L/usr/local/apr/lib -lapr-1 -laprutil-1

�������ɹ���ͨ���� /usr/lib/apache2/modules Ŀ¼�������ļ� mod_esp.so ��

Ȼ���޸�Apache�����ļ� /etc/apache2/apache2.conf ����һ�У�
LoadModule esp_module /usr/lib/apache2/modules/mod_esp.so

Ȼ������Apache��sudo apache2ctl restart ��start/stop/restart��

���û���ҵ�apxs2������Ȱ�װapache2-threaded-dev���ο���
https://plus.google.com/105597640837742873343/posts/2sNwB8fF7Lb
http://hi.baidu.com/zhangsilly/item/383ab80823f141123b53eedd
http://www.fuzhijie.me/?p=122

���û��apr��aprutil�⣬Ҳ��Ҫ�Լ�����Դ������밲װ��apt-get source apr����
��Ҫʱ���޸����������������apr���ļ�·����


by Liigo, 2013-1-8.
