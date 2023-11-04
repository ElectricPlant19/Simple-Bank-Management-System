# Simple Bank Management System

The **Simple Bank Management System** is a basic console application written in C language that allows users to perform simple banking operations such as creating an account, checking account details, depositing money, and withdrawing money.

## Features

1. **Create a New Account:**
   - Users can create a new bank account by providing their name and account number.
   - The account details are stored in a file called "bankRecord.txt".

2. **Display Account Details:**
   - Users can view their account details by entering their account number.
   - The system retrieves the account information from the "bankRecord.txt" file and displays it on the console.

3. **Deposit Money:**
   - Account holders can deposit money into their accounts by specifying the account number and the amount to be deposited.
   - The deposited amount is added to the account balance.

4. **Withdraw Money:**
   - Account holders can withdraw money from their accounts by specifying the account number and the amount to be withdrawn.
   - The system checks if the account has sufficient funds before allowing the withdrawal.

## How to Use

### 1. Compile the Code
Compile the C code using a C compiler (e.g., gcc).
```bash
gcc -o bank_management_system bank_management_system.c
