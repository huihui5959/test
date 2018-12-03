#include "AbstractFactory.h"
#include "properties.h"
#include <string>
#include <map>
#include <Windows.h>
using namespace std;
//class Vector2
//{
//public:
//	int x;
//	int y;
//
//	PROPERTY(int, Length);
//	GET(Length) 
//	{ 
//		return (x*x + y*y);
//	}
//};
char * deleteSpace(char * str){
    char * tail = str;
    char * next = str;

    //while(*next){ // 两个if可以合并到一块儿，这样写只是为了看着方便
    //    if(*next != ' '){ // 查找不是空格的字符
    //        *tail = *next;
    //        tail++;
    //    }
    //    if(*next == ' ' && *(next-1) != ' '){ // 只留一个空格的判断条件；当前字符为空格且前一个不为空格。
    //        *tail = *next;
    //        tail++;
    //    }
    //    next++;
    //}
    //*tail='\0'; // 字符串结束
	char* begin=str;
	while(*next){
		if(*next == ' '){
			begin++;
			//*begin = *(next +1);
		}
		next++;
	}
    return begin;
}

HANDLE hEvent = NULL;  
void OnTestEvent_(){
	/*HANDLE CreateEvent(
		LPSECURITY_ATTRIBUTES lpEventAttributes,
		BOOL bManualReset, 
		BOOL bInitialState,
		LPCSTR lpName
	);
		bManualReset:TRUE，使用ResetEvent()手动重置为无信号状态；FALSE，当一个等待线程被释放时,自动重置状态为无信号状态。

		bInitialState：指定事件对象的初始状态，当TRUE,初始状态为有信号状态；当FALSE,初始状态为无信号状态。*/
	hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	printf("OnTestEvent_()   start!");
}


int main(){

	char a[21] = "      1234";

	char* b="123456";
	char* res = deleteSpace(a);
	printf("res:%s:res\n",res);
	int result = strcmp(res,b);
	printf("结果：%d",result);
	map<char*,char*>* ma = new map<char*,char*>();
	char* in="cu1809";
	char* in2="cu1800";
	in2 = "cu1809";
	ma->insert(make_pair(in,in2));
	map<char*,char*>::iterator it = ma->find(in2);
	if(it!=ma->end()){
		printf("sfs");
	}

	/*
	AbstractFactory* factory = new FactoryA();
	AbstractProduct* product = factory->createProduct();
	product->operation();
	delete product;
	product = NULL;
	delete factory;
	factory = NULL;

	factory = new FactoryB();
	product = factory->createProduct();
	product->operation();
	delete product;
	product = NULL;
	delete factory;
	factory = NULL;
	return 0;
	
	enum Suit { Diamonds, Hearts, Clubs, Spades };
	Suit a;
	if(a==Clubs){
		printf("fsfs");
	}*/

	/*Vector2 vec;
	vec.x = 1;
	vec.y = 1;
	printf("Length of vector(%d,%d)=%d\n",vec.x,vec.y,vec.Length);
	

	return 0;*/
	
}