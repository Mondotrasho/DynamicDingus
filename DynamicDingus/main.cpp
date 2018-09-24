
#include <cstdlib>
#include "DynamicDingus.h"
#include <ctime>
#include <string>

int main()
{
	srand(time(NULL));
//DynamicDingus<int> nums;
	DynamicDingus<int> nums(2,false);
	for (auto i = 0; i < 50; ++i)
	{
		nums.push_back(rand() % 200);
	}
	
	

	DynamicDingus<std::string> box(2,false,false);
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
				box.push_back("not as expected result was : " + std::to_string(c));
			}
		}
		else
		{
			box.push_back("Index not returned -1 returned instead");
			box.push_back("Index was -1");
		}
		
		

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


	system("pause");
	

	return 0;
}
