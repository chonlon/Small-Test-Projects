#!/usr/bin/env python
# coding=utf-8

from requests_html import HTMLSession
import os


url = 'http://localhost:22233'
len_url: int = 0


def create_path(url_arg: str):
    file_path = url_arg[len_url:]
    file_path = './' + file_path
    if not os.path.exists(file_path):
        os.mkdir(file_path)


def write_file(url_arg: str, content):
    file_path = url_arg[len_url:]
    file_path = './' + file_path
    if not os.path.exists(file_path):
        os.mknod(file_path)
    open(file_path, 'wb').write(content)


def get_url(url_arg: str):
    session = HTMLSession()
    return session.get(url_arg)


def download_url(url_arg: str):
    response = get_url(url_arg)
    links = response.html.links

    for link in links:
        print('downloading {} ...'.format(link))

        print(link)
        if not link.find('/') == -1:
            new_link = url_arg + link
            create_path(new_link)
            download_url(new_link)
        else:
            new_link = url_arg + link
            r = get_url(new_link)
            write_file(new_link, r.content)


if not url[-1] == '/':
    url += '/'

len_url = len(url)
download_url(url)


