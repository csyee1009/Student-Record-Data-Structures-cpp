#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	"List.h"
#include	"Student.h"
using namespace std;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Functions & global variable	

bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool InsertExamResult(const char*, List*);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, char*);
int menu();
void titleprint();
void printCentered(const string&);
bool resultinsert = false, studentinsert = false;



//////////////////////////////////////////////////
				//decoration

const int width = 170;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// int main()

int main() {

	List list1;
	List list2;
	char course[3];
	char deleteID[10] = "0";
	int source = 0;
	int year = 0, totalcredit = 0;
	bool repeat = true, repeatmenu = true;
	titleprint();
	cout << endl;
	printCentered("WELCOME TO STUDENT RECORD SYSTEM!");
	cout << endl;

	system("Pause");

	do {
		switch (menu()) {
		case 1:

			cout << "\n>> YOU HAD SELECTED THE <CREATE STUDENT LIST> FUNCTION" << endl;

			// Attempt to create the student list from file.
			if (!CreateStuList("student.txt", &list1)) {
				cout << "\nThe student list cannot be created!" << endl;
			}
			else {
				cout << "\nThe student list has been successfully created!" << endl << endl;
				studentinsert = true;
			}


			break;
		case 2:

			cout << "\n>> YOU HAD SELECTED THE <DELETE STUDENT RECORD> FUNCTION" << endl;

			// Prompt user to input student ID for deletion.
			repeat = true;
			do {
				cout << "Enter the student ID for deletion (E-exit) >> ";
				cin >> deleteID;
				cin.clear();
				cin.ignore(1000, '\n');

				// Check if student list is empty.
				if (list1.empty()) {
					cout << "\nThe student list is empty! Please create a student list before any deletion!!!" << endl;
					repeat = false;
				}

				// Check if user wants to exit.
				else if (strcmp(deleteID, "E") == 0 || strcmp(deleteID, "e") == 0) {
					cout << "\nYou choose to quit this menu" << endl;
					repeat = false;
				}

				// Attempt to delete the student record.
				else if (DeleteStudent(&list1, deleteID)) {
					cout << "\nThe student with ID: """ << deleteID << """ has been deleted from the list." << endl;
					repeat = false;
				}
			} while (repeat);


			break;
		case 3:

			cout << "\n>> YOU HAD SELECTED THE <PRINT LIST> FUNCTION" << endl;

			// Print student list options.
			cout << "\nPRINT STUDENT LIST" << endl;
			cout << "\nSources" << endl;
			cout << "1. Display to screen" << endl;
			cout << "2. Print it to file" << endl;

			// Prompt user for output source.
			do {
				cout << "Enter the source >>";
				cin >> source;

				// Input validation.
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nInvalid input! Please enter only 1 or 2." << endl;
					continue;
				}

				// Display appropriate message based on missing data.
				else if (source == 1 || source == 2) {
					if (list1.empty()) {
						cout << "\nThe list is empty! Please create a student list before any printing!!!" << endl;
					}
					else if (!PrintList(list1, source)) {
						cout << "\nThe student list cannot be printed!" << endl;
					}
				}
				else {
					cout << "\nInvalid input! Please enter only 1 or 2." << endl;
					continue;
				}
			} while (source < 1 || source > 2);


			break;
		case 4:

			cout << "\n>> YOU HAD SELECTED THE <INSERT EXAM RESULT> FUNCTION" << endl;

			// Insert exam results from file.
			cout << "\nINSERT EXAM RESULT" << endl;

			if (list1.empty()) {
				cout << "\nThe student list is empty! Please create a student list before any deletion!!!" << endl;
			}
			else if (InsertExamResult("exam.txt", &list1)) {
				cout << "\nThe exam results have been successfullly inserted!" << endl;
				resultinsert = true;
			}


			break;
		case 5:

			cout << "\n>> YOU HAD SELECTED THE <PRINT STATISTIC> FUNCTION" << endl;

			// Print exam statistics.
			cout << "\nPRINT STATISTIC" << endl;
			if (!PrintStatistic(list1)) {
				cout << "\nERROR OCCUR! The statistics cannot be printed!" << endl;
			}
			else {
				cout << "\nThe statistics has been successfully printed!" << endl;
			}


			break;
		case 6:

			cout << "\n>> YOU HAD SELECTED THE <FILTER STUDENT> FUNCTION" << endl;

			// Prompt user to enter filter criteria.
			cout << "\nEnter the student details that you want to filter:" << endl;
			cout << "\nTips: If you don't know the specific criteria, please refer to main menu option '3' <PRINT LIST> function" << endl << endl;

			// Validate course input
			do {
				cout << "Available Course:" << endl
					<< "CS" << endl
					<< "CN" << endl
					<< "CT" << endl
					<< "IA" << endl
					<< "IB" << endl << endl;
				cout << "Please enter the course for filter >> ";
				cin >> course;
				course[0] = toupper(course[0]);
				course[1] = toupper(course[1]);

				if (strcmp(course, "CS") != 0 && strcmp(course, "CN") != 0 && strcmp(course, "CT") != 0
					&& strcmp(course, "IA") != 0 && strcmp(course, "IB") != 0)
				{
					cout << "Invalid course selection! Please try again." << endl << endl;
				}
				else {
					break;
				}
			} while (true);

			// Validate year input.
			do {
				cout << "Year (2001 to 2099) >> ";
				if (!(cin >> year) || year < 2001 || year > 2099) {
					cout << "Invalid year input! Please enter a valid year (2001-2099)." << endl << endl;
				}
				else {
					break;
				}
			} while (true);

			// Validate total credit input.
			do {
				cout << "Total Credit Hour >> ";
				if (!(cin >> totalcredit) || totalcredit < 0) {
					cout << "Invalid credit hour input! Please enter a non-negative value." << endl << endl;
				}
				else {
					break;
				}
			} while (true);
			cout << endl;

			// Clear previous results from list2.
			while (!list2.empty()) {
				list2.remove(1);
			}

			// Filtering students
			if (FilterStudent(list1, &list2, course, year, totalcredit)) {
				PrintList(list2, 1);
			}


			break;
		case 7:

			cout << "\n>> YOU HAD SELECTED THE <UPDATE ID AND PHONE> FUNCTION" << endl;

			// Update student ID and phone number.
			if (UpdateIDandPhone(&list1)) {
				cout << "\nUpdated Student Information:" << endl;
				PrintList(list1, 1);
			}


			break;
		case 8:

			cout << "\n>> YOU HAD SELECTED THE <FIND POTENTIAL FIRST CLASS> FUNCTION" << endl;

			// Display course options.
			cout << "\nFind Potential First Class: " << endl << endl
				<< "Course:" << endl
				<< "CS" << endl
				<< "CN" << endl
				<< "CT" << endl
				<< "IA" << endl
				<< "IB" << endl;

			do {
				cout << "Please Enter Your Choice of Course: ";
				cin >> course;
				course[0] = toupper(course[0]);
				course[1] = toupper(course[1]);

				if (strcmp(course, "CS") != 0 && strcmp(course, "CN") != 0 && strcmp(course, "CT") != 0
					&& strcmp(course, "IA") != 0 && strcmp(course, "IB") != 0)
				{
					cout << "Invalid course selection! Course '" << course << "' does not exist. Please try again." << endl << endl;;
				}
				else {
					break;
				}
			} while (true);

			// Clear previous results from list2.
			while (!list2.empty()) {
				list2.remove(1);
			}

			// Finding potential first-class students.
			if (!FindPotentialFirstClass(list1, &list2, course)) {

				// Display appropriate message based on missing data.
				if (list1.empty()) {
					if (!resultinsert) {
						cout << "\nBoth student and exam list are empty! Please create and insert both list before searching." << endl;
					}
					else {
						cout << "\nThe student list is empty! Please create a student list first." << endl;
					}
				}
				else if (!resultinsert) {
					cout << "\nThe exam list is empty! Please insert an exam list first." << endl;
				}
				else {
					cout << "No potential first-class students found for the given course." << endl;
				}
			}
			else {
				PrintList(list2, 1);
			}


			break;
		case 9:

			cout << "\n>> YOU HAD SELECTED TO QUIT THE PROGRAM" << endl;

			// Notify user about quitting the program.
			cout << "\nQuit the program" << endl;
			repeatmenu = false;


			break;
		}

		system("pause");
	} while (repeatmenu);

	
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q1 - Read and Store Student Infomation

bool CreateStuList(const char* filename, List* list) {

	Node* cur;
	Student temp;
	string label;
	bool found;

	// Open file for reading.
	ifstream inFile(filename);

	// Check if file opens successfully.
	if (!inFile) {
		return false;
	}

	cout << "\n==========================================================================" << endl;

	// Read student data from file and insert into the list.
	while (inFile >> label >> label >> label >> temp.id
		>> label >> label) {

		inFile.ignore();
		inFile.getline(temp.name, 256);

		inFile >> label >> label >> temp.course
			>> label >> label >> label >> temp.phone_no;

		// Check if student already exists in the list.
		found = false;
		for (int i = 1; i <= list->size(); i++) {
			cur = list->find(i);
			if (temp.compareID(cur->item)) {
				found = true;
				cout << "\nThe student ID: " << temp.id << " had been inserted before." << endl;
				cout << "--------------------" << endl;
				cout << "Student Id: " << temp.id << endl;
				cout << "Name: " << temp.name << endl;
				cout << "course: " << temp.course << endl;
				cout << "Phone Number: " << temp.phone_no << endl;
				cout << "--------------------" << endl;
				cout << "So, the above insertion will be cancelled! " << endl;
				break;
			}
		}

		// Insert student if not found.
		if (!found) {
			list->insert(temp);
		}
	}

	cout << "\n==========================================================================" << endl;

	// Close the file after reading.
	inFile.close();
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q2 - Delete Student From List

bool DeleteStudent(List* list, char* id) {

	Node* cur;
	Student temp;
	strcpy(temp.id, id);

	// Loop through the list to find the student by ID.
	for (int i = 1; i <= list->size(); i++) {

		cur = list->find(i);

		if (cur && cur->item.compareID(temp)) {
			list->remove(i);
			return true;
		}
	}

	// Display error if student ID is invalid.
	cout << "\nInvalid input! Please re-enter a valid and existing student ID." << endl;
	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q3 - Print Student Information

bool PrintList(List list, int source) {


	// Check if the student list is empty.
	if (list.empty()) {
		return false;
	}

	ofstream outFile;
	ostream* out = &cout;

	// Determine the output destination (screen or file).
	if (source == 1) {
		out = &cout;
		cout << "\nSuccessfully output on screen" << endl;
	}
	else if (source == 2) {
		outFile.open("student_result.txt");
		out = &outFile;
		cout << "\nSuccessfully output on file" << endl;
	}

	Node* cur;
	Student temp;

	// Loop through the student list and print each student's data.
	for (int i = 1; i <= list.size(); i++) {

		cur = list.find(i);
		temp = cur->item;

		*out << endl << string(50, '*') << "STUDENT" << i << string(50, '*') << endl;
		temp.print(*out);
		*out << endl << string(50, '*') << "PAST EXAM RESULT:" << i << string(50, '*') << endl;

		if (cur->item.exam_cnt > 0) {
			for (int j = 0; j < cur->item.exam_cnt; j++) {
				cur->item.exam[j].print(*out);
			}
		}
		else {
			*out << endl
				<< "THIS STUDENT HAVEN¡¯T TAKEN ANY EXAM YET"
				<< endl;
		}
		*out << endl
			<< string(50, '*') << "STUDENT" << i << string(50, '*')
			<< endl;
	}

	// Close the file if output is to file.
	if (source == 2) {
		outFile.close();
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q4 - Insert Student Exam Result

bool InsertExamResult(const char* filename, List* list) {

	Node* cur;
	Student temp;
	bool studentFound = false;

	// Open the exam result file.
	ifstream inFile(filename);

	// Check if the file opened successfully.
	if (!inFile) {
		return false;
	}

	// Read exam results for each student from the file.
	while (inFile >> temp.id) {

		inFile >> temp.exam[temp.exam_cnt].trimester >> temp.exam[temp.exam_cnt].year
			>> temp.exam[temp.exam_cnt].numOfSubjects;

		for (int i = 0; i < temp.exam[temp.exam_cnt].numOfSubjects; i++) {
			inFile >> temp.exam[temp.exam_cnt].sub[i].subject_code
				>> temp.exam[temp.exam_cnt].sub[i].subject_name
				>> temp.exam[temp.exam_cnt].sub[i].credit_hours
				>> temp.exam[temp.exam_cnt].sub[i].marks;
		}

		// Calculate GPA for the current exam.
		temp.exam[temp.exam_cnt].calculateGPA();

		for (int i = 1; i <= list->size(); i++) {
			cur = list->find(i);

			if (cur->item.compareID(temp)) {
				int insertIndex = cur->item.exam_cnt;
				cur->item.exam[insertIndex] = temp.exam[temp.exam_cnt];
				cur->item.exam_cnt++;
				cur->item.calculateCurrentCGPA();
				studentFound = true;
				break; 
			}
		}

		if (!studentFound) {
			cout << "\n[Warning] Student with ID " << temp.id
				<< " not found in student list. Skipping their exam result." << endl;
		}
	}

	// Close the file after processing.
	inFile.close();
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q5 - Find and Print Statistics of Student

bool PrintStatistic(List list) {

	Node* cur;
	Student temp;

	// Define courses and a counter for students in each course.
	char course[5][3] = { "CS","IA","IB","CN","CT" };
	int countStudent[5] = { 0,0,0,0,0 }; //According to { CS,IA,IB,CN,CT }
	double totalCGPA = 0, totalSubject = 0, totalCredit = 0;
	int sumStudent = 0, numOfSem = 0;

	// Check if the student list is empty.
	if (list.empty()) {
		return false;
	}

	// Iterate over all students in the list.
	for (int i = 1; i <= list.size(); i++) {

		cur = list.find(i);
		temp = cur->item;

		// Check the student's course and update relevant statistics.
		for (int j = 0; j < 5; j++) {
			if (strcmp(temp.course, course[j]) == 0) {
				sumStudent++;
				countStudent[j]++;

				totalCGPA += temp.current_cgpa;
				totalCredit += temp.totalCreditsEarned;
				for (int k = 0; k < temp.exam_cnt; k++) {
					totalSubject += temp.exam[k].numOfSubjects;
					numOfSem++;
				}
				break;
			}
		}
	}

	// Output the total number of students and the breakdown per course.
	cout << endl << "Total Students: " << sumStudent << endl;
	for (int i = 0; i < 5; i++) {
		cout << "\t" << course[i] << " Students - " << countStudent[i] << endl;
	}

	// Calculate and output average CGPA, subjects per semester, and credits earned.
	cout << "\nAverage CGPA: " << totalCGPA / sumStudent
		<< "\nAverage Subjects Taken Per Semester: " << setprecision(2) << totalSubject / numOfSem
		<< "\nAverage Credits Earned Per Semester: " << totalCredit / numOfSem;
	cout << endl << endl;

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q6 - Filter Student by Course, Year, and Credit Hours

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit) {


	// Check if the student list is empty.
	if (list1.empty()) {
		cout << "The student list is empty. Please create a list first." << endl;
		return false;
	}

	// Prevent adding to a non-empty result list
	if (!list2->empty()) {
		return false;
	}


	else {
		bool found = false;
		Node* cur = list1.head;
		while (cur != NULL) {
			if (strcmp(cur->item.course, course) == 0 && ((cur->item.id[0] - '0') * 10 + (cur->item.id[1] - '0'))
				== (year - 2000) && cur->item.totalCreditsEarned >= totalcredit)
			{
				list2->insert(cur->item);
				found = true;
			}
			cur = cur->next;
		}
		return found;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q7 - Update Student's ID and Phone

bool UpdateIDandPhone(List* list) {


	// Check if the student list is empty.
	if (list->empty()) {
		cout << "The student list is empty. Please create a list first." << endl;
		return false;
	}


	// Perform updates.
	else {
		Node* cur = list->head;
		while (cur != NULL) {

			// Update student ID.
			char tempID[8];
			char newID[12] = "B";
			strcpy(tempID, cur->item.id);
			strcat(newID, cur->item.course);
			strcat(newID, tempID);
			strcpy(cur->item.id, newID);


			// Update phone number.
			char tempNum[9];
			char newNum[12] = "";
			strcpy(tempNum, cur->item.phone_no);

			if (tempNum[0] == '1' || tempNum[0] == '3' || tempNum[0] == '5' || tempNum[0] == '7' || tempNum[0] == '9') {
				strcpy(newNum, "01");
			}
			else {
				strcpy(newNum, "02");
			}


			// Remove dashes '-' from original phone number.
			int j = 0;
			for (int i = 0; tempNum[i] != '\0'; i++) {
				if (tempNum[i] != '-') {
					tempNum[j++] = tempNum[i];
				}
			}
			tempNum[j] = '\0';


			// Append digits to new number, and update.
			strcat(newNum, tempNum);
			strcpy(cur->item.phone_no, newNum);
			cur = cur->next;
		}
		return true;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q8 - Find Potential First Class

bool FindPotentialFirstClass(List list1, List* list2, char* course) {


	// Check if the student list is empty
	if (list1.empty()) {
		return false;
	}


	// Prevent adding to a non-empty result list
	if (!list2->empty()) {
		return false;
	}


	Student stud;
	int stuNo = 0;


	// Loop through all students
	for (int i = 0; i < list1.size(); i++) {
		list1.get(i, stud);

		// Compare if student is from user-input course
		if (strcmp(stud.course, course) == 0) {
			int gpa3_75_cnt = 0;
			int gpa3_5_cnt = 0;

			// Only consider students with at least 3 exam records
			if (stud.exam_cnt < 3) {
				continue;
			}
			else {
				for (int j = 0; j < stud.exam_cnt; j++) {
					int cre_hour_count = 0;
					for (int k = 0; k < stud.exam[j].numOfSubjects; k++) {
						cre_hour_count += stud.exam[j].sub[k].credit_hours;
					}
					if (stud.exam[j].gpa >= 3.75 && cre_hour_count >= 12) {
						gpa3_75_cnt++;
					}
					else if (stud.exam[j].gpa < 3.5) {
						gpa3_5_cnt++;
					}
				}
			}

			// Check if student qualifies as potential first class
			if (gpa3_5_cnt > 0) {
				continue;
			}
			else if (gpa3_75_cnt >= 3) {
				stuNo++;
				list2->insert(stuNo, stud);
			}
		}
	}


	// Display the number of potential first class student(s)
	if (stuNo == 0) {
		cout << "There is no student in " << course << " that has potential to get first class." << endl;
	}
	else if (stuNo == 1) {
		cout << "There is only 1 student in " << course << " who has potential to get first class." << endl;
	}
	else {
		cout << "There are " << stuNo << " number of student in " << course << " who has potential to get first class." << endl;
	}
	return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Q9 - Display Choice Menu

int menu() {

	// Clear the screen.
	system("cls");

	// Display task options (1 - 9).
	titleprint();
	cout << endl;
	printCentered("1. Create Student List");
	printCentered("2. Delete Student");
	printCentered("3. Print Student List");
	printCentered("4. Insert Exam Result");
	printCentered("5. Print Exam Statistic");
	printCentered("6. Filter Student");
	printCentered("7. Update Student's ID and Phone");
	printCentered("8. Find Potential First Class Student");
	printCentered("9. Exit");
	cout << endl;

	// Warning message if student list or exam results are missing.
	if (!studentinsert) {
		if (!resultinsert) {
			printCentered("WARNING! Both Student List and Exam Result have not been inserted yet...");
			cout << endl;
		}
		else {
			printCentered("WARNING! The Student List has not been inserted yet...");
			cout << endl;
		}
	}
	else if (!resultinsert) {
		printCentered("WARNING! The Exam Result has not been inserted yet...");
		cout << endl;
	}

	double choice;
	bool valid = false;

	// Loop until user enters a valid choice.
	while (!valid) {
		printCentered("|=======================================================================================================================|");
		cout << endl;
		cout << right << setw(width / 2) << "Enter Selection >> ";
		cin >> choice;

		// Error Handling
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input! Please enter a valid integer between 1 - 9." << endl;
		}
		else if (choice != static_cast<int>(choice)) {
			cout << "Invalid input! Please enter a valid integer between 1 - 9." << endl;
		}
		else if (choice < 1 || choice > 9) {
			cout << "Invalid input! Please enter a valid integer between 1 - 9." << endl;
		}
		else {
			valid = true;
		}
	}

	// Clear the screen.
	system("cls");

	// Return the valid menu choice.
	return choice;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Extra function - Design

void printCentered(const string& text) {
	int textLength = text.length();
	int padding = width - textLength;
	cout << endl;
	if (padding > 0) {
		int leftPadding = padding / 2;
		int rightPadding = padding - leftPadding;

		cout << setw(leftPadding + textLength) << right
			<< text << setw(rightPadding) << left;
	}
	else {
		cout << text;
	}
}


void titleprint() {
	printCentered("                                          _____                                ");
	printCentered("                                         ||    \\_,                             ");
	printCentered("                                         |\\_____/                              ");
	printCentered("                                         ||                                    ");
	printCentered("                                   ______|______                               ");
	printCentered("                                 //             \\\\                             ");
	printCentered("                                ||     _____     ||                            ");
	printCentered("                                ||    /  |  \\    ||                            ");
	printCentered("                                ||   |   |/  |   ||                            ");
	printCentered("                                ||   |   '   |   ||                            ");
	printCentered("                                ||    \\_____/    ||                            ");
	printCentered("                                ||               ||                            ");
	printCentered("|=======================================================================================================================|");
	printCentered("|    ___  _____  _  _  ___   ____  _  _  _____     ____  ____   ___   ___   ____  ___      __  __  ____  _  _  _  _     |");
	printCentered("|   / __||_   _|| || || _ \\ | ___|| \\| ||_   _|   | __ || ___| / __| / _ \\ | __ || _ \\    |  \\/  || ___|| \\| || || |    |");
	printCentered("|   \\__ \\  | |  | || || || || __| |  \\ |  | |     |  __|| __| | |__ | | | ||  __|| || |   | |\\/| || __| |  \\ || || |    |");
	printCentered("|   |___/  |_|  |____||___/ |____||_|\\_|  |_|     |_||_\\|____| \\___| \\___/ |_||_\\|___/    |_|  |_||____||_|\\_||____|    |");
	printCentered("|                                                                                                                       |");
	printCentered("|=======================================================================================================================|");
}