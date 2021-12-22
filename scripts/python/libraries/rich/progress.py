#!/usr/bin/env python
# coding=utf-8

from rich.progress import track
from time import sleep

for step in track(range(1000)):
   sleep(0.1)
