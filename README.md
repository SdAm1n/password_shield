# Password Shield

 Password Shield is a `Password Manager` written in C++. This program uses file (password.txt) to store Website name, Username/Email and Password. `RSA Algorithm` is implemented inside this program. Password `Encryption` and `Decryption` is done by `RSA Algorithm`. [RSA algorithm](https://www.geeksforgeeks.org/rsa-algorithm-cryptography/) is an asymmetric cryptography algorithm.

This program can do the following things:

First asks for the master password which is `1234`

1. `Generates` a pseudo random password
   1. Generated password is `automatically copied` to clipboard using ClipboardXX library
   2. Passwords can be saved inside the password.txt file
2. `Stores` the password in password.txt file. Before storing it encrypts the password using `Public Key`.
3. `Finds` the saved passwords from password.txt . It finds the encrypted password then decrypts it using `Private Key` before printing.
4. `Change` a particular password. Finds the encrypted password then replaces it with another new encrypted password.
5. `Delete` an entry (whole line).
6. `View Saved Passwords`. It reads from the password.txt file and decrypts all the password using `Private Key` before printing it to the terminal/console.

`q` Quits the program.

![Password Shield](https://github.com/SdAm1n/password_shield/blob/146386042e2a06edab7b7b37789d36e885febd9b/password_shield.png)

Requirements:

C++ compiler (`C++17` or above is needed to compile the program) needs to be installed in your pc.
gcd() function is used inside this code that is only available from C++17.

## [ClipboardXX](https://github.com/Arian8j2/ClipboardXX)

This program uses this external library to copy paste generated password automatically to clipboard. This library only works on Windows and Linux (X11 only).
Please see the external library Github Page for further info.

## [conio.h](https://github.com/zoelabbb/conio.h)

conio.h header file is not available outside of Windows. If you want to run this program on linux, you need
to download the header file.
