#pragma once
#include "Cell.cpp"

template<typename T>
class Iterator {
protected:
	Cell<T>* currentCell;

public:
	Iterator(Cell<T>* cell) {
		currentCell = cell;
	}

	//Iterator() {}

	Cell<T>* getCurrentCell() {
		return currentCell;
	}

	T operator*() const {
		return currentCell->getValue();
	}

	Iterator operator++(int) {
		currentCell = currentCell->getNext();
		return Iterator(currentCell);
	}

	friend bool operator ==(const Iterator<T>& first, const Iterator<T>& second) {
		return first.currentCell == second.currentCell;
	}

	friend bool operator !=(const Iterator<T>& first, const Iterator<T>& second) {
		return first.currentCell != second.currentCell;
	}
};