#pragma once
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CSVParser {
public:

    static int parseLine(const string& line, string tokens[], int maxTokens) {
        int tokenCount = 0;
        string current = "";
        bool inQuotes = false;

        for (int i = 0; i < line.length() && tokenCount < maxTokens; i++) {
            char c = line[i];

            if (c == '"') {
                inQuotes = !inQuotes;
            }
            else if (c == ',' && !inQuotes) {
                tokens[tokenCount++] = trim(current);
                current = "";
            }
            else {
                current += c;
            }
        }

        if (tokenCount < maxTokens && current.length() > 0) {
            tokens[tokenCount++] = trim(current);
        }

        return tokenCount;
    }


    static string trim(const string& str) {
        if (str.empty()) return str;

        int start = 0;
        int end = str.length() - 1;

        while (start <= end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')) {
            start++;
        }

        while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r' || str[end] == '\n')) {
            end--;
        }

        return str.substr(start, end - start + 1);
    }

    //string to float
    static float toFloat(const string& str) {
        float result = 0.0f;
        float decimal = 0.1f;
        bool afterDecimal = false;
        bool negative = false;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '-') {
                negative = true;
            }
            else if (str[i] == '.') {
                afterDecimal = true;
            }
            else if (str[i] >= '0' && str[i] <= '9') {
                if (afterDecimal) {
                    result += (str[i] - '0') * decimal;
                    decimal *= 0.1f;
                }
                else {
                    result = result * 10 + (str[i] - '0');
                }
            }
        }

        return negative ? -result : result;
    }

    //string to int
    static int toInt(const string& str) {
        int result = 0;
        bool negative = false;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '-') {
                negative = true;
            }
            else if (str[i] >= '0' && str[i] <= '9') {
                result = result * 10 + (str[i] - '0');
            }
        }

        return negative ? -result : result;
    }
};

#endif // CSVPARSER_H