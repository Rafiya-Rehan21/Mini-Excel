#pragma once
#include <iostream>
#include <fstream>
#include <type_traits>
#include <algorithm>
#include <cstring>
#include "ascii.h"
#include "Cell.cpp"
#include "Iterator.cpp"
#include "ReverseIterator.cpp"

using namespace std;
template <typename T>

class Excel {
private:
	int rowSize = 5;
	int colSize = 5;
	int rows = 0;
	int cols = 0;
	int cellSize = 4;

	int x = 0;
	int y = 0;

	string clipboard;


	bool isEmpty() {
		return current == nullptr;
	}

	void insertCellNext(T val) {
		Cell<T>* newCell = new Cell<T>(val);
		Cell<T>* temp = current;

		if (isEmpty()) {
			current = newCell;
		}
		else {
			while (temp->getNext() != nullptr) {

				temp = temp->getNext();
			}

			temp->setNext(newCell);
			newCell->setPrev(temp);
		}
	}

	void insertCellBefore(T val) {
		Cell<T>* newCell = new Cell<T>(val);
		Cell<T>* temp = current;

		if (isEmpty()) {
			current = newCell;
		}
		else {
			while (temp->getPrev() != nullptr) {

				temp = temp->getPrev();
			}

			temp->setPrev(newCell);
			newCell->setNext(temp);
		}
	}

	void insertCellAbove(T val) {
		Cell<T>* newCell = new Cell<T>(val);
		Cell<T>* temp = current;

		if (isEmpty()) {
			current = newCell;
		}
		else {
			while (temp->getAbove() != nullptr) {

				temp = temp->getAbove();
			}

			temp->setAbove(newCell);
			newCell->setBelow(temp);
		}
	}

	void insertCellBelow(T val) {
		Cell<T>* newCell = new Cell<T>(val);
		Cell<T>* temp = current;
		newCell->setBelow(nullptr);

		if (isEmpty()) {
			current = newCell;
		}
		else {
			while (temp->getBelow() != nullptr) {

				temp = temp->getBelow();
			}

			temp->setBelow(newCell);
			newCell->setAbove(temp);
		}
	}

	Cell<T>* createRow() {
		Cell<T>* newRow = new Cell<T>();
		Cell<T>* temp = newRow;

		for (int i = 0; i < rowSize - 1; i++) {
			Cell<T>* newCell = new Cell<T>();
			//Cell<T>* newCell = new Cell<T>(rows);
			temp->setNext(newCell);
			newCell->setPrev(temp);
			temp = newCell;
		}

		return newRow;
	}

	Cell<T>* createCol() {
		Cell<T>* newCol = new Cell<T>();
		Cell<T>* temp = newCol;

		for (int i = 0; i < colSize - 1; i++) {
			Cell<T>* newCell = new Cell<T>();
			temp->setBelow(newCell);
			newCell->setAbove(temp);
			temp = newCell;
		}

		return newCol;
	}

	void deleteGrid() {
		if (rows == 0)
			return;

		Cell<T>* temp = getRootCell();
		Cell<T>* rowPtr = temp;
		Cell<T>* next = nullptr;

		for (int i = 0; i < rows; i++) {
			Cell<T>* colPtr = rowPtr;
			rowPtr = rowPtr->getBelow();

			for (int j = 0; j < cols; j++) {
				next = colPtr->getNext();
				delete colPtr;
				colPtr = next;
			}
		}

		rows = cols = rowSize = colSize = 0;
		current = nullptr;
	}

	void makeInitialGrid(int rows, int cols) {
		deleteGrid();
		colSize = rows;
		rowSize = cols;

		for (int i = 0; i < rows; i++) {
			insertRowBelow();
		}

		colSize = rows;
		rowSize = cols;
	}

public:
	Cell<T>* current = nullptr;

	Excel() {
		makeInitialGrid(5, 5);
	}
	
	void printRow(Cell<T> *row) {
		Cell<T>* temp = row;

		while (temp != nullptr) {
			if (temp->getValueExists()) {
				cout << temp->getValue() << "------->";
			}
			else {
				cout << " ------->";
			}
			temp = temp->getNext();
		}

		cout << "NULL" << endl;
	}

	void printCol(Cell<T>* col) {
		Cell<T>* temp = col;

		while (temp != nullptr) {
			if (temp->getValueExists()) {
				cout << temp->getValue() << "------->";
			}
			else {
				cout << " ------->";
			}

			temp = temp->getBelow();
		}

		cout << "NULL" << endl;
	}

