#include <iostream>
#include <windows.h> 
#include <locale>

using namespace std;
static unsigned int id_student = 1;
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

// Индекс массив по фамилии
struct IndexSurname
{
    unsigned int index;// Индекс в исходном массиве
    string surname;// Фамилия
};

// Индекс массив по посещаемости
struct IndexVisiting
{
    unsigned int index;// Индекс в исходном массиве
    unsigned int visiting;// Количество посещений
};
#pragma endregion

#pragma region Заполнение индекс массивов и создание указателей на них
IndexSurname* CreateIndexBySurname(Student* students, int sizeOfCurrentArray)//Создаём указатель на индекс массив и заполняем массив по Фамилии
{
    IndexSurname* indexSurname = new IndexSurname[sizeOfCurrentArray];
    for (unsigned int i = 0; i < sizeOfCurrentArray; i++)
    {
        indexSurname[i].index = i;
        indexSurname[i].surname = students[i].surname;

    }
    return indexSurname;
}

IndexVisiting* CreateIndexByVisiting(Student* students, int sizeOfCurrentArray)//Создаём указатель на индекс массив и заполняем массив по Посещения
{
    IndexVisiting* indexVisiting = new IndexVisiting[sizeOfCurrentArray];
    for (unsigned int i = 0; i < sizeOfCurrentArray; i++)
    {
        indexVisiting[i].index = i;
        indexVisiting[i].visiting = students[i].visiting;
    }
    return indexVisiting;
}

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

void InputBaseStudentsFromClava(Student* students, int sizeOfCurrentArray)
{
    for (int i = 0; i < sizeOfCurrentArray; ++i)
    {
        students[i] = InputStudentFromClava();
    }
}
#pragma endregion

#pragma region Сортировки
void ShakerSort(IndexSurname* indexSurname, int sizeOfCurrentArray)//Шейкерная сортировка по фамилиям
{
    int left = 0;
    int right = sizeOfCurrentArray - 1;
    bool isSwapped = true;
    while (left < right&& isSwapped)
    {
        isSwapped = false;

        for (int i = left; i < right; ++i)
        {
            if (indexSurname[i].surname > indexSurname[i + 1].surname)
            {
                IndexSurname temp = indexSurname[i];
                indexSurname[i] = indexSurname[i + 1];
                indexSurname[i + 1] = temp;
                isSwapped = true;
            }
        }
        right--;
        for (int i = right; i > left; --i)
        {
            if (indexSurname[i].surname < indexSurname[i - 1].surname)
            {
                IndexSurname temp = indexSurname[i];
                indexSurname[i] = indexSurname[i - 1];
                indexSurname[i - 1] = temp;
                isSwapped = true;
            }
        }
        left++;
    }
}

void ShakerSort(IndexVisiting* indexVisiting, int sizeOfCurrentArray)//Шейкерная сортировка по посещениям
{
    int left = 0;
    int right = sizeOfCurrentArray - 1;
    bool isSwapped = true;

    while (left < right&& isSwapped)
    {
        isSwapped = false;
        for (int i = left; i < right; ++i)
        {
            if (indexVisiting[i].visiting > indexVisiting[i + 1].visiting)
            {
                IndexVisiting temp = indexVisiting[i];
                indexVisiting[i] = indexVisiting[i + 1];
                indexVisiting[i + 1] = temp;
                isSwapped = true;
            }
        }
        right--;
        for (int i = right; i > left; --i)
        {
            if (indexVisiting[i].visiting < indexVisiting[i - 1].visiting)
            {
                IndexVisiting temp = indexVisiting[i];
                indexVisiting[i] = indexVisiting[i - 1];
                indexVisiting[i - 1] = temp;
                isSwapped = true;
            }
        }
        left++;
    }
}
#pragma endregion

