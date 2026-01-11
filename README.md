# **ATM C**

## **System Description**  
This project is a simple ATM app made in C.

Users can:
- Log in with the account number
- Input PIN
  - User has maximum 3 attempts to input the PIN. If failed, the program will show the user an error message and close the account. <br/> <br/>
After log in, a menu allows users to choose options which include:
  - Withdraw money
    - Min amount to withdraw is 20e, Max amount is 1000e
    - ATM only gives out in 20e and 50e notes; user can withdraw either 20e or 40e or more at intervals of ten (e.g. 50e, 60e, 70e etc)
    -  The ATM will continue to ask for the amount to be withdrawn until a valid value or zero is given (zero stops the withdrawl process)
    -  
  - Deposit money
  - Query Balance
  - Quit

  After quitting, the balance is printed out.
 

The program utilizes file handling, functions, error checking, 

## **Demo Account**  
Account Number: 12345 <br />
Pin: 1234 <br />
Original Balance: 99.90 <br />

## **Project Files**  
`ATM.c` - ATM file <br />
`12345.acc` - Account file