	void printRows() {
		Cell<T>* temp = current;

		while (temp->getAbove() != nullptr) temp = temp->getAbove();

		for (int i = 0; i < rows; i++) {
			printRow(temp);
			temp = temp->getBelow();
		}
	}

	void printCols() {
		Cell<T>* temp = current;

		while (temp->getPrev() != nullptr) {
			temp = temp->getPrev();
		}

		for (int i = 0; i < cols; i++) {
			printCol(temp);
			temp = temp->getNext();
		}
	}

	void insertRowBelow() {
		Cell<T>* newRow = createRow();
		Cell<T>* newCell = newRow;
		Cell<T>* oldCell = current;
		Cell<T>* mid = nullptr;

		if (isEmpty()) {
			current = newRow;
		}
		else {
			while (oldCell->getPrev())
				oldCell = oldCell->getPrev();

			for (int i = 0; i < rowSize; i++) {
				newCell->setAbove(oldCell);

				mid = oldCell->getBelow();
				if (mid != nullptr) {
					newCell->setBelow(mid);
					mid->setAbove(newCell);
				}

				oldCell->setBelow(newCell);

				oldCell = oldCell->getNext();
				newCell = newCell->getNext();
			}
		}

		rows++;
		colSize++;
	}

	void insertRowAbove() {
		Cell<T>* newRow = createRow();
		Cell<T>* newCell = newRow;
		Cell<T>* oldCell = current;
		Cell<T>* prev = nullptr;

		if (isEmpty()) {
			current = newRow;
		}
		else {
			while (oldCell->getPrev())
				oldCell = oldCell->getPrev();

			for (int i = 0; i < rowSize; i++) {
				newCell->setBelow(oldCell);

				prev = oldCell->getAbove();
				if (prev != nullptr) {
					newCell->setAbove(prev);
					prev->setBelow(newCell);
				}

				oldCell->setAbove(newCell);

				oldCell = oldCell->getNext();
				newCell = newCell->getNext();
			}
		}

		rows++;
		colSize++;
	}

	void insertColumnToRight() {
		Cell<T>* newCol = createCol();
		Cell<T>* newCell = newCol;
		Cell<T>* oldCell = current;
		Cell<T>* mid = nullptr;

		if (isEmpty()) {
			current = newCol;
		}
		else {
			while (oldCell->getAbove())
				oldCell = oldCell->getAbove();

			for (int i = 0; i < colSize; i++) {
				newCell->setPrev(oldCell);

				mid = oldCell->getNext();
				if (mid != nullptr) {
					newCell->setNext(mid);
					mid->setPrev(newCell);
				}

				oldCell->setNext(newCell);

				oldCell = oldCell->getBelow();
				newCell = newCell->getBelow();
			}
		}

		cols++;
		rowSize++;
	}

	void insertColumnToLeft() {
		Cell<T>* newCol = createCol();
		Cell<T>* newCell = newCol;
		Cell<T>* oldCell = current;
		Cell<T>* prev = nullptr;

		if (isEmpty()) {
			current = newCol;
		}
		else {
			while (oldCell->getAbove())
				oldCell = oldCell->getAbove();

			for (int i = 0; i < colSize; i++) {
				newCell->setNext(oldCell);

				prev = oldCell->getPrev();
				if (prev != nullptr) {
					newCell->setPrev(prev);
					prev->setNext(newCell);
				}

				oldCell->setPrev(newCell);

				oldCell = oldCell->getBelow();
				newCell = newCell->getBelow();
			}
		}

		cols++;
		rowSize++;
	}

	void insertCellByRightShift() {
		insertColumnToLeft();
	}

	void insertCellByDownShift() {
		insertRowAbove();
	}

	void deleteRow() {                               
		Cell<T>* temp = current;

		while (temp->getPrev() != nullptr)
			temp = temp->getPrev();

		Cell<T>* next = nullptr;
		Cell<T>* down = temp->getBelow();
		Cell<T>* up = temp->getAbove();

		// When row is a middle row
		if (down != nullptr && up != nullptr) {
			current = down;
			while (down != nullptr && up != nullptr) {
				down->setAbove(up);
				up->setBelow(down);

				down = down->getNext();
				up = up->getNext();
			}
		}
		else {
			// bottom row
			if (down == nullptr) {
				current = up;
				while (up != nullptr) {
					up->setBelow(nullptr);

					up = up->getNext();
				}
			}
			else { // top row
				current = down;
				while (down != nullptr) {
					down->setAbove(nullptr);

					down = down->getNext();
				}
			}
		}

		while (temp != nullptr) {
			next = temp->getNext();
			delete temp;
			temp = next;
		}

		rows--;
		colSize--;
	}

