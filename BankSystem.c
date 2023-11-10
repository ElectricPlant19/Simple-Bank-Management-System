#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct BankAccount
{
    int accountNumber;
    char accountholderName[100];
    float balance;
};

void createAccount(struct BankAccount *account)
{
    FILE *filePointer = fopen("bankRecord.txt", "a");
    if (filePointer != NULL)
    {
        fprintf(filePointer, "%d %s %.2f\n", account->accountNumber, account->accountholderName, account->balance);
        printf("Your Account Number is  : %d\n", account->accountNumber);
        fclose(filePointer);
        printf("Account created successfully!\n");
    }
    else
    {
        printf("Error in creating account.\n");
    }
}

void displayAccount(int accountNumber)
{
    int number;
    char name[100];
    float balance;
    int accountFound = 0;

    FILE *file = fopen("bankRecord.txt", "r");

    if (file != NULL)
    {
        while (fscanf(file, "%d %s %f", &number, name, &balance) != EOF)
        {
            if (accountNumber == number)
            {
                printf("Account Holder Name: %s\n", name);
                printf("Account Balance: %.2f\n", balance);
                accountFound = 1;
                break;
            }
        }

        fclose(file);

        if (!accountFound)
        {
            printf("Account not found.\n");
        }
    }
    else
    {
        printf("Error in retrieving data\n");
    }
}

void deposit(int accountNumber, float depositAmount)
{
    int number;
    char name[100];
    float balance;

    FILE *file = fopen("bankRecord.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file != NULL && tempFile != NULL)
    {
        while (fscanf(file, "%d %s %f", &number, name, &balance) != EOF)
        {
            if (accountNumber == number)
            {
                if (depositAmount >= 0)
                {
                    balance += depositAmount;
                }
                else
                {
                    printf("Invalid deposit amount!\n");
                    fclose(file);
                    fclose(tempFile);
                    remove("temp.txt");
                    return;
                }
            }

            fprintf(tempFile, "%d %s %.2f\n", number, name, balance);
        }

        fclose(file);
        fclose(tempFile);

        remove("bankRecord.txt");
        rename("temp.txt", "bankRecord.txt");

        printf("Amount Deposited!\n");
    }
    else
    {
        printf("Error in depositing amount\n");
    }
}

void withdraw(int accountNumber, float withdrawAmount)
{
    int number;
    char name[100];
    float balance;

    FILE *file = fopen("bankRecord.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file != NULL && tempFile != NULL)
    {
        while (fscanf(file, "%d %s %f", &number, name, &balance) != EOF)
        {
            if (accountNumber == number)
            {
                if (withdrawAmount >= 0 && balance >= withdrawAmount)
                {
                    balance -= withdrawAmount;
                }
                else
                {
                    printf("Insuficient Funds!\n");
                    fclose(file);
                    fclose(tempFile);
                    remove("temp.txt");
                    return;
                }
            }

            fprintf(tempFile, "%d %s %.2f\n", number, name, balance);
        }

        fclose(file);
        fclose(tempFile);

        remove("bankRecord.txt");
        rename("temp.txt", "bankRecord.txt");

        printf("Amount withdrawn successfully!\n");
    }
    else
    {
        printf("Error in withdrawing amount\n");
    }
}

int main(void)
{
    int choice = 0;
    int accountNumber;

    int initialAccountNumber;

    printf("Welcome to the Bank App!\n");
    while (choice != 5)
    {

        printf("--Press 1 to create a new account.\n--Press 2 to see account details.\n--Press 3 to deposit money to your account.\n--Press 4 to withdraw money from your account.\n--Press 5 to exit\n");

        scanf("%d", &choice);

        if (choice == 1)
        {
            FILE *lastAccountNumberPointer = fopen("LatestAccountNumber.txt", "r");
            fscanf(lastAccountNumberPointer, "%d", &initialAccountNumber);
            fclose(lastAccountNumberPointer);
            char accountHolderName[100];
            struct BankAccount account;
            printf("Enter Name: ");
            scanf("%s", accountHolderName);
            accountNumber = initialAccountNumber;
            initialAccountNumber++;
            strcpy(account.accountholderName, accountHolderName);
            account.accountNumber = accountNumber;
            account.balance = 0;
            createAccount(&account);
        }

        if (choice == 2)
        {
            printf("Enter Account Number: ");
            scanf("%d", &accountNumber);
            displayAccount(accountNumber);
        }

        if (choice == 3)
        {
            float depositAmount;
            printf("Enter Account Number: ");
            scanf("%d", &accountNumber);
            printf("Enter Amount to be Deposited: ");
            scanf("%f", &depositAmount);
            deposit(accountNumber, depositAmount);
        }

        if (choice == 4)
        {
            float withdrawAmount;
            printf("Enter Account Number: ");
            scanf("%d", &accountNumber);
            printf("Enter Amount to be Withdrawn: ");
            scanf("%f", &withdrawAmount);
            withdraw(accountNumber, withdrawAmount);
        }

        if (choice == 5)
            break;

        if (choice < 1 || choice > 5)
        {
            printf("Invalid Choice!\n");
        }

        FILE *tempPointer = fopen("Temp.txt", "w");
        fprintf(tempPointer, "%d", initialAccountNumber);
        fclose(tempPointer);
        remove("LatestAccountNumber.txt");
        rename("Temp.txt", "LatestAccountNumber.txt");
    }

    return 0;
}
