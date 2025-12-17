# Input module
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3

from ewallet_data import Account, MonthlyStatement
from input_utils import parse_header, parse_statement

def read(account: Account):
    print("Reading an ewallet account from a file... \n")
    try:
        with open('ewallet.dat', 'r') as file:
            lines = file.readlines()

            if not lines:
                raise ValueError("File is empty")

            # Read Header (First line)
            if not parse_header(lines[0], account):
                raise ValueError("Invalid account header format")

            # Read Transactions (Remaining lines)
            for line in lines[1:]:
                line = line.strip()
                if not line:
                    continue

                ms = MonthlyStatement()
                if parse_statement(line, ms):
                    account.monthly_statements.append(ms)

        print("Reading done!\n\n")
    except FileNotFoundError:
        print("Error: ewallet.dat not found.")
        raise

# -------------------------------------------------------------------
# End of read()
# -------------------------------------------------------------------
