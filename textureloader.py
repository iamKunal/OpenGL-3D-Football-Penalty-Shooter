#!/usr/bin/python2
import sys
from PIL import Image

if len(sys.argv) != 2:
	print "Add image as argument."
	sys.exit(1)

def mapper(pxl):
	r,g,b,a = pxl
	dat = 0
	for i in pxl:
		dat=dat<<8;
		dat +=i
	return str(dat)

texture = Image.open(sys.argv[1])

data = list(texture.getdata())

data = map(mapper,data)

w,h = texture.size

with open('.'.join(sys.argv[1].split('.')[:-1]) + '.txt', "w") as f:
	f.write("%d %d\n" % (w,h))
	f.write('\n'.join(data))


