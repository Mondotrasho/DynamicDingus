
#include <cstdlib>
#include "DynamicDingus.h"
#include "DynamicArray.h"

int main()
{
	
//DynamicDingus<int> nums;
	DynamicArray<int> nums(2);

	nums.PushBack(100);
	nums.PushBack(12);
	nums.PushFront(-23);

	/*nums[1] = 1;
	nums[2] = 1;
	nums[15] = 1;*/

	system("pause");
	return 0;
}
