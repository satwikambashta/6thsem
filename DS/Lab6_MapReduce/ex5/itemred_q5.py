# Try to apply finding max value using map reduce concept for the output of Heart
# Disease dataset, covid_19_data dataset, example dataset and German Credit dataset.
# Students can decide their own way of displaying results (can work on any columns in the
# dataset ) on the dataset mentioned.

from itertools import groupby
from operator import itemgetter
import sys

def read_mapper_output(file, separator='\t'):
	for line in file:
		yield line.rstrip().split(separator, 1)

def main(separator='\t'):

	# input comes from STDIN (standard input)
	data = read_mapper_output(sys.stdin, separator=separator)
	# groupby groups multiple word-count pairs by word,
	# and creates an iterator that returns consecutive keys and their group:
	# current_word - string containing a word (the key)
	# group - iterator yielding all ["&lt;current_word&gt;", "&lt;count&gt;"] items
	for current_word, group in groupby(data, itemgetter(0)):
		try:
			total_count = max(int(count) for current_word, count in group)
			print ("%s%s%d" %(current_word, separator, total_count))
		except ValueError:
			# count was not a number, so silently discard this item
			pass
			
if __name__ == "__main__":
	main()