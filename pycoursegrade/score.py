# Score module
# File: score.py
# Created: Wei Gong open-src@qq.com      2025-11-25
# Version: 1.0      License: AGPLv3

from coursegrade import Grade
from utils import median

def score(g: Grade) -> float:
    return 0.2 * g.midterm + 0.4 * g.final + 0.4 * median(g.homeworks)
