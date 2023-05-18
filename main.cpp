/*
    PASSWORD MANAGER
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // exit function prototypes
#include <ctime>
#include <fstream>  // contains file stream processing types
#include <numeric>
#include <conio.h>
#include <iomanip>
#include "clipboardxx/clipboardxx.hpp"  // copy paste to clipboard external library header


using namespace std;

// RSA Algorithm Start
unsigned PUBLIC_KEY;
unsigned PRIVATE_KEY;
unsigned N;
void keyGeneration(){

    unsigned p = 97;     // first prime number
    unsigned q = 101;     // second prime number
    N = p * q;     // n = p*q
    unsigned phi_n = (p-1) * (q-1); // phi_n = (p-1) * (q-1)
    unsigned e;     // 1 < e < phi_n; e should be coprime with phi_n
    unsigned d;     // (e*d) mod phi_n = 1


    // public key generation
    unsigned i = 2;
    while(gcd(i,phi_n) !=1) {
        i++;
    }
    e = i;

    PUBLIC_KEY = e;


    // private key generation
    unsigned k = 1;
 
    while(((k*phi_n)+1) % e != 0) {
        k++;
    }
        
    d = ((k*phi_n)+1)/e;

    PRIVATE_KEY = d;

}

unsigned long long int encrypt(unsigned message){
    unsigned e = PUBLIC_KEY;
    unsigned long long int encrypted_text = 1;
    while(e--){
        encrypted_text *= message;
        encrypted_text  %= N;
    }
    return encrypted_text;
}

unsigned long long int decrypt(unsigned encrpyted_text)
{
    unsigned d = PRIVATE_KEY;

    unsigned long long int decrypted = 1;
    while (d--) {
        decrypted *= encrpyted_text;
        decrypted %= N;
    }

    return decrypted;
}


vector<unsigned>encoder(string message){
    vector<unsigned> form;

    for(auto &letter: message){
        form.push_back(encrypt((unsigned)letter));
    }

    return form;
}


string decoder(vector<unsigned> encoded){
    string s="";
    
    for (auto &num: encoded){
        s+=decrypt(num);
    }
    return s;
}

// RSA Algo Ends


string encrypt_password(string password){
    vector<unsigned> encrypted_password = encoder(password);    // encrypting the password

    string encrypted="";
    for(auto &p: encrypted_password){
        encrypted += to_string(p);
        encrypted += ':';
    }
    return encrypted;
}


vector <unsigned> decrypt_password(string encrypted_password){

    // converting encrypted password string to unsigned vector for decryption 

    vector<unsigned> tovec;
    for(int i=0;i<encrypted_password.length();i++){

        string ns;
        while(encrypted_password[i] != ':') {
            ns += encrypted_password[i];
            i++;
        }
        tovec.push_back((unsigned)stoi(ns));
    }
    return tovec;

}


const string MASTER_PASSWORD = "1234";      // Default MASTER_PASSWORD


/*
    * check_masterPass() return a boolean value
    * this function check MASTER_PASSWORD which is already set in the program
    * with the user typed password (master_password) and returns value with that accord
    * this function also uses password masking. so when you type a password * is shown in the console
    * instead of the typed password
    * password masking is achieved by using conio.h header file
    * this can also be achieved by using win32 api or ncruses library or writing the getch() manually
*/

bool check_masterPass(){

    // asking user to type master password
    cout << "Type your Master Password to Access the program: ";
    string master_password;

    // password masking starts
    char c;
    for(int i=0;i<1000;i++){
        c = getch();            // getch() belongs to header conio.h
        if(c == '\r') break;
        cout << "*";
        master_password += c;
    }
    // password masking ends

    // comparing user typed password with hardcoded password
    if(master_password == MASTER_PASSWORD) {
        return true;
    }
    
    return false;
}

/*
    * clear_display() is a function that clears the terminal/console by sending
    * appropiate system command for respective operating system
    * it can detect Windows, Linux and Mac operating system
*/

void clear_display()
{
    #ifdef _WIN32           // for detecting windows 32 or 64 bit system
        system("cls");
    #elif __linux__         // for detecting linux
        system("clear");
    #elif __MACH__          // for detecting mac
        system("clear");

    #endif
}

/*
    * intro_art() reads from intro_art.txt which contains ascii art
    * output the contents line by line in terminal / console
*/

