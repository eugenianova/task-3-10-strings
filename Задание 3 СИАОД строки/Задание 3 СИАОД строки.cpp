//Дано предложение, состоящее из слов, разделенных запятой или пробелами, среди которых есть группы цифр, определяющих целые числа из диапазона[0 - 19].
//Отредактировать введенную строку, заменив каждое число, на последовательность, заключенную в круглые скобки, символа '+', (если число четное) или
//на '-' (если число нечетное), длина которой равна найденному числу.
//Предполагается, что во введенной строке есть только числа из заданного диапазона[0 - 19],
//допускаются лидирующие нули :
#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <string>  
#include <regex>
using namespace std;

// 1. Вариант на C-string
// 2. Вариант на std::string

bool is_number_suitable(const char* num, unsigned short digits)//////
{
    if (digits == 0) return false;

    char new_num[1000];

    for (int i = 0; i < digits; i++)
        new_num[i] = num[i];

    return std::atoi(new_num) <= 19;
}

bool is_number_even(const char* num, unsigned short digits)//////
{
    if (digits == 0) return false;

    char new_num[1000];

    for (int i = 0; i < digits; i++)
        new_num[i] = num[i];

    int flag = std::atoi(new_num) % 2;
    return (flag == 0); //true = even
}

int the_number_itself(const char* num, unsigned short digits)//////
{
    if (digits == 0) return false;

    char new_num[1000];

    for (int i = 0; i < digits; i++)
        new_num[i] = num[i];

    int flag = std::atoi(new_num);
    return (flag); //true = even
}

// реализуем функцию с учетом того, что на вход мы получаем данные в заведомо верном формате (как указано в условии)
void replace_numbers(const char* sentence, char** new_sentence) ////////
{
    const size_t len = strlen(sentence);

    char transformed_sentence[1000];
    unsigned long c = 0;

    char num[6];
    unsigned short digits = 0;

    for (unsigned long i = 0; i < len; i++)
    {
        if (isdigit(sentence[i]))
        {
            digits++;
            if (digits <= 3)
                num[digits - 1] = sentence[i];

            if (i + 1 == len)
            {
                if (is_number_suitable(num, digits) && is_number_even(num, digits))
                {
                    int nnuumm = the_number_itself(num, digits);

                    for (int i = 0; i < nnuumm; i++) //вставляем нужное количество символов в зависимости от числа
                    {
                        if (i == 0)
                        {
                            transformed_sentence[c++] = '(';
                            transformed_sentence[c++] = '+';
                        }
                        else if (i == nnuumm - 1)
                        {
                            transformed_sentence[c++] = '+';
                            transformed_sentence[c++] = ')';
                        }
                        else
                            transformed_sentence[c++] = '+';
                    }
                }

                if (is_number_suitable(num, digits) == true && is_number_even(num, digits) == false)
                {
                    int nnuumm = the_number_itself(num, digits);

                    for (int i = 0; i < nnuumm; i++) //вставляем нужное количество символов в зависимости от числа
                    {
                        if (i == 0)
                        {
                            transformed_sentence[c++] = '(';
                            transformed_sentence[c++] = '-';
                        }
                        else if (i == nnuumm - 1)
                        {
                            transformed_sentence[c++] = '-';
                            transformed_sentence[c++] = ')';
                        }
                        else
                            transformed_sentence[c++] = '-';
                    }
                }
            }
        }
        else
        {
            if (is_number_suitable(num, digits) && is_number_even(num, digits)) // if even
            {
                int nnuumm = the_number_itself(num, digits);

                for (int i = 0; i < nnuumm; i++) //вставляем нужное количество символов в зависимости от числа
                {
                    if (i == 0)
                    {
                        transformed_sentence[c++] = '(';
                        transformed_sentence[c++] = '+';
                    }
                    else if (i == nnuumm - 1)
                    {
                        transformed_sentence[c++] = '+';
                        transformed_sentence[c++] = ')';
                    }
                    else
                        transformed_sentence[c++] = '+';
                }
            }
            else if (is_number_suitable(num, digits) == true && is_number_even(num, digits) == false)
            {
                int nnuumm = the_number_itself(num, digits);

                for (int i = 0; i < nnuumm; i++) //вставляем нужное количество символов в зависимости от числа
                {
                    if (i == 0)
                    {
                        transformed_sentence[c++] = '(';
                        transformed_sentence[c++] = '-';
                    }
                    else if (i == nnuumm - 1)
                    {
                        transformed_sentence[c++] = '-';
                        transformed_sentence[c++] = ')';
                    }
                    else
                        transformed_sentence[c++] = '-';
                }
            }
            else
            {
                while (digits)
                {
                    transformed_sentence[c++] = sentence[i - digits];
                    digits--;
                }
            }
            transformed_sentence[c++] = sentence[i];
            digits = 0;
        }
    }

    // предложение новой длины
    *new_sentence = new char[c + 1];

    for (unsigned long i = 0; i < c; i++)
        (*new_sentence)[i] = transformed_sentence[i];

    for (unsigned long i = 0; i < c; i++)
        cout << transformed_sentence[i];

}

