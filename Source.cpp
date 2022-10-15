#include "Header.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <clocale>
#include <algorithm>
#include <conio.h>
#include <cctype>
#define N 256
using namespace std;


void start() {
	vector<string> Array;
	cout << "Ââåäèòå ñëîâà" << endl;
	input(Array);
	unique_check(Array);
	output(Array);
	making_matrix(Array);
	
}

int isalpha_rus(char c) {
	if (c >= 'à' && c <= 'ÿ' || c >= 'À' && c <= 'ß' || c == '¸' || c == '¨')
		return 1;
	else if (isalpha(c))
		return 2;
	else
		return 0;
}

void caps_func_rus(vector<string>& Array) {
	int i = 0; 
	int j = 0; 

	char lower[34] = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿ"; //russian alphabets
	char upper[34] = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß";

	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = 0; j < Array[i].size(); j++) {
			for(size_t z = 0; z < 34; z++)
				if(Array[i][j] == lower[z])
					Array[i][j] = upper[z];
		}
	}
}

int correct_insert_check(vector<string>& Array) {
	int err = 0;
	if (isalpha_rus(Array[0][0]) == 2) { 
		for (size_t i = 0; i < Array.size(); i++) {
			for (size_t j = 0; j < Array[i].size(); j++) {
				if (isalpha_rus(Array[i][j]) != 2)
					err++;
			}
		}
	}
	if (isalpha_rus(Array[0][0]) == 1) { 
		for (size_t i = 0; i < Array.size(); i++) {
			for (size_t j = 0; j < Array[i].size(); j++) {
				if (isalpha_rus(Array[i][j]) != 1)
					err++;
			}
		}
	}
	return err;
}

void caps_func(vector<string>& Array) {
	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = 0; j < Array[i].size(); j++) {
			Array[i][j] = (char)toupper(Array[i][j]);
		}
	}
}

void sort(vector<string>& Array) {
	for (size_t j = 0; j < Array.size()-1; j++) {
		for (size_t i = 0; i < Array.size()-1; i++) {
			if (Array[i].size() < Array[i + 1].size())
				swap(Array[i], Array[i + 1]);
		}
	}
}

void output(vector<string>& Array) {
	for (auto i : Array)
		cout << i << " ";
	cout << endl;
}

void input(vector<string>& Array) { 
	char Arr[N] = {0};
	char Tmp[N] = {0};
	int begin = 0;
	int end, count = 0;
	fgets(Arr, N, stdin);
	for (size_t i = 0; Arr[i-1] != '\n'; i++) {
		if ((Arr[i] == ' ')||(Arr[i] == '\n')) {
			end = i;
			memcpy(Tmp, Arr + begin, end-begin);
			begin = end + 1;
			Array.push_back(Tmp);
			for (int j = 0; j < end; j++)
				Tmp[j] = 0;
		}
		else if ((isalpha_rus(Arr[i]) != 1)&&(isalpha_rus(Arr[i]) != 2)) {
			while ((Arr[i] != ' ')&&(Arr[i] != '\n')) {
				i++;
				count++;
			}
			begin = i+1;
		}
	}
	if (correct_insert_check(Array) > 0) {
		cout << "Îøèáêà! Íåïğàâèëüíûé ââîä ñëîâ. Ââåäèòå ñíîâà" << endl;
		Array.clear();
		input(Array);
	}
	if(isalpha_rus(Array[0][0]) == 2)
		caps_func(Array);
	else if(isalpha_rus(Array[0][0]) == 1)
		caps_func_rus(Array);
	sort(Array);
}

void unique_check(vector<string>& Array) { 
	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = i+1; j < Array.size(); j++) {
			if (Array[i] == Array[j]) {
				Array[j].clear();
				for (size_t z = j; z < Array.size()-1; z++)
					Array[z] = Array[z + 1];
				Array.pop_back();
				j--;
			}
		}
	}
}

void delete_matrix(char** mtrx, size_t size) {
	for (size_t i = 0; i < size; i++) {
		delete[] mtrx[i];
	}
	delete[] mtrx;
}

