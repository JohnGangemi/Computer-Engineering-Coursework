#ifndef SORTING_H
#define SORTING_H


#include <cmath>
#include "SortingHelper.h"


template <typename T>
void selectionsort(T* data, int size)
{
	if (size > 1)
	{
		for (int i = 0; i < size; i++)
		{
			// find min value from i to n-1
			int m = i;

			for (int j = i + 1; j < size; j++)
				if (data[j] < data[m])
					m = j;

			// swap data[i] and data[m]
			Swap(data[i], data[m]);
		}
	}
}


template <typename T>
void insertionsort(T* data, int size)
{
	if (size > 1)
	{
		for (int i = 1; i < size; i++)
		{
			T ins = data[i];
			int j = i - 1;

			// iterate over "sorted" section
			while (j >= 0)
			{
				// shift element right if larger than ins
				if (data[j] > ins)
					data[j + 1] = data[j];
				else
					break;

				j--;
			}

			// insert ins into appropriate position
			data[j + 1] = ins;
		}
	}
}


template <typename T>
void mergesort(T* data, int size, T* temp)
{
	if (size > 1)
	{
		// split
		int mid = (size + 1) / 2; // integer divison implements floor
		
		int* left = subarray(0, mid - 1, data); // return subarray of data less than mid - 1
		int* right = subarray(mid, size - 1, data); // return subarray of data greater than mid - 1

		mergesort(left, mid, temp); // using temp as third param for mergesort also works
		mergesort(right, size - mid, temp); // using temp as third param for mergesort also works

		// order
		int l = 0, r = 0, s = 0;

		while ((l < mid) && (r < size - mid))
		{
			if (left[l] < right[r])
			{
				temp[s] = left[l];
				l++;
			}
			else
			{
				temp[s] = right[r];
				r++;
			}

			s++;
		}

		// Append left[l to mid - 1] to temp[]
		while (l < mid)
		{
			temp[s] = left[l];
			s++;
			l++;
		}

		// Append right[r to size - mid - 1] to temp[]
		while (r < size - mid)
		{
			temp[s] = right[r];
			s++;
			r++;
		}

		// data[] = temp[]
		for (int i = 0; i < size; i++)
			data[i] = temp[i];

		free(left);
		free(right);
	}
}


template <typename T>
void quicksort(T* data, int size)
{
	// Only partition arrays of proper size
	if (size <= 1)
		return;

	int mid = (size + 1) / 2; // integer divison implements floor 

	// Find pivot element
	int pivot = medianof3(data[0], data[mid], data[size - 1]);

	if (pivot == 1)
		pivot = 0;
	else if (pivot == 2)
		pivot = mid;
	else
		pivot = size - 1;

	Swap(data[0], data[pivot]);

	// Partition
	int left = 0;
	int right = size - 1;

	while (left < right)
	{
		while (left < right && data[left] <= data[0])
			left++;

		while (left < right && data[right] > data[0])
			right--;

		Swap(data[left], data[right]);
	}

	if (data[left] > data[0])
		left--;

	Swap(data[left], data[0]);
	quicksort(data, left); // sort smaller elements
	quicksort(&data[left + 1], size - (left + 1)); // sort larger elements
}


// Returns specified sub array from data
template <typename T>
T subarray(int start, int end, T data)
{
	T sub = new int[(end - start) + 1];

	int ind = 0;
	for (int i = start; i <= end; i++)
	{
		sub[ind] = data[i];
		ind++;
	}

	return sub;
}


#endif