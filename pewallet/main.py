# A program that calculates the monthly stats of an e-wallet
# Created: GY      2025-12-04
# Version: 1.0      License: AGPLv3
#
# E-Wallet project using top-down, stepwise refinement approach
# Multiple sourcefiles version

import sys
from ewallet_data import Account
from input_data import read
from process import compute_sort
from output import output

def main():
    # Initialize Account object
    my_account = Account()

    try:
        read(my_account)
        compute_sort(my_account)
        output(my_account)
    except Exception as e:
        print(f"An error occurred: {e}")

    # Print current working directory (mimicking the C++ example)
    import os
    print("以下是你的运行路径")
    print(f"当前程序工作目录：{os.getcwd()}")

# -------------------------------------------------------------------
# End of main()
# -------------------------------------------------------------------

if __name__ == "__main__":
    sys.exit(main())
