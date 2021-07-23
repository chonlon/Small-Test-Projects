#!/usr/bin/bash

docker run -d -it -p 23011:80 -v $PWD/conf/nginx.conf:/etc/nginx/conf.d/nginx.conf --name nginx nginx