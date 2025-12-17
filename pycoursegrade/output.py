# Output module
# Created: Wei Gong (open-src@qq.com)      2025-11-24
# Version: 1.0      License: AGPLv3

from coursegrade import CourseGrade, Grade

def output(cg:CourseGrade):
    print("Course: software construction and implementation\nCredit: 5")
    print("name      total");
    for g in cg:
        print(f"{g.name:<10}{g.total:<.1f}")
# -------------------------------------------------------------------
# End of output()
# -------------------------------------------------------------------


