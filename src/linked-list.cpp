#pragma once
#include ".\..\include\linked-list.h"
#include ".\..\include\color_out.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace train_namespace;

LinkedList::LinkedList()
{
    FIRST = nullptr;
    CURRENT = nullptr;
    LAST = nullptr;
    count_elements = 0;
}

LinkedList::~LinkedList()
{
    if (count_elements != 0)
    {
        while (count_elements != 0 && FIRST->next != nullptr)
        {
            CURRENT = FIRST;
            FIRST = FIRST->next;
            delete CURRENT;
            count_elements -= 1;
        }
        if (count_elements != 0)
        {
            delete FIRST;
        }
    }
}

void LinkedList::add(TRAIN *new_element)
{
    add(new_element, count_elements);
}

void LinkedList::add(TRAIN *new_element, int num)
{
    if (num > count_elements)
    {
        num = count_elements;
        wcolor_out(L"[Linked list] [add] : num over count elements \n", "red");
        wcolor_out(L"[Linked list] [add] : add last element in list \n", "red");
    }
    else if(num < 0)
    {
        num = 0;
        wcolor_out(L"[Linked list] [add] : num less 0 \n", "red");
        wcolor_out(L"[Linked list] [add] : add first element in list \n", "red");
    }

    if(FIRST == nullptr)
    {
        FIRST = new_element;
        LAST = new_element;
        new_element->next = nullptr;
        new_element->prev = nullptr;
    }
    else
    {
        if (num == 0) 
        {
            new_element->prev = nullptr;
            FIRST->prev = new_element;
            new_element->next = FIRST;

            FIRST = new_element;
        }
        else if (num == count_elements)
        {
            new_element->next = nullptr;
            LAST->next = new_element;
            new_element->prev = LAST;

            LAST = new_element;
        }
        else
        {
            CURRENT = FIRST;
            while (CURRENT->next != nullptr && num > 0)
            {
                CURRENT = CURRENT->next;
                num -= 1;
            }

            //          paste before CURRENT
            CURRENT->prev->next = new_element;
            new_element->prev = CURRENT->prev;
            CURRENT->prev = new_element;
            new_element->next = CURRENT;
        }
    }

    count_elements += 1;
}

void LinkedList::del(int num)
{
    if (num == -1)
    {
        num = count_elements - 1;
    }
    else if (num > count_elements - 1 && count_elements != 0)
    {
        num = count_elements - 1;
        wcolor_out(L"[Linked list] [del] : num over count elements \n", "red");
        wcolor_out(L"[Linked list] [del] : delete last element in list \n", "red");
    }
    else if(num < -1)
    {
        num = 0;
        wcolor_out(L"[Linked list] [del] : num less 0 \n", "red");
        wcolor_out(L"[Linked list] [del] : command were ignored \n", "red");
        return;
    }

    if(FIRST == nullptr || count_elements == 0)
    {
        // list empty
        wcolor_out(L"[Linked list] [del] : list empty \n", "red");
        return;
    }
    else if(FIRST == LAST)
    {
        // only 1 element
        delete FIRST;
    }
    else
    {
        if (num == 0) 
        {
            FIRST = FIRST->next;
            delete FIRST->prev;
            FIRST->prev = nullptr;
        }
        else if (num == count_elements - 1)
        {
            LAST = LAST->prev;
            delete LAST->next;
            LAST->next = nullptr;
        }
        else
        {
            CURRENT = FIRST;
            while (CURRENT->next != nullptr && num > 0)
            {
                CURRENT = CURRENT->next;
                num -= 1;
            }

            //          paste before CURRENT        // it's ok
            CURRENT->prev->next = CURRENT->next;    // becose first and last 
            CURRENT->next->prev = CURRENT->prev;    // processing apart
            delete CURRENT;
        }
    }
    
    count_elements -= 1;
}

TRAIN LinkedList::get(int num)
{
    if (num == -1)
    {
        num = count_elements - 1;
    }
    else if (num > count_elements - 1 && count_elements != 0)
    {
        num = count_elements - 1;
        wcolor_out(L"[Linked list] [get] : num over count elements \n", "red");
        wcolor_out(L"[Linked list] [get] : return last element in list \n", "red");
    }
    else if(num < -1)
    {
        num = 0;
        wcolor_out(L"[Linked list] [get] : num less 0 \n", "red");
        wcolor_out(L"[Linked list] [get] : return first element in list \n", "red");
    }


    if(FIRST == nullptr || count_elements == 0)
    {
        // list empty
        wcolor_out(L"[Linked list] [get] : list empty \n", "red");
        TRAIN error_TRAIN;
        error_TRAIN.destination[0] = '\0';
        error_TRAIN.number = 0;
        error_TRAIN.time.str[0] =  {'\0'};
        return error_TRAIN;
    }
    else if(FIRST == LAST)
    {
        // only 1 element
        return *FIRST;
    }
    else
    {
        if (num == 0) 
        {
            return *FIRST;
        }
        else if (num == count_elements - 1)
        {
            return *LAST;
        }
        else
        {
            CURRENT = FIRST;
            while (CURRENT->next != nullptr && num > 0)
            {
                CURRENT = CURRENT->next;
                num -= 1;
            }
            return *CURRENT;
        }
    }
}

