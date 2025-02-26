#include <iostream>
#include <windows.h> 
#include <locale>

using namespace std;
static unsigned int id_student = 1;
static unsigned int sizeBase = 0;
static unsigned int sizeBaseMax = 100;

#pragma region Структуры
// Структура для хранения информации об ученике
struct Student
{
	unsigned int id;// Id студента
	string surname;// Фамилия
	string name;// Имя
	string campus;// Кампус
	string direction;// Направление
	string group;// Группа
	unsigned int visiting;// Количество посещений
};

struct ListStudents
{
	string surname;// Фамилия
	ListStudents* nextSurname;//След узел Фамилия
	unsigned int visiting;// Посещения
	ListStudents* nextVisiting;//След узел Посещения
	unsigned int index;// Id в базовом массиве
};
#pragma endregion

#pragma region Заполнение Базового массива


Student InputStudentFromClava()//Считывание Студентов с клавиатуры
{
	cout << "Данные " << id_student << "-ого студента" << endl;
	Student student;
	student.id = id_student++;
	cout << "Введите фамилию: ";
	cin >> student.surname;
	cout << "Введите имя: ";
	cin >> student.name;
	cout << "Введите кампус(Москва, Санкт-Петербург, Нижний Новгород, Пермь):";
	cin >> student.campus;
	cout << "Введите направление: ";
	cin >> student.direction;
	cout << "Введите группу: ";
	cin >> student.group;
	cout << "Введите количество посещений(целое число): ";
	cin >> student.visiting;
	return student;
}

void InputBaseStudentsFromClava(Student* students)
{
	for (int i = 0; i < sizeBase; ++i)
	{
		students[i] = InputStudentFromClava();
	}
}

#pragma endregion

#pragma region Создание списка
void InsertStudentIncrease(ListStudents*& headSurnameIncrease, ListStudents*& headVisitingIncrease, string surname, unsigned int id, unsigned int visiting)
{
	ListStudents* newNode = new ListStudents();
	newNode->index = id;
	newNode->surname = surname;
	newNode->visiting = visiting;
	newNode->nextSurname = nullptr;
	newNode->nextVisiting = nullptr;
	if (!headSurnameIncrease || surname < headSurnameIncrease->surname)
	{
		newNode->nextSurname = headSurnameIncrease;
		headSurnameIncrease = newNode;
	}
	else
	{
		ListStudents* current = headSurnameIncrease;
		while (current->nextSurname && current->nextSurname->surname <= surname)
		{
			current = current->nextSurname;
		}
		newNode->nextSurname = current->nextSurname;
		current->nextSurname = newNode;
	}

	if (!headVisitingIncrease || visiting < headVisitingIncrease->visiting)
	{
		newNode->nextVisiting = headVisitingIncrease;
		headVisitingIncrease = newNode;
	}
	else
	{
		ListStudents* current = headVisitingIncrease;
		while (current->nextVisiting && current->nextVisiting->visiting <= visiting)
		{
			current = current->nextVisiting;
		}
		newNode->nextVisiting = current->nextVisiting;
		current->nextVisiting = newNode;
	}

}

void BuildListStudentsIncrease(Student* studentsBase, unsigned int sizeBase, ListStudents*& headSurnameIncrease, ListStudents*& headVisitingIncrease)
{
	for (unsigned int i = 0; i < sizeBase; i++)
	{
		InsertStudentIncrease(headSurnameIncrease, headVisitingIncrease, studentsBase[i].surname, studentsBase[i].id, studentsBase[i].visiting);
	}
}

void InsertStudentDecrease(ListStudents*& headSurnameDecrease, ListStudents*& headVisitingDecrease, string surname, unsigned int id, unsigned int visiting)
{
	ListStudents* newNode = new ListStudents();
	newNode->index = id;
	newNode->surname = surname;
	newNode->visiting = visiting;
	newNode->nextSurname = nullptr;
	newNode->nextVisiting = nullptr;
	if (!headSurnameDecrease || surname > headSurnameDecrease->surname)
	{
		newNode->nextSurname = headSurnameDecrease;
		headSurnameDecrease = newNode;
	}
	else
	{
		ListStudents* current = headSurnameDecrease;
		while (current->nextSurname && current->nextSurname->surname > surname)
		{
			current = current->nextSurname;
		}
		newNode->nextSurname = current->nextSurname;
		current->nextSurname = newNode;
	}

	if (!headVisitingDecrease || visiting > headVisitingDecrease->visiting)
	{
		newNode->nextVisiting = headVisitingDecrease;
		headVisitingDecrease = newNode;
	}
	else
	{
		ListStudents* current = headVisitingDecrease;
		while (current->nextVisiting && current->nextVisiting->visiting > visiting)
		{
			current = current->nextVisiting;
		}
		newNode->nextVisiting = current->nextVisiting;
		current->nextVisiting = newNode;
	}
}

