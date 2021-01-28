#pragma once
#include ".\..\include\color_out.h"
#include ".\..\include\linked-list.h"
#include <string>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <Windows.h>
#include <iomanip>

// using namespace train_namespace;
using namespace std;

// Для обнаружения утечек памяти
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#define DumpMemoryLeaks                                 \
_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);        \
_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);      \
_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);       \
_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);     \
_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);      \
_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);    \
_CrtDumpMemoryLeaks();

vector <int> v; // история команд

/**
 * @brief               Функция проверяет не упал ли поток ввода
 *                      при попытке ввести не тот тип данных и проверяет
 *                      дополнительные условия checks
 * @tparam T            Тип запрашиваемых данных
 * @param message       Сообщение, какие данные нужны на ввод
 * @param var           Переменная куда записать входные данные
 * @param checks        Дополнительные проверки - функция принимающая var и выводящая сообщение
 *                      при неудачной проверке
 */
template <typename T>
void winput(const wchar_t* message, T &var, bool checks(T) = nullptr)
{
    while(true)
    {
        try
        {
            wcout << message; 
            wcin >> var;
            wcout << endl;
            v.push_back(int(var)); // история команд
            if (wcin.fail()) { throw 1; }

            // Проверка дополнительных условий
            if(checks)
            {
                 if (checks(var) == false)
                 {
                     throw 2;
                 }
            }
            break;
        }
        catch (int error_id)
        {
            switch (error_id)
            {
            case 1:
                wcin.clear();
                wcin.ignore();
                wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ \n", "red");
                wcolor_out(L"Неправильный тип данных \n", "red");
                wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ \n", "red");
                break;
            case 2:
                wcin.clear();
                wcin.ignore();
                // function checks() output message of error
                break;
            default:
                assert(0 && L"Undefined error_id");
            }
        }
        catch (...)
        {
            wcerr << L"Unknown error" << endl;
        }
    }
}

bool check_hour      ( int hour   );
bool check_minute    ( int minute );
bool check_second    ( int second );
bool check_positive  ( int var    );