TRAIN *LinkedList::search(int number)
{
    // find train for nuber
    CURRENT = FIRST;
    if(CURRENT == nullptr || count_elements == 0) { return nullptr; }

    while (CURRENT->next != nullptr)
    {
        if (CURRENT->number == number)
        {
            return CURRENT;
        }
        CURRENT = CURRENT->next;
    }

    if(CURRENT->number == number){ return CURRENT; }
    else { return nullptr; }
}

void LinkedList::edit(TRAIN new_element, int num)
{
    TRAIN *element;
    element = search(num);

    if (element == nullptr) 
    {
        wcolor_out(L"[LinkedList::edit] : element not found \n", "red"); 
        return;
    }

    element->number = new_element.number;
    element->time = new_element.time;
    int i = 0;
    for(auto e : element->destination)
    {
        element->destination[i] = new_element.destination[i];
        i++;
    }
}

void LinkedList::swap(TRAIN *l, TRAIN *r)
{
    TRAIN *nex = r->next;
    TRAIN *last = l->prev;

    if (l == FIRST)
    {
        if (last != nullptr) { last->next = r; }
        l->next = nex;
        l->prev = r;
        r->next = l;
        r->prev = last;
        if (nex != nullptr) { nex->prev = l; }
        FIRST = r;
    }
    else if(r == LAST)
    {
        if (last != nullptr) { last->next = r; }
        l->next = nex;
        l->prev = r;
        r->next = l;
        r->prev = last;
        if (nex != nullptr) { nex->prev = l; }
        LAST = l;
    }
    else
    {
        if (last != nullptr) { last->next = r; }
        l->next = nex;
        l->prev = r;
        r->next = l;
        r->prev = last;
        if (nex != nullptr) { nex->prev = l; }
    }
}

void LinkedList::bubble_sort()
{
    bool swaps = 1;
    while (swaps){
        swaps = false;
        for (TRAIN *ptr = FIRST; ptr != nullptr && ptr->next != nullptr; ptr = ptr->next) {
            if ( ptr->number > ptr->next->number )
            {
                swap(ptr, ptr->next);
                swaps = true;
            }
        }
    }
}

void LinkedList::read()
{
    wifstream fin("in.txt");   // входной поток
    fin >> *this;
    fin.close();
}

void LinkedList::read(wchar_t str[])
{
    wifstream fin(str);   // входной поток
    fin >> *this;
    fin.close();
}

void LinkedList::save()
{
    wofstream fout("out.txt");  // выходной поток
    fout << *this;
    fout.close();
}

void LinkedList::save(wchar_t str[])
{
    wofstream fout(str);  // выходной поток
    fout << *this;
    fout.close();
}


void LinkedList::print()
{
    CURRENT = FIRST;
    int num = count_elements;
    wcout << L"\n";
    wcout << L"╔══════╦══════════╦═══════════════════════════╦══════════╗ \n";
    wcout << L"║  id  ║  number  ║        destination        ║   time   ║ \n";
    while (CURRENT != nullptr && num != 0)
    {
        wcout << L"╠══════╬══════════╬═══════════════════════════╬══════════╣ \n";
        wcout.setf(std::ios::left); wcout << L"╽ "  /* ╏ ╎ ║ ╽ */ << std::setw(5)  << count_elements - num;
        wcout.setf(std::ios::left); wcout << L"╽ "  /* ╏ ╎ ║ ╽ */ << std::setw(9)  << CURRENT->number;
        correct_to_rus_symbol_str(CURRENT->destination);
        wcout.setf(std::ios::left); wcout << L"╽ "  /* ╏ ╎ ║ ╽ */ << std::setw(26) << CURRENT->destination;
        correct_from_rus_symbol_str(CURRENT->destination);
        wcout.setf(std::ios::left); wcout << L"╽ "  /* ╏ ╎ ║ ╽ */ << std::setw(9)  << CURRENT->time;
                                    wcout << L"╽\n" /* ╏ ╎ ║ ╽ */   ;
        CURRENT = CURRENT->next;
        num--;
    }
    wcout << L"╚══════╩══════════╩═══════════════════════════╩══════════╝ \n";
    wcout << L"\n";
}

