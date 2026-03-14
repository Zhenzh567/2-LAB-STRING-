#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Функции проверки символов
bool isLetter(char c) {
    return (c >= 'а' && c <= 'я') || (c >= 'a' && c <= 'z') ||
        (c >= 'А' && c <= 'Я') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Функция приведения к нижнему регистру
char toLower(char c) {
    if ((c >= 'А' && c <= 'Я')) return c + ('а' - 'А');
    if ((c >= 'A' && c <= 'Z')) return c - 'A' + 'a';
    return c;
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка русской локали

    /////////////////////////////////////////////
    // ПУНКТ 0 - показываем таблицу символов
    /////////////////////////////////////////////
    cout << "ПУНКТ 0:" << endl;

    const char* vse_simvoly = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz0123456789.,!?;:-()\"";

    for (int i = 0; vse_simvoly[i]; ++i) {
        cout << vse_simvoly[i] << "=" << static_cast<int>(vse_simvoly[i]) << " ";
        if ((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl << endl;

    /////////////////////////////////////////////
    // ЗАДАЧА 1 - убираем знаки препинания из строки
    /////////////////////////////////////////////
    cout << "ЗАДАЧА 1: Напиши строку" << endl;
    char stroka[101];
    cin.getline(stroka, sizeof(stroka));
    const char* znaki = ".,!?;:\"()'/"; // Дефис (-) убран из списка удаляемых знаков
    int write_pos = 0;

    for (int i = 0; stroka[i]; ++i) {
        bool eto_znak = false;
        for (int j = 0; znaki[j]; ++j) {
            if (stroka[i] == znaki[j]) {
                eto_znak = true;
                break;
            }
        }
        if (!eto_znak) {
            stroka[write_pos++] = stroka[i];
        }
    }
    stroka[write_pos] = '\0';
    cout << "Получилось: " << stroka << endl << endl;

    /////////////////////////////////////////////
    // ЗАДАЧА 2 - ищем слова где гласных столько же сколько согласных (уникальные)
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
    string tekushee_slovo;

    // Читаем файл по словам (разделитель — пробел)
    while (file_s_textom >> tekushee_slovo) {
        string chistoe_slovo = "";
        int start = 0, end = tekushee_slovo.length() - 1;

        // Находим первый допустимый символ (букву или цифру) с начала
        while (start <= end && !isLetter(tekushee_slovo[start]) && !isDigit(tekushee_slovo[start])) {
            start++;
        }

        // Находим последний допустимый символ (букву или цифру) с конца
        while (end >= start && !isLetter(tekushee_slovo[end]) && !isDigit(tekushee_slovo[end])) {
            end--;
        }

        // Копируем от start до end, сохраняя внутренние знаки
        for (int i = start; i <= end; ++i) {
            chistoe_slovo += tekushee_slovo[i];
        }

        // ОБРЕЗКА: если слово заканчивается на цифру, обрезаем до последней буквы
        while (!chistoe_slovo.empty() && isDigit(chistoe_slovo.back())) {
            chistoe_slovo.pop_back();
        }

        // Проверяем, что слово не пустое и начинается на букву или цифру
        if (!chistoe_slovo.empty() &&
            (isLetter(chistoe_slovo[0]) || isDigit(chistoe_slovo[0]))) {

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
        tekushee_slovo.clear(); // Очистка текущего слова после обработки
    }

    file_s_textom.close();

    cout << "Всего уникальных слов: " << vse_slova.size() << endl;

    // Ищем слова с равным числом гласных и согласных
    vector<string> podhodyashie_slova;

    for (const auto& word : vse_slova) {
        int kolvo_glasnyh = 0, kolvo_soglasnyh = 0;

        for (char bukva : word) {
            if (!isLetter(bukva)) continue; // Пропускаем всё, что не буква (включая цифры и знаки)

            char lower_bukva = toLower(bukva);

            bool eto_glasnaya = false;
            for (int g = 0; glasnye[g]; ++g) {
                if (lower_bukva == glasnye[g]) {
                    eto_glasnaya = true;
                    break;
                }
            }

            if (eto_glasnaya) {
                kolvo_glasnyh++;
            }
            else {
                // Если это буква и не гласная, значит — согласная
                kolvo_soglasnyh++;
            }
        }

        // Проверяем условие: гласных столько же, сколько согласных, и слово не пустое
        if (kolvo_glasnyh == kolvo_soglasnyh && !word.empty()) {
            podhodyashie_slova.push_back(word);
        }
    }

    // Сортировка подходящих слов по убыванию длины
    sort(podhodyashie_slova.begin(), podhodyashie_slova.end(),
        [](const string& s1, const string& s2) { return s1.length() > s2.length(); });

    // Записываем результат в файл
    ofstream resultat("result.txt");
    size_t skolko_zapishem = min(static_cast<size_t>(N), podhodyashie_slova.size());

    for (size_t i = 0; i < skolko_zapishem; i++) {
        resultat << podhodyashie_slova[i] << endl;
    }
    resultat.close();

    cout << "ГОТОВО! Смотри файл result.txt" << endl;

    return 0;
}
