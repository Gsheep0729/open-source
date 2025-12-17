# Process module
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3

from ewallet_data import Account
from calc import summarize

def compute_sort(account: Account):
    print("Processing account transactions... \n")

    for ms in account.monthly_statements:
        # 1. Compute summary for the month
        summarize(ms)

        # 2. Sort transactions within the month (ascending)
        ms.transactions.sort()

    # 3. Sort months based on net balance (ascending)
    account.monthly_statements.sort(key=lambda ms: ms.summary.net_balance)

    print("Processing done!\n\n")

# -------------------------------------------------------------------
# End of compute_sort()
# -------------------------------------------------------------------
