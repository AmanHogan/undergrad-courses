# Aman Hogan-Bailey
# 1001830469
# Version Python 3.8.10
# Ubuntu (20.04.1 LTS Focal Fossa) [CSE 1320 Virtual Machine]

import os

#function recursively finds sum of files
#returns sum of files
def  list_all(start):
    #initializing sum to zero
    sum = 0

    #returning list of files & directories in current directory
    file_list = os.listdir(start)

    #loop though list of entries and for each entry...
    for file in file_list:

        #get the abolute path by joining the starting directory path & entry path
        abs_path = os.path.join(start, file)

        #if entry is a directory, recursively call list_all()
        if os.path.isdir(abs_path):
            sum = sum + list_all(abs_path)

        #if entry is a file add total to the sum
        else:
            sum = sum + os.path.getsize(abs_path)
    return sum

#initialize sum
sum = 0

#initialize starting path
start = "."

#call recursive function that returns sum of al files and directories
sum = list_all(start)

#print sum
print(sum)