void BuildListStudentsDecrease(Student* studentsBase, unsigned int sizeBase, ListStudents*& headSurnameDecrease, ListStudents*& headVisitingDecrease)
{
	for (unsigned int i = 0; i < sizeBase; i++)
	{
		InsertStudentDecrease(headSurnameDecrease, headVisitingDecrease, studentsBase[i].surname, studentsBase[i].id, studentsBase[i].visiting);
	}
}

#pragma endregion

#pragma region Базовый Вывод

void PrintStudents(Student student)//Вывод одного студента
{
	cout << "====================" << "\nID: " << student.id << "\nФамилия: " << student.surname << "\nИмя: " << student.name
		<< "\nКампус: " << student.campus << "\nНаправление: " << student.direction
		<< "\nГруппа: " << student.group << "\nПосещения: " << student.visiting << endl;
	cout << "====================" << endl;
}

void PrintStudents(Student* students)//Вывод студентов из базового массива
{
	for (int i = 0; i < sizeBase; i++)
	{
		Student student = students[i];
		PrintStudents(student);
	}
	cout << "====================" << endl;
}

#pragma endregion

#pragma region Поиск

Student FindStudentInBase(Student* students, int left, int right, int keyIndex)
{
	int mid = left + (right - left) / 2;
	if (students[mid].id == keyIndex)
	{
		return students[mid];
	}
	else if (students[mid].id < keyIndex)
	{
		return FindStudentInBase(students, mid + 1, right, keyIndex);
	}
	else
	{
		return FindStudentInBase(students, left, mid - 1, keyIndex);
	}
};

void SearchStudent(ListStudents* curentStudent, Student* students, string keySurnmae, bool& isFound)
{
	if (curentStudent == nullptr)
	{
		return;
	}
	if (curentStudent->surname == keySurnmae)
	{
		Student student = FindStudentInBase(students, 0, sizeBase, curentStudent->index);
		PrintStudents(student);
		isFound = true;
	}
	SearchStudent(curentStudent->nextSurname, students, keySurnmae, isFound);
}

void SearchStudent(ListStudents* curentStudent, Student* students, int keyVisiting, bool& isFound)
{
	if (curentStudent == nullptr)
	{
		return;
	}
	if (curentStudent->visiting == keyVisiting)
	{
		Student student = FindStudentInBase(students, 0, sizeBase, curentStudent->index);
		PrintStudents(student);
		isFound = true;
	}
	SearchStudent(curentStudent->nextVisiting, students, keyVisiting, isFound);
}
void IterativePrintFindStudents(ListStudents* head, Student* students, string keySurname)
{
	ListStudents* current = head;
	bool found = false;
	while (current != nullptr)
	{
		if (current->surname == keySurname)
		{
			found = true;
			Student student = FindStudentInBase(students, 0, sizeBase, current->index);
			PrintStudents(student);
		}
		current = current->nextSurname;
	}
	if (!found)
	{
		cout << "Студенты с фамилией " << keySurname << " не найдены." << endl;
	}
}


void IterativePrintFindStudents(ListStudents* head, Student* students, int keyVisiting)
{
	ListStudents* current = head;
	bool found = false;
	while (current != nullptr)
	{
		if (current->visiting == keyVisiting)
		{
			found = true;
			Student student = FindStudentInBase(students, 0, sizeBase, current->index);
			PrintStudents(student);
		}
		current = current->nextVisiting;
	}
	if (!found)
	{
		cout << "Студенты с с кол-вом посещений " << keyVisiting << " не найдены." << endl;
	}
}
#pragma endregion

#pragma region Вывод информации


void PrintStudentsSurnameA_Z(ListStudents* headSurname, Student* students)
{
	ListStudents* currentStudent = headSurname;
	while (currentStudent)
	{
		PrintStudents(FindStudentInBase(students, 0, sizeBase, currentStudent->index));
		currentStudent = currentStudent->nextSurname;
	}
}

