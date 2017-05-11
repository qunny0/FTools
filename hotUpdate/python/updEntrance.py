#/usr/bin/python
#-*-coding:utf-8-*-

import packup
from updUtil import *

import sys
import yaml
from termcolor import *

def readConfig():
	with open("config.yaml", 'r') as stream:
		try:
			yc = yaml.load(stream)

			G_setValue('bigServer', yc['bigServer'])
			G_setValue('language', yc['language'])
			G_setValue('allVersion', yc['allVersion'])
			G_setValue('svnInfo', yc['svnInfo'])

			print colored("BIG_SERVER : " + G_getValue('bigServer'),"green")
			print colored("LANGUAGE : " + G_getValue('language'),"green")
			print colored("ALL_VERSION : " + ','.join(map(str, G_getValue('allVersion'))), "green")

		except yaml.YAMLError as exc:
			print(exc)


def package():
	for version in G_getValue('allVersion'):
		packup.package(version)

def SVNcommit():
	pass

if __name__ == '__main__':
	G_init()

	readConfig()

	print("")

	package()

	print("")

	SVNcommit()
