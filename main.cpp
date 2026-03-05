
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    /////////////////////////////////////////////
    // ПУНКТ 0 -  показываем таблицу символов
    /////////////////////////////////////////////
    cout << "ПУНКТ 0:" << endl;
    
    // Все символы подряд: русские буквы, английские, цифры, знаки
    char vse_simvoly[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?;:-()\"";
    
    // Печатаем каждый символ и его номер
    for(int i = 0; vse_simvoly[i] != 0; i++) {
        cout << vse_simvoly[i] << "=" << (int)vse_simvoly[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    /////////////////////////////////////////////
    // ЗАДАЧА 1 - убираем знаки препинания из строки
    /////////////////////////////////////////////
    cout << "ЗАДАЧА 1: Напиши строку" << endl;
    
    char stroka[101];              // куда положим то что написал пользователь
    cin.getline(stroka, 100);       // читаем строку
    
    char znaki[] = ".,!?;:-()\"";   // все знаки препинания которые надо убрать
    char chistaya_stroka[101];      // сюда положим результат
    int poziciya = 0;                // место в чистой строке
    
    // Смотрим каждый символ из того что написал пользователь
    for(int i = 0; stroka[i] != 0; i++) {
        
        // Проверяем - это знак препинания?
        bool eto_znak = false;
        for(int j = 0; znaki[j] != 0; j++) {
            if(stroka[i] == znaki[j]) {
                eto_znak = true;    // да, это знак препинания
                break;
            }
        }
        
        // Если это не знак препинания - кладем в результат
        if(eto_znak == false) {
            chistaya_stroka[poziciya] = stroka[i];
            poziciya++;
        }
    }
    
    chistaya_stroka[poziciya] = 0;   // ставим конец строки
    cout << "Получилось: " << chistaya_stroka << endl;
    cout << endl;
    
    /////////////////////////////////////////////
    // ЗАДАЧА 2 - ищем слова где гласных столько же сколько согласных
    /////////////////////////////////////////////
    cout << "ЗАДАЧА 2: Читаю файл text.txt" << endl;
    
    // Открываем файлы
    ifstream file_s_textom("text.txt");
    ifstream file_s_N("input.txt");
    
    // Читаем сколько слов надо найти
    int N;
    file_s_N >> N;
    file_s_N.close();
    
    // Гласные и согласные буквы
    char glasnye[] = "аеёиоуъыьэюя";
    char soglasnye[] = "бвгджзйклмнпрстфхцчшщ";
    
    // Здесь будем хранить все слова из файла
    string vse_slova[1000];
    int skolko_vsego_slov = 0;
    
    // Читаем файл по одной букве
    string tekushee_slovo = "";
    char odna_bukva;
    
    while(file_s_textom.get(odna_bukva)) {
        
        // Если буква большая - делаем маленькой
        if(odna_bukva >= 'А' && odna_bukva <= 'Я') {
            odna_bukva = odna_bukva + 32;
        }
        
        // Проверяем - это русская буква или цифра?
        bool eto_bukva_ili_cifra = false;
        if((odna_bukva >= 'а' && odna_bukva <= 'я') || (odna_bukva >= '0' && odna_bukva <= '9')) {
            eto_bukva_ili_cifra = true;
        }
        
        if(eto_bukva_ili_cifra) {
            // Если да - добавляем к текущему слову
            tekushee_slovo = tekushee_slovo + odna_bukva;
        } else {
            // Если нет - значит слово закончилось
            if(tekushee_slovo != "") {
                
                // Проверяем, может такое слово уже есть?
                bool uzhe_bylo = false;
                for(int i = 0; i < skolko_vsego_slov; i++) {
                    if(vse_slova[i] == tekushee_slovo) {
                        uzhe_bylo = true;
                        break;
                    }
                }
                
                // Если такого слова еще нет - добавляем
                if(uzhe_bylo == false) {
                    vse_slova[skolko_vsego_slov] = tekushee_slovo;
                    skolko_vsego_slov++;
                }
                
                // Начинаем новое слово
                tekushee_slovo = "";
            }
        }
    }
    file_s_textom.close();
    
    cout << "Всего разных слов: " << skolko_vsego_slov << endl;
    
    // Теперь ищем среди всех слов те, где гласных = согласных
    string podhodyashie_slova[1000];
    int skolko_podhodit = 0;
    
    for(int i = 0; i < skolko_vsego_slov; i++) {
        
        int kolvo_glasnyh = 0;
        int kolvo_soglasnyh = 0;
        
        // Смотрим каждую букву в слове
        for(int j = 0; j < vse_slova[i].size(); j++) {
            char bukva_v_slove = vse_slova[i][j];
            
            // Цифры пропускаем
            if(bukva_v_slove >= '0' && bukva_v_slove <= '9') {
                continue;
            }
            
            // Проверяем - это гласная?
            bool eto_glasnaya = false;
            for(int g = 0; glasnye[g] != 0; g++) {
                if(bukva_v_slove == glasnye[g]) {
                    eto_glasnaya = true;
                    break;
                }
            }
            
            if(eto_glasnaya) {
                kolvo_glasnyh++;
            } else {
                // Проверяем - это согласная?
                for(int s = 0; soglasnye[s] != 0; s++) {
                    if(bukva_v_slove == soglasnye[s]) {
                        kolvo_soglasnyh++;
                        break;
                    }
                }
            }
        }
        
        // Если гласных столько же сколько согласных - запоминаем слово
        if(kolvo_glasnyh == kolvo_soglasnyh && kolvo_glasnyh > 0) {
            podhodyashie_slova[skolko_podhodit] = vse_slova[i];
            skolko_podhodit++;
        }
    }
    
    cout << "Подходящих слов: " << skolko_podhodit << endl;
    
    // Сортируем от самого длинного к самому короткому
    for(int i = 0; i < skolko_podhodit - 1; i++) {
        for(int j = i + 1; j < skolko_podhodit; j++) {
            
            int dlina_i = podhodyashie_slova[i].size();
            int dlina_j = podhodyashie_slova[j].size();
            
            if(dlina_i < dlina_j) {
                // Меняем местами
                string vremya = podhodyashie_slova[i];
                podhodyashie_slova[i] = podhodyashie_slova[j];
                podhodyashie_slova[j] = vremya;
            }
        }
    }
    
    // Записываем результат в файл
    ofstream resultat("result.txt");
    
    // Сколько слов реально запишем (не больше чем нашли)
    int skolko_zapishem = N;
    if(skolko_zapishem > skolko_podhodit) {
        skolko_zapishem = skolko_podhodit;
    }
    
    for(int i = 0; i < skolko_zapishem; i++) {
        resultat << podhodyashie_slova[i] << endl;
    }
    resultat.close();
    
    cout << "ГОТОВО! Смотри файл result.txt" << endl;
    
    return 0;
}
