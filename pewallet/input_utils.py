# Input Utils module
# File: input_utils.py
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3

import ewallet_data

def parse_header(line: str, account: ewallet_data.Account) -> bool:
    try:
        parts = line.split()
        if len(parts) < 4:
            return False
        account.name = parts[0]
        account.gender = parts[1]
        account.age = int(parts[2])
        account.current_balance = float(parts[3])
        return True
    except ValueError:
        return False

def parse_statement(line: str, ms: ewallet_data.MonthlyStatement) -> bool:
    parts = line.split()
    if not parts:
        return False

    ms.month = parts[0]
    for s in parts[1:]:
        try:
            val = float(s)
            ms.transactions.append(val)
        except ValueError:
            continue
    return True

# -------------------------------------------------------------------
# End of parsing functions
# -------------------------------------------------------------------
