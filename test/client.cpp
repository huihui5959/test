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

    //while(*next){ // ����if���Ժϲ���һ���������дֻ��Ϊ�˿��ŷ���
    //    if(*next != ' '){ // ���Ҳ��ǿո���ַ�
    //        *tail = *next;
    //        tail++;
    //    }
    //    if(*next == ' ' && *(next-1) != ' '){ // ֻ��һ���ո���ж���������ǰ�ַ�Ϊ�ո���ǰһ����Ϊ�ո�
    //        *tail = *next;
    //        tail++;
    //    }
    //    next++;
    //}
    //*tail='\0'; // �ַ�������
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
		bManualReset:TRUE��ʹ��ResetEvent()�ֶ�����Ϊ���ź�״̬��FALSE����һ���ȴ��̱߳��ͷ�ʱ,�Զ�����״̬Ϊ���ź�״̬��

		bInitialState��ָ���¼�����ĳ�ʼ״̬����TRUE,��ʼ״̬Ϊ���ź�״̬����FALSE,��ʼ״̬Ϊ���ź�״̬��*/
	hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	printf("OnTestEvent_()   start!");
}


int main(){

	char a[21] = "      1234";

	char* b="123456";
	char* res = deleteSpace(a);
	printf("res:%s:res\n",res);
	int result = strcmp(res,b);
	printf("�����%d",result);
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