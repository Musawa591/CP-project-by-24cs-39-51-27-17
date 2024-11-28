#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Room {
private:
    int roomNumber;
    string roomType;
    bool isAvailable;

public:
    Room(int number, const string& type)
        : roomNumber(number), roomType(type), isAvailable(true) {}

    int getRoomNumber() const { return roomNumber; }
    string getRoomType() const { return roomType; }
    bool getAvailability() const { return isAvailable; }
    
    void setAvailability(bool status) { isAvailable = status; }
};

class Tenant {
private:
    string name;
    string contactNumber;
    int age;
    string paymentStatus;

public:
    Tenant(string name, string contact, int age)
        : name(name), contactNumber(contact), age(age), paymentStatus("Pending") {}

    string getName() const { return name; }
    string getContactNumber() const { return contactNumber; }
    int getAge() const { return age; }

    string getPaymentStatus() const { return paymentStatus; }
    void setPaymentStatus(const string& status) { paymentStatus = status; }

    void displayTenantInfo() const {
        cout << "Name: " << name
             << ", Contact: " << contactNumber
             << ", Age: " << age
             << ", Payment Status: " << paymentStatus << endl;
    }

    void updateContactNumber(const string& newContact) {
        contactNumber = newContact;
        cout << "Contact updated successfully.\n";
    }
};

class Booking {
private:
    int roomNumber;
    string tenantName;

public:
    Booking(int roomNum, const string& tenantName)
        : roomNumber(roomNum), tenantName(tenantName) {}

    int getRoomNumber() const { return roomNumber; }
    string getTenantName() const { return tenantName; }
};

class HostelManager {
private:
    vector<Room> rooms;
    vector<Tenant> tenants;
    vector<Booking> bookings;

public:
    void addRoom(int roomNumber, const string& roomType) {
        rooms.push_back(Room(roomNumber, roomType));
        cout << "Room " << roomNumber << " added successfully.\n";
    }

    void addTenant(const Tenant& tenant) {
        tenants.push_back(tenant);
        cout << "Tenant " << tenant.getName() << " added successfully.\n";
    }

    void createBooking(int roomNumber, const Tenant& tenant) {
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (rooms[i].getRoomNumber() == roomNumber && rooms[i].getAvailability()) {
                bookings.push_back(Booking(roomNumber, tenant.getName()));
                rooms[i].setAvailability(false);
                cout << "Room " << roomNumber << " booked successfully for " << tenant.getName() << ".\n";
                return;
            }
        }
        cout << "Room " << roomNumber << " is not available for booking.\n";
    }

    void updateTenantContact(const string& tenantName, const string& newContact) {
        Tenant* tenant = findTenant(tenantName);
        if (tenant) {
            tenant->updateContactNumber(newContact);
        } else {
            cout << "Tenant " << tenantName << " not found.\n";
        }
    }

    void updateTenantPaymentStatus(const string& tenantName, const string& status) {
        Tenant* tenant = findTenant(tenantName);
        if (tenant) {
            tenant->setPaymentStatus(status);
            cout << "Payment status for " << tenantName << " updated to " << status << ".\n";
        } else {
            cout << "Tenant " << tenantName << " not found.\n";
        }
    }

    void generateRoomUsageReport() const {
        cout << "\nRoom Usage Report:\n";
        for (size_t i = 0; i < rooms.size(); ++i) {
            cout << "Room " << rooms[i].getRoomNumber() 
                 << " - " << (rooms[i].getAvailability() ? "Available" : "Occupied") 
                 << endl;
        }
    }

    void generatePaymentStatusReport() const {
        cout << "\nTenant Payment Status Report:\n";
        for (size_t i = 0; i < tenants.size(); ++i) {
            cout << "Tenant: " << tenants[i].getName() 
                 << " - Payment Status: " << tenants[i].getPaymentStatus() 
                 << endl;
        }
    }

    void generateFinancialSummaryReport() const {
        int paidCount = 0;
        int pendingCount = 0;
        
        for (size_t i = 0; i < tenants.size(); ++i) {
            if (tenants[i].getPaymentStatus() == "Paid") {
                paidCount++;
            } else {
                pendingCount++;
            }
        }

        cout << "\nFinancial Summary Report:\n";
        cout << "Total Tenants: " << tenants.size() << endl;
        cout << "Tenants Paid: " << paidCount << endl;
        cout << "Tenants with Pending Payments: " << pendingCount << endl;
    }

    void viewTenants() const {
        if (tenants.empty()) {
            cout << "No tenants in the system.\n";
            return;
        }
        cout << "Tenant List:\n";
        for (size_t i = 0; i < tenants.size(); ++i) {
            tenants[i].displayTenantInfo();
        }
    }

    // Method to find a tenant by name and return a pointer
    Tenant* findTenant(const string& name) {
        for (size_t i = 0; i < tenants.size(); ++i) {
            if (tenants[i].getName() == name) {
                return &tenants[i];
            }
        }
        return NULL;
    }
};

int main() {
    HostelManager manager;
    int choice;

    while (true) {
        cout << "\n--- Hostel Accommodation System ---\n";
        cout << "1. Add Room\n";
        cout << "2. Add Tenant\n";
        cout << "3. Create Booking\n";
        cout << "4. Update Tenant Contact\n";
        cout << "5. Update Tenant Payment Status\n";
        cout << "6. Generate Room Usage Report\n";
        cout << "7. Generate Payment Status Report\n";
        cout << "8. Generate Financial Summary Report\n";
        cout << "9. View Tenants\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            int roomNumber;
            string roomType;
            cout << "Enter room number: ";
            cin >> roomNumber;
            cout << "Enter room type: ";
            cin.ignore();
            getline(cin, roomType);
            manager.addRoom(roomNumber, roomType);
        } else if (choice == 2) {
            string name, contact;
            int age;
            cout << "Enter tenant name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter contact number: ";
            getline(cin, contact);
            cout << "Enter age: ";
            cin >> age;
            manager.addTenant(Tenant(name, contact, age));
        } else if (choice == 3) {
            int roomNumber;
            string tenantName;
            cout << "Enter room number to book: ";
            cin >> roomNumber;
            cout << "Enter tenant name for booking: ";
            cin.ignore();
            getline(cin, tenantName);
            Tenant* tenant = manager.findTenant(tenantName);
            if (tenant) {
                manager.createBooking(roomNumber, *tenant);
            } else {
                cout << "Tenant " << tenantName << " not found.\n";
            }
        } else if (choice == 4) {
            string tenantName, newContact;
            cout << "Enter tenant name: ";
            cin.ignore();
            getline(cin, tenantName);
            cout << "Enter new contact number: ";
            getline(cin, newContact);
            manager.updateTenantContact(tenantName, newContact);
        } else if (choice == 5) {
            string tenantName, status;
            cout << "Enter tenant name: ";
            cin.ignore();
            getline(cin, tenantName);
            cout << "Enter payment status (Paid/Pending): ";
            getline(cin, status);
            manager.updateTenantPaymentStatus(tenantName, status);
        } else if (choice == 6) {
            manager.generateRoomUsageReport();
        } else if (choice == 7) {
            manager.generatePaymentStatusReport();
        } else if (choice == 8) {
            manager.generateFinancialSummaryReport();
        } else if (choice == 9) {
            manager.viewTenants();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