void intro_art(){
    ifstream intro_file("intro_art.txt", ios::in);

    if(!intro_file) {
        cout << "PASSWORD MANAGER" << endl;
        cout << "----------------" << endl;
        return;
    }

    string line;

    while(getline(intro_file, line)){
        cout << line << endl;
    }
    intro_file.close();

}

// menu function shows menu for password manager

void menu() {
    
    cout << internal << "-----------------------" <<endl;
    cout << "|" << setw(11) << "Menu" << setw(11) << "|" << endl;
    cout << "-----------------------\n" <<endl;
    cout << "1. Generate Password" << endl;
    cout << "2. Store Password" << endl;
    cout << "3. Find Password"<<endl;
    cout << "4. Change Password" << endl;
    cout << "5. Delete an Entry" << endl;
    cout << "6. View Saved Passwords" << endl;
    cout << "q. Quit"<<endl;
    cout << endl;
    cout << "Enter Your Choice: "; 
}

/*
    * store_password() stores password in password.txt
    * it stores encrypted_password that is encrypted using RSA Algorithm
*/

void store_password(string &default_password) {
    clear_display();

    ofstream pass_file("password.txt", ios::app);

    // checks if file exists
    if(!pass_file){
        cerr << "Could not open the password file" << endl;
        exit(EXIT_FAILURE);
    }

    string website, username_email, password;
   
    cout << "Enter Website: ";
    cin >> website;
     
    cout << "Enter Username/Email: ";
    cin >> username_email;

    if(!default_password.empty()) {
        password = default_password;
    }
    else {
        cout << "Enter Password: ";
        cin>> password;
    }

    cout << endl;


    // encrypting the password into encrypted_password
    string encrypted_password = encrypt_password(password);  // calling encryp_password fundtion that converts password to encrypted password string

    pass_file << website << " " << username_email << " "<< encrypted_password << endl;

    pass_file.close();

    cout << "Password is stored\n" << endl;

}


/*
    * generate_password() generates a pseudo random password
    * generated password can be saved in the file
    * generated password automatically is saved to clipboard by using clipboardxx library
*/



void generate_password() {
    clear_display();

    string random_str = "0123456789"
                          "!@#$%^&*"
                          "abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand(time(NULL));
    int random_str_len = random_str.size();

    // asks user for password size (how long the password will be) 
    cout << "Enter password size in integers: ";
    int password_length;
    cin >> password_length;
    cout << "\nGenerating Password.......\n" <<endl;


    // Generating password
    string new_pass;
    while(password_length--){
        new_pass+=random_str[rand()%random_str_len];
    }
    cout << new_pass << endl <<endl;

    // copy to clipboard
    clipboardxx::clipboard clip;    // creating clipboard object from external library clipboardxx

    clip << new_pass;   // To copy the generated password to clipboard

    // asks the user to save the password in password.txt file
    cout << "Do you want to save the password (Y or N): ";
    char choice;
    cin>>choice;
    if(choice == 'Y' || choice == 'y'){
        store_password(new_pass);
    }
}

/*
    * find_password() finds the password by using website or username/email
    * this function reads from password.txt, decrypts the password and output it to terminal/console
*/

