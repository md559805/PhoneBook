#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string email;
    string address;
    string workplace;
    Contact* next;
};

Contact* head = nullptr;

bool isDuplicate(const string& name) {
    Contact* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void addContact() {
    Contact* newContact = new Contact;
    cout << "\n\033[1mEnter Full Name: \033[0m";
    cin.ignore();
    getline(cin, newContact->name);

    if (isDuplicate(newContact->name)) {
        cout << "\033[31m\033[1mContact with this name already exists.\033[0m\n";
        delete newContact;
        return;
    }

    cout << "\033[1mEnter Phone Number: \033[0m";
    getline(cin, newContact->phoneNumber);
    
    bool validEmail = false;
    while (!validEmail) {
        cout << "\033[1mEnter Email: \033[0m";
        getline(cin, newContact->email);
        if (newContact->email.find('@') == string::npos || newContact->email.find('.') == string::npos) {
            cout << "\033[31m\033[1mInvalid email. Please include '@' and '.' in the email.\033[0m\n";
        } else {
            validEmail = true;
        }
    }

    cout << "\033[1mEnter Address: \033[0m";
    getline(cin, newContact->address);
    cout << "\033[1mEnter Workplace: \033[0m";
    getline(cin, newContact->workplace);
    newContact->next = head;
    head = newContact;
    cout << "\033[32m\033[1mContact added successfully!\033[0m\n";
    cout << endl;
}

int countContacts() {
    int count = 0;
    Contact* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void displayContacts() {
    if (head == nullptr) {
        cout << "\n\033[31m\033[1mNo contacts to display.\033[0m\n";
        return;
    }
    
    int contactCount = countContacts();

    cout << "\nYou have " << "\033[1;3;36m( " << contactCount << " )\033[0m" << " contacts in your phonebook.\n";
    cout << "------------------------------------------\n";
    cout << "\n\033[4m\033[1;94mPhonebook Contacts:\033[0m\n";
    Contact* current = head;
    while (current != nullptr) {
        cout << "\033[1mName: \033[0m\033[1;3;36m" << current->name << "\033[0m\n";
        cout << "\033[1mPhone Number: \033[0m" << current->phoneNumber << "\n";
        cout << "\033[1mEmail: \033[0m" << current->email << "\n";
        cout << "\033[1mAddress: \033[0m" << current->address << "\n";
        cout << "\033[1mWorkplace: \033[0m" << current->workplace << "\n";
        cout << "\033[36m-------------------------\033[0m\n";
        cout << endl;
        current = current->next;
    }
}

void searchContact() {
    string searchName;
    cout << "\n\033[1mEnter Name to Search: \033[0m";
    cin.ignore();
    getline(cin, searchName);

    int contactCount = countContacts();

    cout << "\033[1;33mSearching among your ( " << contactCount << " ) contacts";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    cout << "\033[0m\n";
    cout << endl;

    Contact* current = head;
    while (current != nullptr) {
        if (current->name == searchName) {
            cout << "\n\033[1mName: \033[0m\033[1;3;36m" << current->name << "\033[0m\n";
            cout << "\033[1mPhone Number: \033[0m" << current->phoneNumber << "\n";
            cout << "\033[1mEmail: \033[0m" << current->email << "\n";
            cout << "\033[1mAddress: \033[0m" << current->address << "\n";
            cout << "\033[1mWorkplace: \033[0m" << current->workplace << "\n";
            cout << endl;
            cout << "\033[32m\033[1mContact found!\033[0m\n";
            cout << endl;
            return;
        }
        current = current->next;
    }
    cout << "\033[31m\033[1mContact not found.\033[0m\n";
    cout << endl;
}

void deleteContact() {
    string deleteName;
    cout << "\n\033[1mEnter Name to Delete: \033[0m";
    cin.ignore();
    getline(cin, deleteName);
    Contact* current = head;
    Contact* previous = nullptr;
    while (current != nullptr) {
        if (current->name == deleteName) {
            cout << "\n\033[1mAre you sure you want to delete \033[0m\033[1;3;36m" << current->name << "\033[0m? \033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
            char deleteChoice;
            cin >> deleteChoice;
            if (deleteChoice == 'y' || deleteChoice == 'Y') {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << "\033[32m\033[1mContact deleted successfully!\033[0m\n";
            } else {
                cout << "\033[32m\033[1mContact deletion canceled.\033[0m\n";
            }
            cout << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "\033[31m\033[1mContact not found.\033[0m\n";
    cout << endl;
}

void editContact() {
    string editName;
    cout << "\n\033[1mEnter Name to Edit: \033[0m";
    cin.ignore();
    getline(cin, editName);

    Contact* current = head;
    while (current != nullptr) {
        if (current->name == editName) {
            cout << "\n\033[1mEditing Contact: \033[0m\033[1;3;36m" << current->name << "\033[0m\n";
            cout << "\033[1mEnter New Phone Number (leave blank to keep current): \033[0m";
            string newPhoneNumber;
            getline(cin, newPhoneNumber);
            if (!newPhoneNumber.empty()) {
                current->phoneNumber = newPhoneNumber;
            }

            cout << "\033[1mEnter New Email (leave blank to keep current): \033[0m";
            string newEmail;
            getline(cin, newEmail);
            if (!newEmail.empty()) {
                current->email = newEmail;
            }

            cout << "\033[1mEnter New Address (leave blank to keep current): \033[0m";
            string newAddress;
            getline(cin, newAddress);
            if (!newAddress.empty()) {
                current->address = newAddress;
            }

            cout << "\033[1mEnter New Workplace (leave blank to keep current): \033[0m";
            string newWorkplace;
            getline(cin, newWorkplace);
            if (!newWorkplace.empty()) {
                current->workplace = newWorkplace;
            }

            cout << "\033[32m\033[1mContact updated successfully!\033[0m\n";
            cout << endl;
            return;
        }
        current = current->next;
    }
    cout << "\033[31m\033[1mContact not found.\033[0m\n";
    cout << endl;
}

void saveContacts() {
    ofstream outFile("contacts.txt");
    if (!outFile) {
        cout << "\033[31m\033[1mError saving contacts to file.\033[0m\n";
        return;
    }
    Contact* current = head;
    while (current != nullptr) {
        outFile << current->name << "\n";
        outFile << current->phoneNumber << "\n";
        outFile << current->email << "\n";
        outFile << current->address << "\n";
        outFile << current->workplace << "\n";
        current = current->next;
    }
    outFile.close();
    cout << "\033[32m\033[1mContacts saved successfully!\033[0m\n";
    cout << endl;
}

void loadContacts() {
    ifstream inFile("contacts.txt");
    if (!inFile) {
        cout << "\033[31m\033[1mNo saved contacts found.\033[0m\n";
        return;
    }
    head = nullptr;
    string name, phoneNumber, email, address, workplace;
    while (getline(inFile, name)) {
        getline(inFile, phoneNumber);
        getline(inFile, email);
        getline(inFile, address);
        getline(inFile, workplace);
        Contact* newContact = new Contact{name, phoneNumber, email, address, workplace, head};
        head = newContact;
    }
    inFile.close();
    cout << "\033[32m\033[1mContacts loaded successfully!\033[0m\n";
    cout << endl;
}

void displayMenu() {
    cout << "\033[1;94m\033[4mPhonebook Menu:\033[0m\n";
    cout << "1. Add Contact\n";
    cout << "2. Display Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Edit Contact\n";
    cout << "6. Save Contacts\n";
    cout << "7. Load Contacts\n";
    cout << "8. Exit\n";
    cout << "\n\033[1;5;31m==>\033[0m \033[1mEnter your choice: \033[0m";
}

int main() {
    loadContacts();
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                editContact();
                break;
            case 6:
                saveContacts();
                break;
            case 7:
                loadContacts();
                break;
            case 8:
                cout << "\n\033[1mAre you sure you want to exit?\033[0m \033[1;31m(y/n)\033[0m\033[1m:\033[0m";
                char exitChoice;
                cin >> exitChoice;
                if (exitChoice == 'y' || exitChoice == 'Y') {
                    saveContacts();
                    cout << "\033[32m\033[1mExiting Phonebook. Goodbye!\033[0m\n";
                    return 0;
                }
                break;
            default:
                cout << "\033[31m\033[1mInvalid choice. Please try again.\033[0m\n";
        }
    }
    return 0;
}