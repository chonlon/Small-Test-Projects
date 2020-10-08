#!/bin/bash

declare -A dict

# 存储当前目录下所有有size的Ep*文件到字典中
# grep -P "regex-expression" -o可以做到正则提取
# find 的正则需要加上-regex, 并且匹配其实是有路径的, 所以前面记得加上'.*'或者相应的路径匹配正则. size 可匹配大小比如 +100M.
for file_name in $( find . -maxdepth 1 -regex "\./Ep[0-9]*\.cpp" -type f -size +0 | grep -P "Ep[0-9]*\\.cpp" -o)
do
    dict[$file_name]=1
done

for file_name in $(git ls-files --others --exclude-standard)
do
    #如果未提交文件中被存在字典中的话提交到仓库
    [ ${dict[${file_name}]+abc} ] && git add $file_name && git commit -m "add: (c++ weekly) $(echo $file_name | grep -P "Ep[0-9]*" -o)"
    #[ ${dict[${file_name}]+abc} ] && echo "$(echo $file_name | grep -P "Ep[0-9]*" -o)"
done