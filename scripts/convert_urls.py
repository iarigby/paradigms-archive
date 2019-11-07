#!/usr/bin/env python

import sys
import os
import requests


filename = sys.argv[1]
name=filename.split('.')[0]
new_lines = []

def download_rss_feed(url):
    req = requests.get(url)
    with open(f'{name}_downloaded.txt', 'a') as f:
        f.write("%s\n" % req.text)

with open(filename) as file:
    for line in file:
        split = line.split(':', 1)
        url = split[1]
        print('getting url')
        try:
            req = requests.get(url)
            new_url = req.url
            print(f'{url} has moved to {new_url}')
            if not "https" in new_url:
                new_lines.append(split[0] + ': ' + new_url)
            download_rss_feed(new_url)
        except:
            print('couldn\'t get link but who cares')


with open(f'{name}_fixed.txt', 'w') as f:
    for item in new_lines:
        f.write("%s\n" % item)
