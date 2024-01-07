#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Excel.cpp"

using namespace std;
Excel<string> cell;

BOOL WINAPI ctrlHandler(DWORD key) {
	return TRUE;
}

string getOption();
void getFunction();
void getColor();
string getColorOption();
string getAlignmentOption();
void getAlignment();
string getTypeOption();
void getDataType();

int main() {

	//SetConsoleCtrlHandler(ctrlHandler, TRUE);


	ifstream f("Sheet.txt");
	if (f.good()) {
		cell.readFromFile();
	}

	std::string s;
	while (true) {
		system("cls");
		cell.printGrid();

		while (!_kbhit());
		int c = _getch();

		if (c == 0 || c == 0xe0) {
			c = _getch();

			switch (c) {
			case 0x4B: // LEFT
				cell.moveCursor(Direction::Prev);
				break;
			case 0x4D: // RIGHT
				cell.moveCursor(Direction::Next);
				break;
			case 0x48: // UP
				cell.moveCursor(Direction::Up);
				break;
			case 0x50: // DOWN
				cell.moveCursor(Direction::Down);
				break;
			}
		}
		else {
			switch (toupper(c)) {
			case 'D': // set data
				cin >> s;
				cell.setCurrentData(s);
				break;
			case 'C':
				cell.copy();
				break;
			case 'X':
				cell.cut();
				break;
			case 'V':
				cell.paste();
				break;
			case 'A':
				cell.insertRowAbove();
				break;
			case 'B':
				cell.insertRowBelow();
				break;
			case 'R':
				cell.insertColumnToRight();
				break;
			case 'L':
				cell.insertColumnToLeft();
				break;
			case 'T':
				cell.insertCellByDownShift();
				break;
			case 'W':
				cell.insertCellByRightShift();
				break;
			case 'U':
				cell.clearColumn();
				break;
			case 'I':
				cell.clearRow();
				break;
			case 'F':
				cell.deleteRow();
				break;
			case 'G':
				cell.deleteColumn();
				break;
			case 'H':
				cell.deleteCellByLeftShift();
				break;
			case 'J':
				cell.deleteCellByUpShift();
				break;
			case 'M':
				getFunction();
				break;
			case 'P':
				getColor();
				break;
			case 'Q':
				getAlignment();
				break;
			case 'Z':
				getDataType();
				break;
			case 'S':
				cell.saveSheetInFile();
				break;
			}
		}
	}
	Sleep(100);
	return 0;
}

string getOption() {
	string option;

	cout << "Excel Formulas " << endl;
	cout << "1. Sum" << endl;
	cout << "2. Average" << endl;
	cout << "3. Maximum Element" << endl;
	cout << "4. Minimum Element" << endl;
	cout << "5. Element Count" << endl;
	cout << "6. Get Back" << endl;

	cout << "Enter Option: ";
	cin >> option;

	return option;
}

void getFunction() {
	int startRow, startCol, endRow, endCol;
	string option = getOption();

	if (option != "6") {
		cout << "Enter Starting Cell for Row: ";
		cin >> startRow;

		cout << "Enter Starting Cell for Col: ";
		cin >> startCol;

		cout << "Enter Ending Cell for Row: ";
		cin >> endRow;

		cout << "Enter Ending Cell for Col: ";
		cin >> endCol;

		if (option == "1") {
			float sum = cell.getRangeSum(startRow, startCol, endRow, endCol);
			cell.setCurrentData(to_string(sum));
		}
		if (option == "2") {
			float avg = cell.getRangeAverage(startRow, startCol, endRow, endCol);
			cell.setCurrentData(to_string(avg));
		}
		if (option == "3") {
			float max = cell.getRangeMax(startRow, startCol, endRow, endCol);
			cell.setCurrentData(to_string(max));
		}
		if (option == "4") {
			float min = cell.getRangeMin(startRow, startCol, endRow, endCol);
			cell.setCurrentData(to_string(min));
		}
		if (option == "5") {
			int total = cell.count(startRow, startCol, endRow, endCol);
			cell.setCurrentData(to_string(total));
		}
	}
}

void getColor() {
	string option = getColorOption();

	if (option != "6") {
		if (option == "1") {
			cell.current->setColor(Color::Red);
		}
		else if (option == "2") {
			cell.current->setColor(Color::Green);
		}
		else if (option == "3") {
			cell.current->setColor(Color::Blue);
		}
		else if (option == "4") {
			cell.current->setColor(Color::Cyan);
		}
		else if (option == "5") {
			cell.current->setColor(Color::White);
		}
	}
}

string getColorOption() {
	string option;

	cout << "Color Options " << endl;
	cout << "1. Red" << endl;
	cout << "2. Green" << endl;
	cout << "3. Blue" << endl;
	cout << "4. Cyan" << endl;
	cout << "5. White" << endl;
	cout << "6. Get Back" << endl;

	cout << "Enter Option: ";
	cin >> option;

	return option;
}

string getAlignmentOption() {
	string option;

	cout << "Alignment Options " << endl;
	cout << "1. Left" << endl;
	cout << "2. Right" << endl;
	cout << "3. Center" << endl;
	cout << "4. Get Back" << endl;

	cout << "Enter Option: ";
	cin >> option;

	return option;
}

void getAlignment() {
	string option = getAlignmentOption();

	if (option != "4") {
		if (option == "1") {
			cell.current->setAlignment(Alignment::Left);
		}
		else if (option == "2") {
			cell.current->setAlignment(Alignment::Right);
		}
		else if (option == "3") {
			cell.current->setAlignment(Alignment::Center);
		}
	}
}

string getTypeOption() {
	string option;

	cout << "Data Type Options " << endl;
	cout << "1. Char" << endl;
	cout << "2. Int" << endl;
	cout << "3. Float" << endl;
	cout << "4. Get Back" << endl;

	cout << "Enter Option: ";
	cin >> option;

	return option;
}

void getDataType() {
	string option = getTypeOption();

	if (option != "4") {
		if (option == "1") {
			cell.current->setDataType(Type::Char);
		}
		else if (option == "2") {
			cell.current->setDataType(Type::Int);
		}
		else if (option == "3") {
			cell.current->setDataType(Type::Float);
		}
	}
}
