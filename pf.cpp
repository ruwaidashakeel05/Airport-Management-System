//Libraries//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Constants for maximum limits in the system
const int MAX_FLIGHTS = 100;
const int MAX_LUGGAGE = 100;
const int MAX_USERS = 100;
const int MAX_NAME = 20;

//Structure to store flight details
struct Flight {
    int flightID;
    char destination[20];
    char departure[10];
    char arrival[10];
    float price;
};

// Global variables
Flight flights[MAX_FLIGHTS];
int flightCount = 0;

// Function prototypes
int main_menu();
int sub_menu();

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
void add_luggage();
void delete_luggage();
void display_luggage();
void checkin();
void boarding();


//Functions to validate other functions
void stringCopy(char* destination, const char* src);
bool stringCompare(const char* str1, const char* str2);
bool validate_flight_id(int flightID);
void write_flights_to_file();
void read_flights_from_file();

// Helper function to copy strings safely
void stringCopy(char* destination, const char* src) { //stringCopy as src
    int i = 0;
    while (src[i] != '\0' && i < MAX_NAME - 1) {
        destination[i] = src[i];
        i++;
    }
    destination[i] = '\0'; //Use to prevent memory overflow
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

//Validate flight Id
bool validate_flight_id(int flightID) {
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightID) {
            return true; // ID already exists
        }
    }
    return false; // ID is unique
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


/*------------------------------------------------------------------MAIN FUNCTION------------------------------------------------*/
int main() {
    cout << "\n\tAirport Reservation System\n";
    cout << setfill('-') << setw(43) << "-" << endl;
    return main_menu();
}

/*------------------------------------------------------------------MAIN MENU------------------------------------------------*/
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

/*------------------------------------------------------------------SUB MENU------------------------------------------------*/
int sub_menu() {
    system("cls"); // Clears the console

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
        case '4': return 0; // Exit
        default: cout << "Invalid choice\n";
        }
    } while (role != '4');

    return 0;
}

/*------------------------------------------------------------------LOGIN------------------------------------------------*/
string login() {
    system("cls"); // Clears the console

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
        sub_menu();
    }
    else {
        cout << "Invalid credentials\n";
    }
    return username;
}

/*------------------------------------------------------------------SIGNUP------------------------------------------------*/
string signup() {
    system("cls"); // Clears the console

    char username[MAX_NAME];
    char password[MAX_NAME];

    cout << "\n=== Signup ===\n";
    cout << "Choose username (without using space): ";
    cin >> username;
    cout << "Choose password (without using space): ";
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

/*------------------------------------------------------------------CUSTOMER------------------------------------------------*/
int customer() {
    system("cls"); // Clears the console

    string loggedInUsername;

    // Simulate a login system (you can replace this with your actual login logic)
    cout << "Enter your username (without using space): ";
    cin >> loggedInUsername;

    char choice;
    do {
        cout << "\n=== Customer Menu ===\n";
        cout << "1. Seat Reservation\n";
        cout << "2. View Ticket\n";
        cout << "3. Flight Details\n";
        cout << "4. Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            seat_reservation(loggedInUsername);
            break;
        case '2':
            user_ticket(loggedInUsername);
            break;
        case '3':
            flight_details();
            break;
        case '4':
            return sub_menu();
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != '5');
    return 0;
}

/*------------------------------------------------------------------ADMIN------------------------------------------------*/
int admin() {
    system("cls"); // Clears the console

    char choice;
    do {
        cout << "\n=== Admin Menu ===\n";
        cout << "1. Check Passenger Details\n";
        cout << "2. Check Tickets Bought\n";
        cout << "3. Add Flights\n";
        cout << "4. Delete Flights\n";
        cout << "5. Display Flights\n";
        cout << "6. Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': total_passengers(); break;
        case '2': tickets_bought(); break;
        case '3': add_flights(); break;
        case '4': delete_flights(); break;
        case '5': flight_details(); break;
        case '6': return sub_menu();
        default: cout << "Invalid choice\n";
        }
    } while (choice != '6');
    return 0;
}

/*------------------------------------------------------------------STAFF------------------------------------------------*/
int staff() {
    system("cls"); // Clears the console

    char choice;
    do {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Luggage Management\n";
        cout << "2. Check-in\n";
        cout << "3. Boarding\n";
        cout << "4. Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': luggage_management(); break;
        case '2': checkin(); break;
        case '3': boarding(); break;
        case '4': return sub_menu();
        default: cout << "Invalid choice\n";
        }
    } while (choice != '5');
    return 0;
}

