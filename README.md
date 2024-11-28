#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <cctype>

using namespace std; 

const string Password = "30aug2007";

void clearScreen() {
    system("cls");
}

bool isAlphabetic(const string &input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isalpha(input[i]) && input[i] != ' ') {
            return false;
        }
    }
    return true;
}

bool isNumeric(const string &input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}


bool isValidEmail(const std::string& email) {
    size_t atPos = email.find('@');
    if (atPos == std::string::npos) {
        return false;
    }

    if (atPos == 0 || atPos == email.length() - 1) {
        return false;
    }

    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos || dotPos == email.length() - 1) {
        return false;
    }

    if (dotPos < atPos + 2) {
        return false;
    }

    return true;
}

class Room {
public:
    int roomNumber;
    bool isAvailable;

    Room(int number) {
        roomNumber = number;
        isAvailable = true;
    }
};

class Tenant {
public:
    string name;
    string email;
    string contact;
    string paymentStatus;

    Tenant(string tenantName, string tenantEmail, string tenantContact) {
        name = tenantName;
        email = tenantEmail;
        contact = tenantContact;
        paymentStatus = "Pending";
    }
};

class Booking {
public:
    int roomNumber;
    string tenantName;
    string email;
    bool paymentStatus;

    Booking(int roomNum, string name, string tenantEmail, bool isPaid) {
        roomNumber = roomNum;
        tenantName = name;
        email = tenantEmail;
        paymentStatus = isPaid;
    }
};

class HostelManager {
public:
    vector<Room> rooms;
    vector<Tenant> tenants;
    vector<Booking> bookings;

    void addRoom(int roomNumber) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                cout << "Room " << roomNumber << " is already added." << endl;
                return;
            }
        }
        Room newRoom(roomNumber);
        rooms.push_back(newRoom);
        cout << "Room " << roomNumber << " added." << endl;
    }

    void addTenant(string tenantName, string tenantEmail, string tenantContact) {
        for (int i = 0; i < tenants.size(); i++) {
            if (tenants[i].email == tenantEmail) {
                cout << "The Email " << tenantEmail << " is already taken." << endl;
                return;
            }
        }
        Tenant newTenant(tenantName, tenantEmail, tenantContact);
        tenants.push_back(newTenant);
        cout << "Tenant " << tenantName << " added." << endl;
    }

    void createBooking(int roomNumber, string tenantName, string tenantEmail, bool isPaid) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber && rooms[i].isAvailable) {
                for (int j = 0; j < tenants.size(); j++) {
                    if (tenants[j].email == tenantEmail) {
                        Booking newBooking(roomNumber, tenantName, tenantEmail, isPaid);
                        bookings.push_back(newBooking);
                        tenants[j].paymentStatus = isPaid ? "Paid" : "Pending";
                        rooms[i].isAvailable = false;
                        cout << "Room " << roomNumber << " successfully booked for " << tenantName << "." << endl;
                        return;
                    }
                }
                cout << "Tenant Email " << tenantEmail << " not found." << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " not available." << endl;
    }

    void deleteRoom(int roomNumber) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                rooms.erase(rooms.begin() + i);
                cout << "Room " << roomNumber << " deleted successfully." << endl;
                cin.ignore(1000, '\n');
                return;
            }
        }
        cout << "Room " << roomNumber << " not found." << endl;
    }

    void deleteTenant(string tenantName, string tenantEmail, string tenantContact) {
        for (int i = 0; i < tenants.size(); i++) {
            if (tenants[i].name == tenantName && tenants[i].email == tenantEmail && tenants[i].contact == tenantContact) {
                tenants.erase(tenants.begin() + i);
                cout << "Tenant " << tenantName << " deleted successfully." << endl;
                cin.ignore(1000, '\n');
                return;
            }
        }
        cout << "Tenant " << tenantName << " not found." << endl;
    }

    void deleteBooking(int roomNumber, string tenantName, string tenantEmail) {
        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].roomNumber == roomNumber && bookings[i].email == tenantEmail) {
                for (int j = 0; j < rooms.size(); j++) {
                    if (rooms[j].roomNumber == roomNumber) {
                        rooms[j].isAvailable = true;
                        break;
                    }
                }

                for (int j = 0; j < tenants.size(); j++) {
                    if (tenants[j].name == tenantName && tenants[j].email == tenantEmail) {
                        tenants[j].paymentStatus = "Pending";
                    }
                }
                bookings.erase(bookings.begin() + i);
                cout << tenantName << " tenant booking cancelled for room no " << roomNumber << endl;
                cin.ignore(1000, '\n');
                return;
            }
        }
        cout << "Booking not found for tenant " << tenantName << " in room " << roomNumber << endl;
        cin.ignore(1000, '\n');
    }

    void generateFinancialSummaryReport() {
        int paidCount = 0;
        for (int i = 0; i < tenants.size(); i++) {
            if (tenants[i].paymentStatus == "Paid") {
                paidCount++;
            }
        }

        cout << "\nFinancial Summary Report: " << endl;
        cout << "Total Tenants: " << tenants.size() << endl;
        cout << "Tenants with Paid Status: " << paidCount << endl;
        cout << "Tenants with Pending Status: " << tenants.size() - paidCount << endl;
    }

    void viewTenants() {
        if (tenants.empty()) {
            cout << "No tenants in the system.\n";
            return;
        }
        cout << "Tenant List:\n";
        for (int i = 0; i < tenants.size(); i++) {
            cout << tenants[i].name << " - " << tenants[i].email << " - "
                 << tenants[i].contact << " - Payment Status: " << tenants[i].paymentStatus << endl;
        }
    }

    void viewRoomAvailability() {
        cout << "Room Availability:\n";
        for (int i = 0; i < rooms.size(); i++) {
            string status = rooms[i].isAvailable ? "Available" : "Occupied";
            cout << "Room " << rooms[i].roomNumber << " - " << status << endl;
        }
    }
};

