/*
	Класс IntegerArray — контейнер данных (целые числа типа int)
	Объект класса хранит массив чисел и способен динамически
	(во время работы программы) изменять свой размер.
*/

#pragma once
#ifndef INTEGER_ARRAY_H_SENTRY
#define INTEGER_ARRAY_H_SENTRY

#include <iostream>
#include <string>
#include <exception>


class IntegerArray {
	public:
		IntegerArray();
		IntegerArray(int capacity);
		IntegerArray(const IntegerArray& other);
		~IntegerArray();

		IntegerArray& operator=(const IntegerArray& other);

		/**
		\return Емкость массива
		*/
		int getCapacity() const;

		/**
		\return Текущее количество элементов в массиве
		*/
		int getSize() const;

		/**
		Возвращает по заданному индексу значение элемента в массиве
		\param[in] index Индекс элемента
		\return Значение элемента
		*/
		int getValue(int index) const;

		/**
		\return Признак пуст ли массив
		*/
		bool isEmpty() const;

		/**
		Помещает в начало массива заданное значение
		\param[in] value Значение
		*/
		void pushFront(int value);

		/**
		Помещает в конец массива заданное значение
		\param[in] value Значение
		*/
		void pushBack(int value);

		/**
		Помещает значение по заданному индексу
		\param[in] value Значение
		\param[in] index Индекс
		*/
		void push(int value, int index);

		/**
		Изменяет емкость массива.
		Если заданная емкость меньше текущей - элементы которые
		не поместились отбрасываются
		\param[in] capacity Емкость
		*/
		void resize(int capacity);

		/**
		Удаляет из массива элемент по заданному индексу.
		Смещает все элементы после удаляемого на 1 назад
		\param[in] size Емкость
		*/
		void remove(int index);

		/**
		Удаляет все элементы из массива.
		*/
		void clear();

		/**
		Возвращает индекс первого элемента в массива с заданным значением
  		Если элемент не найден - возвращает текущее количество элементов + 1
		\param[in] value Значение
		\return Индекс
		*/
		int findValue(int value);

	private:
		/**
		Смещает элементы массива, начиная с позиции index, на 1 вперед.
		\param[in] index Индекс элемента массива, начиная с которого смещать
		*/
		void moveForward(int index);

		/**
		Смещает элементы массива, начиная с позиции index, на 1 назад.
		\param[in] index Индекс элемента массива, начиная с которого смещать
		*/
		void moveBack(int index);

		int capacity_;	///<Емкость массива
		int size_;		///<Текущее количество элементов в массиве
		int* data_;		///<Указатель на участок памяти в котором расположен массив
};

#endif