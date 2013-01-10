cp mod_esp.cpp mod_esp.c
cp espserverapi_impl.cpp espserverapi_impl.c
cp utils.cpp utils.c

apxs2 -c -i -S CC=g++ mod_esp.c espserverapi_impl.c utils.c -I. -L../lib -lesp-core -L/usr/local/apr/lib -lapr-1 -laprutil-1
