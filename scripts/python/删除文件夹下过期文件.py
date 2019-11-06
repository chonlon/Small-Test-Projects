import os
import sys
import time

def delDir(dir,t=120):
    #获取文件夹下所有文件和文件夹
    files = os.listdir(dir)
    for file in files:
        filePath = dir + "/" + file
        #判断是否是文件
        if os.path.isfile(filePath):
            #最后一次修改的时间
            last = int(os.stat(filePath).st_mtime)
            #上一次访问的时间
            #last = int(os.stat(filePath).st_atime)
            #当前时间
            now = int(time.time())
            print("%d, %d", now, last)
            #删除过期文件
            if (now - last >= t):
                os.remove(filePath)
                print(filePath + " was removed!")
        elif os.path.isdir(filePath):
            #如果是文件夹，继续遍历删除
            delDir(filePath,t)
            #如果是空文件夹，删除空文件夹
            if not os.listdir(filePath):
                os.rmdir(filePath)
                print(filePath + " was removed!")

if __name__ == '__main__':
    #获取路径
    path = sys.argv[1]
    #获取过期时间
    t = int(sys.argv[2])
    #获取定期清理时间
    ts = int(sys.argv[3])
    while True:
        delDir(path,t)
        time.sleep(ts)