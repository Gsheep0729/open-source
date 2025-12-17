# utils module
# File: utils.py
# Created: Wei Gong open-src@qq.com      2025-11-25
# Version: 1.0      License: AGPLv3

def median(list :list[float]) -> float:# passing by reference(mutable object)
    size = len(list)
    if size == 0:
        raise ValueError("median of an empty list")
    # sort the grades
    list.sort()

    # compute the median homework grade
    mid = size // 2
    if size % 2 == 0:
        return (list[mid - 1] + list[mid]) / 2
    else:
        return list[mid]
# -------------------------------------------------------------------
# End of median()
# -------------------------------------------------------------------

