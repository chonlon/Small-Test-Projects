#构建
FROM alpine:latest as cpp_builder
RUN apk --no-cache add g++
WORKDIR /root/
COPY hello_world.cpp .
RUN g++ hello_world.cpp -o app -O2

#复制到新镜像
FROM alpine:latest as copyer
WORKDIR /root/

#c++ runtime
RUN apk add --no-cache libstdc++
#也可以下面这样, 但是可能不在此文件夹中
#COPY --from=cpp_builder /usr/lib/libstdc++.so* /usr/lib/ 
#COPY --from=cpp_builder /usr/lib/libgcc* /usr/lib/

#复制...
COPY --from=cpp_builder /root/app .

RUN ls
CMD ["./app"]
