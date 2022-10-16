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
#define Matrix_symbol '•'

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
			Matrix[i][j] = Matrix_symbol;
		}
	}

	cout << endl;

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
char check_words_crisscross(string& Array_1, string& Array_2) { // submit words in a loop, return (q,i) (z,j) 
	int true_count = 0;
	char symb = 0;
	vector<string> Array;
	Array.push_back(Array_1);
	Array.push_back(Array_2);
	for (size_t q = 0; q < Array.size(); q++) {
		for (size_t z = 0; z < Array.size(); z++) {
			if (Array[q] != Array[z]) {
				for (size_t i = 0; i < Array[q].size(); i++) {
					for (size_t j = 0; j < Array[z].size(); j++) {
							if (Array[q][i] == Array[z][j]) {
								symb = Array[q][i];
								return symb;
						}
					}
				}
			}
		}
	}
	return symb;
}

void making_crisscross(vector<string>& Array, char** Matrix) { //// we send 1 word in a subcycle. Then, after a full cycle with the first word, we start with the following
	int mtrx_i = 0, mtrx_j = 0;
	if (Array[0].size() % 2 == 0) { // if it is possible to put it in a separate function so that the recursion with Array_failed works
		mtrx_i = Array[0].size() + 1;
		mtrx_j = 1;
		for (size_t j = 0; j < Array[0].size(); j++) { // for 1-st word
			Matrix[mtrx_i][mtrx_j+j] = Array[0][j];
		}


	}
	else {
		mtrx_i = Array[0].size();
		mtrx_j = 1;
		for(size_t j = 0; j < Array[0].size(); j++) { // for 1-st word
			Matrix[mtrx_i][mtrx_j + j] = Array[0][j];
		}
	}


	for (size_t i = 0; i < Array[0].size() * 2 + 2; i++) { //output matrix   //delete after checking 
		cout << endl << "\t";
		for (size_t j = 0; j < Array[0].size() + 2; j++) {
			cout << Matrix[i][j] << " ";
		}
	}
	cout << endl;


	vector<string> Array_failed; // maybe delete this??

	int** words_begin = new int*[Array.size()];
	for (size_t i = 0; i < Array.size(); i++)
		words_begin[i] = new int[2];


	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = i+1; j < Array.size(); j++) { //need to check on "out of memmory"
			char words_symb = check_words_crisscross(Array[i], Array[j]);
			if (words_symb == '\0') { /////// check it
				// 0
				int p = 0;
			}
			else { // need to know coords of 1-st word (Array[i]) about matrix // use mtrx_i, mtrx_j

				//find mtrx_i and mtrx_j for Array[i] ..............................................................................

					for (size_t t = 0; t < Array[i].size(); t++) {
					if (Matrix[mtrx_i][mtrx_j + t] == words_symb) {
						mtrx_j += t;
						break;
					}
					else if (Matrix[mtrx_i + t][mtrx_j] == words_symb) {
						mtrx_i += t;
						break;
					}
				}

				int symb_idx = 0;
				for (size_t n = 0; n < Array[j].size(); n++) {
					if (Array[j][n] == words_symb) {
						symb_idx = n;
						break;
					}
				}

				int horizontally_check = 0, vertically_check = 0;
				int iter = 0;
				//vertically
				for (size_t q = symb_idx; q > 0; q--) {
					if (Matrix[mtrx_i - q][mtrx_j] == Matrix_symbol)
						vertically_check++;
					iter++;
				}
				for (size_t q = symb_idx; q <= Array[j].size() - iter - 1; q++) {
					if (Matrix[mtrx_i + q][mtrx_j] == Matrix_symbol)
						vertically_check++;
				}

				//horizontally
				iter = 0;
				for (size_t q = symb_idx; q > 0; q--) {
					if (Matrix[mtrx_i][mtrx_j - q] == Matrix_symbol)
						horizontally_check++;
					iter++;
				}
				for (size_t q = symb_idx; q <= Array[j].size() - iter - 1; q++) {
					if (Matrix[mtrx_i][mtrx_j + q] == Matrix_symbol)
						horizontally_check++;
				}

				if (vertically_check == Array[j].size() - 1) { //word isFit to vertically, writting
					int p = 0, u = 0; 
					for (size_t q = symb_idx; q > 0; q--, p++) {
						Matrix[mtrx_i - q][mtrx_j] = Array[j][p];
						u++;
					}p++;
					for (size_t q = symb_idx; q < Array[j].size() - u; q++, p++) {
						Matrix[mtrx_i + q][mtrx_j] = Array[j][p];
					}
				}
				

				if (horizontally_check == Array[j].size() - 1) { //word isFit to horizontally, writting
					int p = 0, u = 0;
					for (size_t q = symb_idx; q > 0; q--, p++) {
						Matrix[mtrx_i][mtrx_j - q] = Array[j][p];
						u++;
					}p++;
					for (size_t q = symb_idx; q < Array[j].size() - u; q++, p++) {
						Matrix[mtrx_i][mtrx_j + q] = Array[j][p];
							
					}
				}
				//add else (if word is not fit horizontally and vertically)

				for (size_t i = 0; i < Array[0].size() * 2 + 2; i++) { //output matrix   //delete after checking 
					cout << endl << "\t";
					for (size_t j = 0; j < Array[0].size() + 2; j++) {
						cout << Matrix[i][j] << " ";
					}
				}
				cout << endl;



			}
		}
	}
	for (size_t i = 0; i < Array.size(); i++) {
		delete[] words_begin[i];
	}
	delete[] words_begin;
}