#!/usr/bin/env python

# Simple script to check if the bathroom is available or not.

import json
import urllib2

BATHROOM_IP = '10.0.126.68'

res = urllib2.urlopen('http://' + BATHROOM_IP);
data = res.read(res)
locked = json.loads(data)['locked']

if locked:
    print 'Bathroom occupied.'
else:
    print 'Bathroom available.'
