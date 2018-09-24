#pragma once
#include <cassert>

template <class TYPE>
class DynamicDingus
{
public:
	//mem management shenanigans
	//these are the defaults
	DynamicDingus(int start_capacity = 10, bool ord = true, bool sor = false);
	DynamicDingus(DynamicDingus& other);
	~DynamicDingus();

	//adding
	void push_back(TYPE value);
	void push_front(TYPE value);
	void insert(TYPE value, int pos);

	//removing
	TYPE pop_back();
	TYPE pop_front();
	void erase(int pos);

	// quick sort and sub funtions
	void sort(DynamicDingus& data, int begin, int end);
	int divide(DynamicDingus& data, int begin, int end);
	static void swap(DynamicDingus& data, TYPE rhs, int rhs_index, TYPE lhs, int lhs_index);
	//Binary search
	int search(DynamicDingus& data, TYPE find_me, int left_end, int right_end);

	//utility and operators
	int get_size() const;
	TYPE& operator[](int index);
	void operator=(const DynamicDingus& other);
	void clear();

private:
	//short hand
	void grow();
	void shrink();
	//sanitisng the size some times I shrink it to negative
	void clamp_size();
	//checking I am accessing a position I should with asserts
	void verify_pos_out(int pos);
	void verify_pos_in(int pos);
	//constructor shortcuts
	void make_copy_of(const DynamicDingus& other);
	void set_capacity(int cap);
	//grow check
	void check_expand();

	//Member vars
	//number of elements in our array atm
	int m_size;
	// number of reserver spots
	int m_capacity;
	//FOR VIEWING IN WATCH USE m_data,10 etc m_data beingthe name and 10 being the number of spaces into the array you want to read
	//the Memory
	TYPE* m_data;

	//togglable qualities
	//Change how some functions work removal for ordered vs un ordered etc
	// is it an m_ordered array
	bool m_ordered;
	// is it m_sorted
	bool m_sorted;
};

template <typename TYPE>
DynamicDingus<TYPE>::DynamicDingus(int start_capacity, bool ord, bool sor)
{
	//allocate space for 10 elements
	set_capacity(start_capacity);

	//there is nothing in it
	m_size = 0;
	//is it an m_ordered array
	m_ordered = ord;
	//is it a m_sorted array
	m_sorted = sor;
}


template <typename TYPE>
DynamicDingus<TYPE>::DynamicDingus(DynamicDingus& other)
{
	make_copy_of(other);
}

template <typename TYPE>
DynamicDingus<TYPE>::~DynamicDingus()
{
	delete[] m_data;
}

template <typename TYPE>
void DynamicDingus<TYPE>::push_back(TYPE value)
{
	//todo MAYBE use insert short code BUT it would maybe use the for loop in insert TBD
	check_expand();

	//add our value on to the end
	m_data[m_size] = value;
	grow();

	//if its m_sorted and double check its not m_ordered as m_ordered takes priority over m_sorted
	//as you can sort later or manually but you cannot order later
	if (m_sorted && !m_ordered)
	{
		sort(*this, 0, m_size);
	}
}

template <typename TYPE>
void DynamicDingus<TYPE>::push_front(TYPE value)
{
	//insert at begining
	insert(value, 0);
}

template <typename TYPE>
void DynamicDingus<TYPE>::insert(TYPE value, int pos)
{
	//Verify input
	verify_pos_in(pos);

	check_expand();

	//move everything in array forward by one after the pos
	for (auto i = m_size; i > pos; i--)
		m_data[i] = m_data[i - 1];

	//add our value on to the front
	m_data[pos] = value;
	grow();

	//if its m_sorted and double check its not m_ordered as m_ordered takes priority over m_sorted
	//as you can sort later or manually but you cannot order later
	if (m_sorted && !m_ordered)
	{
		sort(*this, 0, m_size);
	}
}

template <typename TYPE>
TYPE DynamicDingus<TYPE>::pop_back()
{
	//using 1 less
	shrink();

	//return the last one
	return m_data[m_size];
}

template <typename TYPE>
TYPE DynamicDingus<TYPE>::pop_front()
{
	//store the front
	TYPE value = m_data[0];
	//remove it
	erase(0);

	return value;
}

template <typename TYPE>
void DynamicDingus<TYPE>::erase(int pos)
{
	verify_pos_out(pos);

	if (m_ordered)
	{
		//move all above the  removed point down 1
		for (auto i = pos; i < m_size; i++)
			m_data[i] = m_data[i + 1];
	}
	else
	{
		//copy last over removed one
		m_data[pos] = m_data[m_size - 1]; //todo check this is m_size - 1 the last one or the last - 1
	}
	shrink();
}

