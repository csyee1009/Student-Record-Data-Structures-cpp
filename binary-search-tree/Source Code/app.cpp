#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<iomanip>
#include	"BST.h"
#include    "Student.h"
using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Functions Declaration

bool readFile(const char*, BST*);
int menu();
void titleprint();
void printCentered(const string&);
bool studentinsert = false;



//////////////////////////////////////////////////
				//decoration

const int width = 170;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// int main()

int main() {
	BST t1, t2;
	bool repeat = true, repeatmenu = true;
	Student temp;
	int order, source;


	do {
		switch (menu()) {
		case 1:

			cout << "\n>> YOU HAD SELECTED THE <READ DATA TO BST> FUNCTION" << endl << endl;

			// Attempt to read data to binary search tree from file.
			if (readFile("student.txt", &t1)) {
				cout << "File read successfully." << endl << endl;
				studentinsert = true;
			}
			else {
				cout << "Fail to read file." << endl << endl;
			}


			break;
		case 2:

			cout << "\n>> YOU HAD SELECTED THE <FIND & PRINT ALL DEEPEST NODE> FUNCTION" << endl << endl;
			
			// Check and print deepest nodes
			if (t1.deepestNodes()) {
				cout << "\nSuccessfully printed all deepest node of the tree." << endl << endl;
			}

			else {
				cout << "The tree is empty." << endl << endl;
			}


			break;
		case 3:

			cout << "\n>> YOU HAD SELECTED THE <DISPLAY STUDENT> FUNCTION" << endl << endl;
			
			// Prompt user for display order
			cout << "Choose the order that you want to display:" << endl;
			cout << "1. Ascending by Student ID" << endl;
			cout << "2. Descending by Student ID" << endl;
			cout << "Enter choice (1 or 2): ";
			cin >> order;

			// Prompt user for output destination
			cout << "\nChoose where you want to print your output<" << endl;
			cout << "1. Display on screen" << endl;
			cout << "2. Save to file" << endl;
			cout << "Enter choice (1 or 2): ";
			cin >> source;
			cout << endl;

			// Call display function with chosen order and destination
			if (!t1.display(order, source)) {
				cout << "Display failed. Tree may be empty or input invalid." << endl;
			}


			break;
		case 4:

			cout << "\n>> YOU HAD SELECTED THE <CLONE SUB TREE> FUNCTION" << endl << endl;
			
			// Prompt user for student ID to be the root of cloned subtree
			cout << "Enter the student ID, as the root of the new cloned subtree >> ";
			cin >> temp.id;


			// Clone the subtree from t1 into t2
			if (t2.CloneSubtree(t1, temp)) {
				cout << endl;
				cout << "=================================================";
				cout << " Original tree (t1) in pre-order: ";
				cout << "=================================================" << endl;
				t1.preOrderPrint();
				cout << "=================================================";
				cout << " Cloned subtree tree (t2) in pre-order: ";
				cout << "=================================================" << endl;
				t2.preOrderPrint();
				cout << "=================================================";
				cout << " Subtree cloned successfully. ";
				cout << "=================================================" << endl << endl;
			}
			else {
				cout << "Cannot clone subtree. " << endl << endl;
			}
			

			break;
		case 5:

			cout << "\n>> YOU HAD SELECTED THE <PRINT LEVEL NODES> FUNCTION" << endl << endl;
			
			// Print nodes at each level
			if (t1.printLevelNodes()) {
				cout << endl;
				cout << "All level nodes have been successfully printed!" << endl << endl;
			}
			else {
				cout << "The tree is empty!" << endl;
			}

			break;
		case 6:

			cout << "\n>> YOU HAD SELECTED THE <PRINT ALL EXTERNAL PATH> FUNCTION" << endl << endl;
			
			// Print all external (leaf) paths
			if (t1.printPath()) {
				cout << endl;
				cout << "All external path have been successfully printed!" << endl << endl;
			}
			else {
				cout << "The tree is empty!" << endl;
			}
			break;

		case 7:

			cout << "\n>> YOU HAD SELECTED TO QUIT THE PROGRAM" << endl;

			// Notify user about quitting the program.
			cout << "\nQuit the program" << endl;
			repeatmenu = false;


			break;
		}

	system("pause");
	} while (repeatmenu);

	system("pause");
	return 0;
}


/////////////////////////////////////////////////
			// (a) - Read data to BST

bool readFile(const char* filename, BST* t1) {

	Student student;
	string label;

	ifstream inFile(filename);

	if (!inFile) {
		return false; // File could not be opened
	}

	// Read until end of file
	while (!inFile.eof()) {

		inFile >> label >> label >> label >> student.id
			>> label >> label;

		inFile.ignore();
		inFile.getline(student.name, 30);

		inFile >> label >> label;
		inFile.ignore();
		inFile.getline(student.address, 100);

		inFile >> label >> label >> student.DOB
			>> label >> label >> label >> student.phone_no
			>> label >> label >> student.course
			>> label >> label >> student.cgpa;

		// Create a new node with the read student data
		BTNode* newNode = new BTNode(student);
		if (!newNode) {
			return false; // Memory allocation failed
		}

		// Insert node into the tree
		if (t1->root == NULL) {
			t1->root = newNode;
		}
		else {
			t1->insert2(t1->root, newNode);
		}
		t1->count++; // Increment count of nodes
	}
	inFile.close();
	cout << "Successfully read " << t1->count << " student records." << endl;
	return true;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// (h) - Display Choice Menu

int menu() {

	// Clear the screen
	system("cls");

	titleprint();

	// Display Task 1 - 9
	printCentered("1. Read data to BST");
	printCentered("2. Print deepest nodes");
	printCentered("3. Display student");
	printCentered("4. Clone Subtree");
	printCentered("5. Print Level Nodes");
	printCentered("6. Print Path");
	printCentered("7. Exit.");
	cout << endl;

	// Warning message if student list or exam results are missing.
	if (!studentinsert) {

		printCentered("WARNING! The Student Record Binary Search Tree has not been inserted yet...");
		cout << endl;

	}


	double choice;
	bool valid = false;
	while (!valid) {

		//Prompt user to input the task choice
		printCentered("Enter Selection >> ");
		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input! Please enter a valid integer between 1 - 7." << endl;
		}
		else if (choice != static_cast<int>(choice)) {
			cout << "Invalid input! Please enter a valid integer between 1 - 7." << endl;
		}
		else if (choice < 1 || choice > 7) {
			cout << "Invalid input! Please enter a valid integer between 1 - 7." << endl;
		}
		else {
			valid = true;
		}
	}

	system("cls");
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
	printCentered("         &&& &&  & &&         ");
	printCentered("     && &\\/&\\|& ()|/ @, &&    ");
	printCentered("     &\\/(/&/&||/& /_/)_&/_&   ");
	printCentered("  &() &\\/&|()|/&\\/ '%' & ()   ");
	printCentered(" &_\\_&&_\\ |& |&&/&__%_/_& &&  ");
	printCentered("&&   && & &| &| /& & % ()& /&&");
	printCentered(" ()&_---()&\\&\\|&&-&&--%---()~ ");
	printCentered("     &&     \\|||             ");
	printCentered("             |||             ");
	printCentered("             |||             ");
	printCentered("         , -=-~  .-^- _      ");
	printCentered("|================================|");
	printCentered("|        ____  ___  _____        |");
	printCentered("|       | __ |/ __||_   _|       |");
	printCentered("|       | __ |\\__ \\  | |         |");
	printCentered("|       |____/|___/  |_|         |");
	printCentered("|                                |");
	printCentered("|================================|");
}
