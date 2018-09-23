#pragma once
#include <cassert>
#include <algorithm>


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

		//if its sorted and double check its not ordered as ordered takes priority over sorted
		//as you can sort later or manually but you cannot order later
		if (sorted && !ordered) {
			Sort(*this, 0, size);
		}
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

		//if its sorted and double check its not ordered as ordered takes priority over sorted
		//as you can sort later or manually but you cannot order later
		if (sorted && !ordered) {
			Sort(*this, 0, size);
		}
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

	// quick sort
	void Sort(DynamicArray& data, int begin, int end)
	{
		if (begin < end)
		{
			int DivideIndex = Divide(data, begin, end);

			Sort(data, begin, DivideIndex - 1);  // Before pi
			Sort(data, DivideIndex + 1, end); // After pi
		}

	}
	int Divide(DynamicArray& data,int begin,int end)
	{
		// pivot (Element to be placed at right position)
		T pivot = data[end -1];

		int i = (begin - 1);  // Index of smaller element

			for (int j = begin; j < end - 1; j++)
			{
				// If current element is smaller than or
				// equal to pivot
				if (data[j] <= pivot)
				{
					i++;    // increment index of smaller element
					swap(*this,data[i],i, data[j],j);
				}
			}
			swap(*this,data[i + 1], i + 1, data[end - 1], end - 1);
			return (i + 1);
	}

	void swap(DynamicArray& data,T rhs, int rhsindex,T lhs,int lhsindex)
	{
		//left is right
		data[lhsindex] = rhs;
		//rhs is stored left
		data[rhsindex] = lhs;
	}
	//Binary search
	int Search(DynamicArray& data, T findMe, int leftEnd,int rightEnd)
	{
		if(!sorted)
		{
			Sort(*this, 0, size);
		}
		//if we are in the area we are checking
		if(rightEnd >= leftEnd)
		{
			//middle
			//was using rightEnd / 2 but does not work recursively as we move the left point
			auto middle = leftEnd + (rightEnd - leftEnd) / 2;

			//is it in the middle
			if(data[middle] == findMe)
			{
				return middle;
			}

			//if its smaller
			if(data[middle] > findMe)
			{
				return Search(data, findMe,leftEnd, middle - 1);
			}
			else
			{
				//ok its not smaller
				return Search(data, findMe, middle + 1, rightEnd);
			}
		}


		//not in the array return -1 as thats not an index
		return -1;
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
		//stop from shrinking to negative as I use size to position when accessing by index etc
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
	bool ordered; // is it an ordered array
	bool sorted; // is it sorted
};
