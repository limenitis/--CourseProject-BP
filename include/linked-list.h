#pragma once
#include <iostream>
#include <fstream>

namespace train_namespace 
{
    using std::cerr;
    using std::cin;
    using std::clog;
    using std::cout;
    using std::wcerr;
    using std::wclog;
    using std::wcout;
    using std::wcin;
    using std::endl;
    using std::istream;
    using std::ostream;
    using std::ifstream;
    using std::ofstream;
    using std::wistream;
    using std::wostream;
    using std::wifstream;
    using std::wofstream;
}

struct u_time
{
    wchar_t str[9] = {'0','0',':','0','0',':','0','0','\0'};
    int hour = 0;
    int minute = 0;
    int second = 0;
};

/*  
    Самое длинное название города в мире (57): 
    Лланвайрпуллгуингиллг        
    огерихуирндробуллллан        
    тисилиогогого́х               

    Самое длинное название города в России (25): 
    Александровск-Сахалинский
*/

struct TRAIN
{
    int number;
    wchar_t destination[57]{'\0'}; 
    u_time time;
    TRAIN* next;
    TRAIN* prev;
};

void convert_time(u_time &t);

wchar_t  gen_rand_key(bool);
TRAIN*   gen_rand_train();

bool is_num_c (char);
bool is_num_i (int );
bool is_char  (int );

wchar_t  num2char(int    );
int      char2int(wchar_t);

bool is_russ(wchar_t c);
void correct_to_rus_symbol(wchar_t &symbol);
void correct_to_rus_symbol_str(wchar_t str[]);
void correct_from_rus_symbol(wchar_t &symbol);
void correct_from_rus_symbol_str(wchar_t str[]);

class LinkedList {
protected:
    void  swap(TRAIN *l, TRAIN *r);

    TRAIN* FIRST;
    TRAIN* CURRENT;
    TRAIN* LAST;
    int count_elements;

public:
    LinkedList(); 
    ~LinkedList();

    void add(TRAIN *element);
    void add(TRAIN *element, int num);
    void del(int num = -1);

    TRAIN  get(int num);
    TRAIN* search(int number);

    void edit(TRAIN new_element, int num);
    void bubble_sort();

    void read();
    void read(wchar_t str[]);
    void save();
    void save(wchar_t str[]);
    void print();

    int size();

    friend std::wostream&  operator<< (std::wostream&  out,  LinkedList& obj);
    friend std::wofstream& operator<< (std::wofstream& fout, LinkedList& obj);
    friend std::wifstream& operator>> (std::wifstream& fin,  LinkedList& obj);
};

bool operator< (u_time t1, u_time t2);
bool operator> (u_time t1, u_time t2);
bool operator<=(u_time t1, u_time t2);
bool operator>=(u_time t1, u_time t2);

std::wostream&  operator<< (std::wostream&  out,  TRAIN &n);

std::wostream&  operator<< (std::wostream&  out,  u_time &t);
std::wistream&  operator>> (std::wistream&  in,   u_time &t);
std::wofstream& operator<< (std::wofstream& fout, u_time& obj);
std::wifstream& operator>> (std::wifstream& fin,  u_time& obj);
