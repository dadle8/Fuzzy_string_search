#include "fuzzy_string_search.h"
#include <string>
#include <ctime>
#include <fstream>
#include <vector>

int main()
{
	setlocale(LC_ALL, "Russian");
	clock_t start, end;
	size_t count_str = 8339;
	vector<string> text(count_str);
	vector<string> pattern(count_str);

    ifstream ftin("text.txt"), fpin("pattern.txt");
    size_t i;
    if(ftin.is_open()){
        i=0;
        while(ftin.good()){
            getline(ftin,text[i]);
            i++;
        }
        ftin.close();
    }
    else cout<< "�� ������� ���� text.txt\n";

    if(fpin.is_open()){
        i=0;
        while(fpin.good()){
            getline(fpin,pattern[i]);
            i++;
        }
        fpin.close();
    }
    else {
            cout<< "�� ������� ���� pattern.txt\n";
            return 0;
    }

    vector<int> d(count_str);
    start = clock();
    for(i=0;i<count_str;i++){
        d[i] = levenshtein_distance(text[i], pattern[i]);
    }
    end = clock();

    size_t result = 0;
    for(i=0;i<count_str;i++){
        if(d[i]<3) result++;
    }
    cout << "���������� �����������: " <<(float)result/count_str*100 << "% ���� � 2 �������� � ������.\n����� ������ ������: " << ((float)(end - start)) /CLOCKS_PER_SEC << " ������.\n";

    start = clock();
    for(i=0;i<count_str;i++){
        d[i] = bitap_with_WuMaber_mod(text[i], pattern[i] , 2);
    }
    end = clock();

    result=0;
    for(i=0;i<count_str;i++){
         if(d[i]==2) result++;
    }
    cout << "Bitap: " << (float)result/count_str*100  << "% ���� � 2 �������� � ������. \n����� ������ ������: " << ((float)(end-start))/CLOCKS_PER_SEC << " ������.\n" ;

    start = clock();
    for(i=0;i<count_str;i++){
        d[i] = spell_checker(pattern[i], text[i]);
    }
    end = clock();

    result=0;
    for(i=0;i<count_str;i++){
         if(d[i]==1) result++;
    }
    cout << "������� ���������� �������: " << (float)result/count_str*100 << "% ���� � 1 ��� 0 ��������. \n����� ������ ������: " << ((float)(end-start))/CLOCKS_PER_SEC << " ������.\n" ;

    start = clock();
    for(i=0;i<count_str;i++){
        d[i] = ngramm(pattern[i], text[i]);
    }
    end = clock();

    result=0;
    for(i=0;i<count_str;i++){
         if(d[i]>0) result++;
    }
    cout<< "����� N-�����: " << (float)result/count_str*100 << "% ���� � 1 � ����� ������. \n����� ������ ������: " << ((float)(end-start))/CLOCKS_PER_SEC << " ������.\n\n";

    return 0;
}