template <typename TYPE>
void DynamicDingus<TYPE>::sort(DynamicDingus& data, int begin, int end)
{
	if (begin < end)
	{
		int divide_index = divide(data, begin, end);

		sort(data, begin, divide_index - 1); // Before pi
		sort(data, divide_index + 1, end); // After pi
	}
}

template <typename TYPE>
int DynamicDingus<TYPE>::divide(DynamicDingus& data, int begin, int end)
{
	// pivot (Element to be placed at right position)
	TYPE pivot = data[end - 1];

	// Index of smaller element
	int i = (begin - 1);

	for (auto j = begin; j < end - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (data[j] <= pivot)
		{// increase index of smaller element
			i++;
			swap(*this, data[i], i, data[j], j);
		}
	}
	swap(*this, data[i + 1], i + 1, data[end - 1], end - 1);
	return (i + 1);
}

template <typename TYPE>
void DynamicDingus<TYPE>::swap(DynamicDingus& data, TYPE rhs, int rhs_index, TYPE lhs, int lhs_index)
{
	//left is right
	data[lhs_index] = rhs;
	//rhs is stored left
	data[rhs_index] = lhs;
}

template <typename TYPE>
int DynamicDingus<TYPE>::search(DynamicDingus& data, TYPE find_me, int left_end, int right_end)
{
	if (!m_sorted)
	{
		sort(*this, 0, m_size);
	}
	//if we are in the area we are checking
	if (right_end >= left_end)
	{
		//middle
		//was using rightEnd / 2 but does not work recursively as we move the left point
		auto middle = left_end + (right_end - left_end) / 2;

		//is it in the middle
		if (data[middle] == find_me)
		{
			return middle;
		}

		//if its smaller
		if (data[middle] > find_me)
		{
			return search(data, find_me, left_end, middle - 1);
		}
		else
		{
			//ok its not smaller
			return search(data, find_me, middle + 1, right_end);
		}
	}


	//not in the array return -1 as thats not an index
	return -1;
}

template <typename TYPE>
int DynamicDingus<TYPE>::get_size() const
{
	return m_size;
}

template <typename TYPE>
TYPE& DynamicDingus<TYPE>::operator[](int index)
{
	return m_data[index];
}

template <typename TYPE>
void DynamicDingus<TYPE>::operator=(const DynamicDingus& other)
{
	make_copy_of(other);
}

template <typename TYPE>
void DynamicDingus<TYPE>::clear()
{
	m_size = 0;
}

template <typename TYPE>
void DynamicDingus<TYPE>::grow()
{
	m_size++;
}

template <typename TYPE>
void DynamicDingus<TYPE>::shrink()
{
	m_size--;
	//stop from shrinking to negative as I use m_size to position when accessing by index etc
	clamp_size();
}

template <typename TYPE>
void DynamicDingus<TYPE>::clamp_size()
{
	if (m_size < 0)
	{
		m_size = 0;
	}
}

template <typename TYPE>
void DynamicDingus<TYPE>::verify_pos_out(int pos)
{
	//check its valid
	//less than 0 or greater than the m_size + 1
	//0   -  9       10
	//0   -  m_size    allocated
	//taking from 0 to m_size
	//taking from 0 to 9
	if (pos < 0 || pos > m_size)
	{
		//"HEY THATS NOT IN RANGE"
		assert(true);
	}
}

template <typename TYPE>
void DynamicDingus<TYPE>::verify_pos_in(int pos)
{
	//check its valid
	//less than 0 or greater than the m_size + 1
	//0   -  9       10
	//0   -  m_size    allocated
	//adding from 0 to m_size + 1
	//adding from 0 to 10
	if (pos < 0 || pos > m_size + 1)
	{
		//"HEY THATS TOO FAR INTO OUR ARRAY"
		assert(true);
	}
}

template <typename TYPE>
void DynamicDingus<TYPE>::make_copy_of(const DynamicDingus& other)
{
	//allocate the same ammount of memory as the other has
	set_capacity(other.m_capacity);

	//fill m_data in
	m_size = other.m_size;
	for (int i = 0; i < m_size; ++i)
		m_data[i] = other.m_data[i];

	m_ordered = other.m_ordered;
	m_sorted = other.m_sorted;
}

template <typename TYPE>
void DynamicDingus<TYPE>::set_capacity(int cap)
{
	m_capacity = cap;
	m_data = new TYPE[m_capacity];
}

template <typename TYPE>
void DynamicDingus<TYPE>::check_expand()
{
	//if the array  needs to be grown grow it
	if (m_size == m_capacity)
	{
		//dopuble m_capacity
		m_capacity *= 2; //todo do we want to double it
		TYPE* new_data = new TYPE[m_capacity];

		//copy existing members to new bigger array
		for (int i = 0; i < m_size; i++)
			new_data[i] = m_data[i];

		//delete the old allocation
		delete[] m_data;
		m_data = new_data;
	}
}