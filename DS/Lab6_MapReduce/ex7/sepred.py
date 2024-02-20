import sys

def read_mapper_output(file):
    for line in file:
        yield line.strip().split("\t", 1)

def reduce_counts(data):
    counts = {"even": 0, "odd": 0}
    for key, value in data:
        counts[key] += int(value)
    return counts

def main():
    data = read_mapper_output(sys.stdin)
    counts = reduce_counts(data)
    for key, value in counts.items():
        print(f"{key}: {value}")

if __name__ == "__main__":
    main()
