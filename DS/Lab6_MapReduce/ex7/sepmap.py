import sys
import random

def generate_random_numbers(n):
    for _ in range(n):
        yield str(random.randint(1, 100))

def map_numbers(numbers):
    for num in numbers:
        num = int(num)
        if num % 2 == 0:
            yield "even", 1
        else:
            yield "odd", 1

def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 100
    numbers = generate_random_numbers(n)
    for key, value in map_numbers(numbers):
        print(f"{key}\t{value}")
