#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

struct DataOfSinglePerson {
    string firstName, lastName, phoneNumber, email, address;
    int id;
};

vector <DataOfSinglePerson> loadPersonsList(int totalAmountOfPersons, DataOfSinglePerson person) {
    int lineNumber = 1;
    string line;
    fstream file;
    vector <DataOfSinglePerson> vectorOfPersons;
    char searchedSign = '|';

    file.open("KsiazkaAdresowa.txt", ios::in);

    if (file.good() == true) {

        while (!file.eof()) {

            for (int i = 0; i < totalAmountOfPersons; i++) {
                getline(file,line);

                size_t position1 = line.find(searchedSign);
                person.id = atoi((line.substr(0, position1)).c_str());

                size_t position2 = line.find(searchedSign, position1 + 1 );
                person.firstName = line.substr(position1 + 1,(position2 - position1 - 1));

                size_t position3 = line.find(searchedSign, position2 + 1 );
                person.lastName = line.substr(position2 + 1,(position3 - position2 - 1));

                size_t position4 = line.find(searchedSign, position3 + 1 );
                person.phoneNumber = line.substr(position3 + 1,(position4 - position3 - 1));

                size_t position5 = line.find(searchedSign, position4 + 1 );
                person.email = line.substr(position4 + 1,(position5 - position4 - 1));

                size_t position6 = line.find(searchedSign, position5 + 1 );
                person.address = line.substr(position5 + 1,(position6 - position5 - 1));

                vectorOfPersons.push_back(person);
            }
        }
    }
    file.close();

    return vectorOfPersons;
}

string insertLine() {
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}

char insertSign() {
    string input = "";
    char sign  = {0};

    while (true) {
        getline(cin, input);

        if (input.length() == 1) {
            sign = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}

int checkTotalAmountOfPersons() {
    int totalAmountOfPersons;
    int LineNumber = 0;

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);

    if(file.good() == false)
        totalAmountOfPersons = 0;
    else {
        string line;
        while (getline(file, line)) {
            LineNumber++;
        }
        totalAmountOfPersons = LineNumber;
    }

    file.close();
    return totalAmountOfPersons;
}

int checkLastId (int totalAmountOfPersons) {
    fstream file;
    string line;
    int lastId = 0;

    file.open("KsiazkaAdresowa.txt", ios::in);

    for (int i = 0; i < totalAmountOfPersons; i++) {
        getline(file, line);

        char searchedSign = '|';
        size_t position1 = line.find(searchedSign);
        lastId = atoi((line.substr(0, position1)).c_str());
    }
    file.close();

    return lastId;
}

void saveNewContact(DataOfSinglePerson person, vector <DataOfSinglePerson> vectorOfPersons, int totalAmountOfPersons) {
    string firstName, lastName, phoneNumber, email, address;
    int id;

    cout << "Podaj imie: ";
    firstName = insertLine();
    cout << "Podaj nazwisko: ";
    lastName = insertLine();
    cout << "Podaj numer telefonu: ";
    phoneNumber = insertLine();
    cout << "Podaj e-mail: ";
    email = insertLine();
    cout << "Podaj adres: ";
    address = insertLine();

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);

    if(file.good() == false)
        id = 1;
    else
        id = checkLastId(totalAmountOfPersons) + 1;

    file.close();

    file.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    file << id << '|' << firstName << '|' << lastName << '|' << phoneNumber << '|' << email << '|' << address << '|' << endl;
    file.close();

    cout << "Kontakt dodano do ksiazki adresowej: " << firstName << " " << lastName << endl;
    Sleep(1500);
}

