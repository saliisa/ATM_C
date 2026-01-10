# **ATM C**

The account number is 12345 and the password is the first entry in 12345.acc.
The program allows the user to log in to this account.
Once logged in the user has options to withdraw money, deposit money, query balance or quit the program.

## **System Description**  
This project is a simple ATM app made in C.

Users can:
- Log in with the account number
- Input Pin, with maximum 3 attempts
  After log in, a menu allows users to choose options which include:
  - Withdraw money
    - Min amount to withdraw is 20e, Max amount is 1000e
    - ATM only gives out in 20e and 50e notes; user can withdraw either 20e or 40e or more at intervals of ten (e.g.            50e, 60e, 70e etc)
    -  
  - Deposit money
  - Query Balance
  - Quit

  After quitting, the balance is printed out.
 

The program utilizes file handling, functions, error checking, 

## **Demo Account**  
Account Number: 12345
Pin: 1234
Original Balance: 99.90

## **Project Files**  
`ATM.c` - ATM file
`12345.acc` - Account file