/*------------------------------------------------------------------SEAT RESERVATION------------------------------------------------*/
void seat_reservation(const string& username) {
    system("cls"); // Clear the console

    cout << "\n=== Seat Reservation ===\n";
    cout << "Continue to: " << endl;
    cout << "1. Economy Class" << endl;
    cout << "2. Business Class" << endl;
    cout << "3. Exit" << endl;

    char option = 0;
    cout << "Enter choice: ";
    cin >> option;

    if (option != '1' && option != '2' && option != '3') {
        cout << "Invalid Option" << endl;
        return;
    }

    if (option == '3') {
        cout << "\nExiting Successfully" << endl;
        customer(); // Assuming you have a `customer()` function to return to the main menu
        return;
    }

    flight_details(); // Assuming this function displays available flights

    int flightChoice;
    cout << "\nEnter flight ID to reserve: ";
    cin >> flightChoice;

    // Open flights file to verify flight exists
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
            if (option == '2') {
                price *= 2; // Double price for business class
            }
            break;
        }
    }
    flightFile.close();

    if (!found) {
        cout << "Invalid flight ID\n";
        return;
    }

    // Generate unique ticket ID
    static int ticketID = 1; // Persistent across reservations
    ifstream ticketFile("reservations.txt");
    string line;
    while (getline(ticketFile, line)) {
        if (line.find("Ticket ID: ") != string::npos) {
            ticketID++; // Increment ticket ID for every existing reservation
        }
    }
    ticketFile.close();

    // Assign a unique seat number
    int seatNumber = 0;
    ifstream reservationFile("reservations.txt");
    while (getline(reservationFile, line)) {
        if (line.find("Seat Number: ") != string::npos) {
            int lastSeat = stoi(line.substr(line.find(":") + 2));
            if (option == '1' && lastSeat < 100) { // Economy Class range: 1-100
                seatNumber = lastSeat + 1;
            }
            else if (option == '2' && lastSeat < 150) { // Business Class range: 101-150
                seatNumber = lastSeat + 1;
            }
        }
    }
    reservationFile.close();

    if (seatNumber == 0) {
        // Default starting seat number if no seats were found in the file
        seatNumber = (option == '1') ? 1 : 101;
    }

    // Passenger Details
    char name[20], phone[12], email_address[20];
    cin.ignore(); // Clear input buffer

    cout << "Enter passenger name: ";
    cin.getline(name, 20);

    // Phone number validation (Your Original Logic)
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
    } while (!valid_phone);

    // Email validation (Your Original Logic)
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
            << "Ticket ID: " << ticketID << "\n"
            << "Passenger: " << name << "\n"
            << "Phone: " << phone << "\n"
            << "Email: " << email_address << "@gmail.com\n"
            << "Flight ID: " << id << "\n"
            << "Flight Details: " << flightInfo << "\n"
            << "Price: $" << fixed << setprecision(2) << price << "\n"
            << "Seat Number: " << seatNumber << "\n"
            << "---------------------------------\n";
        file.close();
        cout << "Reservation successful!\n";
    }
    else {
        cout << "Error making reservation\n";
    }
}

/*------------------------------------------------------------------USER TICKET------------------------------------------------*/
void user_ticket(const string& username) {
    system("cls"); // Clears the console

    cout << "\n=== Your Tickets ===\n";

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open reservations file.\n";
        return;
    }

    string line;
    bool ticketFound = false;

    while (getline(file, line)) {
        // Check if the line contains the username
        if (line.find("Username: " + username) != string::npos) {
            ticketFound = true;

            // Display the ticket details
            cout << "\nTicket Details:\n";
            cout << "---------------------------------\n";
            cout << line << "\n"; // Display the username line

            // Read and display all ticket details until the separator line
            while (getline(file, line) && line.find("---------------------------------") == string::npos) {
                cout << line << "\n";
            }
        }
    }

    file.close();

    if (!ticketFound) {
        cout << "No tickets found for username: " << username << "\n";
    }
}

