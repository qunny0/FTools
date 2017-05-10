#/usr/bin/python
#-*-coding:utf-8-*-

import packup

import sys
import yaml
from termcolor import *

BIG_SERVER = ''
LANGUAGE = ''
ALL_VERSION = ''

def readConfig():
	with open("config.yaml", 'r') as stream:
		try:
			yc = yaml.load(stream)
			global BIG_SERVER
			global LANGUAGE
			global ALL_VERSION

			BIG_SERVER=yc['bigServer']
			LANGUAGE=yc['language']
			ALL_VERSION=yc['allVersion']
			print colored("BIG_SERVER : " + BIG_SERVER,"green")
			print colored("LANGUAGE : " + LANGUAGE,"green")
			print colored("ALL_VERSION : " + ','.join(map(str, ALL_VERSION)), "green")
		except yaml.YAMLError as exc:
			print(exc)


def package():
	for version in ALL_VERSION:
		print colored("begin package : " + BIG_SERVER + "  " + LANGUAGE + "  " + str(version), "green")
		packup

def SVNcommit():
	pass

if __name__ == '__main__':
	readConfig()

	print("")

	package()

	print("")

	SVNcommit()
