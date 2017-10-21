#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include<iostream>

using namespace std;

// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

class Book {
public:
int number;
int price;
};

void test(Book* head)
{
Book* p = new Book;
p->number =1;
p->price = 2;
head = p;
//(head)->number = 1;
//(head)->price = 2;
}
/*
int main()
{
Book* head = new Book;

head->number = 11;

head->price = 22;

test(head);
cout<<"num:"<<head->number<<" price:"<<head->price<<endl;
return 0;
}*/
