#!/usr/bin/bash

docker run -d -it \
 -p 23010:80 -p 23011-23013:23011-23013 \
 -v $PWD/conf/test.conf:/etc/nginx/conf.d/test.conf \
 -v $PWD/resource:/root/ \
 --name nginx nginx