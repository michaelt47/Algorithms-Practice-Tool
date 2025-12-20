import random

def create_random_int_file():
    # User inputs
    filename = input("Enter output file name (e.g., numbers.txt): ")
    length = int(input("Enter number of integers to generate: "))

    # Optional: customize range
    min_val = int(input("Enter minimum integer value: "))
    max_val = int(input("Enter maximum integer value: "))

    # Generate and write integers
    with open(filename, "w") as f:
        for _ in range(length):
            f.write(f"{random.randint(min_val, max_val)}\n")

    print(f"File '{filename}' created with {length} random integers.")

if __name__ == "__main__":
    create_random_int_file()
