#!/usr/bin/python2
import sys
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw 
import time
from string import printable
SIZE = 128

if len(sys.argv) != 2:
	print "Add font as argument."
	sys.exit(1)


def getwidth_char():
	img = Image.new("RGBA", (2*SIZE,2*SIZE))
	max_char = 0
	draw = ImageDraw.Draw(img)
	font = ImageFont.truetype(sys.argv[1], SIZE)
	for i in xrange(128):
		max_char = max(draw.textsize(chr(i),font=font)[0], max_char) 
	return max_char

def printwidth(width, string):
	img  = Image.new("RGBA", (len(string)*width, SIZE))

	draw = ImageDraw.Draw(img)
	font = ImageFont.truetype(sys.argv[1], SIZE)
	for i in xrange(len(string)):
		draw.text((width*i,0), string[i], font=font)
	return img

def mapper(pxl):
	r,g,b,a = pxl
	dat = 0
	for i in pxl:
		dat=dat<<8;
		dat +=i
	return str(dat)

wdth = getwidth_char()

im = printwidth(wdth, [chr(i) for i in range(128)])
im.save(".".join(sys.argv[1].split('.')[:-1]) + ".png")


# data = list(img.getdata())

# data = map(mapper,data)

# w,h = img.size

# with open('.'.join(sys.argv[1].split('.')[:-1]) + '.txt', "w") as f:
# 	f.write("%d %d\n" % (w,h))
# 	f.write('\n'.join(data))


