import requests
from bs4 import BeautifulSoup

url = 'https://www.douban.com/group/beijingzufang/discussion?start={num:d}'
for i in range(1,100):
    r = requests.get(url.format(num = i) ,headers={'User-Agent': 'Mozilla/4.0'})
    html = r.text
    #print(html)
    soup = BeautifulSoup(html, "html.parser")
    table = soup.find('table', attrs={'class': 'olt'})
    title = table.find('td', attrs={'class':'title'})
    print(title.getText())