#pragma region Поиск
int RecursiveBinarySearch(IndexSurname* indexSurname, int left, int right, string keySurname)
{
    int result;
    if (left > right)
    {
        result = -1;
    }
    else
    {
        int mid = left + (right - left) / 2;
        if (indexSurname[mid].surname == keySurname)
        {
            result = mid;
        }
        else if (indexSurname[mid].surname > keySurname)
        {
            result = RecursiveBinarySearch(indexSurname, left, mid - 1, keySurname);
        }
        else
        {
            result = RecursiveBinarySearch(indexSurname, mid + 1, right, keySurname);
        }
    }
    return result;
}

int IterativeBinarySearch(IndexSurname* indexSurname, int sizeOfCurrentArray, string keySurname) {
    int left = 0;
    int right = sizeOfCurrentArray - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (indexSurname[mid].surname == keySurname)
        {
            result = mid;
            break;
        }
        if (indexSurname[mid].surname > keySurname)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return result;
}

int RecursiveBinarySearch(IndexVisiting* indexVisiting, int left, int right, int keyVisited)
{
    int result;
    if (left > right)
    {
        result = -1;
    }
    else
    {
        int mid = left + (right - left) / 2;
        if (indexVisiting[mid].visiting == keyVisited)
        {
            result = mid;
        }
        else if (indexVisiting[mid].visiting > keyVisited)
        {
            result = RecursiveBinarySearch(indexVisiting, left, mid - 1, keyVisited);
        }
        else
        {
            result = RecursiveBinarySearch(indexVisiting, mid + 1, right, keyVisited);
        }
    }
    return result;
}

int IterativeBinarySearch(IndexVisiting* indexVisiting, int sizeOfCurrentArray, int keyVisited) {
    int left = 0;
    int right = sizeOfCurrentArray - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (indexVisiting[mid].visiting == keyVisited)
        {
            result = mid;
            break;
        }
        if (indexVisiting[mid].visiting > keyVisited)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return result;
}
#pragma endregion

#pragma region Вывод информации
void PrintStudents(Student student)//Вывод одного студента
{
    cout << "====================" << "\nID: " << student.id << "\nФамилия: " << student.surname << "\nИмя: " << student.name
        << "\nКампус: " << student.campus << "\nНаправление: " << student.direction
        << "\nГруппа: " << student.group << "\nПосещения: " << student.visiting << endl;
    cout << "====================" << endl;
}
void PrintStudents(Student* students, int sizeOfCurrentArray)//Вывод студентов из базового массива
{
    for (int i = 0; i < sizeOfCurrentArray; i++)
    {
        Student student = students[i];
        PrintStudents(student);
    }
    cout << "====================" << endl;
}


void PrintStudentsBySurnameA_Z(Student* students, IndexSurname* indexSurname, int sizeOfCurrentArray)//Вывод студентов по фамилиям от А до Я
{
    cout << "Отсортированный массив по Фамилиям от А до Я" << endl;
    for (int i = 0; i < sizeOfCurrentArray; i++)
    {
        Student student = students[indexSurname[i].index];
        PrintStudents(student);
    }
    cout << "====================" << endl;
}

void PrintStudentsBySurnameZ_A(Student* students, IndexSurname* indexSurname, int sizeOfCurrentArray)//Вывод студентов по фамилиям от Я до А
{
    cout << "Отсортированный массив по Фамилиям от Я до А" << endl;
    for (int i = sizeOfCurrentArray - 1; i >= 0; i--)
    {
        Student student = students[indexSurname[i].index];
        PrintStudents(student);
    }
    cout << "====================" << endl;
}

void PrintStudentsByVisitingIncrease(Student* students, IndexVisiting* indexVisiting, int sizeOfCurrentArray)//Вывод студентов по посещениям Возрастания
{
    cout << "Отсортированный массив по Посещениям в порядке Возрастания" << endl;
    for (int i = 0; i < sizeOfCurrentArray; i++)
    {
        Student student = students[indexVisiting[i].index];
        PrintStudents(student);
    }
    cout << "====================" << endl;
}