void find_password() {

    clear_display();
    ifstream pass_file("password.txt", ios::in);

    // checks if file exists
    if(!pass_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    // asks user by which method want to find the password
    cout << "\nFind password by: " << endl;
    cout << "1. Username/Email" << endl;
    cout << "2. Website" << endl;
    cout << "Enter Your Choice (1 or 2) : ";
    char choice;
    cin>> choice;

    string username_email, website, encrypted_password,find_by;
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
    while(pass_file >> website >> username_email >> encrypted_password){
        

        if(choice == '1' && find_by == username_email) {
            vector<unsigned> tovec = decrypt_password(encrypted_password);  // to decrypt the password
            cout << "For website: "<< website;
            cout << " The password is: "<< decoder(tovec) << endl;
            password_found = true;
        }
        else if(choice == '2' && find_by == website ) {
            vector<unsigned> tovec = decrypt_password(encrypted_password);  // to decrypt the password
            cout << "For Username/Email: "<< username_email;
            cout << " The password is: "<< decoder(tovec) << endl;
            password_found = true;
        }
    }
    if(!password_found) {
        cout << "Password not found" <<endl;
    }
    cout << endl;

}

/*
    * password_list() prints all the password to the terminal/console
    * reads the password.txt file and decrypts the password before printing it
*/

void password_list() {
    clear_display();
    cout << "------------------------------------------- ";
    cout << "PASSWORD LIST";
    cout<< " -------------------------------------------\n"<<endl;
    ifstream pass_file("password.txt", ios::in);

    // checks if file exits
    if(!pass_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    string username_email, website, encrypted_password;
    int serial = 1;

    cout <<left << setw(25) <<"Serial" <<setw(25) << "Website" <<setw(25) <<
     "Username" << setw(25) << "Password" << endl; 

    while(pass_file >> website >> username_email >> encrypted_password){

        vector<unsigned> tovec = decrypt_password(encrypted_password);  // converts encrypted password to unsigned vector

        cout <<left << setw(25) << serial <<setw(25) << website
        << setw(25) << username_email << setw(25) << decoder(tovec) << endl; 
        serial++;
    }

    cout << endl << endl;
    pass_file.close();

}

/*
    * change_password() changes a particular password from password.txt
    * this function replaces the encrypted password by new encrypted password
*/

void change_password() {

    password_list();
    
    // asks the user for the line number the password to be changed
    cout << "Which password do you want to change?" << endl;
    cout << "Type the line number: ";

    int line_number;
    cin>> line_number;
    
    int temp_line = line_number;
    // Read the file and store the password in a variable

    ifstream input_file("password.txt", ios::in);

    if(!input_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    string username_email, website, encrypted_password;

    while(input_file >> website >> username_email >> encrypted_password) {
        --temp_line;
        if(temp_line==0) break;
    }
    input_file.close();

    ifstream inp_file("password.txt", ios::in);

    vector<string> lines;
    string line;

    while(getline(inp_file,line)){
        lines.push_back(line);
    }

    inp_file.close();

    if(line_number>lines.size()){
        clear_display();
        cout << "Line " << line << " not in the file" << endl;
        cout << "File has " << lines.size() << " lines"<<endl;
        return; 
    }

    // asks the user for new password
    cout << "Type the new password: ";
    string new_password;
    cin>>new_password;

    // opens the file in output mode inorder to rewrite it
    ofstream output_file("password.txt", ios::out);

    for(int i=0;i<lines.size();i++){
        int pos = lines[i].find(encrypted_password);    // finds the index of the old encrypted password
        if(pos != string::npos && line_number -1 == i) {
            // replaces the old encrypted password with new encryptes password
            lines[i].replace(pos,encrypted_password.size(),encrypt_password(new_password));
        }
        output_file << lines[i] << endl;
        
    }
    output_file.close();
    cout<< "Successfully changed the password" << endl;

}

/*
    * delete_entry() deletes a whole line from the password.txt file
    * it reads from the password.txt file
    * saves all the lines to a vector
    * then it rewrites to password.txt file except the line to be deleted
*/


void delete_entry(){

    password_list();

    // asks the user which line to delete
    cout << "Which entry do you want to delete?"<<endl;
    cout << "Type the line number: ";
    int line_number;
    cin>> line_number;

    ifstream input_file("password.txt", ios::in); 

    if(!input_file){
        cerr<< "Could not open the password file" <<endl;
        exit(EXIT_FAILURE);
    }

    vector<string> lines;
    string line;

    while(getline(input_file, line)){
        lines.push_back(line);
    }

    input_file.close();

    // check if invalid line number is provided
    if(line_number>lines.size()){
        cout << "Line " << line << " not in the file" << endl;
        cout << "File has " << lines.size() << " lines"<<endl;
        return; 
    }

    ofstream output_file("password.txt",ios::out);

    for(int i=0;i<lines.size();i++){
        if(i != line_number - 1){
            output_file << lines[i] << endl;
        }
    }
    output_file.close();

    cout << "\nSuccessfully deleted Entry...\n" << endl;

}

// main function start

int main(){

    int attempt_counter = 0;
    while(!check_masterPass()){
        if(attempt_counter>=3){
            clear_display();
            cout << "You have typed wrong password more than three times\n" << endl;
            cout << "Please Run the program and try again......" << endl;
            return -1;
        }

        cout << "Master Password is wrong. Try again" << endl;
        attempt_counter++;

    }

    clear_display();
    char option;
    
    intro_art();

    keyGeneration();    // Key generation for RSA Algorithm
    
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
            change_password();
        }
        else if(option == '5'){
            delete_entry();
        }

        else if(option == '6'){
            password_list();
        }
        else if(option != 'q'){
            cout << "Wrong Option\nTry Entering 1, 2 or q :)\n" << endl;
        }
        else {
            cout << "Quiting..." <<endl;
        }
    }while(option != 'q');

}   