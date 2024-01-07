#include "Iterator.cpp"

template<typename T>
class ReverseIterator : public Iterator<T> {
	using Iterator<T>::currentCell;

public:
	ReverseIterator(Cell<T>* cell) : Iterator<T>(cell) {}

	ReverseIterator operator++(int) {
		currentCell = currentCell->getPrev();
		return ReverseIterator<T>(currentCell);
	}
};