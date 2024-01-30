#Write a Python class to find a pair of elements (indices of the two numbers) from 
#a given array whose sum equals a specific target n
class py_solution:
    def findPair(self, nums, target):
        buf = {}
        for i, num in enumerate(nums):
            if target - num in buf:
                return (buf[target - num]+1, i+1)
            buf[num] = i
pairFinder = py_solution()
nums = [10, 20, 10, 40, 50, 60, 70]
target = 50
print(pairFinder.findPair(nums, target))
