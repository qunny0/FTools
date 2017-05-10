#-*-coding:utf-8-*-

import commands

def uu_executeCommand(command):
	st, output = commands.getstatusoutput(command)

	assert st == 0, "execute " + command + " failed!"

	return st, output
