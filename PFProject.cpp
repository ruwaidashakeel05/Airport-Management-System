#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/* Function Prototype */
void seat_reservation();
void user_ticket();
void flight_details();
void login_signup();

/*===================== Phone Number Validation =====================*/

int main() {
	char choice = '0'; //initialization

	/* Menu */
	cout << endl;
	cout << "\tAirport Reservation System"<<endl<<endl;
	cout << setfill('-') << setw(43) << "-" << endl;
    cout << " Press 1 for \"Login/Signup\"" << endl;
	cout << " Press 2 for \"Seat Reservation\"" << endl;
	cout << " Press 3 for \"User Ticket\"" << endl;
	cout << " Press 4 for \"Flight Details\"" << endl;
	cout << " Press 5 for \"Exit\"" << endl;
	cout << "\n Enter number: ";
	cin >> choice;

	switch (choice) {
    case '1': login_signup();
        break;
	case '2': seat_reservation();
		break;
	case '3': user_ticket();
		break;
	case '4': flight_details();
		break;
	case '5': cout << " Exit Successfully";
		return 0;
	default: cout << " Invalid Option";
		return 1;
	}
	return 0;
}

void seat_reservation() {
    // Flight details arrays
    const int num_flights = 5;
    string flight_numbers[num_flights] = { "PK101", "PK102", "PK103", "PK104", "PK105" };
    string destinations[num_flights] = { "New York", "London", "Dubai", "Toronto", "Singapore" };
    string departures[num_flights] = { "10:00 AM", "01:00 PM", "06:00 PM", "08:00 AM", "09:00 PM" };
    string arrivals[num_flights] = { "02:00 PM", "05:00 PM", "10:00 PM", "01:00 PM", "03:00 AM" };
    float prices[num_flights] = { 500, 450, 300, 550, 600 };

    int option;
    cout << "\n--- Seat Reservation ---\n";
    cout << " Press 1 for \"Economy Class\"\n";
    cout << " Press 2 for \"Business Class\"\n";
    cout << " Enter option: ";
    cin >> option;

    // Determine class type using a ternary operator
    switch (option) {
    case 1:cout << "-----------Economy Class-----------" << endl;
        // Display available flights
        cout << "\nAvailable Flights:\n";
        for (int i = 0; i < num_flights; i++) {
            cout << i + 1 << ". Flight No: " << flight_numbers[i] << ", Destination: " << destinations[i]
                << ", Departure: " << departures[i] << ", Arrival: " << arrivals[i]
                << ", Price: $" << prices[i] << endl;
        }

        // Select a flight
        int flight_choice;
        do {
            cout << "\n Enter the number of the flight you want to reserve: ";
            cin >> flight_choice;
            if (flight_choice < 1 || flight_choice > num_flights) {
                cout << " Invalid choice. Please try again.\n";
            }
        } while (flight_choice < 1 || flight_choice > num_flights);

        // Collect user details
        char first_name[20], last_name[20];
        string email_address;
        long long phone_number[11];

        cout << " First Name: ";
        cin.ignore();
        cin.getline(first_name, 20);
        cout << " Last Name: ";
        cin.ignore();
        cin.getline(last_name, 20);

        // Phone number validation
        int count; //Variable for length of phone number
        cout << " Phone number: ";
        for (count = 0; count < 11; count++)
        {
            cout << "the count of the index is :" << endl;
            cin >> phone_number[count];
        }
        do 
        {
            if (phone_number[0] != 0 || phone_number[1] != 3) 
            {
                cout << "\n Your number should start with 03." << endl;
            }
        } while (count != 11 || phone_number[0] || phone_number[1] == 1);

        // Email validation
        do {
            cout << " Email Address(only write username without @gmail.com): ";
            cin >> email_address;
            if (email_address == "@") {
                cout << "Invalid";
            }
        } while (email_address == "@");

        // Save reservation details to a file
        ofstream file("reservations.txt", ios::app);
        if (file) {
            //file << " Class: " << class_type << endl;
            file << " Name: " << first_name << " " << last_name << endl;
            file << " Phone: " << phone_number << endl;
            file << " Email: " << email_address << endl;
            file << " Flight No: " << flight_numbers[flight_choice - 1] << endl;
            file << " Destination: " << destinations[flight_choice - 1] << endl;
            file << " Departure: " << departures[flight_choice - 1] << endl;
            file << " Arrival: " << arrivals[flight_choice - 1] << endl;
            file << " Price: $" << prices[flight_choice - 1] << endl;
            file << "---------------------------------\n";
            file.close();
            cout << "\n Reservation successful! Your ticket has been saved.\n";
        }
        else {
            cout << " Error: Unable to save reservation.\n";
        }
    }
}


        void user_ticket()
{
	cout << "\n User Ticket" << endl;
    ifstream file("reservations.txt"); // Open the file in read mode
    if (!file) {
        cout << " Error: Could not open the file 'reservations.txt'. Make sure reservations exist!" << endl;
        return;
    }

    string line;
    cout << "\n==== User Ticket Details ====\n";

    // Read and display the file contents
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close(); // Close the file

}

