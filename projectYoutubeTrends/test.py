import requests,json,ast
import urllib, urllib.parse, urllib.request
from bs4 import BeautifulSoup
from flask import jsonify

'''response = requests.get("http://www.saavn.com/api.php?__call=content.getHomepageData&_format=json").text

buff = ""
flag,signal = 0,0

for i in response:
    if (i == "["):
        flag += 1
        if (flag == 2):
            signal = 1
    elif (i == "]"):
        flag -= 1

    if (flag > 0):
        buff += i
    if (flag == 0 and signal == 1):
        break;


buff = buff + "]"

fruits = ast.literal_eval(buff)
for im in range(0,39):
    print((fruits[im]["text"]),(fruits[im]["weight"]))
'''

textToSearch = 'helloworld'
query = urllib.parse.quote(textToSearch, safe='')
url = "https://www.youtube.com/results?search_query=" + query

with urllib.request.urlopen("http://www.python.org") as url:
    s = url.read()

#html = s.read()
soup = BeautifulSoup(s, "html.parser")
#print(soup)
for vid in soup.find_all('img'):
    print(vid['src'])
