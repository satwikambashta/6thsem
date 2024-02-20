import sys

def read_input(file):
    for line in file:
        yield line.strip()

def map_numbers(numbers):
    for num in numbers:
        num = int(num)
        if num % 2 == 0:
            yield "even", 1
        else:
            yield "odd", 1

def main():
    data = read_input(sys.stdin)
    for numbers in data:
        numbers = numbers.split()
        for key, value in map_numbers(numbers):
            print(f"{key}\t{value}")

if __name__ == "__main__":
    main()