void flight_details() {
    cout << "\n Flight Details" << endl << endl;
    cout << "\n Available Flights\n";
    cout << left << setw(15) << " Flight No" << setw(20) << " Destination" << setw(15) << " Departure" << setw(15) << " Arrival" << setw(10) << " Price (USD)" << endl << endl;
// Flight details
    cout << left << setw(15) << " PK101" << setw(20) << " New York" << setw(15) << " 10:00 AM" << setw(15) << " 02:00 PM" << setw(10) << " $500" << endl;
    cout << left << setw(15) << " PK102" << setw(20) << " London" << setw(15) << " 01:00 PM" << setw(15) << " 05:00 PM" << setw(10) << " $450" << endl;
    cout << left << setw(15) << " PK103" << setw(20) << " Dubai" << setw(15) << " 06:00 PM" << setw(15) << " 10:00 PM" << setw(10) << " $300" << endl;
    cout << left << setw(15) << " PK104" << setw(20) << " Toronto" << setw(15) << " 08:00 AM" << setw(15) << " 01:00 PM" << setw(10) << " $550" << endl;
    cout << left << setw(15) << " PK105" << setw(20) << " Singapore" << setw(15) << " 09:00 PM" << setw(15) << " 03:00 AM" << setw(10) << " $600" << endl;
    cout << "\n To reserve a seat, please return to the main menu and select 'Seat Reservation' (Press 0).\n";

    int exit_choice;
        
    do 
    {
      cin >> exit_choice;
        if (exit_choice == 0) {
             main();
        }
        else {
             cout << " You entered wrong key";
        }
    } while (exit_choice != 0);

}

void login_signup() {
	cout << "\n Login/Signup" << endl;
    int choice;
    cout << " 1. Login\n";
    cout << " 2. Sign Up\n";
    cout << " Enter your choice: ";
    cin >> choice;

    string username, password;

    if (choice == 1) {
        // Login
        cout << "\n Enter your username: ";
        cin >> username;
        cout << " Enter your password: ";
        cin >> password;

        // Check credentials from the file
        ifstream file("users.txt");
        if (!file) {
            cout << " Error: Could not open user file. No users registered yet.\n";
            return;
        }

        string stored_username, stored_password;
        bool login_successful = false;

        while (file >> stored_username >> stored_password) {
            if (username == stored_username && password == stored_password) {
                login_successful = true;
                break;
            }
        }

        file.close();

        if (login_successful) {
            cout << "\n Login successful! Welcome, " << username << "!\n";
        }
        else {
            cout << "\n Either the provided password or username is incorrect as its not being found in the database.\n";
        }

    }
    else if (choice == 2) {
        // Sign Up
        cout << "\n Choose a username: ";
        cin >> username;
        cout << " Choose a password: ";
        cin >> password;

        // Append credentials to the file
        ofstream file("users.txt", ios::app);
        if (!file) {
            cout << " Error: Could not open user file for writing.\n";
            return;
        }

        file << username << " " << password << endl;
        file.close();

        cout << "\n Sign up successful! You can now log in with your credentials.\n";
    }
    else {
        cout << "\n Invalid choice. Please try again.\n";
    }
    int exit_choice;
    cout << " Enter 0 to go to main menu.";
    cin >> exit_choice;
    do
    {
        if (exit_choice == 0) {
            main();
        }
        else {
            cout << " You entered wrong key";
        }
    } while (exit_choice != 0);
}