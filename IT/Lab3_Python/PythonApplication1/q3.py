#Write a python program to implement binary search with recursion.

def binary_search(arr, low, high, x):
    if high >= low:
 
        mid = (high + low) // 2
 
        if arr[mid] == x:
            return mid
 
        elif arr[mid] > x:
            return binary_search(arr, low, mid - 1, x)
 
        else:
            return binary_search(arr, mid + 1, high, x)
 
    else:
        return -1

def main():
    arr = []
 
    n = int(input("Enter number of elements : "))
 
    for i in range(0, n):
        ele = int(input(f"Enter element {i}: "))
        arr.append(ele)  
 
    print(arr)
    x = int(input("Enter number to search"))
    result = binary_search(arr, 0, len(arr)-1, x)
 
    if result != -1:
        print("Element is present at index", str(result))
    else:
        print("Element is not present in array")

if __name__ == '__main__':
	main()