void making_matrix(vector<string>& Array) {
	char** Matrix = new char*[Array[0].size()*2 + 2]; // making matrix
	for (size_t i = 0; i < Array[0].size()*2 + 2; i++)
		Matrix[i] = new char[Array[0].size()+2];

	for (size_t i = 0; i < Array[0].size()*2 + 2; i++) {
		for (size_t j = 0; j < Array[0].size()+2; j++) {
			Matrix[i][j] = '•';
		}
	}
	making_crisscross(Array, Matrix);

	for (size_t i = 0; i < Array[0].size() * 2 + 2; i++) { //output matrix
		cout << endl << "\t";
		for (size_t j = 0; j < Array[0].size() + 2; j++) {
			cout << Matrix[i][j] << " ";
		}
	}
	cout << endl;

	delete_matrix(Matrix, Array[0].size() * 2);
}

int* check_words_crisscross(string& Array_1, string& Array_2) { // submit words in a loop, return (q,i) (z,j) 
	int true_count = 0;
	int isFit[4] = {0};
	vector<string> Array;
	Array.push_back(Array_1);
	Array.push_back(Array_2);
	/*int** isFit = new int*[2];
	for (size_t i = 0; i < 4; i++)
		isFit[i] = new int[4];*/

	/*for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = 0; j < Array.size(); j++) {
			isFit[i][j] = 0;
		}
	}*/

	for (size_t q = 0; q < Array.size(); q++) {
		for (size_t z = 0; z < Array.size(); z++) {
			if (Array[q] != Array[z]) {
				for (size_t i = 0; i < Array[q].size(); i++) {
					for (size_t j = 0; j < Array[z].size(); j++) {
							if (Array[q][i] == Array[z][j]) {
								isFit[0] = q;
								isFit[1] = i;
								isFit[2] = z;
								isFit[3] = j;
								return isFit;
								/*if ((isFit[z] > 0) && (z + 1 < Array.size())) {
									z++;
									i = 0;
									j = -1;
							}*/
						}
					}
				}
			}
		}
	}
	return isFit;
}

void making_crisscross(vector<string>& Array, char** Matrix) { //// we send 1 word in a subcycle. Then, after a full cycle with the first word, we start with the following
	int mtrx_i = 0, mtrx_j = 0;
	if (Array[0].size() % 2 == 0) { // if it is possible to put it in a separate function so that the recursion with Array_failed works
		int mtrx_i = Array[0].size() + 1;
		int mtrx_j = 1;
		for (size_t j = 0; j < Array[0].size(); j++) { // for 1-st word
			Matrix[mtrx_i][mtrx_j] = Array[0][j];
		}


	}
	else {
		int mtrx_i = Array[0].size();
		int mtrx_j = 1;
		for (size_t i = 0; i < Array.size(); i++) { // for 1-st word
			for (size_t j = 0; j < Array[i].size(); j++) {
				Matrix[mtrx_i + i][mtrx_j + j] = Array[i][j];
			}
		}
	}

	vector<string> Array_failed;
	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = i+1; j < Array.size()-1; j++) { //need to check on "out of memmory"
			int* Intersections = check_words_crisscross(Array[i], Array[j]); // Intersections[0] = i1
																			 // Intersections[1] = j1
																			//  Intersections[2] = i2
																			//  Intersections[3] = j2
			int Intersections_res = Intersections[0] + Intersections[1] + Intersections[2] + Intersections[3];
			if (Intersections_res == 0) { /////// check it
				Array_failed.push_back(Array[i]);
				Array_failed.push_back(Array[j]);
			}
			else { // need to know coords of 1-st word (Array[i]) about matrix // use mtrx_i, mtrx_j
				if ((Matrix[mtrx_i + Intersections[0]][mtrx_j + Intersections[1] - 1]) == '•' && (Matrix[mtrx_i + Intersections[0]][mtrx_j + Intersections[1] + 1]) == '•') { // horizontally
					
				}
				else {// vertically

				}
			}
		}
	}
	
}