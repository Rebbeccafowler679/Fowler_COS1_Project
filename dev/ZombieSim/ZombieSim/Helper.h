#pragma once
#include <iostream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>

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
	// (Kept for older course projects; the zombie sim now reads all
	// keyboard input with getline, so this is no longer needed there.)
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
	// Reads the whole line with getline, converts with stoi inside
	// try/catch, and reprompts on any failure - bad input can never
	// crash the menu or leave cin in a fail state.
	//
	static unsigned int GetMenuChoice(unsigned int min, unsigned int max)
	{
		while (true)
		{
			std::cout << "Enter a number (" << min << " - " << max << "): ";

			// Capture the entire line first; decide what it means after.
			std::string input;
			std::getline(std::cin, input);

			try
			{
				// processedCharacters tells us how much of the string
				// stoi actually converted.
				std::size_t processedCharacters = 0;
				int number = std::stoi(input, &processedCharacters);

				// "12abc" converts to 12 but stops early - reject it.
				if (processedCharacters != input.length())
				{
					std::cout << "Please enter numbers only.\n";
					continue;
				}

				if (number < static_cast<int>(min) || number > static_cast<int>(max))
				{
					std::cout << "That number is outside the available choices.\n";
					continue;
				}

				return static_cast<unsigned int>(number);
			}
			catch (const std::invalid_argument&)
			{
				// The text could not be converted at all ("potato", "").
				std::cout << "Please enter a valid number.\n";
			}
			catch (const std::out_of_range&)
			{
				// The number is too big to fit in an int.
				std::cout << "That number is way too big. Try a smaller one.\n";
			}
		}
	}

	//
	// CoinFlip
	// A coin has two sides - rand() % 2 gives 0 or 1.
	// true = heads, false = tails.
	//
	static bool CoinFlip()
	{
		return rand() % 2 == 1;
	}
}