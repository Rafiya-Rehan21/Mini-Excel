#pragma once
#include <string>
#include "CellExtras.cpp"

template<typename T>

class Cell {
private:
	T value;

	Cell* prev  = nullptr;
	Cell* next  = nullptr;
	Cell* above = nullptr;
	Cell* below = nullptr;
	bool valueExists = true;

	Color color = White;
	Alignment alignment = Center;
	Type dataType = String;
	

public:

	Cell(T value) {
		setValue(value);
	}

	Cell() {
		setValueExists(false);
	}

	void setValue(T val) {
		setValueExists(true);
		this->value = val;
	}

	T getValue() {
		return value;
	}

	void setPrev(Cell* prev) {
		this->prev = prev;
	}

	Cell* getPrev() {
		return prev;
	}

	void setNext(Cell* next) {
		this->next = next;
	}

	Cell* getNext() {
		return next;
	}

	void setBelow(Cell* below) {
		this->below = below;
	}

	Cell* getBelow() {
		return below;
	}

	void setAbove(Cell* above) {
		this->above = above;
	}

	Cell* getAbove() {
		return above;
	}

	void setValueExists(bool val) {
		valueExists = val;
	}

	bool getValueExists() {
		return valueExists;
	}

	void setColor(Color color) {
		this->color = color;
	}

	Color getColor() {
		return color;
	}

	void setAlignment(Alignment align) {
		this->alignment = align;
	}

	Alignment getAlignment() {
		return alignment;
	}

	void setDataType(Type type) {
		this->dataType = type;
	}

	Type getDataType() {
		return dataType;
	}
};