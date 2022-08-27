#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "MyString.h"
using namespace std;

MyString::MyString(const char* stringP, int str_LengthP) :
	string{ stringP ? new char[strlen(stringP) + 1] : nullptr },
	str_Length{ str_LengthP }
{
	if (string)
	{
		strcpy_s(string, strlen(stringP) + 1, stringP);
		/*cout << "String constructed\n";*/
	}
	number++;
}
MyString::MyString() : string {nullptr}, str_Length{0}{}

void MyString::set_string (const char* stringP)
{
	str_Length = strlen(stringP);
	strcpy_s(string, str_Length + 1, stringP);
	number++;
}

MyString::MyString(const MyString& object) : string{ new char[object.str_Length+1] }, str_Length{ object.str_Length }
{
	strcpy_s(string, object.str_Length + 1, object.string);
	number++;
}

char* MyString::get_string() { return string; }

MyString::~MyString()
{
	delete[] string;
}

int MyString::get_str_length()
{
	return str_Length;
}
void MyString::print()
{
	if (string != nullptr)
	{
		cout << "\nThe string: " << string << endl;
		cout << "String Length: " << str_Length << endl;
	}
	else
		cout << "Empty object!" << endl;
}
void MyString::set_string(const int size)
{
	char* temp = new char[size];

	cout << "\nEnter your string: ";
	cin >> temp;

	str_Length = strlen(temp);
	strcpy_s(string, str_Length+1, temp);

	delete[] temp;

}
void MyString::clear_string()
{
	delete[] string;
	string = nullptr;
	str_Length = 0;
}
void MyString::MyStrcpy(const MyString& object) 
{
	str_Length = object.str_Length;
	string = new char[object.str_Length+1];
	strcpy_s(string, object.str_Length + 1, object.string);
}
bool MyString::MyStrStr(const char* str)
{
	if (strstr(string, str))
	{
		cout << "\nThe string " << string << " include the substring " << str <<"\n";
		return true;
	}
	else
	{
		cout << "\nThe string " << string << " doesn't include the substring " << str << "\n";
		return false;
	}
}
int MyString::MyChr(char c)
{
	int result;

	char* pch;
	pch = strchr(string, c);

	if (pch)
	{
		cout << endl << "The string " << string << " include character " << c << endl;	
		result = pch - string + 1;
		cout << "Position of first inclusion is " << result << endl;
	}
	else
	{
		cout << endl << "The string " << string << " doesn't include character " << c << endl;
		result = -1;
	}

	return result;
}
int MyString::MyStrLen() {return str_Length;}
void MyString::MyStrCat(const MyString& b)
{
	char* temp1 = new char[str_Length + b.str_Length + 1];

	
	char* dest = temp1;
	char* src{ string };
	char* end{ temp1 + str_Length };

	if (str_Length) {
		while (dest < end)
		{
			*dest++ = *src++;
		}
	}
	src = b.string;
	end += b.str_Length;

	while (dest < end)
	{
		*dest++ = *src++;
	}
	*end = '\0';

	str_Length += b.str_Length;

	string = new char[str_Length + 1];
	strcpy_s(string, str_Length + 1, temp1);
	
	delete[] temp1;
}
void MyString::MyDelChr(char c)
{
	int temp = MyChr(c);

	if (temp != -1)
	{
		if (temp != str_Length)
		{
			for (int i = temp - 1; i < str_Length - 1; i++)
			{
				string[i] = string[i + 1];
			}
		}
		
		str_Length--;

		char* temp = new char[str_Length+1];

		for (int i = 0; i < str_Length; i++)
			temp[i] = string[i];
		temp[str_Length] = '\0';

		strcpy_s(string, str_Length + 1, temp);

		delete[] temp;
	}
}
int MyString::MyStrCmp(const MyString& b)
{
//Х	int MyStrCmp(MyString& b); // сравнение строк 
//-1 Ц перва€ строка меньше чем втора€
//1 Ц перва€ больше чем втора€
//0 Ц строки равны!
	int result, tmp;

	tmp = strcmp(string, b.string);

	if (tmp > 0)
		result = 1;
	else if (tmp == 0)
		result = 0;
	else
		result = -1;

	return result;
} 
MyString& MyString::operator++()
{
	char* temp = new char[str_Length + 3];
	strcpy_s(temp, str_Length+1, string);
	strncat(temp," ", 2);

	++str_Length;
	string = new char[str_Length + 1];

	strcpy_s(string, str_Length + 1, temp);

	delete[] temp;

	return *this;
}
MyString& MyString::operator--()
{
	char* temp = new char[str_Length];
	for (int i = 0; i < str_Length - 1; i++)
	{
		temp[i] = string[i];
	}
	temp[str_Length - 1] = '\0';

	--str_Length;
	string = new char[str_Length + 1];  

	strcpy_s(string, str_Length + 1, temp);

	delete[] temp;

	return *this;
	
} 
const MyString MyString::operator++(int)
{
	MyString temp{string, str_Length};

	++(*this);
	return temp;

}
const MyString MyString::operator--(int)
{
	MyString temp{ string, str_Length };

	--(*this);
	return temp;
}
char& MyString::operator[](int index)
{
	if (index < 0 || index >= str_Length)
	{
		cout << "Out of range\n";
		exit(1);
	}

	return string[index];
}
char MyString::operator[](int index) const
{
	if (index < 0 || index >= str_Length)
	{
		cout << "Out of range\n";
		exit(1);
	}

	return string[index];
}
int MyString::operator()(char c)
{
	int temp = MyChr(c);
	return temp;
}
MyString::operator int()
{
	return (int) str_Length;
}
MyString operator+(const MyString& left, const MyString& right)
{
	MyString temp;
	temp.MyStrCat(left);
	temp.MyStrCat(right);

	return temp;
}
MyString& MyString::operator+=(const MyString& object)
{
	(*this).MyStrCat(object);
	return *this;
}
bool operator==(const MyString& left, const MyString& right)
{
	MyString temp;
	temp = left;

	return !temp.MyStrCmp(right);
}
bool operator!=(const MyString& left, const MyString& right)
{
	MyString temp;
	temp = left;

	return temp.MyStrCmp(right);
}
MyString::MyString(MyString&& object) 
	:string{ new char[object.str_Length + 1] }, str_Length{ object.str_Length }
{
	strcpy_s(string, object.str_Length + 1, object.string);
	object.string = nullptr;
	object.str_Length = 0;
	number++;
	cout << "MyString move constructed\n";
}

MyString& MyString::operator=(const MyString& object)
{
	if(!(this == &object))
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

	return *this;
}

MyString& MyString::operator=(MyString&& object)
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

	return *this;
}
