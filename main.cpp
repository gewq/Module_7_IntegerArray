/*
Функция main() содержит функции тестирования класса IntegerArray.

Функциональность контейнера IntegerArray:
	- создать контейнер
	- скопировать контейнер
	- получить доступ к любому элементу контейнера по индексу
	- изменить размер контейнера
	- вставить элемент в контейнер
	- удалить элемент из контейнера
	- вставить элемент в начало
	- вставить элемент в конец
	- поиск элемента в контейнере по значению

Поддерживаются исключения:
	- не удалось выделить память
	- некорректная ёмкость (<= 0) контейнера
	- обращение по некорректному индексу (выход за границы массива)
*/

#include <iostream>
#include <assert.h>
#include <exception>

#include "IntegerArray.h"	//Контейнер int



static void testConstructors();
static void testPushFront();
static void testPushBack();
static void testPushIndex();
static void testResize();
static void testRemove();
static void testFind();
static void testEquality();
static void testIsEmpty();
static void testClear();



int main()
{
	try {
		testConstructors();
		testPushFront();
		testPushBack();
		testPushIndex();
		testResize();
		testRemove();
		testFind();
		testEquality();
		testIsEmpty();
		testClear();
	}
	catch (std::bad_alloc& error) {
		std::cerr << "Allocation failed: " << error.what() << std::endl;
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (std::length_error& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Undefined exception" << std::endl;
	}

	return EXIT_SUCCESS;
}



static void testConstructors()
{
	//Тест конструктора по-умолчанию
	IntegerArray* intArray_1 = new IntegerArray;
	assert(intArray_1->getCapacity() == 1);	//Конструктор по-умолчанию задаёт емкость = 1
	assert(intArray_1->getSize() == 0);		//Контейнер пуст

	//Тест параметризованного конструктора
	IntegerArray* intArray_2 = new IntegerArray(543);
	assert(intArray_2->getCapacity() == 543);	//Параметризованный конструктор устанавливает заданную емкость
	assert(intArray_2->getSize() == 0);			//Контейнер пуст

	//Тест копирующего конструктора
	//Поместим элементы в контейнер чтобы было что проверять
	intArray_1->pushBack(643);
	intArray_1->pushBack(23);
	intArray_1->pushBack(5342);
	intArray_1->pushBack(262);

	IntegerArray intArray_3(*intArray_1);
	//Все параметры должны совпадать
	assert(intArray_3.getCapacity() == intArray_1->getCapacity());
	assert(intArray_3.getSize() == intArray_1->getSize());
	assert(intArray_3.getValue(0) == intArray_1->getValue(0));
	assert(intArray_3.getValue(1) == intArray_1->getValue(1));
	assert(intArray_3.getValue(2) == intArray_1->getValue(2));
	assert(intArray_3.getValue(3) == intArray_1->getValue(3));

	IntegerArray intArray_4 = intArray_3;
	assert(intArray_4.getCapacity() == intArray_3.getCapacity());
	assert(intArray_4.getSize() == intArray_3.getSize());
	assert(intArray_4.getValue(0) == intArray_3.getValue(0));
	assert(intArray_4.getValue(1) == intArray_3.getValue(1));
	assert(intArray_4.getValue(2) == intArray_3.getValue(2));
	assert(intArray_4.getValue(3) == intArray_3.getValue(3));

	//Выброс исключения
//	IntegerArray intArray_Exception(-1);
//	IntegerArray intArray_Exception(0);
//	IntegerArray* pIntArray_Exception = new IntegerArray(-156);
//	IntegerArray* pIntArray_Exception = new IntegerArray(0);
//	intArray_1->getValue(235262462);

	delete intArray_1;
	delete intArray_2;
}



static void testPushFront()
{
	const int capacityIni = 3;

	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->pushFront(12);
	intArray_1->pushFront(69);
	intArray_1->pushFront(103);
	//Четвёртый элемент намеренно превышает емкость чтобы проверить
	//увеличение ёмкости
	intArray_1->pushFront(45);

	//При вставке элемента в полный контейнер ёмкость удваивается
	assert(intArray_1->getCapacity() == capacityIni*2);
	assert(intArray_1->getSize() == 4);
	assert(intArray_1->getValue(0) == 45);
	assert(intArray_1->getValue(1) == 103);
	assert(intArray_1->getValue(2) == 69);
	assert(intArray_1->getValue(3) == 12);

	//Выброс исключения
//	intArray_1->getValue(-98);
//	intArray_1->getValue(465);
	delete intArray_1;
}



static void testPushBack()
{
	const int capacityIni = 3;

	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->pushBack(12);
	intArray_1->pushBack(643);
	intArray_1->pushBack(23);
	//Четвёртый элемент намеренно превышает емкость чтобы проверить
	//увеличение ёмкости
	intArray_1->pushBack(5342);

	//При вставке элемента в полный контейнер ёмкость удваивается
	assert(intArray_1->getCapacity() == capacityIni*2);
	assert(intArray_1->getSize() == 4);
	assert(intArray_1->getValue(0) == 12);
	assert(intArray_1->getValue(1) == 643);
	assert(intArray_1->getValue(2) == 23);
	assert(intArray_1->getValue(3) == 5342);

	//Выброс исключения
//	intArray_1->getValue(-98);
//	intArray_1->getValue(465);
	delete intArray_1;
}



static void testPushIndex()
{
	const int capacityIni = 3;

	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->push(12, 0);
	intArray_1->push(512, 1);
	intArray_1->push(234, 0);
	//4-5 элемент намеренно превышает емкость чтобы проверить
	//увеличение ёмкости
	intArray_1->push(633, 3);
	intArray_1->push(8092, 2);

	assert(intArray_1->getCapacity() == capacityIni*2);
	assert(intArray_1->getSize() == 5);
	assert(intArray_1->getValue(0) == 234);
	assert(intArray_1->getValue(1) == 12);
	assert(intArray_1->getValue(2) == 8092);
	assert(intArray_1->getValue(3) == 512);
	assert(intArray_1->getValue(4) == 633);

	//Выброс исключения
//	intArray_1->push(10, 99999);
//	intArray_1->push(10, -1);

	delete intArray_1;
}



static void testResize()
{
	const int capacityIni = 3;
	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->pushFront(11);
	intArray_1->pushBack(98);

	intArray_1->resize(4);	//Увеличить емкость
	assert(intArray_1->getSize() == 2);		//Размер не изменился
	assert(intArray_1->getCapacity() == 4);	//Емкость увеличилась
	assert(intArray_1->getValue(0) == 11);
	assert(intArray_1->getValue(1) == 98);

	intArray_1->pushBack(235);
	intArray_1->pushBack(622);
	assert(intArray_1->getValue(2) == 235);
	assert(intArray_1->getValue(3) == 622);

	intArray_1->resize(2);	//Уменьшить емкость
	assert(intArray_1->getSize() == 2);		//Размер уменьшился до емкости
	assert(intArray_1->getCapacity() == 2);	//Емкость уменьшилась
	assert(intArray_1->getValue(0) == 11);
	assert(intArray_1->getValue(1) == 98);

	//Выброс исключения
//	intArray_1->resize(-1);
	//Элементы отброшены
//	assert(intArray_1->getValue(2) == 235);
//	assert(intArray_1->getValue(3) == 622);

	delete intArray_1;
}



static void testRemove()
{
	const int capacityIni = 10;

	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->pushBack(12);
	intArray_1->pushBack(643);
	intArray_1->pushBack(23);
	intArray_1->pushBack(5342);
	intArray_1->pushBack(235);
	intArray_1->pushBack(734);
	intArray_1->pushBack(853236);
	intArray_1->pushBack(74577);

	//Удалить первый элемент
	intArray_1->remove(0);
	assert(intArray_1->getCapacity() == capacityIni);	//Емкость не изменилась
	assert(intArray_1->getSize() == 7);					//Размер уменьшился
	assert(intArray_1->getValue(0) == 643);
	assert(intArray_1->getValue(1) == 23);
	assert(intArray_1->getValue(2) == 5342);
	assert(intArray_1->getValue(3) == 235);
	assert(intArray_1->getValue(4) == 734);
	assert(intArray_1->getValue(5) == 853236);
	assert(intArray_1->getValue(6) == 74577);

	//Удалить последний элемент
	intArray_1->remove(6);
	assert(intArray_1->getCapacity() == capacityIni);	//Емкость не изменилась
	assert(intArray_1->getSize() == 6);					//Размер уменьшился
	assert(intArray_1->getValue(0) == 643);
	assert(intArray_1->getValue(1) == 23);
	assert(intArray_1->getValue(2) == 5342);
	assert(intArray_1->getValue(3) == 235);
	assert(intArray_1->getValue(4) == 734);
	assert(intArray_1->getValue(5) == 853236);

	//Удалить элемент из середины
	intArray_1->remove(3);
	assert(intArray_1->getCapacity() == capacityIni);	//Емкость не изменилась
	assert(intArray_1->getSize() == 5);					//Размер уменьшился
	assert(intArray_1->getValue(0) == 643);
	assert(intArray_1->getValue(1) == 23);
	assert(intArray_1->getValue(2) == 5342);
	assert(intArray_1->getValue(3) == 734);
	assert(intArray_1->getValue(4) == 853236);

	//Тест удалить из пустого массива
	IntegerArray* intArray_2 = new IntegerArray(capacityIni);
	intArray_2->remove(0);
	assert(intArray_2->getCapacity() == capacityIni);
	assert(intArray_2->getSize() == 0);

	//Выброс исключения
//	intArray_2->remove(-1);
//	intArray_2->remove(100);

	delete intArray_1;
	delete intArray_2;
}



static void testFind()
{
	const int capacityIni = 3;

	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->pushBack(12);
	intArray_1->pushBack(643);
	intArray_1->pushBack(23);
	intArray_1->pushBack(5342);
	intArray_1->pushBack(23);
	
	//Возвращает индексы элементов
	assert(intArray_1->findValue(12) == 0);
	assert(intArray_1->findValue(643) == 1);
	assert(intArray_1->findValue(23) == 2);
	assert(intArray_1->findValue(5342) == 3);
	//Элемент не найден
	assert(intArray_1->findValue(42) == intArray_1->getSize()+1);	

	delete intArray_1;
}



static void testEquality()
{
	//Создать контейнеры разной емкости и заполнить
	//их разными значениями
	const int capacityIni_1 = 3;
	const int capacityIni_2 = 10;

	IntegerArray intArray_1(capacityIni_1);
	IntegerArray intArray_2(capacityIni_2);

	intArray_1.pushBack(12);
	intArray_1.pushBack(643);

	intArray_2.pushBack(325);
	intArray_2.pushBack(512);
	intArray_2.pushBack(1525);
	intArray_2.pushBack(25253);

	intArray_1 = intArray_2;
	//После присваивания все параметры одинаковые
	assert(intArray_1.getCapacity() == intArray_2.getCapacity() );
	assert(intArray_1.getSize() == intArray_2.getSize());
	assert(intArray_1.getValue(0) == intArray_2.getValue(0));
	assert(intArray_1.getValue(1) == intArray_2.getValue(1));
	assert(intArray_1.getValue(2) == intArray_2.getValue(2));
	assert(intArray_1.getValue(3) == intArray_2.getValue(3));
}



static void testIsEmpty()
{
	const int capacityIni = 3;

	IntegerArray* intArray_1 = new IntegerArray();
	IntegerArray* intArray_2 = new IntegerArray(capacityIni);
	assert(intArray_1->isEmpty() == true);
	assert(intArray_2->isEmpty() == true);

	intArray_1->pushBack(13);
	assert(intArray_1->isEmpty() == false);
	intArray_1->remove(0);
	intArray_1->remove(0);
	intArray_1->remove(0);
	assert(intArray_1->isEmpty() == true);

	delete intArray_1;
	delete intArray_2;
}



static void testClear()
{
	const int capacityIni = 10;

	IntegerArray* intArray_1 = new IntegerArray(capacityIni);
	intArray_1->pushBack(12);
	intArray_1->pushBack(643);
	intArray_1->pushBack(23);
	intArray_1->pushBack(5342);

	assert(intArray_1->getCapacity() == capacityIni);
	assert(intArray_1->getSize() == 4);
	assert(intArray_1->isEmpty() == false);

	intArray_1->clear();
	assert(intArray_1->getCapacity() == capacityIni);
	assert(intArray_1->getSize() == 0);
	assert(intArray_1->isEmpty() == true);

	//Выброс исключения
//	assert(intArray_1->getValue(0) == 12);
//	assert(intArray_1->getValue(1) == 643);
//	assert(intArray_1->getValue(2) == 23);
//	assert(intArray_1->getValue(3) == 5342);

	delete intArray_1;
}