void PrintStudentsSurnameZ_A(ListStudents* headSurname, Student* students)
{
	ListStudents* currentStudent = headSurname;
	while (currentStudent)
	{
		PrintStudents(FindStudentInBase(students, 0, sizeBase, currentStudent->index));
		currentStudent = currentStudent->nextSurname;
	}
}

void PrintStudentsVisitingIncrease(ListStudents* headVisiting, Student* students)
{
	ListStudents* currentStudent = headVisiting;
	while (currentStudent)
	{
		PrintStudents(FindStudentInBase(students, 0, sizeBase, currentStudent->index));
		currentStudent = currentStudent->nextVisiting;
	}
}

void PrintStudentsVisitingDecrease(ListStudents* headVisiting, Student* students)
{
	ListStudents* currentStudent = headVisiting;
	while (currentStudent)
	{
		PrintStudents(FindStudentInBase(students, 0, sizeBase, currentStudent->index));
		currentStudent = currentStudent->nextVisiting;
	}
}

void PrintFindStudent(ListStudents* headSurname, Student* students, string keySurname)
{
	bool isFound = false;
	SearchStudent(headSurname, students, keySurname, isFound);
	if (!isFound)
	{
		cout << "Студенты с фамилией '" << keySurname << "' не найдены" << endl;
	}
}

void PrintFindStudent(ListStudents* headSurname, Student* students, int keyVisiting)
{
	bool isFound = false;
	SearchStudent(headSurname, students, keyVisiting, isFound);
	if (!isFound)
	{
		cout << "Студенты с кол-вом посещений '" << keyVisiting << "' не найдены" << endl;
	}
}

#pragma endregion

#pragma region Добавление Студента
void InsertNewStudentIncrease(Student* studentsBase, ListStudents* headSurname, ListStudents* headVisiting, Student student)
{
	InsertStudentIncrease(headSurname, headVisiting, student.surname, student.id, student.visiting);
}

void InsertNewStudentDecrease(Student* studentsBase, ListStudents* headSurname, ListStudents* headVisiting, Student student)
{
	InsertStudentDecrease(headSurname, headVisiting, student.surname, student.id, student.visiting);
}
#pragma endregion

#pragma region Удаление информации

void DeleteBySurnameIncrease(ListStudents*& headSurname, ListStudents*& headVisiting, unsigned int id, string keySurname)
{
	ListStudents* currentSurname = headSurname;
	ListStudents* prevSurname = nullptr;
	while (currentSurname != nullptr)
	{
		if (currentSurname->index == id && currentSurname->surname == keySurname)
		{
			if (prevSurname == nullptr)
			{
				headSurname = currentSurname->nextSurname;
			}
			else
			{
				prevSurname->nextSurname = currentSurname->nextSurname;
			}
			ListStudents* currentVisiting = headVisiting;
			ListStudents* prevVisiting = nullptr;
			while (currentVisiting != nullptr)
			{
				if (currentVisiting == currentSurname)
				{
					if (prevVisiting == nullptr)
					{
						headVisiting = currentVisiting->nextVisiting;
					}
					else
					{
						prevVisiting->nextVisiting = currentVisiting->nextVisiting;
					}
					delete currentSurname;
					return;
				}
				prevVisiting = currentVisiting;
				currentVisiting = currentVisiting->nextVisiting;
			}
		}
		prevSurname = currentSurname;
		currentSurname = currentSurname->nextSurname;
	}
}

void DeleteBySurnameDecrease(ListStudents*& headSurname, ListStudents*& headVisiting, unsigned int id, string keySurname)
{
	ListStudents* currentSurname = headSurname;
	ListStudents* prevSurname = nullptr;
	while (currentSurname != nullptr)
	{
		if (currentSurname->index == id && currentSurname->surname == keySurname)
		{
			if (prevSurname == nullptr)
			{
				headSurname = currentSurname->nextSurname;
			}
			else
			{
				prevSurname->nextSurname = currentSurname->nextSurname;
			}
			ListStudents* currentVisiting = headVisiting;
			ListStudents* prevVisiting = nullptr;

			while (currentVisiting != nullptr)
			{
				if (currentVisiting == currentSurname)
				{
					if (prevVisiting == nullptr)
					{
						headVisiting = currentVisiting->nextVisiting;
					}
					else
					{
						prevVisiting->nextVisiting = currentVisiting->nextVisiting;
					}
					delete currentSurname;
					return;
				}
				prevVisiting = currentVisiting;
				currentVisiting = currentVisiting->nextVisiting;
			}
		}
		prevSurname = currentSurname;
		currentSurname = currentSurname->nextSurname;
	}
}

