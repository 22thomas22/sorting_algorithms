#include <iostream>
#include <string>
#include <functional>
#include <cstdlib>
#include <ctime>

#define startANDlength int start[], const int length
#define iINlengthM1 int i = 0; i < length - 1; i++
#define iINlength int i = 0; i < length; i++

/** 
 *Inspiration:
 * https://www.youtube.com/watch?v=aXXWXz5rF64&list=PL2aHrV9pFqNS79ZKnGLw-RG5gH01bcjRZ
**/

using namespace std;
using std::cout; using std::endl;
using std::to_string;

string showOutput(startANDlength) {
	string output = "{";
	for (iINlength) {
		output += to_string(start[i]);
		if (i != length - 1) {
			output += ", ";
		}
	}
	return output + "}";
}
string showOutput(bool start[], const int length) {
	string output = "{";
	for (iINlength) {
		output += to_string(start[i]);
		if (i != length - 1) {
			output += ", ";
		}
	}
	return output + "}";
}

bool isSorted(startANDlength) {
	for (iINlengthM1) {
		if (start[i] > start[i + 1])
			return false;
	}
	return true;
}

void swap(int& a, int& b) {
	int tmp = a;
	a = b, b = tmp;
}

string check_sort(std::function<string(startANDlength)> fn, startANDlength) {
	int* copy = new int[length];
	for (iINlength) {
		copy[i] = start[i];
	}

	string sortingName = fn(copy, length);
	string output = sortingName + ": List is ";
	output += isSorted(copy, length) ? "" : "NOT ";
	output += "sorted: \n";
	output += showOutput(copy, length);

	delete[] copy;

	return output + "\n\n";
}

////////////////////////////////////////////////////////////////////////
//                  Start of Sorting Algorithms                       //
////////////////////////////////////////////////////////////////////////

string bubble_sort(startANDlength) {
	for (int end = length; end--; ) {
		for (iINlengthM1) {
			if (start[i] > start[i + 1]) {
				swap(start[i], start[i + 1]);
			}
		}
	}
	return "Bubble Sort";
}

string BOGO_sort(startANDlength) {
	int a, b, tmp;
	while (!isSorted(start, length)) {
		a = rand() % length, b = rand() % length;
		swap(start[a], start[b]);
	}
	return "BOGO Sort";
}


string quick_sort(startANDlength) {
	const unsigned int marker = 0b11111111'11111111; // don't use this number I guess
	cout << "marker: " << marker << "\n";

	int* cache = new int[length]; // temporarily holds the values out of the way
	for (iINlength) {
		cache[i] = marker; // Set them all to empty
	}
	
	bool* isPivot = new bool[length]; // Tells us which values are set in place
	for (iINlength) {
		isPivot[i] = false; // set all pivot flags to false
	}
	int totalPivots = 0; // tracks the total pivots we have. When all the pivots are in place we can move on.
	while (totalPivots < length) {
		int startPos = 0;
		int currentPivot = 0;
		int cacheCounter = 0;
		while (isPivot[currentPivot]) {
			currentPivot = (++currentPivot) % length;
		}
		int currentPivotValue = start[currentPivot]; // Holds the value the pivot points to
		for (iINlength) {
			cout << "\nloop " << i << ":\n";
			if (!isPivot[i]) {
				if (i != currentPivot) {
					if (start[i] > currentPivotValue) { // move to cache
						cache[cacheCounter++] = start[i];
						start[i] = marker;
					}
					else { // move to fill gaps
						startPos = 0;
						for (; start[startPos] != marker && startPos < length; startPos++) {} // skip over filled parts
						start[startPos] = start[i];
						if (i != startPos) start[i] = marker;
					}
				}
				else {
					start[currentPivot] = marker;
				}
			}
			cout << "data: " << showOutput(start, length) << "\n";
			cout << "cache: " << showOutput(cache, length) << "\n";
		}
		start[++startPos] = currentPivotValue; // push the pivot on the back
		isPivot[startPos] = true;
		totalPivots++;

		int i = -1;
		while (cache[++i] != marker || isPivot[i]) { // merge the cache list back onto the original
			start[++startPos] = cache[i];
		}
		for (int j = 0; j < i; j++) { // reset the cache
			cache[j] = marker;
		}

		cout << "----------\n";
		cout << "data: " << showOutput(start, length) << "\n";
		cout << "cache: " << showOutput(cache, length) << "\n";
		cout << "pivot flag: " << showOutput(isPivot, length) << "\n\n\n";
	}
	delete cache, isPivot;
	return "Quick Sort";
}


////////////////////////////////////////////////////////////////////////
//                   End of Sorting Algorithms                        //
////////////////////////////////////////////////////////////////////////


int main() {
	int data[] = {4, 7, 2, 3, 5, 3}; // -> {2, 3, 3, 4, 5, 7}
	srand(time(NULL));
	
	//cout << check_sort(bubble_sort, data, 6);
	//cout << check_sort(BOGO_sort, data, 6);
	cout << check_sort(quick_sort, data, 6);
	return 0;
}