#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isLetter(char c) {
    return (c >= 'а' && c <= 'я') || (c >= 'a' && c <= 'z') ||
           (c >= 'А' && c <= 'Я') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

char toLower(char c) {
    if ((c >= 'А' && c <= 'Я')) return c + ('а'-'А');   
    if ((c >= 'A' && c <= 'Z')) return c - 'A' + 'a';   
    return c;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка русской локали

    /////////////////////////////////////////////
    // ПУНКТ 0 - показываем таблицу символов
    /////////////////////////////////////////////
    cout << "ПУНКТ 0:" << endl;
    const char* vse_simvoly = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?;:-()\"";
    for (int i = 0; vse_simvoly[i]; ++i) {              // Используем инкремент переменной внутри условия цикла
        cout << vse_simvoly[i] << "=" << static_cast<int>(vse_simvoly[i]) << " "; // Преобразовали символ в число
    }
    cout << endl << endl;

    /////////////////////////////////////////////
    // ЗАДАЧА 1 - убираем знаки препинания из строки
    /////////////////////////////////////////////
    cout << "ЗАДАЧА 1: Напиши строку" << endl;
    char stroka[101];
    cin.getline(stroka, sizeof(stroka));                 
    const char* znaki = ".,!?;:-()'\"]";                 
    char chistaya_stroka[101]{};
    int poziciya = 0;
    for (int i = 0; stroka[i]; ++i) {
        bool eto_znak = false;
        for (int j = 0; znaki[j]; ++j) {
            if (stroka[i] == znaki[j]) {
                eto_znak = true;
                break;
            }
        }
        if (!eto_znak) {
            chistaya_stroka[poziciya++] = stroka[i];
        }
    }
    chistaya_stroka[poziciya] = '\0';                   // Завершаем строку нулевым символом
    cout << "Получилось: " << chistaya_stroka << endl << endl;

    /////////////////////////////////////////////
    // ЗАДАЧА 2 - ищем слова где гласных столько же сколько согласных
    /////////////////////////////////////////////
    cout << "ЗАДАЧА 2: Читаю файл text.txt" << endl;
    ifstream file_s_textom("text.txt");
    ifstream file_s_N("input.txt");

    int N;
    file_s_N >> N;
    file_s_N.close();

    const char* glasnye = "аеёиоуъыьэюя";              
    const char* soglasnye = "бвгджзйклмнпрстфхцчшщ";

    vector<string> vse_slova;
    string tekushee_slovo = "";
    char odna_bukva;

    while (file_s_textom.get(odna_bukva)) {
        char lower_char = toLower(odna_bukva);          // Приводим букву к нижнему регистру перед проверкой

        // Накапливаем слово: буквы, цифры и дефисы
        if (isLetter(lower_char) || isDigit(lower_char) || odna_bukva == '-') {
            tekushee_slovo += lower_char;
        } else {
            // Встретили разделитель — фиксируем слово
            if (!tekushee_slovo.empty()) {
                // Очищаем слово: начинаем с буквы/цифры, заканчиваем буквой
                int start = 0, end = tekushee_slovo.length() - 1;

                // Пропускаем небуквенные символы в начале
                while (start <= end && !isLetter(tekushee_slovo[start])) start++;
                // Обрезаем небуквенные символы в конце
                while (end >= start && !isLetter(tekushee_slovo[end])) end--;

                if (start <= end) {
                    string chistoe_slovo = tekushee_slovo.substr(start, end - start + 1);

                    // Проверяем уникальность
                    bool uzhe_bylo = false;
                    for (const auto& word : vse_slova) {
                        if (word == chistoe_slovo) {
                            uzhe_bylo = true;
                            break;
                        }
                    }
                    if (!uzhe_bylo) {
                        vse_slova.push_back(chistoe_slovo);
                    }
                }
                tekushee_slovo.clear();                  // Очистка текущего слова после обработки
            }
        }
    }

    // Обрабатываем последнее слово, если файл не закончился разделителем
    if (!tekushee_slovo.empty()) {
        int start = 0, end = tekushee_slovo.length() - 1;
        while (start <= end && !isLetter(tekushee_slovo[start])) start++;
        while (end >= start && !isLetter(tekushee_slovo[end])) end--;
        if (start <= end) {
            string chistoe_slovo = tekushee_slovo.substr(start, end - start + 1);
            bool uzhe_bylo = false;
            for (const auto& word : vse_slova) {
                if (word == chistoe_slovo) {
                    uzhe_bylo = true;
                    break;
                }
            }
            if (!uzhe_bylo) {
                vse_slova.push_back(chistoe_slovo);
            }
        }
    }

    file_s_textom.close();

    cout << "Всего разных слов: " << vse_slova.size() << endl;

    // Ищем слова с равным числом гласных и согласных
    vector<string> podhodyashie_slova;

    for (const auto& word : vse_slova) {
        int kolvo_glasnyh = 0, kolvo_soglasnyh = 0;
        for (char bukva : word) {
            if (bukva >= '0' && bukva <= '9') continue;

            bool eto_glasnaya = false;
            for (int g = 0; glasnye[g]; ++g) {
                if (toLower(bukva) == glasnye[g]) {     // Привели букву к нижнему регистру при проверке
                    eto_glasnaya = true;
                    break;
                }
            }

            if (eto_glasnaya) {
                kolvo_glasnyh++;
            } else {
                kolvo_soglasnyh++;
            }
        }

        // Проверяем условие: гласных столько же, сколько согласных
        if (kolvo_glasnyh == kolvo_soglasnyh && !word.empty()) {
            podhodyashie_slova.push_back(word);
        }
    }

    // Сортировка подходящих слов по убыванию длины
    sort(podhodyashie_slova.begin(), podhodyashie_slova.end(),
         [](const string &s1, const string &s2){return s1.length() > s2.length();}); // Использование стандартной сортировки C++

    // Записываем результат в файл
    ofstream resultat("result.txt");

    // Сколько слов реально запишем (не больше чем нашли или чем N)
    size_t skolko_zapishem = min(static_cast<size_t>(N), podhodyashie_slova.size());

    for (size_t i = 0; i < skolko_zapishem; i++) {
        resultat << podhodyashie_slova[i] << endl;
    }
    resultat.close();

    cout << "ГОТОВО! Смотри файл result.txt" << endl;

    return 0;
}
