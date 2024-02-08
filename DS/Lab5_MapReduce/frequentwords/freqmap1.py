from __future__ import print_function
import sys

for line in sys.stdin:
# create tuples of all words in line
	L = [ (word.strip().lower(), 1 ) for word in line.strip().split() ]
	# increase counters
	for word, n in L:
	# write the results to STDOUT (standard output);
	# what we output here will be the input for the
	# Reduce step, i.e. the input for reducer.py
	## tab-delimited; the trivial word count is 1
		print( '%s\t%d' % (word, n) )