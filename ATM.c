#include <stdio.h>
#include <string.h>

//utility functions
int readInteger(void);
double readDouble(void);
void clearBuffer(void);
void readCharacterString(char aString[], int stringSize);

int accValidation(char *accNum);
void menu(char *accNum);
double queryBalance(char *accNum);
void withdrawMoney(char *accNum);
void updateBalance(char *accNum, double newBalance);
void depositMoney(char* accNum);

int main(void){

    char accFileName[256];

    printf("*** Welcome to use the ATM! ***");
    if(accValidation(accFileName) == 1){
         menu(accFileName);
    } else{
        printf("\nYour account is closed.\n");
    }

    return 0;
}

int accValidation(char *accNum){

    FILE *accFile;
    char pinCode[256];
    char checkPin[256];
    int result = 1;
    int pinCount = 0;

     while(1){
            printf("\nGive account number: ");
            readCharacterString(accNum, 256);
            strcat(accNum, ".acc");

            if((accFile = fopen(accNum, "r")) != NULL){
                    if (fgets(checkPin, 256, accFile) == NULL) {
                        printf("Error reading PIN from file.\n");
                        fclose(accFile);
                    }
                    if (checkPin[strlen(checkPin)-1] == '\n'){//remove newline
                            checkPin[strlen(checkPin)-1] = '\0';
                    }
                    if (checkPin[strlen(checkPin)-1] == '\r'){//remove carriage return
                        checkPin[strlen(checkPin)-1] = '\0';
                    }

                   for(pinCount = 1; pinCount <= 3; pinCount++){

                        printf("\n\nGive your account PIN code (%d. try): ", pinCount);
                        readCharacterString(pinCode, 256);
                        result = strcmp(pinCode, checkPin);

                        if(result == 0){
                            fclose(accFile);
                             return 1;

                        } else{
                            printf("***** Wrong PIN code! Try again.\n");

                             if(pinCount == 3){
                                printf("\n********* Too many wrong attempts\n");
                                  fclose(accFile);
                                return 0;
                            }
                        }
                    }
                } else{
                    printf("\nWrong account number! \n");
            }
    }
    fclose(accFile);
}


void menu(char *accNum){

    double balance = 0.0;
    int option = 0;

     while(option != 9){

        printf("\n\n-------ATM MENU------\n");
        printf("\nSelect an option\n");
        printf("1. = Withdrawl\n");
        printf("2. = Deposit\n");
        printf("3. = Query Balance\n");
        printf("9. = Quit\n\n");

        printf("Your choice: ");
        option = readInteger();

        switch(option){
            case 1:
                //Withdraw
                 withdrawMoney(accNum);
                break;
            case 2:
                //Deposit
                 depositMoney(accNum);
                break;
            case 3:
                //Query
                balance = queryBalance(accNum);
                printf("\n\n***** Balance: %.2f \n\n", balance);

                printf("Press enter");
                getchar();
                break;
            case 9:
                balance = queryBalance(accNum);
                printf("\n\nThe balance %.2f saved to the account file \"%s\". \n\n", balance, accNum);
                printf("*********** Goodbye **********\n");
                break;
            default:
                printf("\nWrong option, try again.\n");
                break;

            }
    }
}

double queryBalance(char *accNum){ //return statement

    double balance = 0.0;
    FILE *file;
    char balanceNum[100];

     if((file = fopen(accNum, "r")) != NULL){
           while(fgets(balanceNum, sizeof(balanceNum), file) != NULL){
                if(fscanf(file, "%lf", &balance) == 1){
                    fclose(file);
                    return balance;
                } else{
                    printf("\nCould not read balance\n");
                    break;
                }
        }
     }else{
        printf("Could not read file.");
    }

     fclose(file);
}