void DeleteByVisitingIncrease(ListStudents*& headSurname, ListStudents*& headVisiting, unsigned int id, unsigned int keyVisiting)
{
	ListStudents* currentVisiting = headVisiting;
	ListStudents* prevVisiting = nullptr;
	while (currentVisiting != nullptr)
	{
		if (currentVisiting->index == id && currentVisiting->visiting == keyVisiting)
		{
			if (prevVisiting == nullptr)
			{
				headVisiting = currentVisiting->nextVisiting;
			}
			else
			{
				prevVisiting->nextVisiting = currentVisiting->nextVisiting;
			}
			ListStudents* currentSurname = headSurname;
			ListStudents* prevSurname = nullptr;

			while (currentSurname != nullptr)
			{
				if (currentSurname == currentVisiting)
				{
					if (prevSurname == nullptr)
					{
						headSurname = currentSurname->nextSurname;
					}
					else
					{
						prevSurname->nextSurname = currentSurname->nextSurname;
					}
					delete currentVisiting;
					return;
				}
				prevSurname = currentSurname;
				currentSurname = currentSurname->nextSurname;
			}
		}
		prevVisiting = currentVisiting;
		currentVisiting = currentVisiting->nextVisiting;
	}
}

void DeleteByVisitingDecrease(ListStudents*& headSurname, ListStudents*& headVisiting, unsigned int id, unsigned int keyVisiting)
{
	ListStudents* currentVisiting = headVisiting;
	ListStudents* prevVisiting = nullptr;
	while (currentVisiting != nullptr)
	{
		if (currentVisiting->index == id && currentVisiting->visiting == keyVisiting)
		{
			if (prevVisiting == nullptr)
			{
				headVisiting = currentVisiting->nextVisiting;
			}
			else
			{
				prevVisiting->nextVisiting = currentVisiting->nextVisiting;
			}
			ListStudents* currentSurname = headSurname;
			ListStudents* prevSurname = nullptr;

			while (currentSurname != nullptr)
			{
				if (currentSurname == currentVisiting)
				{
					if (prevSurname == nullptr)
					{
						headSurname = currentSurname->nextSurname;
					}
					else
					{
						prevSurname->nextSurname = currentSurname->nextSurname;
					}
					delete currentVisiting;
					return;
				}
				prevSurname = currentSurname;
				currentSurname = currentSurname->nextSurname;
			}
		}
		prevVisiting = currentVisiting;
		currentVisiting = currentVisiting->nextVisiting;
	}
}


Student* DeleteStudentVisiting(Student* students, ListStudents*& headSurnameIncrease, ListStudents*& headVisitingIncrease, ListStudents*& headSurnameDecrease, ListStudents*& headVisitingDecrease)
{
	int visiting;
	int ID;
	string surnameOfDeletedStudent;
	string nameOfDeletedStudent;
	cout << "Введите кол-во посещений у студента, Которого хотите исключить из ВШЭ): ";
	cin >> visiting;//Прекращать работу или нет???
	PrintFindStudent(headVisitingIncrease, students, visiting);
	int action;
	cout << "Видите ли Вы студента для удаления выше?(1-Да, 0-Нет): ";
	cin >> action;
	switch (action)
	{
	case 1:
	{
		cout << "Введите ID студента, Которого хотите исключить из ВШЭ): ";
		cin >> ID;
		Student* newStudents = new Student[sizeBase - 1];
		for (int i = 0, j = 0; i < sizeBase; i++)
		{
			if (!(students[i].id == ID))
			{
				newStudents[j++] = students[i];
			}
			else
			{
				surnameOfDeletedStudent = students[i].surname;
				nameOfDeletedStudent = students[i].name;
			}
		}
		delete[] students;
		sizeBase--;
		DeleteByVisitingIncrease(headSurnameIncrease, headVisitingIncrease, ID, visiting);
		DeleteByVisitingDecrease(headSurnameDecrease, headVisitingDecrease, ID, visiting);
		cout << "Студент " << surnameOfDeletedStudent << " " << nameOfDeletedStudent << " Успешно удалён" << endl;
		return newStudents;
	}
	case 0:
	{
		Student* newStudents = new Student[sizeBase];
		for (int i = 0; i < sizeBase; i++)
		{
			newStudents[i] = students[i];
		}
		cout << "Нет элемента для удаления, попробуйте ещё раз";
		delete[] students;
		return newStudents;
	}
	}
}

