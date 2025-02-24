#include <iostream>
#include <windows.h> 
#include <locale>

using namespace std;
static unsigned int id_student = 1;
static unsigned int sizeBase = 0;

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

struct TreeSurname
{
	string surname;// Фамилия
	unsigned int studentIndex;// Индекс в массиве
	TreeSurname* left;
	TreeSurname* right;
};

struct TreeVisiting
{
	unsigned int visiting;// Посещения
	unsigned int studentIndex; // Индекс в массиве
	TreeVisiting* left;
	TreeVisiting* right;
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

#pragma region Вставка узла
TreeSurname* InsertSurname(TreeSurname* node, string surname, int studentIndex)
{
	if (node == nullptr)
	{
		node = new TreeSurname();
		node->studentIndex = studentIndex;
		node->surname = surname;
		node->left = nullptr;
		node->right = nullptr;
	}
	else if (surname < node->surname)//Проверка меньше
	{
		node->left = InsertSurname(node->left, surname, studentIndex);
	}
	else if (surname >= node->surname)//Проверка больще = для одинаковых данных
	{
		node->right = InsertSurname(node->right, surname, studentIndex);
	}
	return node;
}

TreeVisiting* InsertVisiting(TreeVisiting* node, int visiting, int studentIndex)
{
	if (node == nullptr)
	{
		node = new TreeVisiting();
		node->studentIndex = studentIndex;
		node->visiting = visiting;
		node->left = nullptr;
		node->right = nullptr;
	}
	else if (visiting < node->visiting)//Проверка меньше
	{
		node->left = InsertVisiting(node->left, visiting, studentIndex);
	}
	else if (visiting >= node->visiting)//Проверка больше = для одинаковых данных
	{
		node->right = InsertVisiting(node->right, visiting, studentIndex);
	}
	return node;
}
#pragma endregion

#pragma region  Создание деревьев
TreeSurname* BuildTreeSurname(Student* students)
{
	TreeSurname* node = nullptr;
	for (int i = 0; i < sizeBase; i++)
	{
		node = InsertSurname(node, students[i].surname, students[i].id);
	}
	return node;
}

TreeVisiting* BuildTreeVisiting(Student* students)
{
	TreeVisiting* node = nullptr;
	for (int i = 0; i < sizeBase; i++)
	{
		node = InsertVisiting(node, students[i].visiting, students[i].id);
	}
	return node;
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

Student FindStudentInBase(Student* students, int left, int right, int keyIndex)//Бинарный поиск
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

void FindStudentIterative(TreeSurname* node, Student* students, string keySurname)
{
	bool isFind = false;
	while (node != nullptr)
	{
		if (keySurname < node->surname)
		{
			node = node->left;
		}
		else if (keySurname > node->surname)
		{
			node = node->right;
		}
		else
		{
			PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
			isFind = true;
			node = node->right;
		}
	}

	if (!isFind)
	{
		cout << "Студенты с фамилией '" << keySurname << "' не найдены" << endl;
	}
}

void FindStudentIterative(TreeVisiting* node, Student* students, int keyVisiting)
{
	bool isFind = false;
	while (node != nullptr)
	{
		if (keyVisiting < node->visiting)
		{
			node = node->left;
		}
		else if (keyVisiting > node->visiting)
		{
			node = node->right;
		}
		else
		{
			PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
			isFind = true;
			node = node->right;
		}
	}

	if (!isFind)
	{
		cout << "Студенты с кол-вом посещений '" << keyVisiting << "' не найдены" << endl;
	}
}

void SearchStudent(TreeSurname* node, Student* students, string keySurnmae, bool& isFound)
{
	if (node == nullptr)
	{
		return;
	}
	SearchStudent(node->left, students, keySurnmae, isFound);
	if (node->surname == keySurnmae)
	{
		PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
		isFound = true;
	}
	SearchStudent(node->right, students, keySurnmae, isFound);
}

void SearchStudent(TreeVisiting* node, Student* students, int keyVisiting, bool& isFound)
{
	if (node == nullptr)
	{
		return;
	}
	SearchStudent(node->left, students, keyVisiting, isFound);
	if (node->visiting == keyVisiting)
	{
		PrintStudents(students[node->studentIndex - 1]);
		isFound = true;
	}
	SearchStudent(node->right, students, keyVisiting, isFound);
}

TreeSurname* FindMin(TreeSurname* node)//Итерационный поиск
{
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}

TreeVisiting* FindMin(TreeVisiting* node)//Итерационный поиск
{
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}
#pragma endregion

#pragma region Вывод информации

void PrintStudentsSurnameA_Z(TreeSurname* node, Student* students)
{
	if (node != nullptr)
	{
		PrintStudentsSurnameA_Z(node->left, students);
		PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
		PrintStudentsSurnameA_Z(node->right, students);
	}
}

void PrintStudentsSurnameZ_A(TreeSurname* node, Student* students)
{
	if (node != nullptr)
	{
		PrintStudentsSurnameZ_A(node->right, students);
		PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
		PrintStudentsSurnameZ_A(node->left, students);
	}
}

void PrintStudentsVisitingIncrease(TreeVisiting* node, Student* students)
{
	if (node != nullptr)
	{
		PrintStudentsVisitingIncrease(node->left, students);
		PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
		PrintStudentsVisitingIncrease(node->right, students);
	}
}

void PrintStudentsVisitingDecrease(TreeVisiting* node, Student* students)
{
	if (node != nullptr)
	{
		PrintStudentsVisitingDecrease(node->right, students);
		PrintStudents(FindStudentInBase(students, 0, sizeBase, node->studentIndex));
		PrintStudentsVisitingDecrease(node->left, students);
	}
}

void PrintAllFindStudent(TreeSurname* node, Student* students, string keySurname)
{
	bool isFound = false;
	SearchStudent(node, students, keySurname, isFound);
	if (!isFound)
	{
		cout << "Студенты с фамилией '" << keySurname << "' не найдены" << endl;
	}
}

void PrintAllFindStudent(TreeVisiting* node, Student* students, int keyVisiting)
{
	bool isFound = false;
	SearchStudent(node, students, keyVisiting, isFound);
	if (!isFound)
	{
		cout << "Студенты с кол-вом посещений '" << keyVisiting << "' не найдены" << endl;
	}
}
#pragma endregion

#pragma region Удаление информации

TreeSurname* DeleteStudentTree(TreeSurname* node, string keySurname, int keyID)
{
	if (node == nullptr)
	{
		return node;
	}

	if (keySurname < node->surname)
	{
		node->left = DeleteStudentTree(node->left, keySurname, keyID);
	}
	else if (keySurname > node->surname)
	{
		node->right = DeleteStudentTree(node->right, keySurname, keyID);
	}
	else if (keySurname == node->surname && node->studentIndex != keyID)
	{
		node->right = DeleteStudentTree(node->right, keySurname, keyID);
	}
	else
	{
		if (node->left == nullptr)//Первый случай
		{
			TreeSurname* temp = node->right;
			delete node;
			return temp;
		}

		else if (node->right == nullptr)//Второй Случай
		{
			TreeSurname* temp = node->left;
			delete node;
			return temp;
		}
		else
		{
			TreeSurname* temp = FindMin(node->right);//Третий Случай
			node->surname = temp->surname;
			node->studentIndex = temp->studentIndex;
			node->right = DeleteStudentTree(node->right, temp->surname, temp->studentIndex);
		}
	}
	return node;
}

TreeVisiting* DeleteStudentTree(TreeVisiting* node, int keyVisiting, int keyID)
{
	if (node == nullptr)
	{
		return node;
	}

	if (keyVisiting < node->visiting)
	{
		node->left = DeleteStudentTree(node->left, keyVisiting, keyID);
	}
	else if (keyVisiting > node->visiting)
	{
		node->right = DeleteStudentTree(node->right, keyVisiting, keyID);
	}
	else if (keyVisiting == node->visiting && node->studentIndex != keyID)
	{
		node->right = DeleteStudentTree(node->right, keyVisiting, keyID);
	}
	else
	{
		if (node->left == nullptr)//Первый случай
		{
			TreeVisiting* temp = node->right;
			delete node;
			return temp;
		}

		else if (node->right == nullptr)//Второй Случай
		{
			TreeVisiting* temp = node->left;
			delete node;
			return temp;
		}
		else
		{
			TreeVisiting* temp = FindMin(node->right);//Третий Случай
			node->visiting = temp->visiting;
			node->studentIndex = temp->studentIndex;
			node->right = DeleteStudentTree(node->right, temp->visiting, temp->studentIndex);
		}
	}
	return node;
}

Student* DeleteStudent(Student* students, TreeVisiting* nodeVisiting, TreeSurname* nodeSurname)
{
	int visiting;
	int ID;
	string surnameOfDeletedStudent;
	string nameOfDeletedStudent;
	cout << "Введите кол-во посещений у студента, Которого хотите исключить из ВШЭ): ";
	cin >> visiting;//Прекращать работу или нет???
	PrintAllFindStudent(nodeVisiting, students, visiting);
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
		nodeVisiting = DeleteStudentTree(nodeVisiting, visiting, ID);
		nodeSurname = DeleteStudentTree(nodeSurname, surnameOfDeletedStudent, ID);
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

Student* DeleteStudent(Student* students, TreeSurname* nodeSurname, TreeVisiting* nodeVisiting)
{
	string surname;
	string nameOfDeletedStudent;
	int ID;
	int visitingOfDeletedStudent;
	cout << "Введите Фамилию студента, Которого хотите исключить из ВШЭ): ";
	cin >> surname;//Прекращать работу или нет???
	PrintAllFindStudent(nodeSurname, students, surname);
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
				visitingOfDeletedStudent = students[i].visiting;
				nameOfDeletedStudent = students[i].name;
			}
		}
		delete[] students;
		sizeBase--;
		nodeSurname = DeleteStudentTree(nodeSurname, surname, ID);
		nodeVisiting = DeleteStudentTree(nodeVisiting, visitingOfDeletedStudent, ID);
		cout << "Студент " << surname << " " << nameOfDeletedStudent << " Успешно удалён" << endl;
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

#pragma endregion

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Student* studentsBase = nullptr;
	sizeBase = 9;

	cout << "Использовать данные по умолчанию? (1 - Да, Другое - Нет): ";//Если время будет через switch case
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		studentsBase = new Student[sizeBase]
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
		id_student = 9;
	}
	else
	{
		cout << "Введите количество студентов: ";
		cin >> sizeBase;//Добавить Проверку на <1
		studentsBase = new Student[sizeBase];
		InputBaseStudentsFromClava(studentsBase);
	}
	TreeSurname* treeSurname = BuildTreeSurname(studentsBase);
	TreeVisiting* treeVisiting = BuildTreeVisiting(studentsBase);
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
		cout << "6. Найти студента по Фамилии\n";
		cout << "7. Найти студента по Посещениям\n";
		cout << "8. Удалить студента по фамилии\n";
		cout << "9. Удалить студента по посещениям\n";
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
			PrintStudentsSurnameA_Z(treeSurname, studentsBase);
			break;
		case 3:
			PrintStudentsSurnameZ_A(treeSurname, studentsBase);
			break;
		case 4:
			PrintStudentsVisitingIncrease(treeVisiting, studentsBase);
			break;
		case 5:
			PrintStudentsVisitingDecrease(treeVisiting, studentsBase);
			break;
		case 6:
		{
			string studentName;
			cout << "Введите фамилию студента, которого хотите найти: ";
			cin >> studentName;
			PrintAllFindStudent(treeSurname, studentsBase, studentName);
			break;
		}
		case 7:
		{
			int studentVisiting;
			cout << "Введите кол-во посещений студентов, по которым хотите найти: ";
			cin >> studentVisiting;
			PrintAllFindStudent(treeVisiting, studentsBase, studentVisiting);
			break;
		}
		case 8:
		{
			if (sizeBase < 1)
			{
				cout << "Нельзя удалять элементы из пустого массива";
			}
			else
			{
				studentsBase = DeleteStudent(studentsBase, treeSurname, treeVisiting);
			}
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
				studentsBase = DeleteStudent(studentsBase, treeVisiting, treeSurname);
			}
			break;
		}
		case 66:
		{
			FindStudentIterative(treeVisiting, studentsBase, 15);
			cout << "Проверка===========================================Проверка" << endl;
			PrintAllFindStudent(treeVisiting, studentsBase, 15);
			break;
		}
		case 77:
		{
			FindStudentIterative(treeSurname, studentsBase, "Косвинцев");
			cout << "Проверка===========================================Проверка" << endl;
			PrintAllFindStudent(treeSurname, studentsBase, "Косвинцев");
			break;
		}
		case 0:
			delete[] studentsBase;

			isRunning = false;
			cout << "Выход из программы." << endl;
			break;
		default:
			cout << "Неверный выбор. Попробуйте снова." << endl;
		}
	}
	return 0;
}