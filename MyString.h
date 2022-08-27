#pragma once

class MyString
{
	char* string;
	int str_Length;

public:

	static int number;

	MyString(const char* stringP, int str_LengthP);
	MyString(const char* stringP) : MyString{stringP, (int) strlen(stringP)}{}
	MyString(const int str_LengthP) : MyString{new char[str_LengthP+1], str_LengthP}{}
	MyString();
	~MyString();
	MyString(const MyString& object);
	MyString(MyString&& object);
	MyString& operator=(const MyString& object);
	MyString& operator=(MyString&& object);
	void print();
	char* get_string();
	int get_str_length();
	void set_string(const char* stringP);
	void set_string(const int size);
	void clear_string();
	void MyStrcpy(const MyString& object);
	bool MyStrStr(const char* str);
	int  MyChr(char c);
	int MyStrLen();
	void MyStrCat(const MyString& b);
	void MyDelChr(char c);
	int MyStrCmp(const MyString& b);
	MyString& operator++();
	MyString& operator--();
	const MyString operator++(int);
	const MyString operator--(int);
	friend MyString operator+(const MyString& left, const MyString& right);
	char& operator[](int index);
	char operator[](int index) const;
	int operator()(char c);
	operator int();

};
