# Write a map reduce program that returns the cost of the item that is most expensive, for each
# location in the dataset example.txt

import fileinput

for line in fileinput.input():
	data = line.strip().split("\t")
	if len(data) == 6:
		date, time, location, item, cost, payment = data
		print ("{0}\t{1}".format(location, cost))