Student* DeleteStudentSurnmame(Student* students, ListStudents*& headSurnameIncrease, ListStudents*& headVisitingIncrease, ListStudents*& headSurnameDecrease, ListStudents*& headVisitingDecrease)
{
	string surname;
	int ID;
	string surnameOfDeletedStudent;
	string nameOfDeletedStudent;
	cout << "Введите Фамилию студента, Которого хотите исключить из ВШЭ): ";
	cin >> surname;//Прекращать работу или нет???
	PrintFindStudent(headVisitingIncrease, students, surname);
	int action;
	cout << "Видите ли Вы студента для удаления выше?(1-Да, 0-Нет): ";
	cin >> action;
	switch (action)
	{
	case 1:
	{
		cout << "Введите ID студента, Которого хотите исключить из ВШЭ): ";
		cin >> ID;
		Student* newStudents = new Student[sizeBase - 1];
		for (int i = 0, j = 0; i < sizeBase; i++)
		{
			if (!(students[i].id == ID))
			{
				newStudents[j++] = students[i];
			}
			else
			{
				surnameOfDeletedStudent = students[i].surname;
				nameOfDeletedStudent = students[i].name;
			}
		}
		delete[] students;
		sizeBase--;
		DeleteBySurnameIncrease(headSurnameIncrease, headVisitingIncrease, ID, surname);
		DeleteBySurnameDecrease(headSurnameDecrease, headVisitingDecrease, ID, surname);
		cout << "Студент " << surnameOfDeletedStudent << " " << nameOfDeletedStudent << " Успешно удалён" << endl;
		return newStudents;
	}
	case 0:
	{
		Student* newStudents = new Student[sizeBase];
		for (int i = 0; i < sizeBase; i++)
		{
			newStudents[i] = students[i];
		}
		cout << "Нет элемента для удаления, попробуйте ещё раз";
		delete[] students;
		return newStudents;
	}
	}
}
void ClearList(ListStudents*& head)
{
	while (head)
	{
		ListStudents* temp = head;
		head = head->nextSurname;
		delete temp;
	}
}
#pragma endregion

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Student* studentsBase = nullptr;
	ListStudents* headSurnameIncrease = nullptr;
	ListStudents* headVisitingIncrease = nullptr;
	ListStudents* headSurnameDecrease = nullptr;
	ListStudents* headVisitingDecrease = nullptr;
	sizeBase = 9;

	cout << "Использовать данные по умолчанию? (1 - Да, Другое - Нет): ";//Если время будет через switch case
	int choice;
	cin >> choice;



	if (choice == 1)
	{
		studentsBase = new Student[sizeBaseMax]
		{
			{ 1, "Зеленина", "Анастасия", "Москва", "ПИ", "23-7", 30 },
			{ 2, "Бочкарев", "Игнат", "Нижний Новгород", "Э", "24-4", 15 },
			{ 3, "Ахматзянов", "Адис", "Москва", "МБ", "23-3", 15 },
			{ 4, "Косвинцев", "Степан", "Пермь", "РИС", "23-1", 0 },
			{ 5, "Вронский", "Михаил", "Санкт-Петербург", "МБ", "24-5", 5 },
			{ 6, "Катаев", "Денис", "Нижний Новгород", "БИ", "24-5", 2 },
			{ 7, "Чазов", "Вадим", "Пермь", "РИС", "24-2", 15 },
			{ 8, "Косвинцев", "Роман", "Пермь", "РИС", "24-1", 26 },
			{ 9, "Кононов", "Максим", "Санкт-Петербург", "Д", "24-6", 3 },
		};
		id_student = 10;
	}
	else
	{
		cout << "Введите количество студентов: ";
		cin >> sizeBase;//Добавить Проверку на <1
		studentsBase = new Student[sizeBaseMax];
		InputBaseStudentsFromClava(studentsBase);
	}
	BuildListStudentsIncrease(studentsBase, sizeBase, headSurnameIncrease, headVisitingIncrease);
	BuildListStudentsDecrease(studentsBase, sizeBase, headSurnameDecrease, headVisitingDecrease);

	bool isRunning = true;
	int action;
	while (isRunning)
	{
		cout << "\nМеню:\n";
		cout << "1. Показать базовый массив\n";
		cout << "2. Показать список студентов по фамилиям от А до Я\n";
		cout << "3. Показать список студентов по фамилиям от Я до А\n";
		cout << "4. Показать список студентов по посещениям Возрастание\n";
		cout << "5. Показать список студентов по посещениям Убывание\n";
		cout << "6. Добавить нового студента\n";
		cout << "7. Найти студента по Фамилии\n";
		cout << "8. Найти студента по Посещениям\n";
		cout << "9. Удалить студента по фамилии\n";
		cout << "10. Удалить студента по посещениям\n";
		cout << "0. Выход\n";
		cout << "66 - Проверка реализации Рекурсивной и Итеративной функции поиска Посещений\n";
		cout << "77 - Проверка реализации Рекурсивной и Итеративной функции поиска Фамилии\n";
		cout << "Выберите действие(Число): ";
		cin >> action;

		switch (action)
		{
		case 1:
			PrintStudents(studentsBase);
			break;
		case 2:
			PrintStudentsSurnameA_Z(headSurnameIncrease, studentsBase);
			break;
		case 3:
			PrintStudentsSurnameZ_A(headSurnameDecrease, studentsBase);
			break;
		case 4:
			PrintStudentsVisitingIncrease(headVisitingIncrease, studentsBase);
			break;
		case 5:
			PrintStudentsVisitingDecrease(headVisitingDecrease, studentsBase);
			break;
		case 6:
			if (sizeBase + 1 > sizeBaseMax)
			{
				cout << "Максимальное кол-во объектов в базе данных" << endl;
			}
			else
			{
				studentsBase[sizeBase] = InputStudentFromClava();
				sizeBase++;
				InsertNewStudentIncrease(studentsBase, headSurnameIncrease, headVisitingIncrease, studentsBase[sizeBase - 1]);
				InsertNewStudentDecrease(studentsBase, headSurnameDecrease, headVisitingDecrease, studentsBase[sizeBase - 1]);
			}
			break;
		case 7:
		{
			string studentName;
			cout << "Введите фамилию студента, которого хотите найти: ";
			cin >> studentName;
			PrintFindStudent(headSurnameIncrease, studentsBase, studentName);
			break;
		}
		case 8:
		{
			int studentVisiting;
			cout << "Введите кол-во посещений студентов, по которым хотите найти: ";
			cin >> studentVisiting;
			PrintFindStudent(headVisitingIncrease, studentsBase, studentVisiting);
			break;
		}
		case 9:
		{
			if (sizeBase < 1)
			{
				cout << "Нельзя удалять элементы из пустого массива";
			}
			else
			{
				studentsBase = DeleteStudentSurnmame(studentsBase, headSurnameIncrease, headVisitingIncrease, headSurnameDecrease, headVisitingDecrease);
			}
			break;
		}
		case 10:
		{
			if (sizeBase < 1)
			{
				cout << "Нельзя удалять элементы из пустого массива";
			}
			else
			{
				studentsBase = DeleteStudentVisiting(studentsBase, headSurnameIncrease, headVisitingIncrease, headSurnameDecrease, headVisitingDecrease);
			}
			break;
		}
		case 66:
		{
			PrintFindStudent(headSurnameIncrease, studentsBase, "Косвинцев");
			cout << "Проверка===========================================Проверка" << endl;
			IterativePrintFindStudents(headSurnameIncrease, studentsBase, "Косвинцев");
			break;
		}
		case 77:
		{
			PrintFindStudent(headVisitingIncrease, studentsBase, 15);
			cout << "Проверка===========================================Проверка" << endl;
			IterativePrintFindStudents(headVisitingIncrease, studentsBase, 15);
			break;
		}
		case 0:
			delete[] studentsBase;
			isRunning = false;
			ClearList(headSurnameDecrease);
			ClearList(headSurnameIncrease);
			ClearList(headVisitingDecrease);
			ClearList(headVisitingIncrease);

			cout << "Выход из программы." << endl;
			break;
		default:
			cout << "Неверный выбор. Попробуйте снова." << endl;
		}
	}
	return 0;
}