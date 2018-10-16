/*
	Вольный перевод в библиотеку мелкие доработки алгоритма - Tomat7
*/

#include "Arduino.h"
#include "ADCmulti.h"
// defines for setting and clearing register bits

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

volatile unsigned int ADCmulti::_cntr;
volatile unsigned long ADCmulti::_Summ;

//================= Обработка прерывания АЦП для расчета среднеквадратичного тока
ISR(ADC_vect) {
	ADCmulti::GetADC_int();
}

ADCmulti::ADCmulti(int pin1)
{
	nSensor_ = 1;
	pPin_ = (int*) malloc(nSensor_ * sizeof(int));
	pVar_ = (int*) malloc(nSensor_ * sizeof(int));
	*pPin_ = pin1 - 14;
}

ADCmulti::ADCmulti(int pin1, int pin2)
{
	nSensor_ = 2;
	pPin_ = (int*) malloc(nSensor_ * sizeof(int));
	pVar_ = (int*) malloc(nSensor_ * sizeof(int));
	*pPin_ = pin1 - 14;
	*(pPin_+1) = pin2 - 14;
}

ADCmulti::ADCmulti(int pin1, int pin2, int pin3)
{
	nSensor_ = 3;
	pPin_ = (int*) malloc(nSensor_ * sizeof(int));
	pVar_ = (int*) malloc(nSensor_ * sizeof(int));
	*pPin_ = pin1 - 14;
	*(pPin_+1) = pin2 - 14;
	*(pPin_+2) = pin3 - 14;
}

ADCmulti::ADCmulti(int pin1, int pin2, int pin3, int pin4)
{
	nSensor_ = 4;
	pPin_ = (int*) malloc(nSensor_ * sizeof(int));
	pVar_ = (int*) malloc(nSensor_ * sizeof(int));
	*pPin_ = pin1 - 14;
	*(pPin_+1) = pin2 - 14;
	*(pPin_+2) = pin3 - 14;
	*(pPin_+3) = pin4 - 14;
}

void ADCmulti::init() //__attribute__((always_inline))
{  
	// настойка АЦП
	//ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0); // начинаем
	i = 0;
	ADMUX = _BV(REFS0) | *pPin_;
	ADCSRA = B11101111; //Включение АЦП
	ACSR = (1 << ACD);
	Serial.print(F(LIBVERSION));
	Serial.println(nSensor_);
	_Summ=0;		// ??
}

void ADCmulti::check()
{	
	if (_cntr == 1024)
	{	
		//_Summ >>= 10;
		//*(pVar_+i) = int(sqrt(_Summ));	// среднеквадратичное
		*(pVar_+i) = _Summ >> 10;		// среднеарифметическое
		i++;
		if (i == nSensor_) i = 0;
		ADMUX = _BV(REFS0) | *(pPin_+i);
		_Summ = 0;			// sei() and cli() ??
		_cntr = 1050;		// сбросим счетчик в "кодовое" значение 
	}
	return;
}

int ADCmulti::read() //__attribute__((always_inline))
{  
	return *pVar_;
}

int ADCmulti::read(int pin) //__attribute__((always_inline))
{  
	int Value;
	for (int n=0; n<nSensor_; n++)
	{
		if (*(pPin_+n) == (pin-14)) Value = *(pVar_+n);
	}
	return Value;
}

void ADCmulti::GetADC_int() //__attribute__((always_inline))
{
	unsigned long adcData = 0; //мгновенные значения 
	byte An_pin = ADCL;
	byte An = ADCH;
	if (_cntr < 1024)
	{
		adcData = ((An << 8) + An_pin);
		//adcData *= adcData;				// для среднеквадратичного
		_Summ += adcData;                   
		_cntr++;
	}
	if (_cntr == 1050) _cntr = 0;
	return;
}

/*
	//===========================================================Настройка АЦП
	
	ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0); //
	
	Биты 7:6 – REFS1:REFS0. Биты выбора опорного напряжения. Если мы будем менять эти биты во время преобразования,
	то изменения вступят в силу только после текущего преобразования. В качестве опорного напряжения может быть выбран AVcc
	(ток источника питания), AREF или внутренний 2.56В источник опорного напряжения.
	Рассмотрим какие же значения можно записать в эти биты:
	REFS1:REFS0
	00    AREF
	01    AVcc, с внешним конденсатором на AREF
	10    Резерв
	11    Внутренний 2.56В  источник, с внешним конденсатором на AREF
	Бит 5 – ADLAR. Определяет как результат преобразования запишется в регистры ADCL и ADCH.
	ADLAR = 0
	Биты 3:0 – MUX3:MUX0 – Биты выбора аналогового канала.
	MUX3:0
	0000      ADC0
	0001      ADC1
	0010      ADC2
	0011      ADC3
	0100      ADC4
	0101      ADC5
	0110      ADC6
	0111      ADC7
	
	
	//--------------------------Включение АЦП
	
	ADCSRA = B11101111;
	Бит 7 – ADEN. Разрешение АЦП.
	0 – АЦП выключен
	1 – АЦП включен
	Бит 6 – ADSC. Запуск преобразования (в режиме однократного
	преобразования)
	0 – преобразование завершено
	1 – начать преобразование
	Бит 5 – ADFR. Выбор режима работы АЦП
	0 – режим однократного преобразования
	1 – режим непрерывного преобразования
	Бит 4 – ADIF. Флаг прерывания от АЦП. Бит устанавливается, когда преобразование закончено.
	Бит 3 – ADIE. Разрешение прерывания от АЦП
	0 – прерывание запрещено
	1 – прерывание разрешено
	Прерывание от АЦП генерируется (если разрешено) по завершении преобразования.
	Биты 2:1 – ADPS2:ADPS0. Тактовая частота АЦП
	ADPS2:ADPS0
	000         СК/2
	001         СК/2
	010         СК/4
	011         СК/8
	100         СК/16
	101         СК/32
	110         СК/64
	111         СК/128
	
	//------ Timer1 ---------- Таймер задержки времени открытия триака после детектирования нуля (0 триак не откроется)
	
	TCCR1A = 0x00;  //
	TCCR1B = 0x00;    //
	TCCR1B = (0 << CS12) | (1 << CS11) | (1 << CS10); // Тактирование от CLK.
	
	// Если нужен предделитель :
	// TCCR1B |= (1<<CS10);           // CLK/1 = 0,0000000625 * 1 = 0,0000000625, 0,01с / 0,0000000625 = 160000 отсчетов 1 полупериод
	// TCCR1B |= (1<<CS11);           // CLK/8 = 0,0000000625 * 8 = 0,0000005, 0,01с / 0,0000005 = 20000 отсчетов 1 полупериод
	// TCCR1B |= (1<<CS10)|(1<<CS11); // CLK/64 = 0,0000000625 * 64 = 0,000004, 0,01с / 0,000004 = 2500 отсчетов 1 полупериод
	// TCCR1B |= (1<<CS12);           // CLK/256  = 0,0000000625 * 256 = 0,000016, 0,01с / 0,000016 = 625 отсчетов 1 полупериод
	// TCCR1B |= (1<<CS10)|(1<<CS12); // CLK/1024
	// Верхняя граница счета. Диапазон от 0 до 255.
	OCR1A = 0;           // Верхняя граница счета. Диапазон от 0 до 65535.
	
	// Частота прерываний будет = Fclk/(N*(1+OCR1A))
	// где N - коэф. предделителя (1, 8, 64, 256 или 1024)
	
	TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1); // Разрешить прерывание по совпадению и переполнению
	*/
