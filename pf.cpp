#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_FLIGHTS = 100;
const int MAX_LUGGAGE = 100;
const int MAX_USERS = 100;
const int MAX_NAME = 20;


struct Flight {
    int flightID;
    char destination[20];
    char departure[10];
    char arrival[10];
    float price;
};

struct Luggage {
    int id;
    double weight;
    char owner[30];
};

struct Passenger {
    int id;
    char name[30];
    int luggageID;
    bool isCheckedIn;
};

// Global variables
Flight flights[MAX_FLIGHTS];
int flightCount = 0;
Luggage luggageList[MAX_LUGGAGE];
int luggageCount = 0;

// Function prototypes
int main_menu();
string login();
string signup();
int customer();
int admin();
int staff();
void seat_reservation(const string& username);
void user_ticket(const string& username);
void flight_details();
void total_passengers();
void tickets_bought();
void add_flights();
void delete_flights();
void luggage_management();
void checkin();
void boarding();

void write_flights_to_file();
bool validate_flight_id(int flightID);
void stringCopy(char* destination, const char* src);
bool stringCompare(const char* str1, const char* str2);
void read_flights_from_file();

bool validate_flight_id(int flightID) {
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightID) {
            return true; // ID already exists
        }
    }
    return false; // ID is unique
}

// Helper function to copy strings safely
void stringCopy(char* destination, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < MAX_NAME - 1) {
        destination[i] = src[i];
        i++;
    }
    destination[i] = '\0';
}

// Helper function to compare strings
bool stringCompare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0');
}

void read_flights_from_file() {
    ifstream flightFile("flights.txt");
    if (!flightFile) {
        cout << "Error: Could not open flights file.\n";
        flightCount = 0;
        return;
    }

    flightCount = 0; // Reset the count before loading
    while (flightFile >> flights[flightCount].flightID
        >> flights[flightCount].destination
        >> flights[flightCount].departure
        >> flights[flightCount].arrival
        >> flights[flightCount].price) {
        flightCount++;
        if (flightCount >= MAX_FLIGHTS) { // Prevent array overflow
            cout << "Warning: Maximum flight limit reached. Some flights may not be loaded.\n";
            break;
        }
    }

    flightFile.close();
}

// Function to display flight details
void flight_details() {
    // Ensure the latest flights are loaded from the file
    read_flights_from_file();

    while (flightCount == 0) {
        if (flightCount == 0) {
            cout << "No flights available at the moment.\n";
            cout << "Press 0 to exit: ";
            int choice;
            cin >> choice;
            if (choice == 0) {
                customer();
            }
        }
        return;
    }

    cout << "\n=== Available Flights ===\n";
    for (int i = 0; i < flightCount; i++) {
        cout << "Flight ID: " << flights[i].flightID << "  "
            << "Destination: " << flights[i].destination << "  "
            << "Departure: " << flights[i].departure << "  "
            << "Arrival: " << flights[i].arrival << "  "
            << "Price: $" << fixed << setprecision(2) << flights[i].price << "\n"
            << "-------------------------\n";
    }
}

// Function to add flights (ensure it's updating the flight array as well as the file)
void add_flights() {
    cout << "\nEnter Flight Details:\n";
    cout << "Flight ID: ";
    cin >> flights[flightCount].flightID;

    // Check if flight ID already exists
    if (validate_flight_id(flights[flightCount].flightID)) {
        cout << "Flight ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Destination: ";
    cin.getline(flights[flightCount].destination, 20);

    cout << "Departure: ";
    cin.getline(flights[flightCount].departure, 10);

    cout << "Arrival: ";
    cin.getline(flights[flightCount].arrival, 10);

    cout << "Price: ";
    cin >> flights[flightCount].price;

    cin.ignore();

    // Append to the file
    ofstream file("flights.txt", ios::app);
    if (file.is_open()) {
        file << flights[flightCount].flightID << " "
            << flights[flightCount].destination << " "
            << flights[flightCount].departure << " "
            << flights[flightCount].arrival << " "
            << flights[flightCount].price << endl;
        file.close();
        cout << "Flight added successfully!\n";
        flightCount++; // Increment flight count after adding to array
        // Display updated flight details
        flight_details();
    }
    else {
        cout << "Error: Could not add flight\n";
    }
}
void delete_flights() {
    // Ensure the latest flights are loaded from the file
    read_flights_from_file();

    if (flightCount == 0) {
        cout << "No flights available to delete.\n";
        return;
    }

    int flightIDToDelete;
    cout << "Enter the Flight ID to delete: ";
    cin >> flightIDToDelete;

    bool flightFound = false;

    // Iterate through the flights to find the flight to delete
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightIDToDelete) {
            flightFound = true;

            // Shift remaining flights in the array to overwrite the deleted flight
            for (int j = i; j < flightCount - 1; j++) {
                flights[j] = flights[j + 1];
            }

            flightCount--; // Decrease flight count
            cout << "Flight with ID " << flightIDToDelete << " deleted successfully.\n";

            // Update the flights file
            write_flights_to_file();
            break;
        }
    }

    if (!flightFound) {
        cout << "Flight ID " << flightIDToDelete << " not found.\n";
    }
}