void withdrawMoney(char *accNum){

    int withdrawAmt = 0;
    int twentyEuro = 0;
    int fiftyEuro = 0;
    int remainingAmt = 0;
    int success = 0;
    int maxAmt = 1000;
    int minAmt = 20;
    double newBalance = 0.0;
    double balance = queryBalance(accNum);

    while(success != 1){
            printf("\n\nGive amount to withdraw (full tens: 20, 40-1000): ");
            withdrawAmt = readInteger();

            if (withdrawAmt == 0 ) {
                     printf("\n************\n");
                     printf("Cancelled\n");
                     printf("************\n");
                    break;
                }

            if(withdrawAmt >= minAmt && withdrawAmt <= maxAmt){
                 if (withdrawAmt % 10 != 0 || withdrawAmt == 30){
                        printf("\n-- Invalid Amount. Please try again.\n");

                } else if(withdrawAmt > balance ){
                     printf("\n*** Insufficient balance ***\n");
                }else{
                    fiftyEuro = withdrawAmt / 50;
                    remainingAmt = withdrawAmt % 50;

                         while(fiftyEuro >= 0 && remainingAmt % 20 != 0){
                            fiftyEuro--;
                            remainingAmt = withdrawAmt - (fiftyEuro * 50);
                         }

                        if(remainingAmt % 20 == 0){
                                 twentyEuro = remainingAmt / 20;

                                 newBalance = balance - withdrawAmt;

                                if(newBalance < minAmt){
                                        printf("\n** Unable to withdraw\n** Account must have at least 20e left after withdrawal\n");


                                } else{
                                    printf("\n************\n");
                                    printf("Withdrawl ok\n");
                                    printf("************\n\n");

                                    printf("\nAmount %d:\n", withdrawAmt);

                                    printf("*** Notes 50: %d\n", fiftyEuro);
                                    printf("*** Notes 20: %d\n", twentyEuro);

                                    int check = (fiftyEuro * 50) + (twentyEuro * 20);

                                    printf("\n\nCheck: (%d * %d) + (%d * %d) = %d\n", fiftyEuro, 50, twentyEuro, 20 , check );

                                    balance -=withdrawAmt;
                                    updateBalance(accNum, balance);

                                     success = 1;
                                }

                        }
                }

            } else{

                if(withdrawAmt < 0 && withdrawAmt != -1){
                    printf("\n-- Invalid Amount. Please try again.\n");

                } else if(withdrawAmt < minAmt && withdrawAmt != -1){
                    printf("\n-- Invalid amount. Minimum amount is %de. --\n", minAmt);

               } else if( withdrawAmt > maxAmt){
                    printf("\n-- Invalid amount. Maximum amount is %de. --\n", maxAmt);
               }
            }
    }

    printf("\n\n***** Balance: %.2f \n\n", balance);
    printf("Press enter");
    getchar();
}

void updateBalance(char *accNum, double newBalance){

    FILE *file = fopen(accNum, "r");
    FILE *temp =fopen("temp.acc", "w");

    char line[100];
    int lineNum = 0;

    if(file == NULL || temp == NULL){
        printf("Error reading file");

    } else{
        while(fgets(line, sizeof(line), file)){
            lineNum++;
            if(lineNum == 2){
                fprintf(temp, "%.2lf", newBalance);
            } else{
                fputs(line, temp);
            }
        }
    }
    fclose(file);
    fclose(temp);

     if (remove(accNum) != 0) {
        printf("\nCould not delete old account file");
    }
    if (rename("temp.acc", accNum) != 0) {
        printf("\nCould not rename temp file");
    }
}


void depositMoney(char* accNum){

    double depositAmt = 0.0;
    int success = 0;
    double minAmt = 10.00;
    double maxAmt = 1000.00;
    double maxBalance = 2000.00;
    double newBalance = 0.0;
    double balance = queryBalance(accNum);

    while(success != 1){

            printf("\n\nGive money to deposit (min. 10.00, max. 1000.00, (max. balance 2000.00)): ");
            depositAmt = readDouble();

             if (depositAmt == 0 ) {
                     printf("\n************\n");
                     printf("Cancelled\n");
                     printf("************\n");
                    break;
                }

                if(depositAmt >= minAmt && depositAmt <= maxAmt ){
                       newBalance = depositAmt + balance;

                       if(newBalance >= maxBalance){
                            printf("\n-- Exceeds Max Balance 2000.00e\n");
                       } else{
                             printf("\n************\n");
                             printf("Deposit ok\n");
                             printf("************\n\n");

                             balance += depositAmt;

                             updateBalance(accNum, balance);
                             success = 1;
                       }

                } else{

                    if(depositAmt < 0 && depositAmt != -1){
                        printf("\n-- Invalid Amount. Please try again.\n");

                    } else if(depositAmt < minAmt && depositAmt != -1){
                        printf("\n-- Invalid amount. Minimum amount is %.2fe. --\n\n", minAmt);

                    } else if( depositAmt > maxAmt){
                        printf("\n-- Invalid amount. Maximum amount is %.2fe. --\n\n", maxAmt);
                    }
                }
    }

    printf("\n\n***** Balance: %.2f \n\n", balance);
    printf("Press enter");
    getchar();
}

int readInteger(void) {

    int number;
    char character;
    int status;

     if ((status = scanf("%d%c", &number, &character)) == 0|| (2 == status && character != '\n')) {
           clearBuffer();
            printf("\nYou did not enter an integer!\n");
            return -1;
    } else{
            return number;
    }
}

double readDouble(void) {

    double number;
    char character;
    int status;

    if ((status = scanf("%lf%c", &number, &character)) == 0 || (2 == status && character != '\n')) {
        clearBuffer();
        printf("\nYou did not enter a real number!\n");
            return -1;
    } else{
        return number;
    }

}

void clearBuffer(void) {

    while (fgetc(stdin) != '\n');
}

void readCharacterString(char aString[], int stringSize) {

    fgets(aString, stringSize, stdin);

    if (aString[strlen(aString) - 1] == '\n')
        aString[strlen(aString) - 1] = '\0';
    else
        clearBuffer();
}
