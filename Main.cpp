#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "MyString.h"
using namespace std;

//Описать базовый класс «Строка».
//Методы:
//1) конструктор без параметров;
//2) конструктор, принимающий в качестве параметра C - строку(заканчивается нулевым байтом);
//3) конструктор копирования;
//4) оператор присваивания;
//5) получение длины строки;
//6) очистка строки(сделать строку пустой);
//7) деструктор;
//8) конкатенация строк(перегрузить операторы + и +=);
//9) проверка на равенство(= = ) и на неравенство(!= ).
// 
//Описать класс «Битовая строка» производный от класса «Строка».
//
//(Строки данного класса могут содержать только символы ‘0’ и ‘1’).Если в основе 
// инициализирующей строки встретятся любые символы, отличные от допустимых, то
//  «Битовая строка» становится пустой.Содержимое строки рассматривается как 
// двоичное представление целого числа со знаковым разрядом.Отрицательные числа 
// хранятся в дополнительном коде.
//Методы:
//1) конструктор без параметров;
//2) конструктор, принимающий в качестве параметра C - строку;
//3) конструктор копирования;
//4) оператор присваивания;
//4) деструктор;
// 
//5) изменение знака числа(перевод числа в дополнительный код);
//8) сложение битовых строк(перегрузить операторы + и += );
//9) проверка на равенство(= = ) и на неравенство(!= ).

int MyString::number{ 0 };

class Bite_String : public MyString
{
public:
    Bite_String();
    Bite_String(const char* stringP);
    ~Bite_String();
    Bite_String(const Bite_String& object);
    Bite_String(Bite_String && object);
    bool IsCorrect(const char* stringP);
    Bite_String& operator=(const Bite_String& object);
    Bite_String& operator=(Bite_String&& object);
    void empty();
    
};
Bite_String::Bite_String() 
{
    string = nullptr;
    str_Length = 0;
}
Bite_String::Bite_String(const char* stringP)
{

    if (!IsCorrect(stringP))
    {
        string = nullptr;
        str_Length = 0;
    }
    else
    {
        str_Length = strlen(stringP);
        string = new char[strlen(stringP) + 1];
        strcpy_s(string, strlen(stringP) + 1, stringP);
    }

}
Bite_String::Bite_String(const Bite_String& object) 
{
    if (IsCorrect(object.string))
    {
        string = new char[object.str_Length + 1];
        str_Length = object.str_Length;
        strcpy_s(string, object.str_Length + 1, object.string);
        number++;
    }
    else
    {
        cout << "\nError! Unacceptable operation!" << endl;
        empty();
    }
}
Bite_String::Bite_String(Bite_String&& object)
{
    if (IsCorrect(object.string))
    {
        string = new char[object.str_Length + 1];
        str_Length = object.str_Length;
        strcpy_s(string, object.str_Length + 1, object.string);
        object.string = nullptr;
        object.str_Length = 0;
        number++;
        cout << "MyString move constructed\n";
    }
    else
    {
        cout << "\nError! Unacceptable operation!" << endl;
        empty();
    }
}
bool Bite_String::IsCorrect(const char* stringP)
{
    int temp = 1;

    if (stringP != nullptr)
    {
        for (size_t i = 0; i < strlen(stringP); i++)
        {
            if (stringP[i] != '0' && stringP[i] != '1')
                temp = 0;
        }
    }
    else
        temp = 0;

    return temp;
}
Bite_String& Bite_String::operator=(const Bite_String& object)
{
    if (IsCorrect(object.string))
    {
        if (!(this == &object))
        {
            if (str_Length != object.str_Length)
            {
                delete string;
                string = new char[object.str_Length + 1];
            }

            str_Length = object.str_Length;
            char* dest = string;
            char* src{ object.string };
            char* const end{ string + str_Length };

            while (dest < end)
            {
                *dest++ = *src++;
            }
            *end = '\0';
        }
        cout << "MyString copy assigned\n";

    }
    else
    {
        cout << "\nError! Unacceptable operation!" << endl;
        empty();
    }

    return *this;
}
Bite_String& Bite_String::operator=(Bite_String&& object)
{
    if (IsCorrect(object.string))
    {
        if (!(this == &object))
        {
            delete string;

            string = new char[strlen(object.string) + 1];
            str_Length = object.str_Length;

            strcpy_s(string, object.str_Length + 1, object.string);

            object.string = nullptr;
            object.str_Length = 0;
        }
        cout << "MyString move assigned\n";

    }
    else
    {
        cout << "\nError! Unacceptable operation!" << endl;
        empty();
    }

    return *this;
}
void Bite_String::empty()
{
    delete[] string;
    string = nullptr;
    str_Length = 0;
}
Bite_String::~Bite_String()
{}

int main()
{          

    Bite_String b1("Rerw");
    cout << "\nObject b1:";
    b1.print();

    Bite_String b2("10011010101");
    cout << "\nObject b2:";
    b2.print();

    Bite_String b3(b2);
    cout << "\nObject b3:";
    b3.print();

    cout << "\nObject b1:";
    b1 = b3;
    b1.print();

    b2 = "10001";
    cout << "\nObject b2:";
    b2.print();

    b2 = "wefqev";
    cout << "\nObject b2:";
    b2.print();



    //cout << "str2 != str1 ? " << (str2 != str1) << endl;
    //cout << "str3 != str1 ? " << (str1 != str3) << endl;


    return 0;
}
 