void seat_reservation(const string& username) {
    flight_details();

    int flightChoice;
    cout << "\nEnter flight ID to reserve: ";
    cin >> flightChoice;

    // Verify flight exists
    ifstream flightFile("flights.txt");
    int id;
    char destination[MAX_NAME], departure[MAX_NAME], arrival[MAX_NAME];
    float price;
    bool found = false;
    string flightInfo;

    while (flightFile >> id >> destination >> departure >> arrival >> price) {
        if (id == flightChoice) {
            found = true;
            flightInfo = string(destination) + " " + string(departure) + " " + string(arrival);
            break;
        }
    }
    flightFile.close();

    if (!found) {
        cout << "Invalid flight ID\n";
        return;
    }

    // Get passenger details
    char name[20];
    char phone[12];

    cin.ignore();
    cout << "Enter passenger name: ";
    cin.getline(name, 20);

    //Phone number Validation
    bool valid_phone;
    do {
        valid_phone = true; // Reset validity flag
        int length = 0;     // Track the length of the input

        cout << "Phone number (must start with 03 and be 11 digits): ";
        cin >> phone;

        // Calculate the length manually
        while (phone[length] != '\0') {
            length++;
        }

        // Validate length and starting characters
        if (length != 11 || phone[0] != '0' || phone[1] != '3') {
            valid_phone = false;
            cout << "Invalid phone number. Please try again.\n";
        }

        int digit = static_cast<int>(phone[length]);
        // Validate each character as a digit
        for (int i = 0; valid_phone && i < length; i++) {
            if (digit < 0) {
                valid_phone = false;
                cout << " Phone number should contain only positive digits.\n";
                break;
            }
        }
    } while (!valid_phone);

    // Email validation
    char email_address[20];
    do {
        cout << "Email Address(only write username without @gmail.com): ";
        cin >> email_address;
        if (email_address == "@") {
            cout << "Invalid";
        }
    } while (email_address == "@");

        // Save reservation
        ofstream file("reservations.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n"
                << "Passenger: " << name << "\n"
                << "Phone: " << phone << "\n"
                << "Email: " << email_address << "@gmail.com" << "\n"
                << "Flight ID: " << id << "\n"
                << "Flight Details: " << flightInfo << "\n"
                << "Price: $" << fixed << setprecision(2) << price << "\n" << endl
                << "---------------------------------\n";
            file.close();
            cout << "Reservation successful!\n";
        }
        else {
            cout << "Error making reservation\n";
        }
}

void write_flights_to_file() {
    ofstream flightFile("flights.txt");
    if (!flightFile) {
        cout << "Error: Could not open flights file for writing.\n";
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        flightFile << flights[i].flightID << " "
            << flights[i].destination << " "
            << flights[i].departure << " "
            << flights[i].arrival << " "
            << flights[i].price << "\n";
    }

    flightFile.close();
}

    
// Main function
int main() {
    cout << "\n\tAirport Reservation System\n";
    cout << setfill('-') << setw(43) << "-" << endl;
    return main_menu();
}

int main_menu() {
    char choice;
    do {
        cout << "\nSelect Option:\n";
        cout << "1. Login\n";
        cout << "2. Signup\n";
        cout << "3. Exit\n";
        cout << "Enter choice (1-3): ";
        cin >> choice;

        switch (choice) {
        case '1':
            login();
            break;
        case '2':
            signup();
            break;
        case '3':
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice\n";
            break;
        }
    } while (choice != '3');

    return 0;
}

string login() {
    char username[MAX_NAME];
    char password[MAX_NAME];
    char stored_username[MAX_NAME];
    char stored_password[MAX_NAME];

    cout << "\n=== Login ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("users.txt");
    bool found = false;

    while (file >> stored_username >> stored_password) {
        if (stringCompare(username, stored_username) &&
            stringCompare(password, stored_password)) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        cout << "Login successful!\n";
        char role;
        do {
            cout << "\nContinue as:\n";
            cout << "1. Customer\n";
            cout << "2. Admin\n";
            cout << "3. Staff\n";
            cout << "4. Exit\n";
            cout << "Choice: ";
            cin >> role;

            switch (role) {
            case '1': customer(); break;
            case '2': admin(); break;
            case '3': staff(); break;
            case '4': return ""; // Exit
            default: cout << "Invalid choice\n";
            }
        } while (role != '4');
    }
    else {
        cout << "Invalid credentials\n";
    }
    return username;
}

string signup() {
    char username[MAX_NAME];
    char password[MAX_NAME];

    cout << "\n=== Signup ===\n";
    cout << "Choose username: ";
    cin >> username;
    cout << "Choose password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file) {
        file << username << " " << password << "\n";
        file.close();
        cout << "Signup successful!\n";
        return login();
    }
    else {
        cout << "Error creating account\n";
        return "";
    }
}

