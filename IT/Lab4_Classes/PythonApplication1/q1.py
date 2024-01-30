#Write a Python class to get all possible unique subsets from a set of distinct 
#integers

class py_solution:
    def subsets(self, current, set):
        if set:
            return self.subsets(current, set[1:]) + self.subsets(current + [set[0]], set[1:])
        return [current]
        
set = [4, 5, 6]
print(py_solution().subsets([], sorted(set)))
