# Process module
# Created: Wei Gong (open-src@qq.com)      2025-11-24
# Version: 1.0      License: AGPLv3

from coursegrade import CourseGrade, Grade
from score import score

def computeSort(cg:CourseGrade):
    print("Processing all student grades... \n")
    for g in cg:
        g.total = score(g)

    cg.sort(key=lambda g: g.total)
    print("Processing done!\n\n")
# -------------------------------------------------------------------
# End of computeSort()
# -------------------------------------------------------------------