/*------------------------------------------------------------------FLIGHT DETAILS------------------------------------------------*/
// Function to display flight details
void flight_details() {
    system("cls"); // Clears the console

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

/*------------------------------------------------------------------ADD FLIGHTS------------------------------------------------*/
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

/*------------------------------------------------------------------DELETE FLIGHTS------------------------------------------------*/
void delete_flights() {
    system("cls"); // Clears the console

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

/*------------------------------------------------------------------TOTAL PASSENGERS------------------------------------------------*/
void total_passengers() {
    system("cls"); // Clears the console

    cout << "\n=== Total Passengers ===\n";

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "No passenger records found\n";
        return;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        cout << line << "\n";
    }

    file.close();
}

/*------------------------------------------------------------------TICKETS BOUGHT------------------------------------------------*/
void tickets_bought() {
    system("cls"); // Clears the console

    cout << "\n=== Tickets Bought ===\n";

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "No ticket records found\n";
        return;
    }

    string line;

    int totalTicketCount = 0;
    while (getline(file, line)) {
        if (line.find("Username: ") != string::npos) {
            totalTicketCount++;
        }
    }
    cout << "Total tickets bought by all users: " << totalTicketCount << "\n";
    cout << "-----------------------------\n";

    file.close();
}

/*------------------------------------------------------------------CHECKIN------------------------------------------------*/
void checkin() {
    system("cls"); // Clears the console

    cout << "\n=== Check-in ===\n";

    int ticketID, flightID;
    cout << "Enter Ticket ID: ";
    cin >> ticketID;
    cout << "Enter Flight ID: ";
    cin >> flightID;

    ifstream file("reservations.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open reservations file.\n";
        return;
    }

    string line;
    bool ticketFound = false, flightMatched = false;
    string passengerName;

    // Process the reservations file
    while (getline(file, line)) {
        // Extract Ticket ID
        if (line.find("Ticket ID: ") != string::npos) {
            int extractedTicketID = 0;
            for (int i = line.find(":") + 2; i < line.size(); i++) {
                if (isdigit(line[i])) {
                    extractedTicketID = extractedTicketID * 10 + (line[i] - '0');
                }
                else {
                    break;
                }
            }
            if (extractedTicketID == ticketID) {
                ticketFound = true;
            }
        }

        // Extract Flight ID
        if (ticketFound && line.find("Flight ID: ") != string::npos) {
            int extractedFlightID = 0;
            for (int i = line.find(":") + 2; i < line.size(); i++) {
                if (isdigit(line[i])) {
                    extractedFlightID = extractedFlightID * 10 + (line[i] - '0');
                }
                else {
                    break;
                }
            }
            if (extractedFlightID == flightID) {
                flightMatched = true;
            }
        }

        // Extract Passenger Name
        if (ticketFound && line.find("Passenger: ") != string::npos) {
            passengerName = "";
            int start = line.find(":") + 2;
            for (int i = start; i < line.size(); i++) {
                passengerName += line[i];
            }
        }

        // Stop processing if both ticket and flight match
        if (ticketFound && flightMatched) {
            break;
        }
    }
    file.close();

    if (ticketFound && flightMatched) {
        // Save check-in details
        ofstream outFile("checkins.txt", ios::app);
        if (!outFile.is_open()) {
            cout << "Error: Could not open checkins.txt for writing.\n";
            return;
        }

        outFile << "Ticket ID: " << ticketID << "\n";
        outFile << "Passenger Name: " << passengerName << "\n";
        outFile << "Flight ID: " << flightID << "\n";
        outFile << "-----------------------------\n";
        outFile.close();

        cout << "Check-in successful!\n";
    }
    else if (!ticketFound) {
        cout << "Error: Ticket ID not found.\n";
    }
    else if (ticketFound && !flightMatched) {
        cout << "Error: Flight ID does not match the ticket.\n";
    }
}

/*------------------------------------------------------------------BOARDING------------------------------------------------*/
void boarding() {
    system("cls"); // Clears the console

    cout << "\n=== Boarding ===\n";

    int ticketID;
    cout << "Enter Ticket ID: ";
    cin >> ticketID;

    // Open the checkins.txt file
    ifstream checkinFile("checkins.txt");
    if (!checkinFile.is_open()) {
        cout << "Error: Could not open check-ins file.\n";
        return;
    }

    bool isTicketFound = false;
    string checkinLine;
    string passengerName, flightID, luggageID;

    // Loop through the checkins.txt file to find the ticket
    while (getline(checkinFile, checkinLine)) {
        int checkedInTicketID = 0;

        // Check if the line contains the Ticket ID
        if (checkinLine.find("Ticket ID: ") != string::npos) {
            int ticketPos = 11; // Skip past "Ticket ID: "
            while (ticketPos < checkinLine.length() && isdigit(checkinLine[ticketPos])) {
                checkedInTicketID = checkedInTicketID * 10 + (checkinLine[ticketPos] - '0');
                ticketPos++;
            }
        }

        // If the ticket ID matches, extract the details
        if (checkedInTicketID == ticketID) {
            isTicketFound = true;

            // Extract Passenger Name
            if (getline(checkinFile, checkinLine) && checkinLine.find("Passenger Name: ") != string::npos) {
                int namePos = 16; // Skip past "Passenger Name: "
                passengerName = "";
                while (namePos < checkinLine.length()) {
                    passengerName += checkinLine[namePos];
                    namePos++;
                }
            }

            // Extract Flight ID
            if (getline(checkinFile, checkinLine) && checkinLine.find("Flight ID: ") != string::npos) {
                int flightPos = 11; // Skip past "Flight ID: "
                flightID = "";
                while (flightPos < checkinLine.length()) {
                    flightID += checkinLine[flightPos];
                    flightPos++;
                }
            }

            // Display the passenger details
            cout << "\nPassenger Details:\n";
            cout << "Ticket ID: " << ticketID << endl;
            cout << "Passenger Name: " << passengerName << endl;
            cout << "Flight ID: " << flightID << endl;
            cout << "Status: Boarded" << endl;
            break;
        }
    }

    checkinFile.close();

    if (!isTicketFound) {
        cout << "Passenger is not checkin\n";
    }
}

