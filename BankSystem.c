#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int choice;
    int accountNumber;

    printf("Welcome to the Bank App!\n");
    printf("--Press 1 to create a new account.\n--Press 2 to see account details.\n--Press 3 to deposit money to your account.\n--Press 4 to withdraw money from your account.\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        char accountHolderName[100];
        struct BankAccount account;

        printf("Enter Name: ");
        scanf("%s", accountHolderName);
        printf("Enter Account Number: ");
        scanf("%d", &accountNumber);

        strcpy(account.accountholderName, accountHolderName);
        account.accountNumber = accountNumber;
        account.balance = 0;
        createAccount(&account);
        break;
    }

    case 2:
        printf("Enter Account Number: ");
        scanf("%d", &accountNumber);
        displayAccount(accountNumber);
        break;

    case 3:
    {
        float depositAmount;
        printf("Enter Account Number: ");
        scanf("%d", &accountNumber);
        printf("Enter Amount to be Deposited: ");
        scanf("%f", &depositAmount);
        deposit(accountNumber, depositAmount);
        break;
    }

    case 4:
    {
        float withdrawAmount;
        printf("Enter Account Number: ");
        scanf("%d", &accountNumber);
        printf("Enter Amount to be Withdrawn: ");
        scanf("%f", &withdrawAmount);
        withdraw(accountNumber, withdrawAmount);
        break;
    }

    default:
        printf("Invalid choice.\n");
    }

    return 0;
}