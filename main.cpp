#include "Reverse.h"
#include "Storage.h"

int main(int argc, char* argv[])
{
	try
	{
		TestListCyclic();
		// TestListReverse();
		// TestStorage();
	} catch (...)
	{
		cout << "Error executing program!";
	}

	return 0;
}
