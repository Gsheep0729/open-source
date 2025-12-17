# Input module
# Created: Wei Gong (open-src@qq.com)      2025-11-24
# Version: 1.0      License: AGPLv3
from coursegrade import CourseGrade, Grade
from inputgrade import readgrade

def read(cg:CourseGrade):
    print("Reading all student grades (name midterm final homework) from a file... ")
    with open('coursegrade.dat', 'r') as file:
        for line in file:
            g = Grade()
            if readgrade(line, g):
                cg.append(g)
    print("Reading done!\n")
# -------------------------------------------------------------------
# End of read()
# -------------------------------------------------------------------


