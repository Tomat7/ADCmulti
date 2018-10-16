/*
* Оригинальная идея (c) Sebra
* Алгоритм регулирования (c) Chatterbox
* 
* Вольный перевод в библиотеку Tomat7
* Version 0.7
* 
* A0 - подключение "измерителя" напряжения (трансформатор, диодный мост, делитель напряжения)
* A1 - подключение датчика тока ACS712
* D5 - управление триаком
* D3 - детектор нуля
*
*/
#ifndef AMread_h
#define AMread_h

#include "Arduino.h"

#define LIBVERSION "AMread_v20181015 on pin: "

class AMread
{
public:
	//AMread();
	AMread(int pin1);
	AMread(int pin1, int pin2);
	AMread(int pin1, int pin2, int pin3);
	AMread(int pin1, int pin2, int pin3, int pin4);
	
	void init();
	void check();
	int read(int pin);
	//int Value;

	//float Press_kPa;			// раскоментировать если нужны килоПаскали с плавающей точкой
	//uint16_t ADCperiod;		// DEBUG!! убрать
	
	//=== Прерываниe
	static void GetADC_int() __attribute__((always_inline));
	
protected:
	volatile static unsigned int _cntr;
	volatile static unsigned long _Summ;
	byte nSensor_;
	int *pPin_;
	int *pVar_;
	int **ppVal_;
	int pin_;
	int val_;
	int i = 0;

	//unsigned long _ADCmillis;			// DEBUG!! убрать
};

#endif
