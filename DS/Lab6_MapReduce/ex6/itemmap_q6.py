# Exercise 6: Write a map reduce program that returns the highest number of confirmed Covid
# cases for each Country/ Region and display the summary operation of confirmed cases in the
# dataset covid_data_lab_ds.csv


import fileinput
for line in fileinput.input():
    data = line.strip().split(",")
    if len(data) == 8:
        SNo, Observation,  Province, Country, LastUpdate, Confirmed, Deaths, Recovered = data
        if not Confirmed.isnumeric():
            continue
        print("{0}\t{1}".format(Country, Confirmed))