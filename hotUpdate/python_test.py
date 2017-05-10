#!/usr/bin/env python
#coding=utf-8

import functools

# def now():
# 	print "2016-11-11"

# f = now
# f()

def log2(func):
	@functools.wraps(func)
	def wrapper(*args, **kw):
		print('call %s()' %(func.__name__))
		return func(*args, **kw)
	return wrapper


def log(func):
	def wrapper(*args, **kw):
		print('begin call %s()' % func.__name__)
		func(*args, **kw)
		print('end call %s() ' % func.__name__)
	return wrapper


def log3(text):
	def decorator(func):
		@functools.wraps(func)
		def wrapper(*args, **kw):
			print("%s %s(): " % (text, func.__name__))
			return func(*args, **kw)
		return wrapper
	return decorator

def log1(text):
	def decorator(func):
		def wrapper(*args, **kw):
			print "%s %s(): " % (text, func.__name__)
			return func(*args, **kw)
		return wrapper
	return decorator



# 把@log放到now()函数的定义处，相当于执行了语句：now = log(now)

@log
def now():
	print "2016-11-11"

now()
print now.__name__


# print now.__name__
# print f.__name__

# if __name__ == "__main__":
# 	pass