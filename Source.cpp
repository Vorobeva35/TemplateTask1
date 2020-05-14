#include <iostream>
#include "pStackEx.h"
#include <conio.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int N1, N2;

	cout << "¬ведите размер первого стека: ";
	cin >> N1;

	if (N1 < 0) N1 *= -1;

	pStack <int> Stack1(N1);

	for (int i = 0; i < N1; i++)
	{
		int temp;
		cout << "¬ведите " << i << " элемент стека (целое число): ";
		cin >> temp;
		Stack1.push(temp);
	}

	cout << "¬ведите размер второго стека: ";
	cin >> N2;

	if (N2 < 0) N2 *= -1;

	pStack <int> Stack2(N2);

	for (int i = 0; i < N2; i++)
	{
		int temp;
		cout << "¬ведите " << i << " элемент стека (целое число): ";
		cin >> temp;
		Stack2.push(temp);
	}

	pStack <int> Stack3(Stack1, Stack2);

	cout << endl;
	cout << "Ёлементы первого стека: " << endl;

	while (!Stack1.empty()) cout << Stack1.pop() << endl;

	cout << endl;
	cout << "Ёлементы второго стека: " << endl;

	while (!Stack2.empty()) cout << Stack2.pop() << endl;

	cout << endl;
	cout << "Ёлементы стека, который был получен путЄм объединени€ первого и второго: " << endl;

	while (!Stack3.empty()) cout << Stack3.pop() << endl;

	cout << "Ќажмите любую клавишу...";
	_getch();

	return 0;
}