from html.parser import HTMLParser
from urllib.request import urlopen
from urllib import parse


class Parser(HTMLParser):

    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for (key, value) in attrs:
                if key == 'href':
                    newUrl = parse.urljoin(self.baseUrl, value)
                    self.links = self.links + [newUrl]

    def get_links(self, website):
        self.links = []
        self.baseUrl = website
        response = urlopen(website)
        if response.getheader('Content-Type') == 'text/html; charset=utf-8':
            htmlBytes = response.read()
            htmlString = htmlBytes.decode("utf-8")
            self.feed(htmlString)
            return htmlString, self.links
        else:
            return "", []


def WebCrawler(website, word, page_amount):
    VisitPages = [website]
    numberVisited = 0
    while numberVisited < page_amount and VisitPages != []:
        numberVisited = numberVisited + 1
        website = VisitPages[0]
        VisitPages = VisitPages[1:]
        foundWord = False
        try:
            print(numberVisited, "Scrounging:", website)
            parser = Parser()
            data, links = parser.get_links(website)
            if data.find(word) > -1:
                foundWord = True
                VisitPages = VisitPages + links
                print("Accomplished")
            if foundWord:
                print("The word", word, "could be found at", website)
            else:
                print("The word", word, "could not be found")
        finally:
            print("")