	void deleteColumn() {
		Cell<T>* temp = current;

		while (temp->getAbove() != nullptr)
			temp = temp->getAbove();

		Cell<T>* next;
		Cell<T>* left = temp->getPrev();
		Cell<T>* right = temp->getNext();

		// middle row
		if (left != nullptr && right != nullptr) {
			current = left;
			while (right != nullptr && left != nullptr) {
				right->setPrev(left);
				left->setNext(right);
			
				right = right->getBelow();
				left = left->getBelow();
			}
		}
		else {
			// leftmost row
			if (left != nullptr) {
				current = left;
				while (left != nullptr) {
					left->setNext(nullptr);

					left = left->getBelow();
				}
			}
			else { // right most
				current = right;
				while (right != nullptr) {
					right->setPrev(nullptr);

					right = right->getBelow();
				}
			}
		}

		while (temp != nullptr) {
			next = temp->getBelow();
			delete temp;
			temp = next;
		}

		cols--;
		rowSize--;
	}

	void deleteCellByLeftShift() {
		Cell<T>* temp = current;
		Cell<T>* next = temp->getNext();

		if (current->getPrev() != nullptr)
			current = current->getPrev();

		while (next != nullptr) {
			temp->setValue(next->getValue());

			temp = temp->getNext();
			next = next->getNext();
		}

		temp->setValueExists(false);
	}

	void deleteCellByUpShift() {
		Cell<T>* temp = current;
		Cell<T>* below = temp->getBelow();

		if (current->getAbove() != nullptr)
			current = current->getAbove();

		while (below != nullptr) {
			temp->setValue(below->getValue());

			temp = temp->getBelow();
			below = below->getBelow();
		}

		temp->setValueExists(false);
	}

	void clearColumn() {
		Cell<T>* temp = current;
		
		while (temp->getAbove() != nullptr) {
			temp = temp->getAbove();
		}

		while (temp != nullptr) {
			temp->setValueExists(false);
			temp = temp->getBelow();	
		}
	}

	void clearRow() {
		Cell<T>* temp = current;

		while (temp->getPrev() != nullptr) {
			temp = temp->getPrev();
		}

		while (temp != nullptr) {
			temp->setValueExists(false);
			temp = temp->getNext();
		}
	}

	float normalizeValue(Cell<T>* cell) {
		float val = 0;

		if constexpr (std::is_same_v<T, std::string>) {
			try {
				val = stof(cell->getValue());
			}
			catch (std::exception ex) {}
		}
		else if constexpr (std::is_same_v<T, float>) {
			val = cell->getValue();
		}
		else if constexpr (std::is_same_v<T, int>) {
			val = cell->getValue();
		}

		return val;
	}

	Cell<T>* getRootCell() {
		Cell<T>* temp = current;

		while (temp->getAbove() != nullptr) temp = temp->getAbove();
		while (temp->getPrev() != nullptr) temp = temp->getPrev();

		return temp;
	}

	float getRangeSum(int startRow, int startCol, int endRow, int endCol) {
		if ((startRow < 0 || startCol < 0) || (endRow > rowSize || endCol > colSize)) {
			return -1;
		}

		float sum = 0;
		Cell<T>* rowPtr = getRootCell();		

		// Move to the starting row
		for (int i = 0; i < startRow; i++) {
			rowPtr = rowPtr->getBelow();
		}

		for (int i = startRow; i <= endRow; i++) {
			Cell<T>* colPtr = rowPtr;

			// Move to the starting column
			for (int j = 0; j < startCol; j++) {
				colPtr = colPtr->getNext();
			}

			for (int j = startCol; j <= endCol; j++) {
				sum += normalizeValue(colPtr); // Add the value of the current cell to the sum
				colPtr = colPtr->getNext(); // Move to the next column cell
			}

			rowPtr = rowPtr->getBelow(); // Move to the next row
		}

		return sum;
	}

