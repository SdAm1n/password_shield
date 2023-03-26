/*
    PASSWORD MANAGER
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// menu function shows menu for password manager

void menu() {
    cout << "1. Generate Password" << endl;
    cout << "2. Store Password" << endl;
    cout << "3. Find Password"<<endl;
    cout << "4. View All Passwords" << endl;
    cout << "q. Quit"<<endl;
}

// store_password function stores password in password.txt file

void store_password(string &default_password) {
    ofstream pass_file("password.txt",ios::app);

    if(!pass_file){
        cerr << "Could not open the password file" << endl;
        exit(EXIT_FAILURE);
    }
    string username_email, website, password;
    cout << "Enter Username/Email, Website";
    
    if(!default_password.empty()) {
        password = default_password;
    }
    else {
        cout << ", Password: ";
        cin>> password;
    }
    cout << endl;

   
    cin>> username_email >> website;

    pass_file << username_email << " " << website << " "<< password << endl;
    pass_file.close();

    cout << "Password is stored" << endl;

}

// generate_password function is a pseudo random password generator 
// which generates a random password 

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

    string new_pass;
    while(password_length--){
        // cout << random_str[rand()%random_str_len];
        new_pass+=random_str[rand()%random_str_len];
    }
    cout << new_pass << endl <<endl;

    cout << "Do you want to save the password (Y or N): ";
    char choice;
    cin>>choice;
    if(choice == 'Y'){
        store_password(new_pass);
    }
}

void find_password() {

}

void view_all_password() {
    ifstream pass_file("password.txt", ios::in);

    if(!pass_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    string username_email, website, password;
    while(pass_file >> username_email >> website >> password){
        cout << username_email<< " " << website << " " << password << endl; 
    }

    pass_file.close();

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
            string default_password = "";
            store_password(default_password);
        }
        else if(option == '3'){
            find_password();
        }
        else if(option == '4'){
            view_all_password();
        }
        else if(option != 'q'){
            cout << "Wrong Option\nTry Entering 1, 2 or q :)\n" << endl;
        }
        else {
            cout << "Quiting..." <<endl;
        }
    }while(option != 'q');

}