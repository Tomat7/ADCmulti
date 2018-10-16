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
#ifndef ADCmulti_h
#define ADCmulti_h

#include "Arduino.h"

#define LIBVERSION "ADCmulti_v20181016 #pin: "

class ADCmulti
{
public:
	//ADCmulti();
	ADCmulti(int pin1);
	ADCmulti(int pin1, int pin2);
	ADCmulti(int pin1, int pin2, int pin3);
	//ADCmulti(int pin1, int pin2, int pin3, int pin4);
	
	void init();
	void check();
	int read(int pin);
	
	//=== Прерываниe
	static void GetADC_int() __attribute__((always_inline));
	
protected:
	volatile static unsigned int _cntr;
	volatile static unsigned long _Summ;
	byte nSensor_;
	int *pPin_;
	int *pVar_;
	
	int i;

};

#endif
