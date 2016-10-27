#include "stdafx.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

/*PROBLEM: given one single hotel room to rent and a day in a month -> create a function to check whether we can book the hotel room.
INITIAL ASSUMTION: we somehow have an existing methodic of dealing with resetting booking dates for new month? (i.e New textfile being used.)
*/

/*DATA STORAGE ASSUMPTIONS / CONSTAINTS:
*Can be as simple as a textfile or cfg file read/write method -> security flaws...
*Improved by using a database or similar alternative.
*Internal storage of data is unreliable as it assumes an indefinite running-time for the program -> prone to human/technological error...
*/

//Define booking object:
std::map<int, int> inDates;
std::map<int, int> outDates;

//Read  booking data file method:
void bookClient(string configname, int checkIn, int checkOut)
{
	std::ifstream cFile(configname);
	int potIn = 0;						//PotentialDate In												
	int potOut = 0;						//PotentialDate Out
	string lastCust = "";				//Inbetween this date
	string nextCust = "";				//And this date
	bool canBook = 0;					//Can the client book?
	if (cFile.is_open())
	{
		std::string line;
		cout << "Current Bookings On-File:" << endl;
		while (getline(cFile, line)) {
			line.erase(remove_if(line.begin(), line.end(), isspace),				//Remove Spaces
				line.end());
			if (line[0] == '#' || line.empty())
				continue;
			int delimiterPos = line.find("=");
			int delimiter2Pos = line.find("-");
			int delimiter3Pos = line.find("_");
			string name = line.substr(0, delimiterPos);									//Client Name
			string dateIn = line.substr(delimiterPos + 1, 1);							//Booking Checkin Day
			string dateOut = line.substr(delimiter2Pos + 1, 1);							//Booking Checkout Day

			//Debug print values to check correctness.
			cout << name << " " << dateIn << " " << dateOut << endl;


			//Case4: if potential dates exist, and potOut <= next In date - > OK to book.
			if ((potIn <= stoi(dateIn) && potOut <= stoi(dateOut)) && potIn != 0 && potOut != 0) {
				canBook = 1;
				nextCust = name;
			}
			//Case2: checkin date provided is inbetween checkin and checkout -> NO to book.
			if (checkIn <= stoi(dateOut) && checkIn >= stoi(dateIn)) {
				canBook = false;
			}
			//Case3: checkin date is greater or equal to checkin and checkout date -> POTENTIAL booking.
			if (checkIn >= stoi(dateIn) && checkIn >= stoi(dateOut)) {
				lastCust = name;
				potIn = checkIn;
				potOut = checkOut;
			}
			//else would indicate a missed cornercase (TODO!)
		}
		if (canBook != 0) {
			cout << " " << endl;
			cout << "Check-in Date: " << checkIn << " Check-out Date: " << checkOut << " are available!" << endl;
			cout << "In-between : " << lastCust << " and " << nextCust << endl;
		}
		cFile.close();
	}
	//Failed to read file -> throw an error
	else std::cout << "Unable to open config file." << '\n';
	return;
}


//Running implementation of the above methods
int main() {
	//Read current booking file
	bookClient("bookings.txt", 5, 8);
	Sleep(500000);

}