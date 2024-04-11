#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Windows.h"
using namespace std;

class Task {
public:
    string textTask;
    string priority;
    string date;
    string teg;
public:
    Task(string t, string p, string d, string T) : textTask(t), priority(p), date(d), teg(T) {}

    void changeTask() {
        cout << "Введите данные для изменения задачи ->" << endl;
        cout << "Текст: ";
        cin.ignore();
        getline(cin, textTask);
        cout << "Дата выполнения: ";
        cin >> date;
        cout << "Приоритет(HIGH, MEDIUM, LOW): ";
        cin >> priority;
        cout << "Тег: ";
        cin >> teg;
    }
    string getDate() const {
        return date;
    }
    string getTeg() const {
        return teg;
    }
    string getPriority() const {
        return priority;
    }
    string getText() const {
        return textTask;
    }
};

class FactoryTask {
protected:
    vector<Task*>& tasks;
public:
    FactoryTask(vector<Task*>& Tasks) : tasks(Tasks) {}
    void findDate() const {
        string findD;
        cout << "Поиск по дате." << endl;
        cout << "Дата: ";
        cin >> findD;
        cout << "Найденные задачи -> " << endl;
        for (auto task : tasks) {
            if (task->getDate() == findD) {
                cout << "Текст: " << task->getText() << endl;
                cout << "Приоритет: " << task->getPriority() << endl;
                cout << "Тег: " << task->getTeg() << endl;
            }
        }
        cout << endl;
    }
    void findTeg() const {
        string findT;
        cout << "Поиск по тегу." << endl;
        cout << "Тег: ";
        cin >> findT;
        cout << "Найденные задачи -> " << endl;
        for (auto task : tasks) {
            if (task->getTeg() == findT) {
                cout << "Текст: " << task->getText() << endl;
                cout << "Дата: " << task->getDate() << endl;
                cout << "Приоритет: " << task->getPriority() << endl;
            }
        }
        cout << endl;
    }
    virtual void findPriority() const {
        string findP;
        cout << "Поиск по приоритету." << endl;
        cout << "Приоритет: ";
        cin >> findP;
        cout << "Найденные задачи -> " << endl;
        for (auto task : tasks) {
            if (task->getPriority() == findP) {
                cout << "Текст: " << task->getText() << endl;
                cout << "Дата: " << task->getDate() << endl;
                cout << "Тег: " << task->getTeg() << endl;
            }
        }
        cout << endl;
    }
    void saveToFile() const {
        string fileName;
        cout << "Введите название файла: ";
        cin >> fileName;
        ofstream file(fileName);
        if (file.is_open()) {
            for (auto task : tasks) {
                file << task->getText() << endl;
                file << task->getPriority() << endl;
                file << task->getDate() << endl;
                file << task->getTeg() << endl;
            }
            cout << "Задачи успешно сохранены в файл." << endl;
        }
        else
            cout << "Ошибка открытия файла!" << endl;
        file.close();
    }
};


class TaskManagerFacade {
private:
    vector<Task*> tasks;
    FactoryTask* factoryTask;
public:
    TaskManagerFacade() : factoryTask(new FactoryTask(tasks)) {}
    ~TaskManagerFacade() {
        for (auto task : tasks) {
            delete task;
        }
        delete factoryTask;
    }

    void menu() const {
        cout << "Меню:" << endl;
        cout << "1. Создать задачу." << endl;
        cout << "2. Изменить задачу." << endl;
        cout << "3. Удалить задачу." << endl;
        cout << "4. Поиск по дате." << endl;
        cout << "5. Поиск по тегу." << endl;
        cout << "6. Поиск по приоритету." << endl;
        cout << "7. Сохранить задачи в файл." << endl;
        cout << "8. Выход." << endl;
    }

    void start() {
        int choice;
        do {
            menu();
            cout << "Выберите действие: ";
            cin >> choice;
            switch (choice) {
            case 1: {
                system("cls");
                string text, priority, date, teg;
                cout << "Введите текст задачи: ";
                cin.ignore();
                getline(cin, text);
                cout << "Введите приоритет задачи (HIGH, MEDIUM, LOW): ";
                cin >> priority;
                cout << "Введите дату выполнения задачи: ";
                cin >> date;
                cout << "Введите тег задачи: ";
                cin >> teg;
                createTask(text, priority, date, teg);
                system("cls");
                break;
            }
            case 2: {
                system("cls");
                cout << "Введите индекс задачи для изменения: ";
                int index;
                cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    tasks[index]->changeTask();
                    cout << "Задача успешно изменена." << endl;
                }
                else {
                    cout << "Некорректный индекс задачи." << endl;
                }
                break;
            }
            case 3: {
                system("cls");
                cout << "Введите индекс задачи для удаления: ";
                int index;
                cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    delete tasks[index];
                    tasks.erase(tasks.begin() + index);
                    cout << "Задача успешно удалена." << endl;
                }
                else {
                    cout << "Некорректный индекс задачи." << endl;
                }
                break;
            }
            case 4: {
                system("cls");
                factoryTask->findDate();
                break;
            }
            case 5: {
                system("cls");
                factoryTask->findTeg();
                break;
            }
            case 6: {
                system("cls");
                factoryTask->findPriority();
                break;
            }
            case 7: {
                system("cls");
                factoryTask->saveToFile();
                break;
            }
            case 8: {
                system("cls");
                cout << "Завершение работы программы." << endl;
                break;
            }
            default:
                cout << "Некорректный выбор. Пожалуйста, выберите действие из меню." << endl;
            }
        } while (choice != 8);
    }

    void createTask(const string& text, const string& priority, const string& date, const string& teg) {
        tasks.push_back(new Task(text, priority, date, teg));
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    TaskManagerFacade facade;
    facade.start();

    return 0;
}


