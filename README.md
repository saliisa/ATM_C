# **ATM C**

## **System Description**  
This project is a simple ATM app made in C.

Users can:
- Log in with the account number
- Input PIN
  - User has maximum 3 attempts to input the PIN. If failed, the program will show the user an error message and close the account. <br/> <br/>

   If the user succeeds, a menu allows users to choose options which include:
1. Withdraw money
    - Min amount to withdraw is 20e, Max amount is 1000e
    - ATM only gives out in 20e and 50e notes; user can withdraw either 20e or 40e or more at intervals of ten (e.g. 50e, 60e, 70e etc)
    -  The ATM will continue to ask for the amount to be withdrawn until a valid value or zero is given (zero stops the withdrawl process)
    -  The balance of the account must be at least 20e after withdrawal. The user cannot withdraw all money from the account, there must be at least 20 euros left in the bank account
    -  The program will print the amountof 50e and 20e notes and alsp the balance of the account after the withdrawal
    -  The machine will give the money with th least amount of bank notes (e.g. if the money to withdraw is 270e, the program will "give" five 50e notes and one 20e note -->  (5x50 + 1x20 = 270))

2. Deposit money
   - Min deposit is 10.0 euros and maximum is 1000.0 euros.
   - The balance of the account is max 2000.0 euros. The user cannot deposit money if the inputted amount added to the current balance exceeds the maximum amount, i.e. 2000.0 euros.
   - The ATM will continue to ask for the amount to be deposited until a valid value or zero is given (zero stops the deposit process)

3. Query Balance
    - Prints out current balance

4. Quit
    - Quits the program

  After quitting, the final balance is printed out.
 

The program utilizes file handling, functions, error checking, pointers and validation.

## **Demo Account**  
Account Number: 12345 <br />
Pin: 1234 <br />
Original Balance: 99.90 <br />

## **Project Files**  
`ATM.c` - ATM file <br />
`12345.acc` - Account file

