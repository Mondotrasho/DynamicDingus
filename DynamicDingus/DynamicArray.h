#pragma once
#include <cassert>


template<typename T>
class DynamicArray
{
public:
	DynamicArray(int startCapacity = 10,bool ord = true , bool sor = false)
	{
		//allocate space for 10 elements
		SetCapacity(startCapacity);

		//there is nothing in it
		size = 0;
		//is it an ordered array
		ordered = ord;
		//is it a sorted array
		sorted = sor;
	}

	DynamicArray(DynamicArray& other)
	{
		MakeCopyOf(other);
	}

	~DynamicArray()
	{
		delete[] data;
	}
	
	void PushBack(T value)
	{
		//todo MAYBE use insert short code BUT it would maybe use the for loop in insert TBD
		CheckExpand();

		//add our value on to the end
		data[size] = value;
		Grow();

		Sort();
	}

	void PushFront(T value)
	{
		//insert at begining
		Insert(value, 0);
	}

	void Insert(T value, int pos)
	{
		//Verify input
		VerifyPosIn(pos);

		CheckExpand();

		//move everything in array forward by one after the pos
		for (int i = size; i > pos; i--)
			data[i] = data[i - 1];

		//add our value on to the front
		data[pos] = value;
		Grow();

		Sort();
	}

	T PopBack()
	{
		//using 1 less
		Shrink();

		//return the last one
		return data[size];
	}
	T PopFront()
	{
		//store the front
		T value = data[0];
		//remove it
		Erase(0);
		
		return value;
	}
	void Erase(int pos)
	{
		VerifyPosOut(pos);

		if (ordered) {
			//move all above the  removed point down 1
			for (int i = pos; i < size; i++)
				data[i] = data[i + 1];
		}
		else
		{
			//copy last over removed one
			data[pos] = data[size - 1]; //todo check this is size - 1 the last one or the last - 1
		}
		Shrink();
	}
	void Sort()
	{
		//todo Impliment
	}
	void HashedSort(unsigned int hashtosearch)
	{
		//todo Impliment
	}
	void Hash()
	{
		//todo Impliment
	}
	void CheckVsHashed()
	{
		//todo Impliment
	}

	int GetSize()
	{
		return size;
	}
	T& operator[](int index)
	{
		return data[index];
	}
	void operator= (const DynamicArray& other)
	{
		MakeCopyOf(other);
	}
	void Clear()
	{
		size = 0;
	}
	
private:

	void Grow()
	{
		size++;
	}

	void Shrink()
	{
		size--;
		ClampSize();
	}

	void ClampSize()
	{
		if(size < 0)
		{
			size = 0;
		}
	}

	void VerifyPosOut(int pos)
	{
		//check its valid
		//less than 0 or greater than the size + 1
		//0   -  9       10
		//0   -  size    allocated
		//taking from 0 to size
		//taking from 0 to 9
		if (pos<0 || pos > size)
		{
			//"HEY THATS NOT IN RANGE"
			assert(true);
		}
	}
	void VerifyPosIn(int pos)
	{
		//check its valid
		//less than 0 or greater than the size + 1
		//0   -  9       10
		//0   -  size    allocated
		//adding from 0 to size + 1
		//adding from 0 to 10
		if (pos<0 || pos > size + 1)
		{
			//"HEY THATS TOO FAR INTO OUR ARRAY"
			assert(true);
		}
	}

	void MakeCopyOf(const DynamicArray& other)
	{
		//allocate the same ammount of memory as the other has
		SetCapacity(other.capacity);

		//fill data in
		size = other.size;
		for (int i = 0; i < size; ++i)
			data[i] = other.data[i];

		ordered = other.ordered;
		sorted = other.sorted;
	}

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
	//FOR VIEWING IN WATCH USE data,10 etc data beingthe name and 10 being the number of spaces into the array you want to read
	T* data; // our heap allocation for storing the contents of the dynamic array

	//todo variants for ordered or sorted arrays 
	//sort on add or not
	//Ordered removal or not
	//
	bool ordered; // is it an ordered array
	bool sorted; // is it sorted
};