/*------------------------------------------------------------------LUGGAGE MANAGEMENT------------------------------------------------*/
void luggage_management() {
    system("cls"); // Clears the console

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
        case '1': add_luggage();
            break;

        case '2': delete_luggage();
            break;

        case '3': display_luggage();
            break;

        case '4':
            cout << "Exiting luggage management\n";
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != '4');
}

/*------------------------------------------------------------------ADD LUGGAGE------------------------------------------------*/
void add_luggage() {
    system("cls"); // Clears the console

    cout << "\n=== Add Luggage ===\n";

    int ticketID;
    cout << "Enter Ticket ID: ";
    cin >> ticketID;

    // Open checkins.txt to verify if the passenger has checked in
    ifstream checkinFile("checkins.txt");
    if (!checkinFile.is_open()) {
        cout << "Error: Could not open check-ins file.\n";
        return;
    }

    bool isTicketFound = false;
    string checkinLine;
    string passengerName;

    // Loop through the checkins.txt file to find the ticket
    while (getline(checkinFile, checkinLine)) {
        int checkedInTicketID = 0;

        // Check if the line contains the Ticket ID
        if (checkinLine.find("Ticket ID: ") != string::npos) {
            int ticketPos = 11; // Skip past "Ticket ID: "
            while (ticketPos < checkinLine.length() && isdigit(checkinLine[ticketPos])) {
                checkedInTicketID = checkedInTicketID * 10 + (checkinLine[ticketPos] - '0');
                ticketPos++;
            }
        }

        // If the ticket ID matches, get the Passenger Name
        if (checkedInTicketID == ticketID) {
            isTicketFound = true;

            // Read the Passenger Name from the next line
            getline(checkinFile, checkinLine);
            if (checkinLine.find("Passenger Name: ") != string::npos) {
                passengerName = checkinLine.substr(17);  // Extract the name
            }
            break;  // Exit loop after finding the ticket
        }
    }
    checkinFile.close();

    if (!isTicketFound) {
        cout << "Error: Ticket ID not found or passenger has not checked in.\n";
        return;
    }

    // Ask for number of luggage pieces
    int numberOfLuggage;
    cout << "Enter the number of luggage pieces: ";
    cin >> numberOfLuggage;

    // Ask for details for each piece of luggage
    string luggageDescription, luggageType;
    double luggageWeight;

    // Generate the next Luggage ID by checking luggage.txt
    int luggageID = 1; // Default luggage ID if no previous records are found
    ifstream luggageFile("luggage.txt");
    if (luggageFile.is_open()) {
        string luggageLine;
        while (getline(luggageFile, luggageLine)) {
            if (luggageLine.find("Luggage ID: ") != string::npos) {
                int lastLuggageID = 0;
                int pos = 12; // Skip past "Luggage ID: "
                while (pos < luggageLine.length() && isdigit(luggageLine[pos])) {
                    lastLuggageID = lastLuggageID * 10 + (luggageLine[pos] - '0');
                    pos++;
                }
                luggageID = lastLuggageID + 1; // Increment the Luggage ID
            }
        }
        luggageFile.close();
    }

    // Collect and store luggage details
    ofstream luggageFileOut("luggage.txt", ios::app);
    if (luggageFileOut.is_open()) {
        for (int i = 1; i <= numberOfLuggage; i++) {
            // Ask user for each luggage type and weight
            cout << "Enter type of luggage " << i << ": ";
            cin.ignore();  // To clear the buffer before getline
            getline(cin, luggageType);
            cout << "Enter weight of luggage " << i << " (kg): ";
            cin >> luggageWeight;
            cout << "Assigned Luggage ID: " << luggageID << endl << endl;

            // Write the luggage details into luggage.txt
            luggageFileOut << "Luggage ID: " << luggageID << "\n";
            luggageFileOut << "Ticket ID: " << ticketID << "\n";
            luggageFileOut << "Passenger Name: " << passengerName << "\n";
            luggageFileOut << "Luggage Type: " << luggageType << "\n";
            luggageFileOut << "Luggage Weight: " << luggageWeight << " kg\n";
            luggageFileOut << "-----------------------------\n";

            luggageID++; // Increment the Luggage ID for the next luggage
        }
        luggageFileOut.close();
        cout << "Luggage added successfully!\n";
    }
    else {
        cout << "Error: Could not open luggage file.\n";
    }
}