void adminPanel();
void userPanel();

void adminPanel(HostelManager &manager){
    int choice;
	 while (true) {
        clearScreen();
        cout << setw(38) << left << "";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(80) << left << "--------------- Admin Panel -------------\n";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(50) << left << "1. Add Room\n";
        cout << setw(52) << left << "2. Add Tenant\n";
        cout << setw(56) << left << "3. Create Booking\n";
        cout << setw(53) << left << "4. Delete Room\n";
        cout << setw(55) << left << "5. Delete Tenant\n";
        cout << setw(56) << left << "6. Cancel Booking\n";
        cout << setw(75) << left << "7. Generate Financial Summary Report\n";
        cout << setw(54) << left << "8. View Tenants\n";
        cout << setw(64) << left << "9. View Room Availability\n";
        cout << setw(58) << left << "0. Exit Admin Panel\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(1000, '\n');
		clearScreen();
        
		switch (choice) {
            case 0:
                cout << "\nBack to Main Menu.\n";
                return;
            case 1: {
                string input;
                int roomNumber;
                cout << "Enter room number: ";
                getline(cin, input);

                if (!isNumeric(input)) {
                    cout << "Invalid input! Room number must be numeric.\n";
                    break;
                }

                roomNumber = atoi(input.c_str());
                manager.addRoom(roomNumber);
                break;
            }
            case 2: {
                string name, email, contact;
                
                cout << "Enter tenant name: ";
                getline(cin, name);
                
                if (!isAlphabetic(name)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }

                cout << "Enter tenant email: ";
                getline(cin, email);
                
                if (!isValidEmail(email)) {
                    cout << "The email is invalid." << endl;
                    break;
                }
                cout << "Enter tenant contact: ";
                getline(cin, contact);
                
                if (!isNumeric(contact)) {
                    cout << "Invalid input! Contact number must be numeric.\n";
                    break;
                }
                
                manager.addTenant(name, email, contact);
                break;
            }
            case 3: {
                int roomNumber;
                string tenantName, tenantEmail;
                int paymentStatusInput;
                bool paymentStatus = false;

                cout << "Enter room number: ";
                cin >> roomNumber;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Room number must be numeric.\n";
                    break;
                }
                
                cin.ignore(1000, '\n');
                cout << "Enter tenant name: ";
                getline(cin, tenantName);
                
                if (!isAlphabetic(tenantName)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }
                
                cout << "Enter tenant email: ";
                getline(cin, tenantEmail);
                
                if (!isValidEmail(tenantEmail)) {
                    cout << "The email is invalid." << endl;
                    break;
                }

                cout << "Is the payment complete (1. Paid || 0. Pending): ";
                cin>> paymentStatusInput;

                cin.ignore(1000, '\n');
                if (paymentStatusInput == 1) {
                    paymentStatus = true;
                    manager.createBooking(roomNumber, tenantName, tenantEmail, paymentStatus);
                    break;
                }
                
                else if(paymentStatusInput == 0){
                	cout<<"Booking unsuccessful: complete payment to proceed."<<endl;
                	break;
                }
                else{
                	cout<<"Invalid input!"<<endl;
                	break;
                }

            }
            case 4: {
                int roomNumber;
                cout << "Enter room number to delete: ";
                cin >> roomNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Room number must be numeric.\n";
                    break;
                }
                manager.deleteRoom(roomNumber);
                break;
            }
            case 5: {
                string name, email, contact;
                cout << "Enter tenant name: ";
                getline(cin, name);
                
                if (!isAlphabetic(name)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }
                
                cout << "Enter tenant email: ";
                getline(cin, email);
                
                if (!isValidEmail(email)) {
                    cout << "The email is invalid." << endl;
                    break;
                }
                
                cout << "Enter tenant contact: ";
                getline(cin, contact);

                if (!isNumeric(contact)) {
                    cout << "Invalid input! Contact number must be numeric.\n";
                    break;
                }
                
                manager.deleteTenant(name, email, contact);
                break;
            }
            case 6: {
                int roomNumber;
                string tenantName, tenantEmail;
                cout << "Enter room number to cancel booking: ";
                cin >> roomNumber;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Room number must be numeric.\n";
                    break;
                }
                
                cin.ignore(1000, '\n');
                cout << "Enter tenant name: ";
                getline(cin, tenantName);
                
                if (!isAlphabetic(tenantName)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }
                
                cout << "Enter tenant email: ";
                getline(cin, tenantEmail);
                
                if (!isValidEmail(tenantEmail)) {
                    cout << "The email is invalid." << endl;
                    break;
                }

                manager.deleteBooking(roomNumber, tenantName, tenantEmail);
                break;
            }
            case 7:
                manager.generateFinancialSummaryReport();
                break;
            case 8:
                manager.viewTenants();
                break;
            case 9:
                manager.viewRoomAvailability();
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
        cout << "\nPress any key to continue...\n";
        cin.ignore();
    }

}