string sen(string s) //задание 2
{
    bool flag = true;
    string tmp = s;
    string ans;

    regex nums("[^0-9]|^([0-9]+)[^0-9]");
    smatch m; //экземпляр шаблона класса match_results для сопоставления строковых объектов
    s += " ";
    while (regex_search(s, m, nums)) //Поиск соответствия регулярному выражению.
    {
        if (m[1] != "")
        {
            if (stoi(m[1]) > 19)
            {
                flag = false;
            }
            string r = "";
            int len = stoi(m[1]);
            if (len % 2 == 0)
            {
                r.insert(0, len, '+');
            }
            else
            {
                r.insert(0, len, '-');
            }
            if (len)
            {
                ans = tmp.replace(tmp.find(m[1]), m[1].length(), "(" + r + ")");
            }
            else
            {
                ans = tmp.replace(tmp.find(m[1]), m[1].length(), "0");
            }
        }
        s = m.suffix();
    }
    if (flag)
    {
        cout << ans << "\n";
    }
    else
    {
        cout << "Error! Each number in a string should be >= 0 and <= 19!\n";
    }
    cout << endl;
    return ans;
}

int main()
{
    setlocale(LC_ALL, "");
    cout << "Практическая работа №3 Тараканова Евгения. Вариант 10" << endl;

    cout << "Условие задачи:  " << endl;
    cout << "Дано предложение, состоящее из слов, разделенных запятой или пробелами, среди которых есть группы цифр, определяющих целые числа из диапазона [0..19]." << endl;
    cout << "Отредактировать введенную строку, заменив каждое число, на последовательность, заключенную в круглые скобки, символа + , (если число четное) ";
    cout << endl << "или на –(если число нечетное), длина которой равна найденному числу." << endl;
    cout << endl <<"Выберите способ решения задачи:" << endl << "1 - строки c-string" << endl << "2 - string" << endl;
    int mode, size;
    do
    {
        cin >> mode;
        if (mode < 1 || mode > 3) cout << "Такого режима нет. Введите число от 1 до 3: ";
    } while (mode < 1 || mode > 3);


    switch (mode)
    {
    case 1:
    {//строки c-string
        cout << "Решение с помощью строк в стиле С: " << endl << endl;
        char* new_sentence;

        cout << "Строка 1, над которой нужно произвести операции: " << endl;
        const char* sentence1 = "Tell 65432 me I'm 4, a screwed up 17 mess 6 234!";

        int k = strlen(sentence1);
        for (unsigned long i = 0; i < k; i++)
            cout << sentence1[i];
        cout << endl;

        cout << "Изменённая строка 1: " << endl;
        replace_numbers(sentence1, &new_sentence);
        cout << endl << endl;

        cout << "Строка 2, над которой нужно произвести операции: " << endl;
        const char* sentence2 = "That I never 28 4 listen 10 11 listen 1200";

        int l = strlen(sentence2);
        for (unsigned long i = 0; i < l; i++)
            cout << sentence2[i];
        cout << endl;

        cout << "Изменённая строка 2: " << endl;
        replace_numbers(sentence2, &new_sentence);
        cout << endl;
        cout << endl << "Программа успешно завершила свою работу." << endl << endl;
        break;
    }
    case 2:
    { //string
        cout << "Решение с помощью string: " << endl << endl;
        string chass1, chass2;
        cout << "Строка 1, над которой нужно произвести операции: " << endl;
        chass1 = "Tonight lets 4 get some 15";
        cout << chass1 << endl;
        //getline(cin, chass);
        cout << "Изменённая строка 1: " << endl;
        sen(chass1);
        cout << endl;

        cout << "Строка 2, над которой нужно произвести операции: " << endl;
        chass2 = "And live  9 while we're  8 young";
        cout << chass2 << endl;
        cout << "Изменённая строка 2: " << endl;
        sen(chass2);
        cout << endl;
        cout << "Программа успешно завершила свою работу." << endl << endl;
        break;
    }
    }
}