void PrintStudentsByVisitingDecrease(Student* students, IndexVisiting* indexVisiting, int sizeOfCurrentArray)//Вывод студентов по посещениям Убывание
{
    cout << "Отсортированный массив по Посещениям в порядке Убыванию" << endl;
    for (int i = sizeOfCurrentArray - 1; i >= 0; i--)
    {
        Student student = students[indexVisiting[i].index];
        PrintStudents(student);
    }
    cout << "====================" << endl;
}

void PrintAllFindStudents(Student* students, IndexSurname* indexSurname, int sizeOfCurrentArray, string keySurname)
{
    int foundPosition = RecursiveBinarySearch(indexSurname, 0, sizeOfCurrentArray, keySurname);
    if (foundPosition == -1)
    {
        cout << "Студенты с фамилией " << keySurname << " не найдены." << endl;
        return;
    }

    // Расширяем область  влево
    int leftPosition = foundPosition;
    while (leftPosition > 0 && indexSurname[leftPosition - 1].surname == keySurname)
    {
        leftPosition--;
    }

    // Расширяем область вправо
    int rightPosition = foundPosition;
    while (rightPosition < sizeOfCurrentArray - 1 && indexSurname[rightPosition + 1].surname == keySurname)
    {
        rightPosition++;
    }

    cout << "Найдено " << rightPosition - leftPosition + 1 << " Студентов с фамилией '" << keySurname << "'" << endl;//Добавить фунцию проверки окончаний
    for (int i = leftPosition; i <= rightPosition; i++)
    {
        int baseIndex = indexSurname[i].index;
        Student student = students[baseIndex];
        PrintStudents(student);
    }
}

void PrintAllFindStudents(Student* students, IndexVisiting* indexVisiting, int sizeOfCurrentArray, int keyVisited)
{
    int foundPosition = RecursiveBinarySearch(indexVisiting, 0, sizeOfCurrentArray, keyVisited);
    if (foundPosition == -1)
    {
        cout << "Студенты с кол-во посещений " << keyVisited << " не найдены." << endl;
        return;
    }

    // Расширяем область  влево
    int leftPosition = foundPosition;
    while (leftPosition > 0 && indexVisiting[leftPosition - 1].visiting == keyVisited)
    {
        leftPosition--;
    }

    // Расширяем область вправо
    int rightPosition = foundPosition;
    while (rightPosition < sizeOfCurrentArray - 1 && indexVisiting[rightPosition + 1].visiting == keyVisited)
    {
        rightPosition++;
    }

    cout << "Найдено " << rightPosition - leftPosition + 1 << " Студентов с фамилией '" << keyVisited << "'" << endl;//Добавить фунцию проверки окончаний
    for (int i = leftPosition; i <= rightPosition; i++)
    {
        int baseIndex = indexVisiting[i].index;
        Student student = students[baseIndex];
        PrintStudents(student);
    }
}
#pragma endregion

#pragma region Изменение информации
void EditVisiting(Student* students, IndexSurname* indexSurname, int sizeOfCurrentArray)
{
    string surname;
    int ID;
    cout << "Введите Фамилию студента, у которого хотите изменить Данные: ";
    cin >> surname;
    PrintAllFindStudents(students, indexSurname, sizeOfCurrentArray, surname);
    cout << "Введите ID студента, у которого хотите изменить Данные: ";
    cin >> ID;
    cout << "Введите новые данные для студента " << students[ID - 1].surname << " " << students[ID - 1].name << ": ";
    cout << "Введите фамилию: ";
    cin >> students[ID - 1].surname;
    cout << "Введите имя: ";
    cin >> students[ID - 1].name;
    cout << "Введите кампус(Москва, Санкт-Петербург, Нижний Новгород, Пермь):";
    cin >> students[ID - 1].campus;
    cout << "Введите направление: ";
    cin >> students[ID - 1].direction;
    cout << "Введите группу: ";
    cin >> students[ID - 1].group;
    cout << "Введите количество посещений(целое число): ";
    cin >> students[ID - 1].visiting;
}

