FROM alpine
RUN sed -i "s/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g" /etc/apk/repositories \
    && cppBuildDeps='g++ clang cmake' \
    && pyBuildDeps='python3 py3-pip' \
    && otherPkgs='wget git' \
    && apk add --no-cache $otherPkgs $cppBuildDeps $pyBuildDeps