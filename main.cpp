#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

string glas = "аеёиоуъыьэюя";
string soglas = "бвгджзйклмнопрстфхцчшщ";

// Пункт 0
void task0() {
    cout << "Буква -> Код\n";
    string vse = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,!?;:-()\"'";
    for(int i = 0; i < vse.size(); i++) {
        cout << vse[i] << " -> " << (int)vse[i] << endl;
    }
}

// Задача 1
void task1() {
    cout << "\nВведи строку: ";
    char s[100];
    cin.getline(s, 99);
    
    char r[100];
    int k = 0;
    char znaki[] = {'.', ',', '!', '?', ';', ':', '-', '(', ')', '"', '\''};
    
    for(int i = 0; i < 100; i++) {
        char c = s[i];
        if(c == 0) break;
        
        bool eto_znak = false;
        for(int j = 0; j < 11; j++) {
            if(c == znaki[j]) eto_znak = true;
        }
        
        if(eto_znak == false) {
            r[k] = c;
            k++;
        }
    }
    r[k] = 0;
    cout << "Результат: " << r << endl;
}


void task2() {
    // читаем N
    ifstream file("input.txt");
    int N;
    file >> N;
    file.close();
    
    // читаем текст из файла построчно
    ifstream file2("text.txt");
    string text = "";
    string line;
    
    // читаем все строки из файла
    while(getline(file2, line)) {
        text = text + line + " ";
    }
    file2.close();
    
    vector<string> slova;
    string tek = "";
    
    // проходим по всем символам
    for(int i = 0; i < text.size(); i++) {
        char c = text[i];
        
        // проверяем буква ли это
        bool eto_bukva = false;
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я') ||
           c == 'ё' || c == 'Ё') {
            eto_bukva = true;
        }
        
        if(eto_bukva == true) {
            tek = tek + c;
        } else {
            if(tek != "") {
                // считаем гласные и согласные
                int g = 0, s = 0;
                for(int j = 0; j < tek.size(); j++) {
                    char ch = tek[j];
            
            // делаем маленькой
            if(ch >= 'A' && ch <= 'Z') ch = ch + 32;
            if(ch >= 'А' && ch <= 'Я') ch = ch + 32;
            if(ch == 'Ё') ch = 'ё';
            
            // проверяем гласная
            for(int k = 0; k < glas.size(); k++) {
                if(ch == glas[k]) g++;
            }
            // проверяем согласная
            for(int k = 0; k < soglas.size(); k++) {
                if(ch == soglas[k]) s++;
            }
        }
        
        // если гласных столько же сколько согласных
        if(g == s && g > 0) {
            // проверяем нет ли такого слова уже
            bool est = false;
            for(int j = 0; j < slova.size(); j++) {
                if(slova[j] == tek) est = true;
            }
            
            if(est == false) {
                slova.push_back(tek);
            }
        }
        tek = "";
    }
}
}

    // сортируем слова по длине (от самых длинных)
    for(int i = 0; i < slova.size(); i++) {
        for(int j = i+1; j < slova.size(); j++) {
            if(slova[i].size() < slova[j].size()) {
                string temp = slova[i];
                slova[i] = slova[j];
                slova[j] = temp;
            }
        }
    }
    
    // записываем результат
    ofstream out("result.txt");
    int skolko = N;
    if(skolko > slova.size()) skolko = slova.size();
    
    for(int i = 0; i < skolko; i++) {
        out << i+1 << ". " << slova[i] << " (" << slova[i].size() << " букв)\n";
    }
    out.close();
    
    cout << "\nГотово! Найдено слов: " << slova.size() << endl;
}

// Функция main
int main() {
    int choice;

    do {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "0 — Показать коды символов" << endl;
        cout << "1 — Удалить знаки препинания из строки" << endl;
        cout << "2 — Найти слова с равным числом гласных и согласных" << endl;
        cout << "3 — Выход" << endl;
        cout << "Выберите задачу (0–3): ";
        cin >> choice;

        // Очистка буфера ввода от символа новой строки
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 0:
                task0();
                break;
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    } while(choice != 3);

    return 0;
}

