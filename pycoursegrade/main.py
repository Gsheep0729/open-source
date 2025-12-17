# A program that calculates the scores of all students in a course
# Created: Wei Gong (open-src@qq.com)      2025-11-24
# Version: 1.0      License: AGPLv3
#
# Coursegrade project using top-down, stepwise refinement approach
# Multiple sourcefiles version
#
# The 1st level decomposition of coursegrade calculation
import sys
from coursegrade import CourseGrade, Grade
from input import read
from process import computeSort
from output import output

def main():
    cg : CourseGrade = []
    read(cg)
    computeSort(cg)
    output(cg)
# -------------------------------------------------------------------
# End of main()
# -------------------------------------------------------------------

if __name__ == "__main__":
    sys.exit(main())
