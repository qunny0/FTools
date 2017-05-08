#!/usr/bin/python
#-*- code:utf8 -*-

import sys
import yaml

def parseConfig(path):
    f = open(path)
    yc = yaml.load(f)
    f.close()

    # yaml.dump(yc)

    print yc['age']
    print yc['name']
    print yc['spouse']['name']
    print yc['spouse']['age']

if __name__ == "__main__":
    parseConfig("./config/config.yaml")