	float getRangeAverage(int startRow, int startCol, int endRow, int endCol) {

		if ((startRow < 0 || startCol < 0) || (endRow > rowSize || endCol > colSize)) {
			return -1;
		}

		int totalElements = 0;
		Cell<T>* rowPtr = getRootCell();

		for (int i = 0; i < startRow; i++) {
			rowPtr = rowPtr->getBelow();
		}

		for (int i = startRow; i <= endRow; i++) {
			Cell<T>* colPtr = rowPtr;

			for (int j = 0; j < startCol; j++) {
				colPtr = colPtr->getNext();
			}

			for (int j = startCol; j <= endCol; j++) {
				if (!isAlphabetsOnlyOrEmpty(colPtr->getValue()))
					totalElements++;
				colPtr = colPtr->getNext();
			}

			rowPtr = rowPtr->getBelow();
		}


		float sum = getRangeSum(startRow,startCol,endRow,endCol);
		if (sum == -1) {
			return -1;
		}

		float average = sum / totalElements;

		return average;
	}

	Iterator<T> begin() {
		return Iterator<T>(current);
	}

	Iterator<T> end() {
		return Iterator<T>(nullptr);
	}

	ReverseIterator<T> rBegin() {
		Cell<T>* temp = current;

		for (int i = 0; i < rowSize-1; i++) {
			temp = temp->getBelow();
		}

		for (int j = 0; j < colSize - 1; j++) {
			temp = temp->getNext();
		}

		return ReverseIterator<T>(temp);
	}

	ReverseIterator<T> rEnd() {
		return ReverseIterator<T>(nullptr);
	}

	bool isAlphabetsOnlyOrEmpty(const std::string& input) {
		return input.empty() || 
			std::all_of(input.begin(), input.end(), ::isspace) || 
			std::all_of(input.begin(), input.end(), ::isalpha);
	}

	int count(int startRow, int startCol, int endRow, int endCol) {
		if ((startRow < 0 || startCol < 0) || (endRow > rowSize || endCol > colSize)) {
			return -1;
		}

		int totalElements = 0;
		Cell<T>* rowPtr = getRootCell();

		for (int i = 0; i < startRow; i++) {
			rowPtr = rowPtr->getBelow();
		}

		for (int i = startRow; i <= endRow; i++) {
			Cell<T>* colPtr = rowPtr;

			for (int j = 0; j < startCol; j++) {
				colPtr = colPtr->getNext();
			}

			for (int j = startCol; j <= endCol; j++) {
				if (!isAlphabetsOnlyOrEmpty(colPtr->getValue()))
					totalElements++;
				colPtr = colPtr->getNext(); 
			}

			rowPtr = rowPtr->getBelow(); 
		}

		return totalElements;
	}

	float getRangeMax(int startRow, int startCol, int endRow, int endCol) {
		bool isFirstElement = true;
		float maxElement;
		bool maxSet = false;

		if ((startRow < 0 || startCol < 0) || (endRow > rowSize || endCol > colSize)) {
			return -1;
		}

		float sum = 0;
		Cell<T>* rowPtr = getRootCell();

		for (int i = 0; i < startRow; i++) {
			rowPtr = rowPtr->getBelow();
		}

		for (int i = startRow; i <= endRow; i++) {
			Cell<T>* colPtr = rowPtr;

			for (int j = 0; j < startCol; j++) {
				colPtr = colPtr->getNext();
			}

			for (int j = startCol; j <= endCol; j++) {
				float cellValue = normalizeValue(colPtr);
				sum += cellValue; 

				if (isFirstElement || cellValue > maxElement) {
					maxElement = cellValue;
					isFirstElement = false; 
					maxSet = true;
				}
				colPtr = colPtr->getNext();
			}

			rowPtr = rowPtr->getBelow();
		}

		if (!maxSet) {
			return false; 
		}

		return maxElement;
	}

	 float getRangeMin(int startRow, int startCol, int endRow, int endCol) {
		bool isFirstElement = true;
		float minElement;
		bool minSet = false;

		if ((startRow < 0 || startCol < 0) || (endRow > rowSize || endCol > colSize)) {
			return -1; 
		}

		float sum = 0;
		Cell<T>* rowPtr = getRootCell();

		for (int i = 0; i < startRow; i++) {
			rowPtr = rowPtr->getBelow();
		}

		for (int i = startRow; i <= endRow; i++) {
			Cell<T>* colPtr = rowPtr;

			for (int j = 0; j < startCol; j++) {
				colPtr = colPtr->getNext();
			}

			for (int j = startCol; j <= endCol; j++) {
				float cellValue = normalizeValue(colPtr);
				sum += cellValue;

				if ((isFirstElement || cellValue < minElement) && !isAlphabetsOnlyOrEmpty(colPtr->getValue())) {
					minElement = cellValue; 
					isFirstElement = false; 
					minSet = true;
				}
				colPtr = colPtr->getNext(); 
			}

			rowPtr = rowPtr->getBelow(); 
		}

		if (!minSet) {
			return false;
		}

		return minElement;
	 }

