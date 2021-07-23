#from ./ubun-dev
FROM ubuntu_base_env

RUN mkdir -p /root/nginx/ && \
    cd /root/nginx \
    && wget http://nginx.org/download/nginx-1.20.0.tar.gz \
    && tar -xzf nginx-1.20.0.tar.gz \
    && cd nginx-1.20.0 \
    && mkdir -p /root/app/ \
    # enable debug info.
    ## && sed  -i 's/^\(ngx_compile_opt\=\).\+$/\1\"-c -O0 -g\"/g' ./auto/cc/conf \
    && ./configure --prefix=/root/app/nginx --with-http_ssl_module --with-http_v2_module --with-http_realip_module \
    && make \
    && make install \
    && sed -i '1i\user root;' /root/app/nginx/conf/nginx.conf

#install redis