int customer() {
    char choice;
    do {
        cout << "\n=== Customer Menu ===\n";
        cout << "1. Seat Reservation\n";
        cout << "2. View Ticket\n";
        cout << "3. Flight Details\n";
        cout << "4. Main Menu\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        string username; // Get current username

        switch (choice) {
        case '1':
            seat_reservation(username);
            break;
        case '2':
            user_ticket(username);
            break;
        case '3':
            flight_details();
            break;
        case '4':
            return main_menu();
        case '5':
            return 0;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != '5');
    return 0;
}

void user_ticket(const string& username) {
    cout << "\n=== Your Tickets ===\n";

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "No tickets found\n";
        return;
    }

    string line;
    bool printing = false;
    bool found = false;

    while (getline(file, line)) {
        if (line.find("Username: " + username) != string::npos) {
            printing = true;
            found = true;
        }
        else if (line.find("---") != string::npos) {
            printing = false;
        }

        if (printing) {
            cout << line << "\n";
        }
    }

    if (!found) {
        cout << "No tickets found for " << username << "\n";
    }

    file.close();
}

void total_passengers() {
    cout << "\n=== Total Passengers ===\n";

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "No passenger records found\n";
        return;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.find("Username: ") != string::npos) {
            count++;
            cout << line << "\n";
        }
    }

    file.close();
    cout << "\nTotal Passengers: " << count << "\n";
}

void tickets_bought() {
    cout << "\n=== Tickets Bought ===\n";

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "No ticket records found\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

void luggage_management() {
    char choice;
    do {
        cout << "\n=== Luggage Management ===\n";
        cout << "1. Add Luggage\n";
        cout << "2. Remove Luggage\n";
        cout << "3. Display Luggage\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        int id;
        switch (choice) {
        case '1':
            if (luggageCount >= MAX_LUGGAGE) {
                cout << "Maximum luggage limit reached\n";
                break;
            }
            cout << "Enter Luggage ID: ";
            cin >> luggageList[luggageCount].id;
            cout << "Enter Weight: ";
            cin >> luggageList[luggageCount].weight;
            cout << "Enter Owner Name: ";
            cin >> luggageList[luggageCount].owner;

            luggageCount++;
            break;

        case '2':
            cout << "Enter Luggage ID to remove: ";
            cin >> id;
            for (int i = 0; i < luggageCount; i++) {
                if (luggageList[i].id == id) {
                    for (int j = i; j < luggageCount - 1; j++) {
                        luggageList[j] = luggageList[j + 1];
                    }
                    luggageCount--;
                    cout << "Luggage removed\n";
                    break;
                }
            }
            break;

        case '3':
            cout << "\nLuggage List:\n";
            for (int i = 0; i < luggageCount; i++) {
                cout << "ID: " << luggageList[i].id
                    << " Weight: " << luggageList[i].weight
                    << " Owner: " << luggageList[i].owner << "\n";
            }
            break;

        case '4':
            cout << "Exiting luggage management\n";
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != '4');
}

void checkin() {
    char name[MAX_NAME];
    int flightId;

    cout << "\n=== Check-in ===\n";
    cout << "Passenger Name: ";
    cin >> name;
    cout << "Flight ID: ";
    cin >> flightId;

    // Verify flight exists
    bool flightFound = false;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightId) {
            flightFound = true;
            break;
        }
    }

    if (!flightFound) {
        cout << "Flight not found\n";
        return;
    }

    // Save check-in record
    ofstream file("checkins.txt", ios::app);
    if (file) {
        file << name << " " << flightId << "\n";
        file.close();
        cout << "Check-in successful\n";
    }
    else {
        cout << "Error processing check-in\n";
    }
}

void boarding() {
    int flightId;
    cout << "\n=== Boarding ===\n";
    cout << "Enter Flight ID: ";
    cin >> flightId;

    // Check if flight exists
    bool flightFound = false;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightId) {
            flightFound = true;
            break;
        }
    }

    if (!flightFound) {
        cout << "Flight not found\n";
        return;
    }

    // Display checked-in passengers for this flight
    ifstream file("checkins.txt");
    char name[MAX_NAME];
    int fid;

    cout << "\nBoarding List:\n";
    while (file >> name >> fid) {
        if (fid == flightId) {
            cout << "Passenger: " << name << "\n";
        }
    }
    file.close();
}


int admin() {
    char choice;
    do {
        cout << "\n=== Admin Menu ===\n";
        cout << "1. Check Passenger Details\n";
        cout << "2. Check Tickets Bought\n";
        cout << "3. Add Flights\n";
        cout << "4. Delete Flights\n";
        cout << "5. Main Menu\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': total_passengers(); break;
        case '2': tickets_bought(); break;
        case '3': add_flights(); break;
        case '4': delete_flights(); break;
        case '5': return main_menu();
        case '6': return 0;
        default: cout << "Invalid choice\n";
        }
    } while (choice != '6');
    return 0;
}

int staff() {
    char choice;
    do {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Luggage Management\n";
        cout << "2. Check-in\n";
        cout << "3. Boarding\n";
        cout << "4. Main Menu\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': luggage_management(); break;
        case '2': checkin(); break;
        case '3': boarding(); break;
        case '4': return main_menu();
        case '5': return 0;
        default: cout << "Invalid choice\n";
        }
    } while (choice != '5');
    return 0;
}