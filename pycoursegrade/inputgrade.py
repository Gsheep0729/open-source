# readonegrade module
# File: readonegrade.py
# Created: Wei Gong open-src@qq.com      2025-11-25
# Version: 1.0      License: AGPLv3
import coursegrade

def readgrade(line: str, g: coursegrade.Grade)-> bool:
    print("  Reading a student grade... ", end='')
    numbers=line.split()
    g.name = numbers[0]
    g.midterm = float(numbers[1])
    g.final = float(numbers[2])
    for s in numbers[3:]:
        h = float(s)
        g.homeworks.append(h)
    if len(g.homeworks) == 0:
        raise ValueError("No homework was done.")
    print(f"Done!  {g.name}")
    return True;


