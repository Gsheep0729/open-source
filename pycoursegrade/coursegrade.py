# dataclass Grade
#
# Created: Wei Gong (open-src@qq.com) 2025-11-24


import sys
from dataclasses import dataclass, field
from typing import TypeAlias

@dataclass
class Grade:
    name: str = ""
    midterm: float = 0
    final: float = 0
    homeworks: list = field(default_factory=list) # 每个Grade实例有独立列表

# -------------------------------------------------------------------
# End of class Grade
# -------------------------------------------------------------------
CourseGrade: TypeAlias = list[Grade]
