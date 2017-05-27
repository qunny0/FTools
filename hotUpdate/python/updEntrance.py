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
		print ""
		packup.package(version)

def SVNcommit():
	pass

if __name__ == '__main__':
	currentDir = os.path.abspath(os.path.join(os.path.dirname(__file__)))
	os.chdir(currentDir)
	print currentDir

	G_init()

	readConfig()

	package()

	SVNcommit()