void searchByFirstName(vector <DataOfSinglePerson> vectorOfPersons) {
    string firstName;
    string correctData = "";

    cout << "Podaj szukane imie: ";
    firstName = insertLine();

    for(int i = 0; i < vectorOfPersons.size(); i++) {
        if(vectorOfPersons[i].firstName == firstName) {
            correctData = "OK";
            cout << endl;
            cout << "ID: " << vectorOfPersons[i].id << endl;
            cout << "Imie i nazwisko: " << vectorOfPersons[i].firstName << " " << vectorOfPersons[i].lastName << endl;
            cout << "Numer telefonu: " << vectorOfPersons[i].phoneNumber << endl;
            cout << "E-mail: " << vectorOfPersons[i].email << endl;
            cout << "Adres: " << vectorOfPersons[i].address << endl;
        }
    }
    cout << endl;

    if(correctData == "OK") {
        cout << "Wyswietlono wszystkie kontakty o podanym imieniu." << endl;
    } else {
        cout << "Brak kontaktow o podanym imieniu." << endl;
    }

    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void searchByLastName(vector <DataOfSinglePerson> vectorOfPersons) {
    string lastName;
    string correctData = "";

    cout << "Podaj szukane nazwisko: ";
    lastName = insertLine();

    for(int i = 0; i < vectorOfPersons.size(); i++) {
        if(vectorOfPersons[i].lastName == lastName) {
            correctData = "OK";
            cout << endl;
            cout << "ID: " << vectorOfPersons[i].id << endl;
            cout << "Imie i nazwisko: " << vectorOfPersons[i].firstName << " " << vectorOfPersons[i].lastName << endl;
            cout << "Numer telefonu: " << vectorOfPersons[i].phoneNumber << endl;
            cout << "E-mail: " << vectorOfPersons[i].email << endl;
            cout << "Adres: " << vectorOfPersons[i].address << endl;
        }
    }
    cout << endl;

    if(correctData == "OK") {
        cout << "Wyswietlono wszystkie kontakty o podanym nazwisku." << endl;
    } else {
        cout << "Brak kontaktow o podanym nazwisku." << endl;
    }

    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void displayAllContacts(vector <DataOfSinglePerson> vectorOfPersons) {
    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);

    if(file.good() == false) {
        cout << "Ksiazka adresowa jest pusta." << endl;
    }

    else {
        for(int i = 0; i < vectorOfPersons.size() / 2; i++) { // jak tu nie podziele przez 2 to wstawia puste kontakty, dlaczego (alokacja przez wektor?)?
            cout << endl;
            cout << "ID: " << vectorOfPersons[i].id << endl;
            cout << "imie: " << vectorOfPersons[i].firstName << endl;
            cout << "nazwisko: " << vectorOfPersons[i].lastName << endl;
            cout << "nr tel.: " << vectorOfPersons[i].phoneNumber << endl;
            cout << "e-mail: " << vectorOfPersons[i].email << endl;
            cout << "adres: " << vectorOfPersons[i].address << endl;
        }
    }
    file.close();

    cout << endl;
    cout << "Kliknij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void deleteContact (int totalAmountOfPersons, vector <DataOfSinglePerson> vectorOfPersons) {
    int id;
    char userChoiceSideMenu;

    cout << "Podaj numer ID kontaktu ktory zamierzasz usunac ";
    cin >> id;
    cout << "Czy na pewno usunac kontakt o numerze ID: " << id << "? (kliknij: 't' aby potwierdzic / 'n' aby anulowac) ";
    cin >> userChoiceSideMenu;
    cout << endl;

    bool condition = false;

    if (userChoiceSideMenu == 't') {
        for(int i = 0; i < vectorOfPersons.size(); i++) {
            if (vectorOfPersons[i].id == id)
                condition = true;
        }

        if (condition == false) {
            cout << "Kontakt o wskazanym numerze ID nie istnieje." << endl;
        }

        else {
            fstream file, file2;
            string line;

            file.open("KsiazkaAdresowa.txt", ios::in);
            file2.open("KsiazkaAdresowa_tymczasowa.txt", ios::out);

            for (int i = 0; i < totalAmountOfPersons; i++) {
                getline(file,line);

                char searchedSign = '|';
                size_t position1 = line.find(searchedSign);
                int checkedId = atoi((line.substr(0, position1)).c_str());

                if (checkedId != id) {
                    file2 << line << endl;
                }
            }

            file.close();
            file2.close();

            remove("KsiazkaAdresowa.txt");
            rename("KsiazkaAdresowa_tymczasowa.txt", "KsiazkaAdresowa.txt");

            cout << "Kontakt zostal usuniety.";
        }

        cout << endl;
        cout << "Wcisnij enter aby wrocic do menu glownego.";
        getchar();
        getchar();
    }
}

void editContact (int totalAmountOfPersons, vector <DataOfSinglePerson> vectorOfPersons) {
    int id;
    char userChoiceSideMenu;
    string changedData;
    string correctID = "";

    cout << "Podaj numer ID kontaktu ktory chcesz edytowac ";
    cin >> id;

    for(int i = 0; i < vectorOfPersons.size(); i++) {
        if(vectorOfPersons[i].id == id) {
            correctID = "ID poprawne";
        }
    }

    if (correctID == "ID poprawne") {
        cout << "Ktore dane chcesz edytowac? " << endl;
        cout << "1. Imie." << endl;
        cout << "2. Nazwisko." << endl;
        cout << "3. Numer telefonu." << endl;
        cout << "4. E-mail." << endl;
        cout << "5. Adres." << endl;
        cout << "6. Powrot do menu glownego." << endl;
        cout << "Twoj wybor: ";
        cin >> userChoiceSideMenu;
        cout << endl;

        if (userChoiceSideMenu == '1') {
            for(int i = 0; i < vectorOfPersons.size(); i++) {
                if(vectorOfPersons[i].id == id) {
                    cout << "Aktualne imie: " << vectorOfPersons[i].firstName <<endl;
                    cout << "Zmiana na: " ;
                    changedData = insertLine();
                    vectorOfPersons[i].firstName = changedData;
                    cout << endl << "Imie zostalo zmienione." << endl;
                }
            }
        }

        else if (userChoiceSideMenu == '2') {
            for(int i = 0; i < vectorOfPersons.size(); i++) {
                if(vectorOfPersons[i].id == id) {
                    cout << "Aktualne nazwisko: " << vectorOfPersons[i].lastName <<endl;
                    cout << "Zmiana na: " ;
                    changedData = insertLine();
                    vectorOfPersons[i].lastName = changedData;
                    cout << endl << "Nazwisko zostalo zmienione." << endl;
                }
            }
        }

        else if (userChoiceSideMenu == '3') {
            for(int i = 0; i < vectorOfPersons.size(); i++) {
                if(vectorOfPersons[i].id == id) {
                    cout << "Aktualny nr. telefonu : " << vectorOfPersons[i].phoneNumber <<endl;
                    cout << "Zmiana na: " ;
                    changedData = insertLine();
                    vectorOfPersons[i].phoneNumber = changedData;
                    cout << endl << "Nr tel. zostal zmieniony." << endl;
                }
            }
        }

        else if (userChoiceSideMenu == '4') {
            for(int i = 0; i < vectorOfPersons.size(); i++) {
                if(vectorOfPersons[i].id == id) {
                    cout << "Aktualny email: " << vectorOfPersons[i].email <<endl;
                    cout << "Zmiana na: " ;
                    changedData = insertLine();
                    vectorOfPersons[i].email = changedData;
                    cout << endl << "Email zostal zmieniony." << endl;
                }
            }
        }

        else if (userChoiceSideMenu == '5') {
            for(int i = 0; i < vectorOfPersons.size(); i++) {
                if(vectorOfPersons[i].id == id) {
                    cout << "Aktualny adres: " << vectorOfPersons[i].address <<endl;
                    cout << "Zmiana na: " ;
                    changedData = insertLine();
                    vectorOfPersons[i].address = changedData;
                    cout << endl << "Adres zostal zmieniony." << endl;
                }
            }
        }

        else if (userChoiceSideMenu == '6') {
            getchar();
            getchar();
        }

        fstream file, file2;
        string line;

        file.open("KsiazkaAdresowa.txt", ios::in);
        file2.open("KsiazkaAdresowa_tymczasowa.txt", ios::out);

        for (int i = 0; i < totalAmountOfPersons; i++) {
            getline(file, line);

            char searchedSign = '|';
            size_t position1 = line.find(searchedSign);
            int checkedId = atoi((line.substr(0, position1)).c_str());

            if (checkedId == id) {
                for(int changedPosition = 0; changedPosition < vectorOfPersons.size(); changedPosition++) {
                    if(vectorOfPersons[changedPosition].id == id) {
                        file2 << vectorOfPersons[changedPosition].id << '|';
                        file2 << vectorOfPersons[changedPosition].firstName << '|';
                        file2 << vectorOfPersons[changedPosition].lastName << '|' ;
                        file2 << vectorOfPersons[changedPosition].phoneNumber << '|';
                        file2 << vectorOfPersons[changedPosition].email << '|';
                        file2 << vectorOfPersons[changedPosition].address << '|' << endl;
                    }
                }
            }
            else {
                file2 << line << endl;
            }
        }

        file.close();
        file2.close();

        remove("KsiazkaAdresowa.txt");
        rename("KsiazkaAdresowa_tymczasowa.txt", "KsiazkaAdresowa.txt");
    }

    else {
        cout << "Kontakt o wskazanym numerze ID nie istnieje." << endl;
    }

    cout << endl;
    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
}

int main() {
    DataOfSinglePerson person;

    int totalAmountOfPersons = checkTotalAmountOfPersons();

    vector <DataOfSinglePerson> vectorOfPersons;

    char userChoiceMainMenu;

    while(1) {
        system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata." << endl;
            cout << "2. Wyszukaj po imieniu." << endl;
            cout << "3. Wyszukaj po nazwisku." << endl;
            cout << "4. Wyswietl wszystkich adresatow." << endl;
            cout << "5. Usun adresta." << endl;
            cout << "6. Edytuj adresata." << endl;
            cout << "9. Zakoncz program." << endl;
            cout << "Twoj wybor: ";
            cin >> userChoiceMainMenu;
            cout << endl;

        totalAmountOfPersons = checkTotalAmountOfPersons();
        vectorOfPersons = loadPersonsList(totalAmountOfPersons, person);

        if (userChoiceMainMenu == '1') {
            saveNewContact(person, vectorOfPersons, totalAmountOfPersons);
        }
        if (userChoiceMainMenu == '2') {
            searchByFirstName(vectorOfPersons);
        }
        if (userChoiceMainMenu == '3') {
            searchByLastName(vectorOfPersons);
        }
        if (userChoiceMainMenu == '4') {
            displayAllContacts(vectorOfPersons);
        }
        if (userChoiceMainMenu == '5') {
            deleteContact(totalAmountOfPersons, vectorOfPersons);
            totalAmountOfPersons = checkTotalAmountOfPersons();
        }
        if (userChoiceMainMenu == '6') {
            editContact(totalAmountOfPersons, vectorOfPersons);
        }
        else if (userChoiceMainMenu == '9') {
            exit(0);
        }
    }
    return 0;
}
