#!/usr/bin/python

import sys

if len(sys.argv) != 3:
    print "Usage:"
    print "  %s <file> <key>" % (sys.argv[0])
    sys.exit(1)

with open(sys.argv[1], "rb") as f:
    content = f.read()

key = sys.argv[2]
keylen = len(key)
size = len(content)
out = ''

count = 0
i = 0
last = 0
with open(sys.argv[1], "wb") as f:
    while i < size:
        if content[i:i+keylen] == key:
            if i > last:
                f.write(content[last:i])
            count += 1
            f.write("%s(%d)" % (key, count))
            i += keylen
            last = i
        else:
            i += 1

    if i > last:
        f.write(content[last:i])

print count