/*------------------------------------------------------------------DELETE LUGGAGE------------------------------------------------*/
void delete_luggage() {
    system("cls"); // Clears the console

    cout << "\n=== Delete Luggage ===\n";

    int ticketID, luggageID;
    cout << "Enter Ticket ID: ";
    cin >> ticketID;
    cout << "Enter Luggage ID to delete: ";
    cin >> luggageID;

    // Open the luggage file and create a temporary file to store updated data
    ifstream luggageFile("luggage.txt");
    ofstream tempFile("temp_luggage.txt");

    if (!luggageFile.is_open() || !tempFile.is_open()) {
        cout << "Error: Could not open luggage files.\n";
        return;
    }

    string line;
    bool luggageDeleted = false;

    // Copy the data except the luggage we want to delete
    while (getline(luggageFile, line)) {
        if (line.find("Luggage ID: ") != string::npos) {
            int currentLuggageID = 0;
            int pos = 12; // Skip past "Luggage ID: "
            while (pos < line.length() && isdigit(line[pos])) {
                currentLuggageID = currentLuggageID * 10 + (line[pos] - '0');
                pos++;
            }

            // If we find the matching luggage ID, skip writing that line
            if (currentLuggageID == luggageID) {
                luggageDeleted = true;
                // Skip lines for this luggage entry
                for (int i = 0; i < 4; i++) {
                    getline(luggageFile, line);
                }
            }
            else {
                tempFile << line << endl;
            }
        }
        else {
            tempFile << line << endl;
        }
    }

    luggageFile.close();
    tempFile.close();

    if (luggageDeleted) {
        // Replace the original luggage file with the updated one
        remove("luggage.txt");
        rename("temp_luggage.txt", "luggage.txt");
        cout << "Luggage deleted successfully!\n";
    }
    else {
        cout << "Error: Luggage not found.\n";
    }
}

/*------------------------------------------------------------------DISPLAY LUGGAGE------------------------------------------------*/
void display_luggage() {
    system("cls"); // Clears the console

    cout << "\n=== Display Luggage ===\n";

    int ticketID;
    cout << "Enter Ticket ID to display luggage (0 to display all): ";
    cin >> ticketID;

    ifstream luggageFile("luggage.txt");
    if (!luggageFile.is_open()) {
        cout << "Error: Could not open luggage file.\n";
        return;
    }

    string line;
    bool luggageFound = false;

    // Loop through the luggage file and display the luggage for the specified ticket ID
    while (getline(luggageFile, line)) {
        if (line.find("Luggage ID: ") != string::npos) {
            string luggageID = line; // Store the Luggage ID line
            getline(luggageFile, line); // Read Ticket ID line
            int currentTicketID = 0;
            int pos = 11; // Skip past "Ticket ID: "
            while (pos < line.length() && isdigit(line[pos])) {
                currentTicketID = currentTicketID * 10 + (line[pos] - '0');
                pos++;
            }

            // If ticketID is 0 (display all) or the line matches the entered ticketID
            if (ticketID == 0 || currentTicketID == ticketID) {
                luggageFound = true;

                // Print the entire luggage record, including Luggage ID
                cout << luggageID << endl;
                cout << line << endl; // Ticket ID
                for (int i = 0; i < 3; i++) {
                    getline(luggageFile, line);
                    cout << line << endl;
                }
                cout << "-----------------------------\n";
            }
        }
    }

    luggageFile.close();

    if (!luggageFound) {
        cout << "No luggage found for the given Ticket ID.\n";
    }
}
