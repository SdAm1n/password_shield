/*
    PASSWORD MANAGER
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void menu() {
    cout << "1. Generate Password" << endl;
    cout << "2. Store Password" << endl;
    cout << "3. Find Password"<<endl;
    cout << "q. Quit"<<endl;
}

// pseudo random password generator

void generate_password() {

    string random_str = "0123456789"
                          "!@#$%^&*"
                          "abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand(time(NULL));
    int random_str_len = random_str.size();
    cout << "Enter password size in integers" << endl;
    int password_length;
    cin >> password_length;
    cout << "\nGenerating Password.......\n" <<endl;
    while(password_length--){
        cout << random_str[rand()%random_str_len];
    }
    cout << endl <<endl;
}

void store_password() {

}

void find_password() {

}


int main(){
    char option;
    cout << "PASSWORD MANAGER"<<endl;
    do {
        menu();
        cin >> option;
        if (option == '1'){
            generate_password();
        }
        else if (option == '2') {
            store_password();
        }
        else if(option == '3'){
            find_password();
        }
        else if(option != 'q'){
            cout << "Wrong Option\nTry Entering 1, 2 or q :)\n" << endl;
        }
        else {
            cout << "Quiting..." <<endl;
        }
    }while(option != 'q');

}