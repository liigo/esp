#!/bin/sh

cp mod_esp.cpp mod_esp.c
cp espserverapi_impl.cpp espserverapi_impl.c
cp utils.cpp utils.c

# use `apxs2` in Ubuntu
#APXS=apxs2

# CentOS 5
APXS=/usr/sbin/apxs

${APXS} -c -i -S CC=g++ mod_esp.c espserverapi_impl.c utils.c -I. -L../lib -lesp-core -L/usr/lib -lapr-1 -laprutil-1