int main()
{
    LinkedList* list = new LinkedList;
    TRAIN* element;
    TRAIN  element2;
    int input_int;
    wchar_t input_str[10];

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    input_int = _setmode(_fileno(stdout), _O_U16TEXT);

    while (true)
    {
        wcolor_out( L"╔═══════════════════════════════════════════════════════════════╗  \n", "cyan");
        wcolor_out( L"║                       Расписание поездов                      ║  \n", "cyan");
        wcolor_out( L"╠═══════════════════════════════════════════════════════════════╣  \n", "cyan");
        wcolor_out( L"║  mode 1  : Добавить n случайных поездов                       ║  \n", "cyan");
        wcolor_out( L"║  mode 2  : Добавить поезд в конец                             ║  \n", "cyan");
        wcolor_out( L"║  mode 3  : Добавить поезд в позицию id                        ║  \n", "cyan");
        wcolor_out( L"║  mode 4  : Удалить поезд                                      ║  \n", "cyan");
        wcolor_out( L"║  mode 5  : Посмотреть поезд в позиции id                      ║  \n", "cyan");
        wcolor_out( L"║  mode 6  : Найти поезд по номеру поезда                       ║  \n", "cyan");
        wcolor_out( L"║  mode 7  : Печать                                             ║  \n", "cyan");
        wcolor_out( L"║  mode 8  : Сортировка по номеру поезда                        ║  \n", "cyan");
        wcolor_out( L"║  mode 9  : Изменить поезд                                     ║  \n", "cyan");
        wcolor_out( L"║  mode 11 : Сохранить расписание                               ║  \n", "cyan");
        wcolor_out( L"║  mode 12 : Загрузить расписание                               ║  \n", "cyan");
        wcolor_out( L"║  mode 13 : Сохранить расписание (указать имя файла)           ║  \n", "cyan");
        wcolor_out( L"║  mode 14 : Загрузить расписание (указать имя файла)           ║  \n", "cyan");
        wcolor_out( L"║  mode 0  : Выйти                                              ║  \n", "cyan");
        wcolor_out( L"╚═══════════════════════════════════════════════════════════════╝  \n", "cyan");

        winput(L"mode : ", input_int);

        switch (input_int)
        {
        case 1:
            winput(L"Количество поездов : ", input_int, check_positive);
            while (input_int--)
            {
                list->add(gen_rand_train());
            }
            break;
        case 2:
            element = new TRAIN;
            winput(L"Номер поезда : ", element->number, check_positive);
            winput(L"Пункт назначения : ", element->destination);
            winput(L"час : ", element->time.hour, check_hour);
            winput(L"минута : ", element->time.minute, check_minute);
            winput(L"секунда : ", element->time.second, check_second);

            list->add(element);
            break;
        case 3:
            element = new TRAIN;
            winput(L"Номер поезда : ", element->number, check_positive);
            winput(L"Пункт назначения : ", element->destination);
            winput(L"час : ", element->time.hour, check_hour);
            winput(L"минута : ", element->time.minute, check_minute);
            winput(L"секунда : ", element->time.second, check_second);

            // winput(L"id : ", input_int, check_positive);
            winput(L"id : ", input_int);
            list->add(element, input_int);
            break;
        case 4:
            winput(L"id : ", input_int, check_positive);
            list->del(input_int);
            break;
        case 5:
            winput(L"id : ", input_int, check_positive);
            element2 = list->get(input_int);
            wcout << endl << element2 << endl;
            break;
        case 6:
            winput(L"Номер поезда : ", input_int, check_positive);
            element = list->search(input_int);
            if(element != nullptr)
            {
                wcout << *element;
            }
            else
            {
                wcolor_out(L"Не найден \n", "red");
            }
            break;
        case 7:
            list->print();
            break;
        case 8:
            list->bubble_sort();
            break;
        case 9:
            element = nullptr;
            while (true)
            {
                wcolor_out( L"╔═════════════════════════════════════════════╗  \n", "cyan");
                wcolor_out( L"║        Редактирование данных поезда         ║  \n", "cyan");
                wcolor_out( L"╠═════════════════════════════════════════════╣  \n", "cyan");
                wcolor_out( L"║  mode 1 : Выбрать поезд                     ║  \n", "cyan");
                wcolor_out( L"║  mode 2 : Изменить номер поезда             ║  \n", "cyan");
                wcolor_out( L"║  mode 3 : Изменить пункт назначения         ║  \n", "cyan");
                wcolor_out( L"║  mode 4 : Изменить час                      ║  \n", "cyan");
                wcolor_out( L"║  mode 5 : Изменить минуту                   ║  \n", "cyan");
                wcolor_out( L"║  mode 6 : Изменить секунду                  ║  \n", "cyan");
                wcolor_out( L"║  mode 0 : Выйти из редактирования           ║  \n", "cyan");
                wcolor_out( L"╚═════════════════════════════════════════════╝  \n", "cyan");

                wcout << L"╔═════════════════════════════════════════════════╗  \n";
                wcout << L"║                 Изменяемый поезд                ║  \n";
                wcout << L"╚═════════════════════════════════════════════════╝  \n";
                if (element) { wcout << *element << endl; }
                else 
                {
                    wcout << L"╔═════════════════════════════════════════════════╗  \n";
                    wcout << L"║ ::::::::::::::::::::: None :::::::::::::::::::: ║  \n";
                    wcout << L"╚═════════════════════════════════════════════════╝  \n";
                }

                winput(L"mode : ", input_int);
                if(input_int == 0) { break; }

                switch (input_int)
                {
                case 1:
                    winput(L" mode 1 : Изменение по номеру поезда \n mode 2 : Изменение по id поезда \n mode : ", input_int, check_positive);
                    if(input_int == 1)
                    {
                        winput(L"Номер поезда, который изменяем : ", input_int, check_positive);
                        element = list->search(input_int);
                    }
                    else if(input_int == 2)
                    {
                        winput(L"id поезда, который изменяем : ", input_int, check_positive);
                        element2 = list->get(input_int);
                        element = list->search(element2.number);
                    }
                    break;
                case 2:
                    winput(L"Новый номер поезда : ", element->number, check_positive);
                    break;
                case 3:
                    winput(L"Новый пункт назначения : ", element->destination);
                    break;
                case 4:
                    winput(L"Новый час : ", element->time.hour, check_hour);
                    break;
                case 5:
                    winput(L"Новая минута : ", element->time.minute, check_minute);
                    break;
                case 6:
                    winput(L"Новая секунда : ", element->time.second, check_second);
                    break;
                default:
                    wcolor_out(L"Такой опции нет \n", "red");
                    break;
                }
            }
            break;
        case 11:
            list->save();
            break;
        case 12:
            list->read();
            break;
        case 13:
            winput(L"Имя фала в который сохранить : ", input_str);
            list->save(input_str);
            break;
        case 14:
            winput(L"Имя фала из которого загрузить : ", input_str);
            list->read(input_str);
            break;
        case 0:
            delete list;
            
            wcout << L"--------------" << endl;
            wcout << L"История комманд" << endl;
            for(int i : v)
            {
                wcout << i << endl;
            }
            wcout << L"--------------" << endl;

            // из-за хранения команд существует утечка памяти
            // стоит заметить, что эта история существует только для удобства отладки 
            // (или например составления тестов)
            // так что в Release версии ее не будет, и следовательно это не ошибка

            DumpMemoryLeaks
            return 0;
        default:
            wcolor_out(L"Такой опции нет \n", "red");
            break;
        }
    }
}

bool check_hour     (int hour  ) 
{
    if (hour > -1 && hour < 24)
    {
        return true;
    }
    else
    {
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        wcolor_out(L"Неверное время! \n", "red");
        wcolor_out(L"Час должен быть больше 0 и меньше 24! \n", "red");
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        return false;
    }
}
bool check_minute   (int minute) 
{
    if (minute > -1 && minute < 60)
    {
        return true;
    }
    else
    {
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        wcolor_out(L"Неверное время! \n", "red");
        wcolor_out(L"Минута должна быть больше 0 и меньше 60! \n", "red");
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        return false;
    }
}
bool check_second   (int second) 
{
    if (second > -1 && second < 60)
    {
        return true;
    }
    else
    {
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        wcolor_out(L"Неверное время! \n", "red");
        wcolor_out(L"Секунда должна быть больше 0 и меньше 60! \n", "red");
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        return false;
    }
}
bool check_positive (int var )
{
    if (var >= 0)
    {
        return true;
    }
    else
    {
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        wcolor_out(L"Неверные двнные! \n", "red");
        wcolor_out(L"Значение должно быть положительным! \n", "red");
        wcolor_out(L"╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n", "red");
        return false;
    }
}
