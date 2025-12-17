# ewallet_data module
# Defines the data structures for the e-wallet application
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3

from dataclasses import dataclass, field

@dataclass
class Summary:
    income_count: int = 0
    total_income: float = 0.0
    pay_count: int = 0
    total_pay: float = 0.0
    net_balance: float = 0.0

@dataclass
class MonthlyStatement:
    month: str = ""
    transactions: list[float] = field(default_factory=list)
    summary: Summary = field(default_factory=Summary)

@dataclass
class Account:
    name: str = ""
    gender: str = ""
    age: int = 0
    current_balance: float = 0.0
    monthly_statements: list[MonthlyStatement] = field(default_factory=list)

# -------------------------------------------------------------------
# End of dataclasses
# -------------------------------------------------------------------
