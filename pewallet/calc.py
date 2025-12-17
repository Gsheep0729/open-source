# Calculation module
# File: calc.py
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3

from ewallet_data import MonthlyStatement, Summary

def summarize(ms: MonthlyStatement):
    """Calculates the summary statistics for a single month."""
    # Reset summary
    ms.summary = Summary()

    for amount in ms.transactions:
        if amount > 0:
            ms.summary.total_income += amount
            ms.summary.income_count += 1
        else:
            ms.summary.total_pay += amount # Keep as negative
            ms.summary.pay_count += 1

    # Net balance = Total Income + Total Pay (which is negative)
    ms.summary.net_balance = ms.summary.total_income + ms.summary.total_pay

# -------------------------------------------------------------------
# End of summarize()
# -------------------------------------------------------------------
