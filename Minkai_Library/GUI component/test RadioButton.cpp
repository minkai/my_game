#include <iostream>
#include "RadioButton.h"

using namespace std;

int main()
{
	const int NUM_OF_MEMBERS = 4;
	RadioButton<4> obj1;
	RadioButton<NUM_OF_MEMBERS>* full = new RadioButton<NUM_OF_MEMBERS>[NUM_OF_MEMBERS];

	for(int index = 0; index <= NUM_OF_MEMBERS-1; index++)
	{
		full[index].setGroupMembers(full, &full[index]);
	}
	

	cout << "Testing RadioButton\n";

	for(int index = 0; index <= NUM_OF_MEMBERS-1; index++)
	{
		cout << "Address of full[" << index << "] is " << &full[index] << endl;
	}
	
	cout << endl;

	for(int index = 0; index <= NUM_OF_MEMBERS-1; index++)
	{
		cout << "Displaying groupMembers of full[" << index << "]\n";
		full[index].displayGroupMembers();
	}
	
	cout << endl;
	system("PAUSE");
	return 0;
}