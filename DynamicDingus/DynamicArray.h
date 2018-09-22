#pragma once


template<typename T>
class DynamicArray
{
public:
	DynamicArray(int startCapacity = 10)
	{
		//allocate space for 10 elements
		SetCapacity(startCapacity);

		//there is nothing in it
		size = 0;
	}

	void PushBack(T value)
	{
		CheckExpand();

		//add our value on to the end
		data[size] = value;
		size++;
	}

	void PushFront(T value)
	{
		CheckExpand();

		//move everything in array forward by one
		for (int i = size; i > 0; i--)
			data[i] = data[i - 1];

		//add our value on to the front
		data[0] = value;
		size++;
	}

private:

	void SetCapacity(int cap)
	{
		capacity = cap;
		data = new T[capacity];
	}

	void CheckExpand()
	{
		if (size == capacity)
		{
			//dopuble capacity
			capacity *= 2; //todo do we want to double it
			T* newData = new T[capacity];

			//copy existing members to new bigger array
			for (int i = 0; i < size; i++)
				newData[i] = data[i];
			
			//delete the old allocation
			delete[] data;
			data = newData;
		}
	}
	int size; //size Number of elements in our array atm
	int capacity; // number of elements which have memory allocated for
	T* data; // our heap allocation for storing the contents of the dynamic array
};