# Write a Python class to implement pow(x, n).

class Power:
    # def pow(self, x: float, n: int) -> float:
    def pow(self, x, n):
        if n == 0:
            return 1
        elif n < 0:
            return 1 / self.pow(x, -n)
        elif n % 2 == 0:
            return self.pow(x * x, n // 2)
        else:
            return x * self.pow(x, n - 1)

power = Power()
x = 2
n = 3
print(power.pow(x, n))

x = 2
n = -2
print(power.pow(x, n))
