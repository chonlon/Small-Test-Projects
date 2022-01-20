FROM draco-env

RUN apt install libeigen3-dev faketime libssl-dev locales -y 
RUN locale-gen en_US.UTF-8
ENV LD_PRELOAD=/usr/lib/x86_64-linux-gnu/faketime/libfaketime.so.1
ENV FAKETIME="-1y"
