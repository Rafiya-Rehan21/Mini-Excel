#pragma once

#define RED 4
#define GREEN 2
#define BLUE 1

enum Color {
	Red = RED,
	Green = GREEN,
	Blue = BLUE,
	Cyan = BLUE | GREEN,
	White = BLUE | GREEN | RED
};

enum Alignment {
	Left,
	Right,
	Center
};

enum Direction {
	Up,
	Down,
	Prev,
	Next
};

enum Type {
	Int,
	Float,
	Char,
	String
};