#include "pqueue.h"

// constructor
pqueue::pqueue()
{
	count = 0;  // no jobs yet
}
// destructor does nothing
pqueue::~pqueue()
{
}
// Purpose: to add a job to a right place in the Pqueue
// Argument: j is the job priority number
void pqueue::insertjob(int j)
{
	count++;			//increment count since we're adding  job
	cout << "Adding: " << j << endl;
	Q[count - 1] = j;	//add the job j at the rear
	trickleup(); // moves the job to the right place
}
// Purpose: to print a job and reheapify the Pqueue
void pqueue::printjob()
{
	cout << "printing: " << Q[0] << endl;		//prints the root
	reheapify();								//reheapifies the Pqueue
}
// Purpose: to display all jobs
void pqueue::displayAll()
{
	int x = 0;
	cout << "Jobs: ";
	for (int i = 0; i < count; i++)			//loop to display jobs from slot 0 to slot count-1 horizontally
	{
		cout << Q[i] << " ";
	}
	cout << endl;
	for (int x = 0; x < count; x++)				//prints the array in a tree form, only works for three levels
	{
		if (x == 0)							//root is alone at the top
		{
			cout << "         " << Q[x] << endl;
		}
		else if (x <= 2 && x >= 1)			//two children of root
		{
			if (x == 2)						//checks for the index of the right most node on level two
				cout << "      " << Q[x] << endl;			//print it and end line
			else
				cout << "     " << Q[x];
		}
		else
		{
			if (x == count - 1)					//checks for the index of the right most node on level three
				cout << "  " << Q[x];			//print it
			else
				cout << "  " << Q[x];
		}
	}
	cout << endl;	//end line for level three of tree
}

// Utility functions follow: ------------------

// Purpose: to make the very last job trickle up to the right location 
void pqueue::trickleup()
{
	int x = count - 1;				// the very last job location
	while (x > 0)					//while x is > 0
	{
		if (Q[x] <= Q[getParent(x)])		//compare Q[x] with the parent and if the parent is bigger swap & update x. Otherwise stop.
		{									//You can call getParent to get the location of the parent
			swap(Q[x], Q[getParent(x)]);
			x = getParent(x);
		}
		else
			return;
	}
}
// Purpose: find the location of the parent 
// The child location is given.  Need to call even.
int pqueue::getParent(int child)
{
	if (even(child) == true)			//return the parent location
		return (child / 2) - 1;			//return the location if the child is in an even index
	else
		return (child - 1) / 2;			//else return this if it is odd
}
// Purpose: is location i even? Important in finding its parent location
bool pqueue::even(int i)
{
	if ((i % 2) == 0)			//check if the index i is even or odd 
		return true;
	else
		return false;
}
// Purpose: to reheapify the Pqueue after printing
void pqueue::reheapify()
{
	Q[0] = Q[count - 1];		// move the last job to the front
	count--;					//decrement the count since we're removing a jod
	int x = 0;					//x keeps track of the root we have to move down
	while (getSmallerchild(x) < count)		//start at the root and repeat the following:
	{										//find the location of the smaller child if you have not fallen off the tree yet
		if (Q[x] > Q[getSmallerchild(x)])
		{
			swap(Q[x], Q[getSmallerchild(x)]);				//if the smaller child is smaller than the parent, swap
			x = getSmallerchild(x);
		}
		else
			return;					//else stop
	}
}
// Purpose: to find the location of the smaller child
// where children at locations 2*i+1 and 2*i+2
int pqueue::getSmallerchild(int i)
{
	if (Q[2 * i + 1] <= Q[2 * i + 2])			//return the location of the smaller child 
		return 2 * i + 1;			//returns the index of the left child
	else
		return 2 * i + 2;			//returns the index of the right child
}