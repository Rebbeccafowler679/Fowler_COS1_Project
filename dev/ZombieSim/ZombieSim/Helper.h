#pragma once
#include <iostream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>

// Helper Library
// Reusable utility functions used across course projects.
// Everything lives in namespace Helper as static methods.
namespace Helper
{
	//
	// IntegerValidation
	// Returns true if the char* contains a valid integer
	// (optional +/- sign, then digits only).
	//
	static bool IntegerValidation(char* input)
	{
		if (input == nullptr || input[0] == '\0')
		{
			return false;
		}

		size_t i = 0;

		// allow one leading + or -
		if (input[i] == '+' || input[i] == '-')
		{
			i++;
		}

		if (input[i] == '\0')
		{
			return false;
		}

		for (; input[i] != '\0'; i++)
		{
			if (!std::isdigit(static_cast<unsigned char>(input[i])))
			{
				return false;
			}
		}

		return true;
	}

	//
	// PrintIntegerBinary
	// Prints all 32 bits of the integer. Bitwise ops only, no bitset.
	//
	static void PrintIntegerBinary(int* num)
	{
		for (int i = 31; i >= 0; i--)
		{
			std::cout << ((*num >> i) & 1);
		}
		std::cout << "\n";
	}

	//
	// BubbleSort
	// Sorts an int array in ascending order.
	//
	static void BubbleSort(int* arr, int size)
	{
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size - 1 - i; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

	//
	// ClearInputBuffer
	// Clears leftover input and any fail state from previous cin use.
	//
	static void ClearInputBuffer()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	//
	// ClearConsoleWindow
	//
	static void ClearConsoleWindow()
	{
		system("cls");
	}

	//
	// PauseConsoleWindow
	// Waits for the user to press Enter before continuing.
	//
	static void PauseConsoleWindow()
	{
		std::cout << "\nPress Enter to continue...";
		std::cin.get();
	}

	//
	// RandomNumberGenerator
	// Returns a random int in [min, max] inclusive.
	//
	static int RandomNumberGenerator(int min = 1, int max = 100)
	{
		return min + std::rand() % (max - min + 1);
	}

	//
	// GetMenuChoice
	// Prompts until the user enters a number within [min, max].
	// Used for all menu input in course projects.
	//
	static unsigned int GetMenuChoice(unsigned int min, unsigned int max)
	{
		unsigned int choice = 0;

		std::cout << "Enter a number (" << min << " - " << max << "): ";
		while (!(std::cin >> choice) || choice < min || choice > max)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid choice. Try again (" << min << " - " << max << "): ";
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return choice;
	}

	//
	// CoinFlip
	// A coin has two sides — rand() % 2 gives 0 or 1.
	// true = heads, false = tails.
	//
	static bool CoinFlip()
	{
		return rand() % 2 == 1;
	}
}