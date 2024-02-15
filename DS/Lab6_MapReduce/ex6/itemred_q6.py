# Exercise 6: Write a map reduce program that returns the highest number of confirmed Covid
# cases for each Country/ Region and display the summary operation of confirmed cases in the
# dataset covid_data_lab_ds.csv


from itertools import groupby
from operator import itemgetter
import sys
import pandas as pd

lst=[]

def rmo(file: str, sep='\t'):
    for line in file:
        a =  line.rstrip().split(sep, 1)
        lst.append(int(a[1]))
        yield a


def main(sep='\t'):
    maxv = -1
    data = rmo(sys.stdin, sep='\t')
    loc = None
    # print(groupby(data, itemgetter(0)))
    for cw, g in groupby(data, itemgetter(0)):
        try:
            # lst = [count for _,count in g]
            total_count = max(int(count) for _, count in g)
            # print(lst)
            if maxv<total_count:
                maxv = total_count
                loc = cw
            print("Max in %s:%d" % (cw, total_count))
        except ValueError:
            pass
    # print("Max Confirmed are in: %s%s%d" % (loc, sep, maxv))
    # print(lst)
    df = pd.DataFrame(lst,columns=['Confirmed'])
    print('Summary of Confirmed Cases:')
    summary = df['Confirmed'].describe().apply("{0:.4f}".format)
    print(summary)


if __name__ == "__main__":
    main()