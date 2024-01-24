#include <iostream>;
#include <cstdlib>;
#include <vector>;
#include <chrono>;

using namespace std::chrono;

// Constants
const unsigned int MAX = 1000;	// largest number to generated
int size;


// Function Prototypes
std::vector<int> genNumbers(int size);
void insertionSort(std::vector<int>& numbers);
void printNumbers(std::vector<int> numberList);
int radixGetMaxLength(std::vector<int>& numbers);
int radixGetLength(int value);
void radixSort(std::vector<int>& numbers);
void bucketSort(std::vector<int>& numbers, int numBuckets);

int main() {

	// seed the random number generator via system clock
	auto seedTime = system_clock::now();
	unsigned int seed = duration_cast<seconds>(seedTime.time_since_epoch()).count() % UINT_MAX;	// modulo by the maximum value for an object of type unsigned int
	std::srand(seed);


	//Sort Loops:
	std::vector<int> randNumbers(size);
	size = 10;
	while(size <= 10000)
	{	
		//insertionSort loop
		for (int i = 0; i < 10; i++)
		{
			randNumbers = genNumbers(size);

			auto start = high_resolution_clock::now();

			insertionSort(randNumbers);

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);

			std::cout << "Time to use insertionSort with " << size << " numbers is: " << duration.count() / 1000.0 << " ms" << std::endl;
		}


		//bucketSort loop
		for (int i = 0; i < 10; i++)
		{
			randNumbers = genNumbers(size);

			auto start = high_resolution_clock::now();

			bucketSort(randNumbers, 10);

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);

			std::cout << "Time to use bucketSort with " << size << " numbers is: " << duration.count() / 1000.0 << " ms" << std::endl;
		}

		//radixSort loop
		for (int i = 0; i < 10; i++)
		{
			randNumbers = genNumbers(size);

			auto start = high_resolution_clock::now();

			radixSort(randNumbers);

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);

			std::cout << "Time to use radixSort with " << size << " numbers is: " << duration.count() / 1000.0 << " ms" << std::endl;
		}

		size *= 10;
	}

	return 0;
}

void insertionSort(std::vector<int>& numbers)
{
	for (int i = 1; i < numbers.size(); ++i)
	{
		int j = i;

		while (j > 0 && numbers[j] < numbers[j - 1])
		{
			int temp = numbers[j];
			numbers[j] = numbers[j - 1];
			numbers[j - 1] = temp;
			--j;
		}
	}
}

void bucketSort(std::vector<int>& numbers, int numBuckets)
{
	if (numbers.size() < 1)
		return;

	std::vector<std::vector<int>> buckets(numBuckets);
	//std::vector<int> buckets(std::vector<int> test);

	// Find the maximum value
	int maxValue = numbers[0];
	for (int i = 1; i < numbers.size(); i++)
	{
		if (numbers[i] > maxValue)
			maxValue = numbers[i];
	}

	//put each number in a bucket
	for (int i = 0; i < numbers.size(); i++)
	{

		int index = floor(numbers[i] * numBuckets / (maxValue + 1));
		buckets[index].push_back(numbers.at(i));
	}

	for (int i = 0; i < numBuckets; i++)
	{
		insertionSort(buckets[i]);
	}

	//concatenate the buckets
	int index = 0;
	for (int i = 0; i < numBuckets; i++)
	{
		for (int j = 0; j < buckets[i].size(); j++)
		{
			numbers.at(index) = buckets[i].at(j);
			index++;
		}

	}

}

void radixSort(std::vector<int>& numbers)
{
	std::vector<std::vector<int>> buckets(10);

	//Find the max length, in number of digits
	int maxDigits = radixGetMaxLength(numbers);

	int pow10 = 1;
	for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			int num = numbers.at(i);
			int bucketIndex = (num / pow10) % 10;
			buckets[bucketIndex].push_back(num);
		}

		int vectorIndex = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < buckets.at(i).size(); j++)
			{
				numbers.at(vectorIndex) = buckets[i].at(j);
				vectorIndex++;
			}
			buckets[i].clear();
		}
		pow10 *= 10;
	}
}


int radixGetMaxLength(std::vector<int>& numbers)
{
	int maxDigits = 0;
	for (int i = 0; i < numbers.size(); i++)
	{
		int digitCount = radixGetLength(numbers[i]);
		if (digitCount > maxDigits)
			maxDigits = digitCount;
	}
	return maxDigits;
}

int radixGetLength(int value)
{
	if (value == 0)
		return 1;

	int digits = 0;
	while (value != 0)
	{
		digits++;
		value /= 10;
	}

	return digits;
}


std::vector<int> genNumbers(int size) {
	// vector to hold random numbers
	std::vector<int> randomNums(size);

	// generate some random numbers
	for (int i = 0; i < size; i++)
	{
		// divide by RAND_MAX from <cstdlib>
		// the maximum value that can be returned by rand()
		randomNums.at(i) = rand() * (MAX + 1) / (RAND_MAX + 1);
	}

	return randomNums;
}


void printNumbers(std::vector<int> numberList) {
	std::cout << "A List of " << size << " randomly generate numbers between 0 and " <<
		MAX << ":" << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << numberList.at(i) << std::endl;
	}

	std::cout << std::endl;
}