int LinkedList::size() { return count_elements; }

std::wostream  &operator<<(std::wostream &out,   u_time &t)
{
    convert_time(t);
    out << t.str;

    return out;
}

std::wistream  &operator>>(std::wistream &in,    u_time &t)
{
    wcout << L"hour   : "; in >> t.hour;
    wcout << L"minute : "; in >> t.minute;
    wcout << L"second : "; in >> t.second;
    convert_time(t);
    return in;
}

std::wofstream &operator<<(std::wofstream &fout, u_time &t)
{
    fout << t.str;

    return fout;
}

std::wifstream &operator>>(std::wifstream &fin,  u_time &t)
{
    wchar_t symbol = ' ';
    wchar_t tmp[2] = {' ', ' '};

    fin >> tmp[0];
    fin >> tmp[1];
    t.hour   = char2int(tmp[0])*10 + char2int(tmp[1]);
    fin >> symbol; // get ':'
    fin >> tmp[0];
    fin >> tmp[1];
    t.minute = char2int(tmp[0])*10 + char2int(tmp[1]);
    fin >> symbol; // get ':'
    fin >> tmp[0];
    fin >> tmp[1];
    t.second = char2int(tmp[0])*10 + char2int(tmp[1]);
    convert_time(t);
    return fin;
}

std::wostream  &operator<<(std::wostream &out,   LinkedList &obj)
{
    out << L"\n";
    obj.print();
    out << L"\n";

    return out;
}

std::wofstream &operator<<(std::wofstream &fout, LinkedList &obj)
{
    obj.CURRENT = obj.FIRST;
    int num = obj.count_elements;
    while (obj.CURRENT != nullptr && num > 0)
    {
        fout << obj.CURRENT->number << endl;
        fout << obj.CURRENT->destination << endl;
        fout << obj.CURRENT->time << endl;
        obj.CURRENT = obj.CURRENT->next;
        num--;
    }
    fout << L"\n";

    return fout;
}

std::wifstream &operator>>(std::wifstream &fin,  LinkedList &obj)
{
    while (!fin.eof())
    {
        TRAIN* new_element = new TRAIN;
        fin >> new_element->number;
        fin >> new_element->destination;
        fin >> new_element->time;
        obj.add(new_element);
    }
    obj.del();

    return fin;
}

std::wostream  &operator<<(std::wostream  &out,  TRAIN &n)
{
    out << L"╔══════════╦═══════════════════════════╦══════════╗ \n";
    out << L"║  number  ║        destination        ║   time   ║ \n";
    out << L"╠══════════╬═══════════════════════════╬══════════╣ \n";
    out.setf(std::ios::left); out << L"║ " << std::setw(9)  << n.number;
    correct_to_rus_symbol_str(n.destination);
    out.setf(std::ios::left); out << L"║ " << std::setw(26) << n.destination;
    correct_from_rus_symbol_str(n.destination);
    out.setf(std::ios::left); out << L"║ " << std::setw(9)  << n.time;
    out << L"║\n";
    out << L"╚══════════╩═══════════════════════════╩══════════╝ \n";

    return out;
}

