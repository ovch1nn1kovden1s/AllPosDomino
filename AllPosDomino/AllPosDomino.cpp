#include <iostream>

using namespace std;

class Node {
public:
	int data[2];
	Node* prev, * next;

public:
	Node(int data[2]) {
		this->data[0] = data[0];
		this->data[1] = data[1];
		this->prev = this->next = NULL;
	}
};

class LinkedList {
public:
	Node* head, * tail;

public:
	LinkedList() {
		head = NULL;
		tail = NULL;
	}

	// Добавление элемента в начало списка
	Node* push_front(int data[2]) {
		Node* ptr = new Node(data);
		ptr->next = head;
		if (head != NULL)
			head->prev = ptr;
		if (tail == NULL)
			tail = ptr;
		head = ptr;

		return ptr;
	}

	// Добавление элемента в конец списка
	Node* push_back(int data[2]) {
		Node* ptr = new Node(data);
		ptr->prev = tail;
		if (tail != NULL)
			tail->next = ptr;
		if (head == NULL)
			head = ptr;
		tail = ptr;

		return ptr;
	}

	// Удаление элемента с начала списка
	void pop_front() {
		if (head == NULL) return;

		Node* ptr = head->next;
		if (ptr != NULL)
			ptr->prev = NULL;
		else
			tail = NULL;

		delete head;
		head = ptr;
	}
};

// Вывод списка
void print(LinkedList list) {
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
		cout << "[" << ptr->data[0] << "|" << ptr->data[1] << "] ";
	cout << endl;
}

// Поиск возможных комбинаций
void search(LinkedList array, int j, int k, int n, int* arrayMark, LinkedList& outputD, int m, int leftD, int rightD, int& leftF, int& rightB) {
	arrayMark[k] = 1;
	int dom[2];

	// Ставим домино правильной стороной
	if (m == 0) {
		dom[0] = leftD;
		dom[1] = rightD;
	}
	else {
		dom[0] = rightD;
		dom[1] = leftD;
	}

	// Ставим кость в конец или начало списка
	if (j == 0) {
		outputD.push_front(dom);
		leftF = dom[0];
	}
	else {
		outputD.push_back(dom);
		rightB = dom[1];
	}

	// Рекурсивно подбираем новые кости
	int newIndex = 0;
	for (Node* ptr = array.head; ptr != NULL; ptr = ptr->next) {
		for (int j = 0; j < 2; j++) {
			if (arrayMark[newIndex] != 1) {

				int leftP;
				int rightP;

				// Ставим новую кость разными сторонами
				if (j == 0) {
					leftP = ptr->data[0];
					rightP = ptr->data[1];
				}
				else {
					leftP = ptr->data[1];
					rightP = ptr->data[0];
				}

				if (leftF == rightP) {
					search(array, 0, newIndex, n, arrayMark, outputD, j, ptr->data[0], ptr->data[1], leftF, rightB);
				}
				if (rightB == leftP) {
					search(array, 1, newIndex, n, arrayMark, outputD, j, ptr->data[0], ptr->data[1], leftF, rightB);
				}

			}
		}
		newIndex++;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	LinkedList inputD;
	bool flag = true;
	int n;
	cout << "Введите количество костей домино: "; cin >> n;
	for (int i = 0; i < n; i++) {
		int dice[2];
		int left_dots, right_dots;
		cout << "Введите левую сторону " << i + 1 << " кости: ";
		cin >> left_dots;
		cout << "Введите правую сторону " << i + 1 << " кости: ";
		cin >> right_dots;

		// Проверка введеных сторон
		if ((left_dots < 0) || (left_dots > 6) || (right_dots < 0) || (right_dots > 6))
		{
			flag = false;
			break;
		}

		// Проверка на отсутвие совпадений в спике
		for (Node* ptr = inputD.head; ptr != NULL; ptr = ptr->next) {
			if (((left_dots == ptr->data[0]) && (right_dots == ptr->data[1])) || ((left_dots == ptr->data[1]) && (right_dots == ptr->data[0]))) {
				flag = false;
				break;
			}
		}

		dice[0] = left_dots;
		dice[1] = right_dots;
		inputD.push_back(dice);
	}
	cout << endl << "Введенные кости: ";
	print(inputD);
	cout << endl;

	LinkedList outputD;
	int leftF = 1000;
	int rightB = 1000;
	if (flag) {
		int index = 0;
		for (Node* ptr = inputD.head; ptr != NULL; ptr = ptr->next) {

			for (int m = 0; m < 2; m++) {
				int* arrayMark = new int[n];
				search(inputD, 1, index, n, arrayMark, outputD, m, ptr->data[0], ptr->data[1], leftF, rightB);
				cout << "Начинаем с кости [" << ptr->data[0] << "|" << ptr->data[1] << "] : ";
				print(outputD);

				// очищяем список
				while (outputD.head != NULL) {
					outputD.pop_front();
				}

			}

			index++;
		}

	}
	else {
		cout << "Некорректные входные данные" << endl;
	}

	return 0;
}