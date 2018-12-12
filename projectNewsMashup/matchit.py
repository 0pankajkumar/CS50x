import feedparser
import urllib.parse
from bs4 import BeautifulSoup

feed = feedparser.parse(f"https://www.aninews.in/rss/feed/category/national/general-news.xml")

s = [{"title": item["title"], "link": item["link"], "description": item["description"]}
    for item in feed["items"]]

print(s[0]['description'])
soup = BeautifulSoup(s[0]['description'], 'html.parser')

w = soup.img
x = w['src']
print(x)