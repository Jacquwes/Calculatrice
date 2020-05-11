#pragma once

#include <Windows.h>

LRESULT CALLBACK WndProc(
	_In_ HWND hWnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
);

wchar_t* stringToTchar(const char* string);

struct buttonsStruct
{
	HWND Clear;
	HWND OpenParenthese;
	HWND CloseParenthese;
	HWND AND;
	HWND NOT;
	HWND LeftShift;
	HWND RightShift;
	HWND OR;
	HWND XOR;
	HWND Euler;
	HWND Exponential;
	HWND NaturalLogartithm;
	HWND Logarithm;
	HWND Root;
	HWND SquareRoot;
	HWND CubicRoot;
	HWND Exponentiation;
	HWND Pi;
	HWND zero;
	HWND one;
	HWND two;
	HWND three;
	HWND four;
	HWND five;
	HWND six;
	HWND seven;
	HWND eight;
	HWND nine;
	HWND Dot;
	HWND Multiply;
	HWND Divide;
	HWND Add;
	HWND Substract;
	HWND Equal;
};
HWND display;

buttonsStruct buttons;

const std::vector<std::vector<const char*>> buttonsText
{
	{"C"},
	{"(", ")", "AND", "NOT"},
	{"<<",">>","OR", "XOR"},
	{"e", "exp", "ln", "log"},
	{"rt", "sqrt", "cbrt", "^"},
	{"pi"},
	{"7", "8", "9", "*"},
	{"4", "5", "6", "/"},
	{"1", "2", "3", "+"},
	{".", "0", "=", "-"}
};
