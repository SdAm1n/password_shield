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
    cout << endl;
    cout << "Enter Your Choice: "; 
}


void clear_display()        // for detecting operating system
{
    #ifdef _WIN32           // for detecting windows 32 or 64 bit system
        system("cls");
    #elif __linux__         // for detecting linux
        system("clear");
    #elif __MACH__          // for detecting mac
        system("clear");

    #endif
}

// store_password function stores password in password.txt file

void store_password(string &default_password) {
    clear_display();

    ofstream pass_file("password.txt",ios::app);

    if(!pass_file){
        cerr << "Could not open the password file" << endl;
        exit(EXIT_FAILURE);
    }
    string username_email, website, password;
    cout << "Enter Username/Email: ";
    cin >> username_email;
    cout << "Enter Website: ";
    cin >> website;

    if(!default_password.empty()) {
        password = default_password;
    }
    else {
        cout << "Enter Password: ";
        cin>> password;
    }
    cout << endl;

   
    

    pass_file << username_email << " " << website << " "<< password << endl;
    pass_file.close();

    cout << "Password is stored\n" << endl;

}

// generate_password function is a pseudo random password generator 
// which generates a random password 

void generate_password() {
    clear_display();

    string random_str = "0123456789"
                          "!@#$%^&*"
                          "abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand(time(NULL));
    int random_str_len = random_str.size();
    cout << "Enter password size in integers: ";
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

    clear_display();
    ifstream pass_file("password.txt", ios::in);

    if(!pass_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    cout << "\nFind password by: " << endl;
    cout << "1. Username/Email" << endl;
    cout << "2. Website" << endl;
    cout << "Enter Your Choice: ";
    char choice;
    cin>> choice;

    string username_email, website, password,find_by;
    if(choice == '1'){
            cout << "Type Username/Email: ";
            cin>> find_by;
    }
    else if(choice == '2') {
            cout << "Type Website: ";
            cin>> find_by;
            
    }
    else {
            cout << "Invalid choice....." << endl;
            cout << "Please type 1 or 2" << endl;
            find_password();
    }

    bool password_found = false;
    while(pass_file >> username_email >> website >> password){
        
        if(choice == '1' && find_by == username_email) {
            cout << "For website: "<< website;
            cout << " The password is: "<< password << endl;
            password_found = true;
        }
        else if(choice == '2' && find_by == website ) {
            cout << "For Username/Email: "<< username_email;
            cout << " The password is: "<< password << endl;
            password_found = true;
        }
    }
    if(!password_found) {
        cout << "Password not found" <<endl;
    }
    cout << endl;

}

void view_all_password() {
    clear_display();
    cout << "All Passwords" <<endl;
    cout << "-------------\n" << endl;
    ifstream pass_file("password.txt", ios::in);

    if(!pass_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    string username_email, website, password;
    while(pass_file >> username_email >> website >> password){
        cout << username_email<< " " << website << " " << password << endl; 
    }
    cout << endl << endl;
    pass_file.close();

}

int main(){
    char option;
    cout << "PASSWORD MANAGER" << endl;
    cout << "----------------" << endl << endl;
    
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