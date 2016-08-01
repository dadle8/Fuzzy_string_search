#include <vector>
#include <algorithm>
#include <string>
#include "fuzzy_string_search.h"

string alphabet::get_ru() {
	return ru_ru;
}

string alphabet::get_en() {
	return en_en;
}

alphabet::alphabet(){
    ru_ru = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	en_en = "abcdefghijklmnopqrstuvwxyz";
}

int levenshtein_distance(const string str, const string dst) {
	const size_t m = str.size();
	const size_t n = dst.size();

	if (m == 0) return n;
	if (n == 0) return m;

	vector<vector<int> > D(m + 1, vector<int>(n + 1));

	size_t i;
	size_t j;

	/* Filling the zero column from 0 to m */
	for (i = 0; i <= m; i++) {
		D[i][0] = i;
	}

	/* Filling zero line from 0 to n */
	for (i = 0; i <= n; i++) {
		D[0][i] = i;
	}

	size_t left_value, above_value, top_left_value;

	/* Matrix filling */
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (str[i - 1] == dst[j - 1]) D[i][j] = D[i - 1][j - 1];
			else {
				left_value = D[i][j - 1];
				above_value = D[i - 1][j];
				top_left_value = D[i - 1][j - 1];
				D[i][j] = min(min(left_value, above_value), top_left_value) + 1;
			}
		}
	}

	return D[m][n];
}

int bitap_with_WuMaber_mod(const string pattern, const string text, int k) {
    size_t CHAR_MAX=127;
	vector<unsigned long> R(k+1);
	unsigned long endMask = 1 << (pattern.size()-1);
	unsigned long pattern_mask[CHAR_MAX + 1];
	int result = -1;

	/* Initialize the bit array R */
	size_t i, j;
	for (i = 0; i < R.size(); i++) {
		R[i] = 0;
	}

	/* Initialize the pattern bitmasks */
	for (i = 0; i <= CHAR_MAX; i++)
		pattern_mask[i] = 0;
	for (i = 0; i < pattern.size(); i++)
		pattern_mask[abs(pattern[i])] |= 1UL << i;

	/* Search */
	for (i = 0; i < text.size(); i++) {
		unsigned long oldR = R[0];
		unsigned long nextoldR = 0;
		R[0] = ((R[0] << 1) | 1) & pattern_mask[abs(text[i])];

		for (j = 1; j < R.size(); j++) {
			unsigned long ins = oldR | (((R[j] << 1) | 1) & pattern_mask[abs(text[i])]);
			unsigned long del = ((nextoldR<<1)|1) | (((R[j] << 1) | 1) & pattern_mask[abs(text[i])]);
			unsigned long sub = ((oldR << 1) | 1) | (((R[j] << 1) | 1) & pattern_mask[abs(text[i])]);

			oldR = R[j];
			R[j] =ins | del | sub;
			nextoldR = R[j];
		}

		if ((R[k] & endMask)>0) {
			result = k;
			break;
		}

	}

	return result;
}

int spell_checker(const string str, const string dst) {
	alphabet alp;
	int result = 0;
	string nalphabet;

	/* Set locale */
	if (str[0] >= 97 && str[0] <= 122) nalphabet = alp.get_en();
	else if ((str[0] >= (-32) && str[0] <= (-1)) || str[0]==(-72)) nalphabet = alp.get_ru();
	else return result;

	/* Array with "error" strings */
	vector<string> err_string(nalphabet.size()*(str.size()+1) + nalphabet.size()*str.size() + str.size());

	size_t i; /* Index in err_string */

	/* Delete symbol */
	for (i = 0; i < str.size(); i++) {
		err_string[i] = str.substr(0, i) + str.substr(i + 1, str.size() - i-1);
		//cout << err_string[i]<< "\n";
	}

	size_t j; /* Index in str */
	size_t d; /* Index in nalphabet */

	/* Insert symbol */
	for (j=0; j <= str.size();j++) {
		for (d = 0; d < nalphabet.size(); d++,i++) {
			err_string[i]= str.substr(0, j)+ nalphabet[d] + str.substr(j, str.size() - j);
		//	cout << err_string[i] << "\n";
		}
	}

	/* Substitute symbol */
	for (j = 0; j < str.size(); j++) {
		for (d = 0; d < nalphabet.size(); d++, i++) {
			err_string[i] = str.substr(0, j) + nalphabet[d] + str.substr(j+1, str.size() - j);
		//	cout << err_string[i] << "\n";
		}
	}

	/* Search */
	for (i = 0; i < err_string.size(); i++) {
		if (err_string[i] == dst) {
			result = 1;
			break;
		}
	}

	return result;
}

int ngramm(string str, string dst){
    int result = 0, n=3;
    size_t value_gramm=str.size()-2;

    vector<string> ngramms(value_gramm);

    size_t i;
    for(i=0;i<str.size()-2;i++){
        ngramms[i]=str.substr(i,n);
       // cout<<ngramms[i] <<"\n";
    }

    for(i=0;i<value_gramm;i++){
        if(dst.find(ngramms[i])!= string::npos) result++;
    }

    return result;
}
