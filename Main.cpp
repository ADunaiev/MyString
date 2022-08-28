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
    Bite_String& sign_change();
    void size_increase(int size);
    void delete_sign();
    void add_sign(char c);
    Bite_String Sum(const Bite_String& object);
    bool operator<(const Bite_String& object);
    friend Bite_String operator+(const Bite_String& left, const Bite_String& right);
    Bite_String& operator+=(const Bite_String& object);
    bool operator==(const Bite_String& object);
    bool operator!=(const Bite_String& object);
    
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
        /*cout << "MyString move constructed\n";*/
    }
    else
    {
        /*cout << "\nError! Unacceptable operation!" << endl;*/
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
        /*cout << "MyString copy assigned\n";*/

    }
    else
    {
        /*cout << "\nError! Unacceptable operation!" << endl;*/
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
        /*cout << "MyString move assigned\n";*/

    }
    else
    {
        /*cout << "\nError! Unacceptable operation!" << endl;*/
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
Bite_String& Bite_String::sign_change()
{
    if (str_Length <= 1)
    {
        /*cout << "Sign change is impossible" << endl;*/
    }
    else
    {
        // from positive to negative
        if (string[0] == '0')
        {
            //change of 0 to 1, and 1 to 0
            for (size_t i = 0; i < str_Length; i++)
            {
                if (string[i] == '0')
                    string[i] = '1';
                else
                    string[i] = '0';
            }
            
            //adding 1
            int temp = 0;

            if (string[str_Length - 1] == '1')
            {
                string[str_Length - 1] = '0';
                temp = 1;
            }
            else
                string[str_Length - 1] = '1';

            if (str_Length > 2)
            {
                for (size_t i = str_Length - 2; i > 0; i--)
                {
                    if (string[i] == '1' && temp == 1)
                    {
                        string[i] = '0';
                        temp = 1;
                    }
                    else
                    {
                        if (temp == 1)
                        {
                            string[i] = '1';
                            temp = 0;
                        }
                        else
                            temp = 0;
                    }
                }
            }

            
        }
        else
        {
            //adding 1
            int temp = 0;

            if (string[str_Length - 1] == '1')
            {
                string[str_Length - 1] = '0';
            }
            else
            {
                string[str_Length - 1] = '1';
                temp = 1;
            }

            if (str_Length > 2)
            {
                for (size_t i = str_Length - 2; i > 0; i--)
                {
                    if (string[i] == '0' && temp == 1)
                    {
                        string[i] = '1';
                        temp = 1;
                    }
                    else
                    {
                        if (temp == 1)
                        {
                            string[i] = '0';
                            temp = 0;
                        }
                        else
                            temp = 0;
                    }
                }
            }

            //change of 0 to 1, and 1 to 0
            for (size_t i = 0; i < str_Length; i++)
            {
                if (string[i] == '0')
                    string[i] = '1';
                else
                    string[i] = '0';
            }

        }
    }

    return *this;
}
void Bite_String::size_increase(int size)
{
    if (size > str_Length)
    {
        char* temp = new char[size+1];
        char* dest = temp;
        char* source = string;

        *dest++ = *source++;

        for (size_t i = 1; i <= size - str_Length; i++)
            *dest++ = '0';
        
        for (size_t i = size - str_Length + 1; i < size; i++)
            *dest++ = *source++;
        *dest = '\0';
        
        str_Length = size;
        delete[] string;
        string = new char[size + 1];
        
        strcpy_s(string, size+1, temp);

        delete[] temp;
    }
    //else
    //   /* cout << "Unable to increase size!" << endl;*/
}
void Bite_String::delete_sign()
{
    if (string != nullptr)
    {
        char* temp = new char[str_Length];

        for (size_t i = 1; i < str_Length; i++)
            temp[i - 1] = string[i];
        temp[str_Length - 1] = '\0';

        str_Length--;
        delete[] string;
        string = new char[str_Length + 1];
        strcpy_s(string, str_Length + 1, temp);

        delete[] temp;
    }
}
void Bite_String::add_sign(char c)
{
    if (string != nullptr && (c == '1' || c == '0'))
    {
        char* temp = new char[str_Length + 2];
        temp[0] = c;

        for (size_t i = 0; i < str_Length; i++)
            temp[i + 1] = string[i];
        temp[str_Length + 1] = '\0';

        str_Length++;
        delete[] string;
        string = new char[str_Length + 1];
        strcpy_s(string, str_Length + 1, temp);

        delete[] temp;
    }
}
bool Bite_String::operator<(const Bite_String& object)
{
    Bite_String temp1, temp2;
    temp1 = *this;
    temp2 = object;
    int max = str_Length > object.str_Length ? str_Length : object.str_Length;

    temp1.size_increase(max);
    temp2.size_increase(max);

    temp1.delete_sign();
    temp2.delete_sign();

    return strcmp(temp1.string, temp2.string) < 0;
}
Bite_String Bite_String::Sum(const Bite_String& object)
{
    Bite_String sum;

    if (string != nullptr)
    {
        if (str_Length == object.str_Length)
        {
            int temp = 0;
            char c;
            Bite_String temp1, temp2;

            temp1 = *this;
            temp2 = object;

            if (temp1 < temp2)
                c = temp2.string[0];
            else
                c = temp1.string[0];

            temp1.delete_sign();
            temp2.delete_sign();

            sum.str_Length = temp1.str_Length;
            sum.string = new char[sum.str_Length + 1];

            for (int i = (str_Length -2); i >= 0; i--)
            {              
                if (temp1.string[i] == '1' && temp2.string[i] == '1')
                {
                    if (temp == 1)
                        sum.string[i] = '1';
                    else
                    {
                        sum.string[i] = '0';
                        temp = 1;
                    }                   
                }
                else if ((temp1.string[i] == '0' && temp2.string[i] == '1') ||
                    (temp1.string[i] == '1' && temp2.string[i] == '0'))
                {
                    if (temp == 1)
                        sum.string[i] = '0';
                    else
                        sum.string[i] = '1';
                }
                else
                {
                    if (temp == 1)
                    {
                        sum.string[i] = '1';
                        temp = 0;
                    }
                    else
                        sum.string[i] = '0';
                }
            }
            sum.string[sum.str_Length] = '\0';
            
            sum.add_sign(c);
           ;
        }
        else
            cout << "Operation impossible!" << endl;
    }
    return sum;
}
Bite_String operator+(const Bite_String& left, const Bite_String& right)
{
    Bite_String t1(left);
    Bite_String t2(right);
    Bite_String sum;

    if (left.string[0] == right.string[0])
    {
        int max = left.str_Length > right.str_Length ? left.str_Length : right.str_Length;

        t1.size_increase(max);
        t2.size_increase(max);

        sum = t1.Sum(t2);

    }
    else 
    {   
        char c;

        if (t1.string[0] == '0')
        {
            t2.sign_change();

            if (t1 < t2)
                c = '1';
            else
                c = '0';

            t2.sign_change();

            int max = t1.str_Length > t2.str_Length ? t1.str_Length : t2.str_Length;
            t1.size_increase(max);
            t2.size_increase(max);

            sum = t1.Sum(t2);
            sum.string[0] = c;

        }
        else
        {
            t1.sign_change();

            if (t1 < t2)
                c = '0';
            else
                c = '1';

            t1.sign_change();

            int max = t1.str_Length > t2.str_Length ? t1.str_Length : t2.str_Length;
            t1.size_increase(max);
            t2.size_increase(max);

            sum = t1.Sum(t2);
            sum.string[0] = c;
        }
     
    }

    return sum;
}
Bite_String& Bite_String::operator+=(const Bite_String& object)
{
    *this = *this + object;
    return * this;
}
bool Bite_String::operator==(const Bite_String& object)
{
    if (str_Length == object.str_Length)
    {
        return !strcmp(string, object.string);
    }
    else
        return 0; 
}
bool Bite_String::operator!=(const Bite_String& object)
{
    return !( * this == object);
}

int main()
{          

    Bite_String b1("01101");
    cout << "\nObject b1:";
    b1.print();

    Bite_String b2("10000111");
    cout << "\nObject b2:";
    b2.print();

    cout << "\nb1 + b2 is ";
    (b1 + b2).print();

    cout << "\nb1 += b2 is ";
    (b1 += b2).print();

    Bite_String b3(b1);
    cout << "\nObject b3:";
    b3.print();

    cout << "\nb1 == b2 ? " << (b1 == b2) << endl;
    cout << "b1 == b3 ? " << (b1 == b3) << endl;

    cout << "\nb1 != b2 ? " << (b1 != b2) << endl;
    cout << "b1 != b3 ? " << (b1 != b3) << endl;

    return 0;
}
 