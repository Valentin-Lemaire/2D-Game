def file_to_matrix(filename: str) -> list[list]:
    matrix = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            row = [int(char) for char in line]
            matrix.append(row)
    return matrix