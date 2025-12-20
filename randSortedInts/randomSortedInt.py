import random

def create_sorted_random_int_file():
    # User inputs
    filename = input("Enter output file name (e.g., numbers.txt): ")
    length = int(input("Enter number of integers to generate: "))

    # Optional: customize range
    min_val = int(input("Enter minimum integer value: "))
    max_val = int(input("Enter maximum integer value: "))

    # Generate random integers
    numbers = [random.randint(min_val, max_val) for _ in range(length)]

    # Sort the list
    numbers.sort()

    # Write to file
    with open(filename, "w") as f:
        for num in numbers:
            f.write(f"{num}\n")

    print(f"File '{filename}' created with {length} sorted random integers.")

if __name__ == "__main__":
    create_sorted_random_int_file()
