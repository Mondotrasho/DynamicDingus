
#include <cstdlib>
#include "DynamicDingus.h"
#include "DynamicArray.h"

int main()
{
	
//DynamicDingus<int> nums;
	DynamicArray<int> nums(2,false);

	nums.PushBack(100);
	nums.PushBack(12);

	nums.Erase(1);
	int front = nums.PopFront();
	int front1 = nums.PopFront();
	int front2 = nums.PopFront();

	nums.PushBack(27);
	nums.Insert(-23,1);

	/*nums[1] = 1;
	nums[2] = 1;
	nums[15] = 1;*/

	


	system("pause");
	return 0;
}
