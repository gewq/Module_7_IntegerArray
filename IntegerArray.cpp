#include "IntegerArray.h"

//Public методы========================================================
IntegerArray::IntegerArray() :capacity_(1), size_(0)
{
	data_ = new int[capacity_] {0};
}



IntegerArray::IntegerArray(int capacity) : capacity_(capacity), size_(0)
{
	//Некорректная емкость
	if (capacity <= 0) {
		std::string errorMessage = "Error: capacity (" + std::to_string(capacity) + ") <= 0";
		throw std::length_error(errorMessage.c_str());
	}
	data_ = new int[capacity_] {0};
};



IntegerArray::IntegerArray(const IntegerArray& other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;
	data_ = new int[capacity_] {0};
	//Скопировать массив
	for (int i = 0; i < size_; ++i) {
		data_[i] = other.data_[i];
	}
}



IntegerArray::~IntegerArray()
{
	delete[] data_;
}



IntegerArray& IntegerArray::operator=(const IntegerArray& other)
{
	//Присваивание объекта самому себе
	if (this == &other) {
		return *this;
	}
	size_ = other.size_;
	capacity_ = other.capacity_;
	delete[] data_;

	data_ = new int[capacity_] {0};
	//Скопировать массив
	for (int i = 0; i < size_; ++i) {
		data_[i] = other.data_[i];
	}
	return *this;
}



int IntegerArray::getCapacity() const
{
	return capacity_;
}



int IntegerArray::getSize() const
{
	return size_;
}



int IntegerArray::getValue(int index) const
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_ - 1)) {
		std::string errorMessage = "Error: index (" + std::to_string(index) + ") is out_of_range";
		throw std::out_of_range(errorMessage.c_str());
	}
	return data_[index];
}



bool IntegerArray::isEmpty() const
{
	if (size_ == 0) {
		return true;
	}
	return false;
}



void IntegerArray::pushFront(int value)
{
	//Массив уже полон
	if (size_ == capacity_) {
		resize(size_*2);
	}
	//Сместить все элементы на 1 вперед
	moveForward(0);

	data_[0] = value;
	++size_;
}



void IntegerArray::pushBack(int value)
{
	//Массив уже полон
	if (size_ == capacity_) {
		resize(size_*2);
	}

	data_[size_] = value;
	++size_;
}



void IntegerArray::push(int value, int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		std::string errorMessage = "Error: index (" + std::to_string(index) + ") is out_of_range";
		throw std::out_of_range(errorMessage.c_str());
	}
	//Вставить в начало
	if (index == 0) {
		pushFront(value);
	}
	//Вставить в конец
	else if (index == size_) {
		pushBack(value);
	}
	else {
		//Массив уже полон
		if (size_ == capacity_) {
			resize(size_*2);
		}
		moveForward(index);
		data_[index] = value;
		++size_;
	}
}



void IntegerArray::resize(int capacity)
{
	//Некорректная емкость
	if (capacity < 0) {
		std::string errorMessage = "Error: capacity (" + std::to_string(capacity) + ") < 0";
		throw std::out_of_range(errorMessage.c_str());
	}
	capacity_ = capacity;
	if (capacity < size_) {
		size_ = capacity;
	}

	//Выделить новую память
	int* newData = new int[capacity_];
	//Скопировать массив
	for (int i = 0; i < size_; ++i) {
		newData[i] = data_[i];
	}
	//Освободить память текущего массива
	delete[] data_;
	//Указать на новый массив
	data_ = newData;
}



void IntegerArray::remove(int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		std::string errorMessage = "Error: index (" + std::to_string(index) + ") is out_of_range";
		throw std::out_of_range(errorMessage.c_str());
	}
	//Массив НЕ пуст
	if (size_ > 0) {
		moveBack(index);
		--size_;
	}
}



void IntegerArray::clear()
{
	size_ = 0;
}



int IntegerArray::findValue(int value)
{
	for (int i = 0; i < size_; ++i) {
		if (data_[i] == value) {
			return i;	//Выход потому что нужен первый элемент
		}
	}
	return size_+1;
}



//Pivate методы========================================================
void IntegerArray::moveForward(int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		std::string errorMessage = "Error: index (" + std::to_string(index) + ") is out_of_range";
		throw std::out_of_range(errorMessage.c_str());
	}
	//Сместить все элементы на 1 вперед
	for (int i = size_; i > index; --i) {
		data_[i] = data_[i - 1];
	}
}



void IntegerArray::moveBack(int index)
{
	//Индекс за пределами массива
	if ((index < 0) || (index > size_)) {
		std::string errorMessage = "Error: index (" + std::to_string(index) + ") is out_of_range";
		throw std::out_of_range(errorMessage.c_str());
	}
	//Сместить все элементы на 1 назад
	for (int i = index; i < size_; ++i) {
		data_[i] = data_[i + 1];
	}
}