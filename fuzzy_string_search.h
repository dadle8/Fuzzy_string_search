#pragma once
#include <iostream>
using namespace std;

class alphabet {
	string ru_ru;
	string en_en;

public:
    alphabet();
	string get_ru();
	string get_en();
};

int levenshtein_distance(const string str, const string dst);

int bitap_with_WuMaber_mod(const string pattern,const string text, int k);

int spell_checker(const string str, const string dst);

int ngramm(string str, string dst);
