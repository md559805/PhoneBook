#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>
#include <conio.h>

using namespace std;

struct Contact
{
    string name;
    string phoneNumber;
    string email;
    string address;
    string workplace;
    Contact *next;
};

Contact *head = nullptr;

void Boxed(const string &message, const string &colorCode = "\033[0m")
{
    int width = 80;
    int padding = (width - message.length() - 4) / 2;
    string border = string(width, '-');
    cout << colorCode << border << "\033[0m" << endl;
    cout << colorCode << "|" << string(padding, ' ') << message << string(padding, ' ') << "|\033[0m" << endl;
    cout << colorCode << border << "\033[0m" << endl;
}

bool isDuplicate(const string &name)
{
    Contact *current = head;
    while (current != nullptr)
    {
        if (current->name == name)
        {
            Boxed("Contact with this name already exists.", "\033[31m\033[1m");
            cout << "\033[1mDo you want to still save the contact? \033[0m\033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
            char saveChoice;
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

bool isDuplicatePhoneNumber(const string &phoneNumber)
{
    Contact *current = head;
    while (current != nullptr)
    {
        if (current->phoneNumber == phoneNumber)
        {
            Boxed("Contact with this phone number already exists.", "\033[31m\033[1m");
            return true;
        }
        current = current->next;
    }
    return false;
}

void addContact()
{
    system("cls");
    Contact *newContact = new Contact;
    cout << "\n\033[1mEnter Full Name: \033[0m";
    getline(cin, newContact->name);

    if (isDuplicate(newContact->name))
    {
        delete newContact;
        return;
    }

    cout << "\033[1mEnter Phone Number: \033[0m";
    getline(cin, newContact->phoneNumber);

    if (isDuplicatePhoneNumber(newContact->phoneNumber))
    {
        delete newContact;
        return;
    }

    bool validEmail = false;
    while (!validEmail)
    {
        cout << "\033[1mEnter Email: \033[0m";
        getline(cin, newContact->email);
        if (newContact->email.empty())
        {
            validEmail = true;
        }
        else if (newContact->email.find('@') == string::npos || newContact->email.find('.') == string::npos)
        {
            Boxed("Invalid email. Please include '@' and '.' in the email.", "\033[31m\033[1m");
        }
        else
        {
            validEmail = true;
        }
    }

    cout << "\033[1mEnter Address: \033[0m";
    getline(cin, newContact->address);
    cout << "\033[1mEnter Workplace: \033[0m";
    getline(cin, newContact->workplace);
    newContact->next = head;
    head = newContact;
    Boxed("Contact added successfully!", "\033[32m\033[1m");
    cout << endl;
    system("pause");
}

int countContacts()
{
    int count = 0;
    Contact *current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

void displayContacts()
{
    system("cls");

    cout << "\033[1;33mLoading the contacts to display  ";
    char loadingChars[] = {'\\', '|', '/', '-'};
    for (int i = 0; i < 12; ++i)
    {
        cout << loadingChars[i % 4] << "\b";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    int contactCount = countContacts();

    if (contactCount == 0)
    {
        Boxed("No contacts to display.", "\033[31m\033[1m");
        cout << "\033[1mWould you like to add a contact? \033[0m\033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
        char addChoice = _getch();
        cout << addChoice << endl;
        if (addChoice == 'y' || addChoice == 'Y')
        {
            addContact();
        }
        else
        {
            Boxed("Returning to the Menu.", "\033[32m\033[1m");
            cout << endl;
            system("pause");
        }
        return;
    }

    Boxed("You have " + to_string(contactCount) + " contacts in your phonebook.", "\033[1;3;36m");
    cout << endl;
    Boxed("Phonebook Contacts:", "\033[1;94m");
    cout << endl;
    Contact *current = head;
    while (current != nullptr)
    {
        cout << "\033[1mName: \033[0m\033[1;3;36m" << current->name << "\033[0m\n";
        cout << "\033[1mPhone Number: \033[0m" << current->phoneNumber << "\n";
        cout << "\033[1mEmail: \033[0m" << current->email << "\n";
        cout << "\033[1mAddress: \033[0m" << current->address << "\n";
        cout << "\033[1mWorkplace: \033[0m" << current->workplace << "\n";
        cout << endl;
        cout << "\033[36m----------------------------\033[0m\n";
        cout << endl;
        current = current->next;
    }

    system("pause");
}

void searchContact()
{
    system("cls");
    string searchQuery;
    cout << "\n\033[1mWhich Contact are you searching for? (name, phone number) \033[0m";
    cin.ignore();
    getline(cin, searchQuery);

    int contactCount = countContacts();

    cout << "\033[1;33mSearching among your ( " << contactCount << " ) contacts";
    for (int i = 0; i < 3; ++i)
    {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    Contact *current = head;
    bool foundAny = false;
    while (current != nullptr)
    {
        if (current->name.find(searchQuery) != string::npos ||
            current->phoneNumber.find(searchQuery) != string::npos)
        {
            foundAny = true;
            cout << "\n\033[1mName: \033[0m\033[1;3;36m" << current->name << "\033[0m\n";
            cout << "\033[1mPhone Number: \033[0m" << current->phoneNumber << "\n";
            cout << "\033[1mEmail: \033[0m" << current->email << "\n";
            cout << "\033[1mAddress: \033[0m" << current->address << "\n";
            cout << "\033[1mWorkplace: \033[0m" << current->workplace << "\n";
            cout << endl;
            cout << "\033[36m----------------------------\033[0m\n";
            cout << endl;
        }
        current = current->next;
    }

    if (!foundAny)
    {
        Boxed("No contacts found.", "\033[31m\033[1m");
        cout << "\033[1mWould you like to add the contact? \033[0m\033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
        char addChoice = _getch();
        cout << addChoice << endl;
        if (addChoice == 'y' || addChoice == 'Y')
        {
            addContact();
        }
        else
        {
            Boxed("Returning to the Menu.", "\033[32m\033[1m");
        }
    }
    else
    {
        Boxed("Contacts found!", "\033[32m\033[1m");
    }
    
    cout << endl;
    system("pause");
}

void deleteContact()
{
    system("cls");
    string deleteQuery;
    cout << "\n\033[1mEnter Name or Number to Delete: \033[0m";
    cin.ignore();
    getline(cin, deleteQuery);

    cout << "\033[1;33mSearching the contact  ";
    char loadingChars[] = {'\\', '|', '/', '-'};
    for (int i = 0; i < 12; ++i)
    {
        cout << loadingChars[i % 4] << "\b";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    Contact *current = head;
    Contact *previous = nullptr;
    bool foundAny = false;
    while (current != nullptr)
    {
        if (current->name.find(deleteQuery) != string::npos ||
            current->phoneNumber.find(deleteQuery) != string::npos)
        {
            cout << "\n\033[1mAre you sure you want to delete \033[0m\033[1;3;36m" << current->name << "\033[0m? \033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
            char deleteChoice = _getch();
            cout << deleteChoice << endl;
            if (deleteChoice == 'y' || deleteChoice == 'Y')
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                Boxed("Contact deleted successfully!", "\033[32m\033[1m");
                cout << endl;
                system("pause");
            }
            else
            {
                Boxed("Contact deletion canceled.", "\033[32m\033[1m");
                system("pause");
            }
            return;
        }
        previous = current;
        current = current->next;
    }
    if (!foundAny)
    {
        Boxed("No contacts found.", "\033[31m\033[1m");
        cout << "\033[1mWould you like to add the contact? \033[0m\033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
        char addChoice = _getch();
        cout << addChoice << endl;
        if (addChoice == 'y' || addChoice == 'Y')
        {
            addContact();
        }
        else
        {
            Boxed("Returning to the Menu.", "\033[32m\033[1m");
        }
    }
    else
    {
        Boxed("Contacts found!", "\033[32m\033[1m");
    }
    cout << endl;
    system("pause");
}

void editContact()
{
    system("cls");
    string editQuery;
    cout << "\n\033[1mEnter Name or Number to Edit: \033[0m";
    cin.ignore();
    getline(cin, editQuery);

    cout << "\033[1;33mSearching the contact  ";
    char loadingChars[] = {'\\', '|', '/', '-'};
    for (int i = 0; i < 12; ++i)
    {
        cout << loadingChars[i % 4] << "\b";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    Contact *current = head;
    bool foundAny = false;
    while (current != nullptr)
    {
        if (current->name.find(editQuery) != string::npos ||
            current->phoneNumber.find(editQuery) != string::npos)
        {
            cout << "\n\033[1mEditing Contact: \033[0m\033[1;3;36m" << current->name << "\033[0m\n";
            cout << "\033[1mEnter New Phone Number (leave blank to keep current): \033[0m";
            string newPhoneNumber;
            getline(cin, newPhoneNumber);
            if (!newPhoneNumber.empty())
            {
                current->phoneNumber = newPhoneNumber;
            }

            bool validEmail = false;
            while (!validEmail)
            {
                string newEmail;
                cout << "\033[1mEnter New Email (leave blank to keep current): \033[0m";
                getline(cin, newEmail);
                if (newEmail.empty())
                {
                    validEmail = true;
                }
                else if (newEmail.find('@') == string::npos || newEmail.find('.') == string::npos)
                {
                    Boxed("Invalid email. Please include '@' and '.' in the email.", "\033[31m\033[1m");
                }
                else
                {
                    current->email = newEmail;
                    validEmail = true;
                }
            }

            cout << "\033[1mEnter New Address (leave blank to keep current): \033[0m";
            string newAddress;
            getline(cin, newAddress);
            if (!newAddress.empty())
            {
                current->address = newAddress;
            }

            cout << "\033[1mEnter New Workplace (leave blank to keep current): \033[0m";
            string newWorkplace;
            getline(cin, newWorkplace);
            if (!newWorkplace.empty())
            {
                current->workplace = newWorkplace;
            }

            Boxed("Contact updated successfully!", "\033[32m\033[1m");
            cout << endl;
            system("pause");
            return;
        }
        current = current->next;
    }

    if (!foundAny)
    {
        Boxed("No contacts found.", "\033[31m\033[1m");
        cout << "\033[1mWould you like to add the contact? \033[0m\033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
        char addChoice = _getch();
        cout << addChoice << endl;
        if (addChoice == 'y' || addChoice == 'Y')
        {
            addContact();
        }
        else
        {
            Boxed("Returning to the Menu.", "\033[32m\033[1m");
        }
    }
    else
    {
        Boxed("Contacts found!", "\033[32m\033[1m");
    }
    cout << endl;
    system("pause");
}

void saveContacts()
{
    system("cls");

    cout << "\033[1;33mSaving the contacts  ";
    char loadingChars[] = {'\\', '|', '/', '-'};
    for (int i = 0; i < 12; ++i)
    {
        cout << loadingChars[i % 4] << "\b";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    ofstream outFile("contacts.txt");
    if (!outFile)
    {
        Boxed("Error saving contacts to file.", "\033[31m\033[1m");
        return;
    }
    Contact *current = head;
    while (current != nullptr)
    {
        outFile << current->name << "\n";
        outFile << current->phoneNumber << "\n";
        outFile << current->email << "\n";
        outFile << current->address << "\n";
        outFile << current->workplace << "\n";
        current = current->next;
    }
    outFile.close();
    Boxed("Contacts saved successfully!", "\033[32m\033[1m");
    cout << endl;
    system("pause");
}

void loadContacts(bool showMessage = true)
{
    system("cls");

    cout << "\033[1;33mLoading the contact  ";
    char loadingChars[] = {'\\', '|', '/', '-'};
    for (int i = 0; i < 12; ++i)
    {
        cout << loadingChars[i % 4] << "\b";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    ifstream inFile("contacts.txt");
    if (!inFile)
    {
        if (showMessage)
        {
            Boxed("No saved contacts found.", "\033[31m\033[1m");
            cout << endl;
        }
        return;
    }
    head = nullptr;
    string name, phoneNumber, email, address, workplace;
    while (getline(inFile, name))
    {
        getline(inFile, phoneNumber);
        getline(inFile, email);
        getline(inFile, address);
        getline(inFile, workplace);
        Contact *newContact = new Contact{name, phoneNumber, email, address, workplace, head};
        head = newContact;
    }
    inFile.close();
    if (showMessage)
    {
        Boxed("Contacts loaded successfully!", "\033[32m\033[1m");
        cout << endl;
        system("pause");
    }
}

void displayMenu(int selectedOption)
{
    system("cls");

    Boxed("Phonebook Menu:", "\033[1;94m");
    string options[] = {
        "1. Add Contact",
        "2. Display Contacts",
        "3. Search Contact",
        "4. Delete Contact",
        "5. Edit Contact",
        "6. Save Contacts",
        "7. Load Contacts",
        "8. Exit"};
    for (int i = 0; i < 8; ++i)
    {
        if (i == selectedOption)
        {
            cout << "\033[1;32m> " << options[i] << " <\033[0m\n";
        }
        else
        {
            cout << options[i] << "\n";
        }
    }
    Boxed("Use arrow keys to navigate and press Enter to select.", "\033[1;5;31m");
}

int navigateMenu()
{
    int selectedOption = 0;
    while (true)
    {
        displayMenu(selectedOption);
        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
            {
                selectedOption = (selectedOption - 1 + 8) % 8;
            }
            else if (key == 80)
            {
                selectedOption = (selectedOption + 1) % 8;
            }
        }
        else if (key >= '1' && key <= '8')
        {
            return key - '1';
        }
        else if (key == 13)
        {
            return selectedOption;
        }
    }
}

int main()
{
    loadContacts(false);
    system("cls");

    cout << "\033[1;33mPreparing the Menu";
    for (int i = 0; i < 3; ++i)
    {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    cout << "\033[0m\n";
    cout << endl;

    system("cls");

    while (true)
    {
        int choice = navigateMenu();

        switch (choice)
        {
        case 0:
            addContact();
            break;
        case 1:
            displayContacts();
            break;
        case 2:
            searchContact();
            break;
        case 3:
            deleteContact();
            break;
        case 4:
            editContact();
            break;
        case 5:
            saveContacts();
            break;
        case 6:
            loadContacts();
            break;
        case 7:
        {
            cout << "\n\033[1mAre you sure you want to exit?\033[0m \033[1;31m(y/n)\033[0m\033[1m:\033[0m ";
            char exitChoice = _getch();
            cout << exitChoice << endl;

            if (exitChoice == 'y' || exitChoice == 'Y')
            {
                saveContacts();
                cout << endl;
                Boxed("Exiting Phonebook. Goodbye!", "\033[32m\033[1m");
                return 0;
            }
            break;
        }

        default:
            Boxed("Invalid choice. Please try again.", "\033[31m\033[1m");
            break;
        }
    }
    return 0;
}