void userPanel(HostelManager &manager){
    int choice;
	while (true) {
         clearScreen();
         cout << setw(38) << left << "";
         cout << setw(80) << left << "-----------------------------------------\n";
         cout << setw(80) << left << "-----------------------------------------\n";
         cout << setw(80) << left << "--------------- User Panel -------------\n";
         cout << setw(80) << left << "-----------------------------------------\n";
         cout << setw(80) << left << "-----------------------------------------\n";
         cout << setw(55) << left << "1. Add Your Info\n";
         cout << setw(56) << left << "2. Create Booking\n";
         cout << setw(56) << left << "3. Cancel Booking\n";
         cout << setw(64) << left << "4. View Room Availability\n";
         cout << setw(57) << left << "0. Exit User Panel\n";
         cout << "Choose an option: ";
         cin >> choice;
         cin.ignore(1000, '\n');
		 clearScreen();
		 
		 switch(choice){
		 	 case 0:
                cout << "\nBack to Main Menu.\n";
                return;
		    case 1: {
               string name, email, contact;
                
                cout << "Enter tenant name: ";
                getline(cin, name);
                
                if (!isAlphabetic(name)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }

                cout << "Enter tenant email: ";
                getline(cin, email);
                
                if (!isValidEmail(email)) {
                    cout << "The email is invalid." << endl;
                    break;
                }
                cout << "Enter tenant contact: ";
                getline(cin, contact);
                
                if (!isNumeric(contact)) {
                    cout << "Invalid input! Contact number must be numeric.\n";
                    break;
                }
                
                manager.addTenant(name, email, contact);
                break;
            }
            case 2: {
                int roomNumber;
                string tenantName, tenantEmail;
                int paymentStatusInput;
                bool paymentStatus = false;

                cout << "Enter room number: ";
                cin >> roomNumber;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Room number must be numeric.\n";
                    break;
                }
                
                cin.ignore(1000, '\n');
                cout << "Enter tenant name: ";
                getline(cin, tenantName);
                
                if (!isAlphabetic(tenantName)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }
                
                cout << "Enter tenant email: ";
                getline(cin, tenantEmail);
                
                if (!isValidEmail(tenantEmail)) {
                    cout << "The email is invalid." << endl;
                    break;
                }

                cout << "Is the payment complete (1. Paid || 0. Pending): ";
                cin>> paymentStatusInput;

                cin.ignore(1000, '\n');
                if (paymentStatusInput == 1) {
                    paymentStatus = true;
                    manager.createBooking(roomNumber, tenantName, tenantEmail, paymentStatus);
                    break;
                }
                
                else if(paymentStatusInput == 0){
                	cout<<"Booking unsuccessful: complete payment to proceed."<<endl;
                	break;
                }
                else{
                	cout<<"Invalid input!"<<endl;
                	break;
                }

            }
            case 3: {
                int roomNumber;
                string tenantName, tenantEmail;
                cout << "Enter room number to cancel booking: ";
                cin >> roomNumber;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Room number must be numeric.\n";
                    break;
                }
                
                cin.ignore(1000, '\n');
                cout << "Enter tenant name: ";
                getline(cin, tenantName);
                
                if (!isAlphabetic(tenantName)) {
                    cout << "Invalid input! Name must contain only alphabetic characters and spaces.\n";
                    break;
                }
                
                cout << "Enter tenant email: ";
                getline(cin, tenantEmail);
                
                if (!isValidEmail(tenantEmail)) {
                    cout << "The email is invalid." << endl;
                    break;
                }

                manager.deleteBooking(roomNumber, tenantName, tenantEmail);
                break;
            }
            case 4:
                manager.viewRoomAvailability();
                break;
            default:
                cout << "Invalid option. Please try again.\n";
		 }
		cout << "\nPress any key to continue...\n";
        cin.ignore();
    }
}

int main() {
    system("color 71");
    HostelManager manager;
    int choice;

    while (true) {
    	string password;
        clearScreen();
        cout << setw(38) << left << "";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(80) << left << "------ Hostel Accommodation System ------\n";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(80) << left << "-----------------------------------------\n";
        cout << setw(53) << left << "1. Admin Panel\n";
        cout << setw(52) << left << "2. User Panel\n";
        cout << setw(46) << left << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        clearScreen();
        switch (choice) {
            case 1:
            	cout<<"Enter Password"<<endl;
            	getline(cin, password);
            	if(password == Password){
            		cout<<"Welcome to Admin Panel"<<endl;
            		cin.ignore(1000, '\n');
				    adminPanel(manager);	
            	}
            	else{
            		cout<<"Wrong Password!"<<endl;
            	}
                break;
            case 2:
                userPanel(manager);
                break;
            case 0:
                cout << setw(38) << left << "";
                cout << setw(80) << left << "*\n";
                cout << setw(80) << left << "*********** Program Terminated **********\n";
                cout << setw(80) << left << "*\n";
                return 0;
            default:
                cout << "Invalid input! Please try again.\n";
        }
        cout << "\nPress any key to return to the main menu...\n";
        cin.get();
    }
}
