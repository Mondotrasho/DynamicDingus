#pragma once
template <class TYPE>
class DynamicDingus
{
public:

	//  a.A constructor, destructor, assignment operator and copy constructor
	DynamicDingus();
	~DynamicDingus();
	DynamicDingus(const DynamicDingus<TYPE>*& other);
	DynamicDingus<TYPE>& operator = (const DynamicDingus<TYPE>& other);

	TYPE& operator[](int index);
	int getAllocatedInt() const { return allocatedElements / sizeof(TYPE); }
	int getUsedInt() const { return usedElements / sizeof(TYPE); }
	void setUsedInt(int a){usedElements = a * sizeof(TYPE)}
	//	b.Functions for adding and removing from the end of the array
	void pushback(TYPE value);
	void pushfront(TYPE value);
	bool isEmpty() const { return usedElements == 0; }
	void Clear();

	void pushbefore(TYPE value);
	void pushafter(TYPE value);
		
	    TYPE pop();

		void set(size_t index, TYPE value);
		TYPE get(size_t index);

		size_t size();
		size_t capacity();
		void print();

	private:
		size_t allocatedElements;
		size_t usedElements;
		TYPE* theArray;
		size_t initialSize ;
		int spaceMulti = 2;

		//Your class will need the following functions :
		
		
		//	c.Functions for adding 1 or more elements from the middle of the array
		//	d.Functions for removing from the middle of the array
		//	i.Both ordered and unordered removal
		//	e.Functions for changing how much space is allocated for the array
		//	i.If less space is allocated than is used, the extra used data is discarded
		//	f.A function for clearing the array
};
template<class TYPE>
DynamicDingus<TYPE>::DynamicDingus()
{
	initialSize = sizeof(TYPE) * 10;
	allocatedElements = initialSize;
	usedElements = 0;
	auto a = new TYPE[allocatedElements]();
	theArray = a;
}

template <class TYPE>
DynamicDingus<TYPE>::~DynamicDingus()
{
	delete[] theArray;
}

template <class TYPE>
void DynamicDingus<TYPE>::pushback(TYPE value)
{
	//IF array.allocatedElements == array.usedElements THEN
	if (allocatedElements == usedElements)
	{
		//	newData = new array[array.allocatedElements * 2];
		auto NewDingus = new DynamicDingus<TYPE>[allocatedElements * 2];
		//copy(newData, array.data, array.allocatedElements);
		copy(NewDingus, theArray, allocatedElements);
		//delete array.data
		delete theArray;
		//	array.data = newData;
		theArray = NewDingus;
		//array.allocatedElements *= 2
		allocatedElements *= 2;
	}
	if(theArray[usedElements] == value)
	{
		usedElements += 1 * sizeof(TYPE);
	}
	//	END IF
	//	array.data[array.usedElements] = newElement;
	//array.usedElements += 1;
}

template <class TYPE>
void DynamicDingus<TYPE>::pushfront(TYPE value)
{
	//IF array.allocatedElements == array.usedElements THEN
	if (allocatedElements == usedElements)
	{
		//	newData = new array[array.allocatedElements * 2];
		auto NewDingus = new TYPE[allocatedElements * spaceMulti];
		//copy(newData, array.data, array.allocatedElements);
		copy(NewDingus, theArray, allocatedElements);
		//delete array.data
		delete theArray;
		//	array.data = newData;
		theArray = NewDingus;
		//array.allocatedElements *= 2
		allocatedElements *= 2;
	}
	if (theArray[usedElements] == value)
	{
		usedElements += 1 * sizeof(TYPE);
	}
	//	END IF
	//	array.data[array.usedElements] = newElement;
	//array.usedElements += 1;
}

template <class TYPE>
void DynamicDingus<TYPE>::Clear()
{
	TYPE* a = new TYPE[sizeof(TYPE) * spaceMulti]();
	delete[] theArray;
	theArray = a;
}

template <class TYPE>
DynamicDingus<TYPE>& DynamicDingus<TYPE>::operator=(const DynamicDingus<TYPE>& other)
{
	if (this == &other)
	{
		return *this; // I am myself
	}
	if (other.isEmpty())
	{
		this->Clear(); //the one we are copying from is empty so I need to be too
	}
	auto a = new TYPE[other.getAllocatedInt() * sizeof(TYPE)];
	//copy from 0 - how ever many are allocated to how every are in the other
	for (int i = 0; i < other.getAllocatedInt(); i++)
		a[i] = other[i];

	theArray = a;
	return this;
}

template <class TYPE>
TYPE& DynamicDingus<TYPE>::operator[](int index) {


	if (index >= this->getAllocatedInt()) {
		//number of elements = this far in in TYPE bytes + 10 * TYPE bytes
		allocatedElements = index * sizeof(TYPE) + 10;
		//the next array cause the old one does not go that high
		TYPE* NewDingus = new TYPE[allocatedElements];
		//from 0 - the last index copy in
		for (int i = 0; i < this->getUsedInt(); i++)
			NewDingus[i] = theArray[i];

		//initialize the remaining positions using default
		for (int j = this->getUsedInt(); j < this->getAllocatedInt(); j++)
			NewDingus[j] = TYPE();

		//delete the old array using the array version of delete
		delete[] theArray;
		//the array = next array
		theArray = NewDingus;

	}
	//if the position is less than the last index we have accessed
	if (index > this->getUsedInt())
		//move forward 1 after where we are
		usedElements = index*sizeof(TYPE) + sizeof(TYPE);
	//return the pointer at 
	return *(theArray + (index * sizeof(TYPE)));
}
