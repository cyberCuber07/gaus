
import numpy as np
import os
import sys

#path = "C:\\USers\\krzyk\\Desktop\\I\\jimp\\lmp9\\trunk\\tests\\data"
#tpath = "C:\\USers\\krzyk\\Desktop\\I\\jimp\\lmp9\\trunk\\tests\\results"

path = "../data"
tpath = "../results"

name = "test_"

sing_path = "../../sing_list"
sing_list = []

def read_file(path):
    file = open(path, "r")
    next(file)
    mat = []
    for line in file:
        tmp = line.split(' ')
        mat.append([float(x) for x in tmp[:-1]])

    return mat


def write_into(path, x):
    file = open(path, "w")
    size = x.size
    file.write(str(size))
    file.write(" ")
    file.write("1\n")
    for val in x:
        file.write(str(val)[1:-1])
        # print(str(val)[1:-1])
        file.write("\n")


def main():
    if len(sys.argv) != 2:
        print("Incorrect input!")
    else:
        for i in range(1, int(sys.argv[1])+1):
            a_path = os.path.join(path, name + str(i))
            b_path = os.path.join(a_path + "_b_")
            A = read_file(a_path)
            b = read_file(b_path)
            A = np.array(A)
            s = A.shape
            try:
                if s[0] == s[1]:
                    x = np.linalg.solve(A, b)
                    tmp_test = os.path.join(tpath, name + str(i) + "_x_")
                    write_into(tmp_test, x)
            except np.linalg.LinAlgError as err:
                print(i, "singular matrix")
                sing_list.append(i)
                continue

        sing_file = open(sing_path, "a")
        for i in sing_list:
            sing_file.write(str(i))
            sing_file.write("\n")




if __name__=="__main__":
    main()
