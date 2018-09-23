
#include <cstdlib>
#include "DynamicDingus.h"
#include "DynamicArray.h"
#include <ctime>
#include <string>

int main()
{
	srand(time(NULL));
//DynamicDingus<int> nums;
	DynamicArray<int> nums(2,false);
	for (int i = 0; i < 50; ++i)
	{
		nums.PushBack(rand() % 200);
	}
	
	

	DynamicArray<std::string> box(2,false,false);
	for (int i = 0; i < 10; ++i)
	{
		auto a = rand() % 200;
		auto b = nums.Search(nums, a, 0, nums.GetSize());
		box.PushBack("search was : " + std::to_string(a));
		
		if (b != -1) {
			int c = nums[b];
			box.PushBack("the index its at is : " + std::to_string(b));
			if(c == a)
			{
				box.PushBack("returned : " + std::to_string(c) + " as Expected");
			}
			else
			{
				box.PushBack("not as expected result was : " + std::to_string(c));
			}
		}
		else
		{
			box.PushBack("Index not returned -1 returned instead");
			box.PushBack("Index was -1");
		}
		
		

	}
	/*nums[1] = 1;
	nums[2] = 1;
	nums[15] = 1;*/

	nums.PushBack(12);

	//nums.Erase(1);
	//int front = nums.PopFront();
	//int front1 = nums.PopFront();
	//int front2 = nums.PopFront();


	nums.Insert(-23, 1);
	nums.PushBack(45);


	system("pause");
	

	return 0;
}
