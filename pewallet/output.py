# Output module
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3

from ewallet_data import Account

def output(account: Account):
    print(f"Ewallet Account: {account.name}  {account.gender}   Age:{account.age}   CurrentBalance: {account.current_balance:.2f}")
    print("Account Currency:CNY        Calender Year 2025")
    print("Monthly Transactions:")

    for ms in account.monthly_statements:
        print(f"  {ms.month} netBalance:{ms.summary.net_balance:.2f}")

        print("         transactions:", end="")
        for t in ms.transactions:
            print(f" {t:.2f}", end="")
        print() # Newline

        print(f"         {ms.summary.income_count} incomes: {ms.summary.total_income:.2f}")
        print(f"         {ms.summary.pay_count} pays: {ms.summary.total_pay:.2f}")

# -------------------------------------------------------------------
# End of output()
# -------------------------------------------------------------------
