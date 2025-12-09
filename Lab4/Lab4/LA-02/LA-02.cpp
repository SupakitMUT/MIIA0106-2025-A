#include <iostream>
#include <string>

using namespace std;

int main()
{
	int i = 0;
	cout << " 2) Even numbers from 2 to 20" << endl;
	for (i = 2; i < 21; i++)
	{
		if (i % 2 == 0) // เลข คู่
			cout << i << endl;
	}
	return 0;
}