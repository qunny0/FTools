#-*-coding:utf-8-*-

import commands
import subprocess

def uu_executeCommand(command):
	st, output = commands.getstatusoutput(command)

	assert st == 0, "execute " + command + " failed!"

	print output

	return st, output

def uu_executeProcess(command):
	p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)

	returnCode = p.poll()
	while returnCode is None:
		print p.stdout.readline().strip()
		returnCode = p.poll()

	print p.stdout.read()

	return returnCode

def G_init():
	global _GLOBAL_DICT
	_GLOBAL_DICT = {}

def G_setValue(key, value):
	_GLOBAL_DICT[key] = value

def G_getValue(key, defValue=None):
	try:
		return _GLOBAL_DICT[key]
	except KeyError:
		return defValue
