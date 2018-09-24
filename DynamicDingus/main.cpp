
#include <cstdlib>
#include "DynamicDingus.h"
#include <ctime>
#include <string>
#include "HashFunction.h"
#include <iostream>

//tested OWOhash with a 50k number array
//tested search with a 50k number array crashes due to stack overflow I think its with the splitting idk why maybe too large?

bool checkOwo(DynamicDingus<int> nums)
{
	//check compare by hash of array
	bool test1;
	bool test2;
	bool overall;
	auto l = nums.make_byte_array(nums);
	auto x = HashFunction::owoHash(l, nums.get_size());
	auto y = HashFunction::owoHash(l, nums.get_size());
	nums.push_back(34);
	l = nums.make_byte_array(nums);
	auto z = HashFunction::owoHash(l, sizeof(l) * nums.get_size());
	auto f = sizeof(l) * nums.get_size();
	auto g = nums.get_size();
	if (x == y)
	{
		test1 = true;
		//std::cout << "success" << std::endl;
	}
	if (!(x == z))
	{
		test2 = true;
		//std::cout << "success" << std::endl;
	}

	if (test1 && test2)
	{
		overall = true;
	}
	return overall;
}

bool checkBKDR(DynamicDingus<int> nums)
{
	//check compare by hash of array
	bool test1;
	bool test2;
	bool overall;
	auto l = nums.make_byte_array(nums);
	auto x = HashFunction::BKDRHash(l, nums.get_size());
	auto y = HashFunction::BKDRHash(l, nums.get_size());
	nums.push_back(34);
	l = nums.make_byte_array(nums);
	auto z = HashFunction::BKDRHash(l, sizeof(l) * nums.get_size());
	auto f = sizeof(l) * nums.get_size();
	auto g = nums.get_size();
	if (x == y)
	{
		test1 = true;
		//std::cout << "success" << std::endl;
	}
	if (!(x == z))
	{
		test2 = true;
		//std::cout << "success" << std::endl;
	}

	if (test1 && test2)
	{
		overall = true;
	}
	return overall;
}

int main()
{
	srand(time(NULL));
//DynamicDingus<int> nums;
	DynamicDingus<int> nums(2,false);
	for (auto i = 0; i < 500; ++i)
	{
		nums.push_back(rand() % 200);
	}
	
	
	//test search
DynamicDingus<std::string> box(2,false,false);
bool testPast = true;
for (auto i = 0; i < 10; ++i)
{
	auto a = rand() % 200;
	auto b = nums.search(nums, a, 0, nums.get_size());
	box.push_back("search was : " + std::to_string(a));
	
	if (b != -1) {
		auto c = nums[b];
		box.push_back("the index its at is : " + std::to_string(b));
		if(c == a)
		{
			box.push_back("returned : " + std::to_string(c) + " as Expected");
		}
		else
		{
			testPast = false;
			box.push_back("not as expected result was : " + std::to_string(c));
		}
	}
	else
	{

		box.push_back("Index not returned -1 returned instead");
		box.push_back("Index was -1");
	}
}
if (testPast)
{
	std::cout << "Search is working" << std::endl;
}

	nums[1] = 1;
	nums[2] = 1;
	nums[15] = 1;

	nums.push_back(12);

	nums.erase(1);
	auto front = nums.pop_front();
	auto front1 = nums.pop_front();
	auto front2 = nums.pop_front();


	nums.insert(122, 1);
	nums.push_back(34);

	//hash then compare 2 dynamicArray<int>s using Brian kernigans hash
	if (checkBKDR(nums))
	{
		std::cout << "Bkdr hash is working" << std::endl;
	}

	//hash then compare 2 dynamicArray<int>s using my hash
	if (checkOwo(nums))
	{
		std::cout << "OwO hash is working" << std::endl;
	}
	system("pause");
	

	return 0;
}
