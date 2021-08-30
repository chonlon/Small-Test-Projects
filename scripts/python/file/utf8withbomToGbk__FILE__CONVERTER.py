import codecs


f=open("1.txt", "r")


bom = f.read(3)
if(bom == codecs.BOM_UTF8):
    f.seek(3)
    data = f.read()
f.close()

f1 = open("1.txt", "w")
newdata = data.decode("utf-8").encode("gbk")
f1.write(newdata)
f1.close()