	string getAlignedString(string s, Alignment align, int len) {
		switch (align) {
			case Left:
				break;
			case Right: {
				int diff = len - s.length();
				for (int i = 0; i < diff; i++) {
					s = ' ' + s;
				}
				break;
			}
			case Center: {
				int diff = len - s.length();
				for (int i = 0; i < diff/2; i++) {
					s = ' ' + s;
				}
				break;
			}
		}

		return s;
	}

	void printCell(int x, int y, Cell<T>* cell) {
		string s;

		if (cell->getValueExists()) {
			s = getAlignedString(cell->getValue(), cell->getAlignment(), cellSize);
		}
		else
			s = "";

		if (cell != current)
			setColor(cell->getColor());
		else
			setColor(Green);
		printBoxAt(x, y, cellSize, s);
	}

	void printRow(int x, int y, Cell<T>* row) {
		while (row != nullptr) {
			printCell(x, y, row);

			x += cellSize + 4;

			row = row->getNext();
		}
	}

	void printGrid() {
		Cell<T>* temp = current;
		Cell<T>* rowPtr = nullptr;
		int x = 0, y = 0;

		while (temp->getPrev() != nullptr) {
			temp = temp->getPrev();
		}

		while (temp->getAbove() != nullptr) {
			temp = temp->getAbove();
		}

		rowPtr = temp;

		while (rowPtr != nullptr) {
			printRow(x, y, rowPtr);
			cout << endl;

			y += 3;

			rowPtr = rowPtr->getBelow();
		}
	}

	void moveCursor(Direction dir) {
		Cell<T>* next = nullptr;

		switch (dir) {
		case Up:
			next = current->getAbove();
			break;
		case Down:
			next = current->getBelow();
			break;
		case Prev:
			next = current->getPrev();
			break;
		case Next:
			next = current->getNext();
			break;
		}

		if (next != nullptr)
			current = next;
	}

	void setCurrentData(string s) {
		current->setValue(s);
	}

	void appendCurrentData(char c) {
		setCurrentData(current->getValue() + c);
	}

	void copy() {
		clipboard = current->getValue();
	}

	void cut() {
		copy();
		current->setValueExists(false);
	}

	void paste() {
		current->setValue(clipboard);
	}	

	void saveSheetInFile() {
		fstream file;
		file.open("Sheet.txt", ios::out);

		file << rowSize << endl;
		file << colSize << endl;

		Cell<T>* rowPtr = getRootCell();

		for (int i = 0; i < rowSize; i++) {
			Cell<T>* colPtr = rowPtr;

			for (int j = 0; j < colSize; j++) {
				if (!colPtr->getValueExists()) {
					file << "";
				}
				else {
					file << colPtr->getValue();
				}

				file << '|' << colPtr->getColor() << '|' << colPtr->getAlignment() << '|' << colPtr->getDataType() << ',';

				colPtr = colPtr->getNext();
			}

			file << endl;
			rowPtr = rowPtr->getBelow();
		}

		file.close();
	}

	string getField(string record, int field, char delim = ',') {
		int commaCount = 0;
		string item;

		for (int idx = 0; idx < record.length(); idx++){
			if (record[idx] == delim){
				commaCount = commaCount + 1;
			}

			else if (commaCount == field){
				item = item + record[idx];
			}
		}

		return item;
	}

	void readFromFile() {
		string record, line;
		fstream data;

		system("cls");
		data.open("Sheet.txt", ios::in);

		data >> rowSize;
		data >> colSize;

		makeInitialGrid(rowSize, colSize);

		Cell<T>* rowPtr = getRootCell();

		for (int i = 0; i < rowSize; i++) {
			Cell<T>* colPtr = rowPtr;
			getline(data >> ws, line);

			for (int j = 0; j < colSize; j++) {
				record = getField(line, j);

				colPtr->setValue(getField(record, 0, '|'));
				colPtr->setColor((Color)stoi(getField(record, 1, '|')));
				colPtr->setAlignment((Alignment)stoi(getField(record, 2, '|')));
				colPtr->setDataType((Type)stoi(getField(record, 3, '|')));

				if (colPtr->getValue() == "")
					colPtr->setValueExists(false);

				colPtr = colPtr->getNext();
			}

			rowPtr = rowPtr->getBelow();
		}
	}
};