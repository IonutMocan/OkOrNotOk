/*    INFO

Enuntul problemei:
		In fiecare zi de luni, miercuri si vineri intre orele 9 dimineata si 22 seara, programul va afisa OK daca este executat. Dupa ora
	22 va afisa Not OK. Martea, daca luni a fost afisat OK de minim 10 ori, va afisa OK, in caz contrar va afisa Not OK. La fel si pentru
	miercuri-joi. Sambata si duminica va afisa OK indiferent de ora atata vreme cat zilele nu sunt pare, daca se ruleaza programul in zi 
	para, va afisa Not OK.


		Programul ARE cateva BUGURI, in primul rand necesita creat in directorul programului un fisier "Data.txt" care sa contina exact 7
	 randuri cu cate un 0 pe fiecare linie, nimic mai mult. Fiecare linie reprezinta o zi din saptaman 1 = luni, 2 = marti ... pana la
	 7 = duminica. Fiecare rand corespunzator zilei in care se executa programul va avea valoarea incrementata cu 1. Pe langa problema
	 necesitatii unui ".txt" cu acele valori in interior, acestea sunt incrementate la infinit.. Programul nu stie sa reseteze la finalul
	 fiecarei saptamani datele din fisier. Pe viitor o sa implementez niste solutii la aceste probleme. Codul este aproape integral comentat
	 in limba engleza, mai putin acest comment.

*/

#include <iostream> // Needed for cout/cin
#include <Windows.h> // Needed to retrieve date and time 
#include <string> // Needed for getline()  and stoi() methods
#include <fstream> // Needed for file input/output
#include <cstdlib> // Needed for exit() method
using namespace std; // Needed to acces methos from std namespace

bool checkPreviousDay(int day) // Method to check if previous day was accesed for 10 times or more
{
	ifstream inf("Data.txt");
	string DayShows; // variable needed to store every line value

	if (!inf) // Checking if file can be opened
	{
		cerr << "Couldn't open file for reading";
		exit(1); // If it cannot be opened show an error message
	}

	for (int i = 1; i < day; i++) // Reading every line untill we get to the day before "day" ( < day)
	{
		getline(inf, DayShows); // Storing that line value
	}



	if (stoi(DayShows) >= 10) // Check if previous day was accesed for 10 or more time
	{
		return true;
	}

	return false;
}

void updateData(int day)
{
	string newVal; // Variable to store the old text file value
	ifstream infile("Data.txt");
	ofstream offile("Text.txt");
	int lineNo = 1; // The starting line

	while (!infile.eof()) // While I did not reach the end of the file
	{
		getline(infile, newVal); // Get line value
		if (lineNo == day) // If we are at the line we want to update
		{
			offile << stoi(newVal) + 1 << endl; // Put in the new text file the replacing value
		}
		else
			offile << newVal << endl; // Else put the old one
		++lineNo; // Increment the line number
	}
	infile.close();
	offile.close();
	remove("Data.txt"); // Remove the old text file
	rename("Text.txt", "Data.txt"); // Renaming the new value like the old one
}


void main() {

	SYSTEMTIME time;

	GetLocalTime(&time); // Retrieving the data and time

	string message = "Not OK"; // Set the default message to show

	int hour = time.wHour; // Getting the current hour
	int day = time.wDay; // Getting the day of mounth
	int dayOfWeek = time.wDayOfWeek; // Getting the day of week

	// SOME TEST DATA PARAMETERS
	/*int hour = 10;
	int day = 20;
	int dayOfWeek = 6;*/

	updateData(dayOfWeek); // Update the "Data.txt" file that we executed the program today



	if (dayOfWeek == 2 || dayOfWeek == 4) // If today it's Tuesday (2) or Thurstday (4)
	{
		if (checkPreviousDay(dayOfWeek)) // Check if Monday (1) or Wednesday (3) the program was executed for 10 or more times
		{
			message = "OK"; // Change the default message to show
		}

	}


	if ((dayOfWeek == 1 || dayOfWeek == 3 || dayOfWeek == 5) && (hour >= 9 && hour <= 22)) // If today it's Monday ( 1 ) or Wednesday (3)
		// or Fraiday (5) AND the current hour it's between 9 AM  and 10 PM (22), inclusev
	{
		message = "OK"; // Change the default message

	}



	if ((dayOfWeek == 6 || dayOfWeek == 7) && (day % 2 != 0)) // If today is Saturday (6) or Sunday (7) AND it's not even day
	{
		message = "OK"; // Change the default message

	}



	cout << message << endl; // Show the corresponding message

}