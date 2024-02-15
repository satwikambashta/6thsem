# Try to apply finding max value using map reduce concept for the output of Heart
# Disease dataset, covid_19_data dataset, example dataset and German Credit dataset.
# Students can decide their own way of displaying results (can work on any columns in the
# dataset ) on the dataset mentioned.

import fileinput

for line in fileinput.input():
	data = line.strip().split(",")
	if len(data) == 14:
		age,sex,cp,trestbps,chol,fbs,restecg,thalach,exang,oldpeak,slope,ca,thal,target = data
		if not chol.isnumeric():
			continue
		print ("{0}\t{1}".format(age, chol))