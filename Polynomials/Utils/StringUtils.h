/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#ifndef POLYNOMIALS_STRINGUTILS_H
#define POLYNOMIALS_STRINGUTILS_H

#include <iostream>
#include <cctype>
#include "../framework.h"

class StringUtils {
public:
	static WCHAR * charToWCHAR(const char * str) {
		size_t length = strlen(str);
		WCHAR * text = new WCHAR[length + 1]{ 0 };
		for (size_t i = 0; i <= length; i++)
		{
			text[i] = (WCHAR)str[i];
		}

		return text;
	}

    /// Remove all whitespace characters from the beginning of the specified input stream.
    static void removeWhitespace(std::istream & in) {
        int c;
        // \n means end of line, so avoid of getting back to the loop and wait for user input.
        while (((c = in.peek()) != EOF) && isspace(c) && (c != std::char_traits<char>::to_int_type('\n'))) {
            in.get();
        }
    }

    /// Remove all whitespace characters from the beginning of the specified input stream and return
    /// the first non-whitespace character (without extracting it from the input stream), or EOF if there is nothing to read.
    static int peekIgnoringWhitespace(std::istream & in) {
        removeWhitespace(in);
        return in.peek();
    }

    /// Remove all whitespace characters from the beginning of the specified input stream and return
    /// the first non-whitespace character, or EOF if there is nothing to read.
    static int getIgnoringWhitespace(std::istream & in) {
        return (peekIgnoringWhitespace(in) != EOF) ? in.get() : EOF;
    }

    /// Remove all whitespace characters from the specified char array (in and out).
    static void removeWhitespace(char * str) {
        unsigned int newIndexer = 0, actualIndex = 0;

        while (str[actualIndex] != std::char_traits<char>::to_int_type('\0')) {
            if (!isspace(str[actualIndex])) {
                str[newIndexer++] = str[actualIndex];
            }

            actualIndex++;
        }

        str[newIndexer] = std::char_traits<char>::to_int_type('\0');
    }
};


#endif //POLYNOMIALS_STRINGUTILS_H
