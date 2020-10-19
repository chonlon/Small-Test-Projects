import os
import re

# rename 文件, 把文件第一个序号改小两号. eg: 4.1.py ==> 2.1.py
for file in os.listdir(r'./'):
    if(re.match(r'.*\.py', file)):
        matched = re.match(r'(\d+)\.(\d+.*\.py)', file)
        if matched:
            group1_num = int(matched.group(1)) #获取第一个序列数字
            group1_num -= 2 
            replaced_file_name = str(group1_num) + '.' + matched.group(2) #组合
            os.rename(file, replaced_file_name)
            print("rename {} to {}".format(file, replaced_file_name))
        else:
            print("match failed: ", file)