void EditVisiting(Student* students, IndexVisiting* indexVisiting, int sizeOfCurrentArray)
{
    int visiting;
    int ID;
    cout << "Введите кол-во посещений студента, у которого хотите изменить Данные: ";
    cin >> visiting;
    PrintAllFindStudents(students, indexVisiting, sizeOfCurrentArray, visiting);
    cout << "Введите ID студента, у которого хотите изменить Данные: ";
    cin >> ID;
    cout << "Введите новые данные для студента " << students[ID - 1].surname << " " << students[ID - 1].name << ": ";
    cout << "Введите фамилию: ";
    cin >> students[ID - 1].surname;
    cout << "Введите имя: ";
    cin >> students[ID - 1].name;
    cout << "Введите кампус(Москва, Санкт-Петербург, Нижний Новгород, Пермь):";
    cin >> students[ID - 1].campus;
    cout << "Введите направление: ";
    cin >> students[ID - 1].direction;
    cout << "Введите группу: ";
    cin >> students[ID - 1].group;
    cout << "Введите количество посещений(целое число): ";
    cin >> students[ID - 1].visiting;
}
#pragma endregion

#pragma region Удаление информации
Student* DeleteStudent(Student* students, IndexSurname* indexSurname, IndexVisiting* indexVisiting, int& sizeOfCurrentArray)
{
    string surname;
    int ID;
    bool isFindDeleteStudent = false;
    cout << "Введите Фамилию студента, Которого хотите исключить из ВШЭ): ";
    cin >> surname;//Прекращать работу или нет???
    PrintAllFindStudents(students, indexSurname, sizeOfCurrentArray, surname);
    int action;
    cout << "Видите ли Вы студента для удаления выше?(1-Да, 0-Нет): ";
    cin >> action;
    switch (action)
    {
    case 1:
    {
        cout << "Введите ID студента, Которого хотите исключить из ВШЭ): ";
        cin >> ID;
        Student* newStudents = new Student[sizeOfCurrentArray - 1];
        for (int i = 0, j = 0; i < sizeOfCurrentArray; i++)
        {
            if (i != ID - 1)
            {
                if (isFindDeleteStudent)
                {
                    newStudents[j] = students[i];
                    newStudents[j++].id = students[i].id - 1;
                }
                else
                {
                    newStudents[j++] = students[i];
                }
            }
            else
            {
                isFindDeleteStudent = true;
            }
        }
        delete[] students;
        sizeOfCurrentArray--;
        return newStudents;
    }
    case 0:
    {
        Student* newStudents = new Student[sizeOfCurrentArray];
        for (int i = 0; i < sizeOfCurrentArray; i++)
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
    IndexSurname* indexSurname = nullptr;
    IndexVisiting* indexVisiting = nullptr;
    Student* studentsBase = nullptr;
    int size = 9;

    cout << "Использовать данные по умолчанию? (1 - Да, 0 - Нет): ";//Если время будет через switch case
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        studentsBase = new Student[size]
        {
            { 1, "Чазов", "Вадим", "Пермь", "РИС", "24-2", 15 },
            { 2, "Бочкарев", "Игнат", "Нижний Новгород", "Э", "24-4", 15 },
            { 3, "Ахматзянов", "Адис", "Москва", "МБ", "23-3", 15 },
            { 4, "Косвинцев", "Степан", "Пермь", "РИС", "23-1", 0 },
            { 5, "Вронский", "Михаил", "Санкт-Петербург", "МБ", "24-5", 5 },
            { 6, "Катаев", "Денис", "Нижний Новгород", "БИ", "24-5", 2 },
            { 7, "Зеленина", "Анастасия", "Москва", "ПИ", "23-7", 30 },
            { 8, "Косвинцев", "Роман", "Пермь", "РИС", "24-1", 26 },
            { 9, "Кононов", "Максим", "Санкт-Петербург", "Д", "24-6", 3 },
        };
        id_student = 9;
    }
    else
    {
        cout << "Введите количество студентов: ";
        cin >> size;//Добавить Проверку на <1
        studentsBase = new Student[size];
        InputBaseStudentsFromClava(studentsBase, size);
    }
    indexSurname = CreateIndexBySurname(studentsBase, size);
    indexVisiting = CreateIndexByVisiting(studentsBase, size);
    ShakerSort(indexSurname, size);
    ShakerSort(indexVisiting, size);
    bool isRunning = true;
    int action;
    while (isRunning)
    {
        cout << "\nМеню:\n";
        cout << "1. Показать базовый массив\n";
        cout << "2. Показать отсортированный массив по фамилиям от А до Я\n";
        cout << "3. Показать отсортированный массив по фамилиям от Я до А\n";
        cout << "4. Показать отсортированный массив по посещениям Возрастание\n";
        cout << "5. Показать отсортированный массив по посещениям Убывание\n";
        cout << "6. Найти студента по Фамилии\n";
        cout << "7. Найти студента по Посещениям\n";
        cout << "8. Изменить данные студента по Фамилии\n";
        cout << "9. Изменить данные студента по Посещениям\n";
        cout << "10. Удалить студента по фамилии\n";
        cout << "0. Выход\n";
        cout << "66 - Проверка реализации Рекурсивной и Итеративной функции поиска Фамилии\n";
        cout << "77 - Проверка реализации Рекурсивной и Итеративной функции поиска Посещений\n";
        cout << "Выберите действие(Число): ";
        cin >> action;

        switch (action)
        {
        case 1:
            PrintStudents(studentsBase, size);
            break;
        case 2:
            PrintStudentsBySurnameA_Z(studentsBase, indexSurname, size);
            break;
        case 3:
            PrintStudentsBySurnameZ_A(studentsBase, indexSurname, size);
            break;
        case 4:
            PrintStudentsByVisitingIncrease(studentsBase, indexVisiting, size);
            break;
        case 5:
            PrintStudentsByVisitingDecrease(studentsBase, indexVisiting, size);
            break;
        case 6:
        {
            string studentName;
            cout << "Введите фамилию студента, которого хотите найти: ";
            cin >> studentName;
            PrintAllFindStudents(studentsBase, indexSurname, size, studentName);
            break;
        }
        case 7:
        {
            int studentVisiting;
            cout << "Введите кол-во посещений студентов, по которым хотите найти: ";
            cin >> studentVisiting;
            PrintAllFindStudents(studentsBase, indexVisiting, size, studentVisiting);
            break;
        }
        case 8:
        {
            EditVisiting(studentsBase, indexSurname, size);
            indexVisiting = CreateIndexByVisiting(studentsBase, size);
            indexSurname = CreateIndexBySurname(studentsBase, size);
            ShakerSort(indexSurname, size);
            ShakerSort(indexVisiting, size);
            break;
        }
        case 9:
        {
            EditVisiting(studentsBase, indexVisiting, size);
            indexVisiting = CreateIndexByVisiting(studentsBase, size);
            indexSurname = CreateIndexBySurname(studentsBase, size);
            ShakerSort(indexSurname, size);
            ShakerSort(indexVisiting, size);
            break;
        }
        case 10:
        {
            if (size < 1)
            {
                cout << "Нельзя удалять элементы из пустого массива";
            }
            else
            {
                studentsBase = DeleteStudent(studentsBase, indexSurname, indexVisiting, size);
                indexSurname = CreateIndexBySurname(studentsBase, size);
                indexVisiting = CreateIndexByVisiting(studentsBase, size);
                ShakerSort(indexSurname, size);
                ShakerSort(indexVisiting, size);
            }
            break;
        }
        case 66:
        {
            int n, m;

            n = IterativeBinarySearch(indexSurname, size, "Чазов");

            m = RecursiveBinarySearch(indexSurname, 0, size, "Чазов");
            cout << n << " = " << m << endl;
            break;
        }
        case 77:
        {
            int n, m;

            n = IterativeBinarySearch(indexVisiting, size, 15);

            m = RecursiveBinarySearch(indexVisiting, 0, size, 15);
            cout << n << " = " << m << endl;
            break;
        }
        case 0:
            delete[] studentsBase;
            delete[] indexSurname;
            delete[] indexVisiting;
            isRunning = false;
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
    return 0;
}