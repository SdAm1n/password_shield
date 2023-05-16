/*
    PASSWORD MANAGER
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // exit function prototypes
#include <ctime>
#include <fstream>  // contains file stream processing types

using namespace std;

const string MASTER_PASSWORD = "1234";

bool check_masterPass(){
    cout << "Type your Master Password to Access the program: ";
    string master_password;
    cin>> master_password;

    if(master_password == MASTER_PASSWORD) {
        return true;
    }
    
    return false;
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

void intro_art(){
    ifstream intro_file("intro_art.txt",ios::in);

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
    
    cout << "1. Generate Password" << endl;
    cout << "2. Store Password" << endl;
    cout << "3. Find Password"<<endl;
    cout << "4. Change Password" << endl;
    cout << "5. Delete an Entry" << endl;
    cout << "6. View All Passwords" << endl;
    cout << "q. Quit"<<endl;
    cout << endl;
    cout << "Enter Your Choice: "; 
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
    if(choice == 'Y' || choice == 'y'){
        store_password(new_pass);
    }
}

// find_password function finds password by username/email or website

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

// view_all_password functions prints all password from password.txt file

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
    int serial = 1;
    while(pass_file >> username_email >> website >> password){
        cout << serial << ". " <<username_email<< " " 
        << website << " " << password << endl; 
        serial++;
    }
    cout << endl << endl;
    pass_file.close();

}

void change_password() {

    view_all_password();

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

    string username_email, website, password;

    while(input_file >> username_email >> website >> password) {
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

    cout << "Type the new password: ";
    string new_password;
    cin>>new_password;

    ofstream output_file("password.txt", ios::out);

    for(int i=0;i<lines.size();i++){
        int pos = lines[i].find(password);
        if(pos != string::npos) {
            lines[i].replace(pos,password.size(),new_password);
        }
        output_file << lines[i] << endl;
        
    }
    output_file.close();
    cout<< "Successfully changed the password" << endl;

}

void delete_entry(){

    view_all_password();
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

    while(getline(input_file,line)){
        lines.push_back(line);
    }

    input_file.close();

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