bool operator< (u_time t1, u_time t2)
{
    if (t1.hour < t2.hour)
    {
        return true;
    }
    else if (t1.hour == t2.hour)
    {
        if (t1.minute < t2.minute)
        {
            return true;
        }
        else if (t1.minute == t2.minute)
        {
            if (t1.second < t2.second)
            {
                return true;
            }
            else if (t1.second == t2.second)
            {
                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }        
    }
    else
    {
        return false;
    }
}
bool operator> (u_time t1, u_time t2)
{
    if (t1.hour > t2.hour)
    {
        return true;
    }
    else if (t1.hour == t2.hour)
    {
        if (t1.minute > t2.minute)
        {
            return true;
        }
        else if (t1.minute == t2.minute)
        {
            if (t1.second > t2.second)
            {
                return true;
            }
            else if (t1.second == t2.second)
            {
                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool operator<=(u_time t1, u_time t2)
{
    if(t1.hour == t2.hour && t1.minute == t2.minute && t1.second == t2.second)
    {
        return true;
    }

    if (t1.hour <= t2.hour)
    {
        return true;
    }
    else if (t1.hour == t2.hour)
    {
        if (t1.minute <= t2.minute)
        {
            return true;
        }
        else if (t1.minute == t2.minute)
        {
            if (t1.second <= t2.second)
            {
                return true;
            }
            else if (t1.second == t2.second)
            {
                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool operator>=(u_time t1, u_time t2)
{
    if (t1.hour == t2.hour && t1.minute == t2.minute && t1.second == t2.second)
    {
        return true;
    }

    if (t1.hour >= t2.hour)
    {
        return true;
    }
    else if (t1.hour == t2.hour)
    {
        if (t1.minute >= t2.minute)
        {
            return true;
        }
        else if (t1.minute == t2.minute)
        {
            if (t1.second >= t2.second)
            {
                return true;
            }
            else if (t1.second == t2.second)
            {
                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

TRAIN* gen_rand_train()
{
    TRAIN* train = new TRAIN;
    train->time.hour   = 0 + rand() % 12;
    train->time.minute = 0 + rand() % 60;
    train->time.second = 0;
    train->number      = 0 + rand() % 1000;

    int i = 0;
    bool format[] = { 1, 1, 1, 1, 1, 1 };  // char -> 1		int -> 0
    for (bool f : format)
    {
        train->destination[i] = gen_rand_key(f);
        i += 1;
    }

    train->next = nullptr;
    train->prev = nullptr;

    return train;
}

wchar_t gen_rand_key(bool f)
{
    wchar_t key;
    int MIN_VALUE_C = 65;
    int MAX_VALUE_C = 122;
    int MIN_VALUE_I = 0;
    int MAX_VALUE_I = 9;

    int tmp;
    if (f) // char
    {
        tmp = MIN_VALUE_C + rand() % MAX_VALUE_C;
        while (!is_char(tmp))
        {
            tmp = MIN_VALUE_C + rand() % MAX_VALUE_C;
        }
        key = tmp;
    }
    else // int
    {
        tmp = MIN_VALUE_I + rand() % MAX_VALUE_I;
        while (!is_num_i(tmp))
        {
            tmp = MIN_VALUE_I + rand() % MAX_VALUE_I;
        }
        key = num2char(tmp);
    }
    return key;
}

bool is_num_c(char num)
{
    char nums[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    for (auto i : nums)
    {
        if (num == i)
        {
            return true;
        }
    }
    return false;
}

bool is_num_i(int num)
{
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    for (auto i : nums)
    {
        if (num == i)
        {
            return true;
        }
    }
    return false;
}

bool is_char(int c)
{
    if ((64 < c) && (c < 91) || (96 < c) && (c < 123))
    {
        return true;
    }
    else
    {
        return false;
    }
}

wchar_t num2char(int i) // 48 char == 0 int
{
    return i + 48;
}

int char2int(wchar_t c) // 48 char == 0 int
{
    return c - 48;
}

void convert_time(u_time &t)
{
    // ints to str
    wchar_t temp[2] = {'0','0'};
    if(t.hour / 10 == 0) // one-digit number
    {
        temp[0] = '0';
        temp[1] = num2char(t.hour);
    }
    else // two-digit number
    {
        temp[0] = num2char(t.hour / 10);
        temp[1] = num2char(t.hour % 10);
    }

    t.str[0] = temp[0];
    t.str[1] = temp[1];

    if(t.minute / 10 == 0)
    {
        temp[0] = '0';
        temp[1] = num2char(t.minute);
    }
    else
    {
        temp[0] = num2char(t.minute / 10);
        temp[1] = num2char(t.minute % 10);
    }

    t.str[3] = temp[0];
    t.str[4] = temp[1];

    if(t.second / 10 == 0)
    {
        temp[0] = '0';
        temp[1] = num2char(t.second);
    }
    else
    {
        temp[0] = num2char(t.second / 10);
        temp[1] = num2char(t.second % 10);
    }

    t.str[6] = temp[0];
    t.str[7] = temp[1];
}


bool is_russ(wchar_t c)
{
	return c >= 192 && c<= 255;
}

// A == 1040 // print
// А == 192 // input
// Я == 223 // input
// а == 224 // input
// я == 255 // input
void correct_to_rus_symbol(wchar_t &symbol)
{
    if (is_russ(symbol))
    {
        symbol = wchar_t( int(symbol) + 848);
    }
}

void correct_to_rus_symbol_str(wchar_t str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        correct_to_rus_symbol(str[i]);
        i++;
    }    
}

void correct_from_rus_symbol(wchar_t &symbol)
{
    if ( is_russ( wchar_t( int(symbol) - 848) ) )
    {
        symbol = wchar_t( int(symbol) - 848);
    }
}

void correct_from_rus_symbol_str(wchar_t str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        correct_from_rus_symbol(str[i]);
        i++;
    }
}
