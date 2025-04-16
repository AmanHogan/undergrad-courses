def create_puzzle(filename):
    filehandle = open(filename, 'r')
    puzzle = list(filehandle.readline().replace(' ', '').strip()) + list(filehandle.readline().replace(' ', '').strip()) + list(filehandle.readline().replace(' ', '').strip())
    for i in range(len(puzzle)):
        puzzle[i] = int(puzzle[i])
    return puzzle
