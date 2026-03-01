#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
using namespace std;

// Пункт 0: вывод таблицы «Буква/Код»
void printCharCodeTable() {
    cout << "=== Пункт 0: Таблица Буква/Код ===\n";
    cout << "Символ\тКод\n";
    cout << "----------------\n";

    // Английский алфавит (верхний регистр)
    for (char c = 'A'; c <= 'Z'; c++) {
        cout << c << "\t\t" << static_cast<int>(c) << endl;
    }

    // Английский алфавит (нижний регистр)
    for (char c = 'a'; c <= 'z'; c++) {
        cout << c << "\t\t" << static_cast<int>(c) << endl;
    }

    // Русский алфавит (верхний регистр) — диапазон кириллицы в Windows‑1251/UTF‑8
    for (char c1 = -64; c1 >= -33; c1--) {  // А–Я в однобайтовой кодировке
        cout << c1 << "\t\t" << static_cast<int>(static_cast<unsigned char>(c1)) << endl;
    }

    // Русский алфавит (нижний регистр) — аналогично
    for (char c1 = -32; c1 >= -1; c1--) {  // а–я в однобайтовой кодировке
        cout << c1 << "\t\t" << static_cast<int>(static_cast<unsigned char>(c1)) << endl;
    }

    // Цифры
    for (char c = '0'; c <= '9'; c++) {
        cout << c << "\t\t" << static_cast<int>(c) << endl;
    }

    // Стандартные знаки препинания
    const char punctuation[] = {'.', ',', ';', ':', '!', '?', '-',
                              '(', ')', '[', ']', '{', '}', '"', '\''};
    const int punctCount = 15;

    for (int i = 0; i < punctCount; i++) {
        cout << punctuation[i] << "\t\t" << static_cast<int>(punctuation[i]) << endl;
    }
}

// Часть 1: удаление знаков препинания из char[]
void removePunctuation(char str[]) {
    int j = 0;  // Индекс для записи символов

    // Проходим по строке до нулевого символа
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        // Проверяем, является ли символ знаком препинания
        if (!(c == '.' || c == ',' || c == ';' || c == ':' ||
              c == '!' || c == '?' || c == '-' || c == '(' ||
              c == ')' || c == '[' || c == ']' || c == '{' ||
              c == '}' || c == '"' || c == '\'')) {
            str[j] = c;  // Копируем символ, если это не знак препинания
            j++;
        }
    }
    str[j] = '\0';  // Завершаем строку нулевым символом
}

// Проверка, гласная ли буква (в нижнем регистре)
bool isVowel(char c) {
    string vowels = "аеёиоуъыьэюя";
    return vowels.find(c) != string::npos;
}

// Подсчёт гласных и согласных в слове
bool hasEqualVowelsConsonants(const string& word) {
    int vowels = 0, consonants = 0;
    for (char c : word) {
        if (isalpha(c)) {
            char lower = tolower(c);
            if (isVowel(lower)) {
                vowels++;
            } else {
                consonants++;
            }
        }
    }
    return vowels == consonants;
}

// Проверка, есть ли слово уже в векторе
bool isWordInVector(const vector<string>& vec, const string& word) {
    for (const string& existingWord : vec) {
        if (existingWord == word) {
            return true;
        }
    }
    return false;
}

int main() {
    // Пункт 0: таблица Буква/Код
    printCharCodeTable();

    // Часть 1: удаление знаков препинания
    cout << "\n=== Часть 1: Удаление знаков препинания ===\n";
    char inputStr[101];  // Массив для строки до 100 символов
    cout << "Введите строку (до 100 символов): ";
    cin.getline(inputStr, 101);  // Безопасное чтение строки

    removePunctuation(inputStr);
    cout << "Результат: " << inputStr << endl;

    // Часть 2: поиск слов с равным числом гласных и согласных
    cout << "\n=== Часть 2: Поиск слов с равным числом гласных/согласных ===\n";

    ifstream inputFile("input.txt");
    ofstream resultFile("result.txt");
    ifstream textFile("text.txt");

    // Пункт 0 (дополнительно): проверка открытия файлов
    if (!inputFile.is_open()) {
        cerr << "Ошибка: не удалось открыть input.txt для чтения!\n";
        return 1;
    }
    if (!resultFile.is_open()) {
        cerr << "Ошибка: не удалось открыть result.txt для записи!\n";
        inputFile.close();
        return 1;
    }
    if (!textFile.is_open()) {
        cerr << "Ошибка: не удалось открыть text.txt для чтения!\n";
        inputFile.close();
        resultFile.close();
        return 1;
    }

    int N;
    inputFile >> N;

    vector<string> words;  // Храним все подходящие слова

    string line;
    regex wordRegex(R"([а-яa-zA-Z]+)");  // Ищем только слова из букв

    while (getline(textFile, line)) {
        auto wordsBegin = sregex_iterator(line.begin(), line.end(), wordRegex);
        auto wordsEnd = sregex_iterator();

        for (sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
            string word = (*i)[0].str();
            // Приводим к нижнему регистру
            for (char& c : word) {
                c = tolower(c);
            }

            // Проверяем условие и уникальность (через вектор)
            if (hasEqualVowelsConsonants(word) && !isWordInVector(words, word)) {
                words.push_back(word);
            }
        }
    }

    // Сортировка по убыванию длины
    sort(words.begin(), words.end(),
        [](const string& a, const string& b) {
            return a.length() > b.length();
        });

    // Записываем N самых длинных слов в файл
    for (int i = 0; i < N && i < words.size(); i++) {
        resultFile << words[i] << endl;
    }

    inputFile.close();
    resultFile.close();
    textFile.close();

    cout << "Готово! Результаты записаны в result.txt\n";
    return 0;
}
