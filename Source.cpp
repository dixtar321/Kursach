#include "Header.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <clocale>
#include <algorithm>
#include <conio.h>
#include <cctype>
#include <Windows.h>
#include <cmath>
#define N 256
using namespace std;
#define Matrix_symbol '�'

void start() {
	vector<string> Array;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������� �����" << endl;
	input(Array);
	unique_check(Array);
	output(Array);
	making_matrix(Array);
	
}

int isalpha_rus(char c) {
	if (c >= '�' && c <= '�' || c >= '�' && c <= '�' || c == '�' || c == '�')
		return 1;
	else if (isalpha(c))
		return 2;
	else
		return 0;
}

void caps_func_rus(vector<string>& Array) {
	int i = 0; 
	int j = 0; 

	char lower[34] = "��������������������������������"; //russian alphabets
	char upper[34] = "�����Ũ��������������������������";

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

int max_size(vector<string>& Array) {
	vector<string> Arr = Array;
	for (size_t j = 0; j < Arr.size()-1; j++) {
		for (size_t i = 0; i < Arr.size()-1; i++) {
			if (Arr[i].size() < Arr[i + 1].size())
				swap(Arr[i], Arr[i + 1]);
		}
	}
	return Arr[0].size();
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
		cout << "������! ������������ ���� ����. ������� �����" << endl;
		Array.clear();
		input(Array);
	}
	if(isalpha_rus(Array[0][0]) == 2)
		caps_func(Array);
	else if(isalpha_rus(Array[0][0]) == 1)
		caps_func_rus(Array);
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

	char** Matrix = new char*[max_size(Array) * 2 + 2]; // making matrix
	for (size_t i = 0; i < max_size(Array) * 2 + 2; i++)
		Matrix[i] = new char[max_size(Array) * max_size(Array) + 2];

	for (size_t i = 0; i < max_size(Array) * 2 + 2; i++) {
		for (size_t j = 0; j < max_size(Array) * max_size(Array) + 2; j++) {
			Matrix[i][j] = Matrix_symbol;
		}
	}

	cout << endl;

	making_crisscross(Array, Matrix);
	delete_matrix(Matrix, Array[0].size() * 2 + 2);
}
char check_words_crisscross(string& Array_1, string& Array_2) {
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

int check_words_crisscross_int(string& Array_1, string& Array_2) {
	int true_count = 0;
	char symb = 0;
			if (Array_1 != Array_2) {
				for (size_t i = 0; i < Array_1.size(); i++) {
					for (size_t j = 0; j < Array_2.size(); j++) {
						if (Array_1[i] == Array_2[j]) {
							symb = Array_1[i];
							true_count++;
						}
					}
				}
			}
	return true_count;
}

int find_w_begin_horizontally(char** Matrix, string Array, int n, int m) {
	int isFit = 0;
	int m_tmp = m;
	for (size_t i = 0; i < Array.size(); i++) {
		if (Matrix[n][m_tmp] == Array[i])
			isFit++;
		m_tmp++;
	}
	if (isFit == Array.size())
		return 1;
	else
		return 0;
}

int find_w_begin_vertically(char** Matrix, string Array, int n, int m) {
	int isFit = 0;
	int n_tmp = n;
	for (size_t i = 0; i < Array.size(); i++) {
		if (Matrix[n_tmp][m] == Array[i])
			isFit++;
		n_tmp++;
	}
	if (isFit == Array.size())
		return 1;
	else
		return 0;
}

void best_first_word(vector<string>& Array){
	int** intersections = new int*[Array.size()];
	for (size_t i = 0; i < Array.size(); i++)
		intersections[i] = new int[Array.size() - 1];

	int* intersections_main = new int[Array.size()];
	for (size_t i = 0; i < Array.size(); i++)
		intersections_main[i] = 0;

	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = 0; j < Array.size(); j++) {
			intersections[i][j] = check_words_crisscross_int(Array[i], Array[j]);
			intersections_main[i] += intersections[i][j];
		}
	}

	for (int i = 0; i < Array.size(); i++)
		cout << intersections_main[i] << endl;
	cout << endl;

	for (size_t j = 0; j < Array.size(); j++) {
		for (size_t i = 0; i < Array.size(); i++) {
			if (intersections_main[i] < intersections_main[i + 1]) {
				swap(intersections_main[i], intersections_main[i + 1]);
				swap(Array[i], Array[i + 1]);
			}
		}
	}
	for (int i = 0; i < Array.size(); i++)
		cout << intersections_main[i] << endl;
}

void making_crisscross(vector<string>& Array, char** Matrix) { //// we send 1 word in a subcycle. Then, after a full cycle with the first word, we start with the following
	int mtrx_i = 0, mtrx_j = 0;
	//int* intersections = new int[Array.size()];
	int Matrix_size_i = max_size(Array) * 2 + 2;
	int Matrix_size_j = max_size(Array) * max_size(Array) + 2;
	int first_word = 0;
	best_first_word(Array);
	output(Array);
	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = i+1; j < Array.size(); j++) { //need to check on "out of memmory"
			char words_symb = check_words_crisscross(Array[i], Array[j]);
			if (words_symb == '\0') { /////// check it
				continue;
			}
			else {

				if (first_word == 0) {
					if (Array[i].size() % 2 == 0) {
						mtrx_i = max_size(Array) + 1;
						mtrx_j = max_size(Array) * max_size(Array) / 2 - max_size(Array) / 2;
						for (size_t f = 0; f < Array[i].size(); f++) {
							Matrix[mtrx_i][mtrx_j + f] = Array[i][f];
						}
					}

					else {
						mtrx_i = max_size(Array);
						mtrx_j = max_size(Array) * max_size(Array) / 2 - max_size(Array) / 2;
						for (size_t j1 = 0; j1 < Array[0].size(); j1++) {
							Matrix[mtrx_i][mtrx_j + j1] = Array[i][j1];
						}
					}
					first_word++;
				}
				else {
					int break_count = 0;
					for (size_t vj = 0; vj < Array[i].size(); vj++) {
						for (size_t n = 0; n < Matrix_size_i; n++) {
							for (size_t m = 0; m < Matrix_size_j; m++) {
								if ((Matrix[n][m] == Array[i][vj]) && (Matrix[n][m + 1] == Array[i][vj + 1])) {
									if (find_w_begin_horizontally(Matrix, Array[i], n, m)) {
										mtrx_i = n;
										mtrx_j = m;
										break_count++;
									}
								}
								else if ((Matrix[n][m] == Array[i][vj]) && (Matrix[n + 1][m] == Array[i][vj + 1])) {
									if (find_w_begin_vertically(Matrix, Array[i], n, m)) {
										mtrx_i = n;
										mtrx_j = m;
										break_count++;
									}
								}
							}if (break_count == 1) break;
						}if (break_count == 1) break;
					}
				}



					for (size_t t = 0; t < Array[i].size(); t++) { //////////////////// stack over flow 
					if (Matrix[mtrx_i][mtrx_j + t] == words_symb) {
						//if((mtrx_j + t) <= (Array[i].size()))
							mtrx_j += t;
						break;
					}
					else if (Matrix[mtrx_i + t][mtrx_j] == words_symb) {
						//if ((mtrx_i + t) <= (Array[i].size()))
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
					if ((Matrix[mtrx_i - q][mtrx_j] == Matrix_symbol)&&(Matrix[mtrx_i - q][mtrx_j - 1] == Matrix_symbol) && (Matrix[mtrx_i - q][mtrx_j + 1] == Matrix_symbol))
						vertically_check++;
					iter++;
				}
				/*if((Array[j].size() - iter - 1) <= symb_idx) // mb not helpful
					iter = 1;*/
				for (size_t q = 1; Array[j].size() != iter; q++, iter++) {
						if ((Matrix[mtrx_i + q][mtrx_j] == Matrix_symbol) && (Matrix[mtrx_i + q][mtrx_j - 1] == Matrix_symbol) && (Matrix[mtrx_i + q][mtrx_j + 1] == Matrix_symbol))
							vertically_check++;
					}
				
				

				//horizontally
				iter = 0;
				for (size_t q = symb_idx; q > 0; q--) {
					if ((Matrix[mtrx_i][mtrx_j - q] == Matrix_symbol) && (Matrix[mtrx_i - 1][mtrx_j - q] == Matrix_symbol) && (Matrix[mtrx_i + 1][mtrx_j - q] == Matrix_symbol))
						horizontally_check++;
					iter++;
				}

				for (size_t q = 1; Array[j].size() != iter; q++, iter++) {
					if ((Matrix[mtrx_i][mtrx_j + q] == Matrix_symbol) && (Matrix[mtrx_i - 1][mtrx_j + q] == Matrix_symbol) && (Matrix[mtrx_i + 1][mtrx_j + q] == Matrix_symbol))
						horizontally_check++;
				}



				if (vertically_check == Array[j].size()) { //word isFit to vertically, writting
					int p = 0, u = 0;
					
					for (size_t q = symb_idx; q > 0; q--, p++) { /////////////////////////////////////////////////////////����������
						Matrix[mtrx_i - q][mtrx_j] = Array[j][p];
						u++;
					}p++;

					for (size_t q = 1; Array[j].size() - 1 != u; q++, p++, u++) {
						Matrix[mtrx_i + q][mtrx_j] = Array[j][p];
					}
					//Array[j].erase();
				}
				

				if (horizontally_check == Array[j].size()) { //word isFit to horizontally, writting
					int p = 0, u = 0;

					for (size_t q = symb_idx; q > 0; q--, p++) {
						Matrix[mtrx_i][mtrx_j - q] = Array[j][p];
						u++;
					}p++;
					for (size_t q = 1; Array[j].size() - 1 != u; q++, p++, u++) {
						Matrix[mtrx_i][mtrx_j + q] = Array[j][p];
							
					}
					//Array[j].erase();
				}
				//add else (if word is not fit horizontally and vertically)


			}
		}
	}

	for (size_t i = 0; i < Matrix_size_i; i++) { //output matrix
		cout << endl << "\t";
		for (size_t j = 0; j < Matrix_size_j; j++) {
			cout << Matrix[i][j] << " ";
		}
	}
	cout << endl;

	crisscross_reduction(Matrix, Matrix_size_i, Matrix_size_j);

	for (size_t i = 0; i < Matrix_size_i; i++) { //output matrix
		cout << endl << "\t";
		for (size_t j = 0; j < Matrix_size_j; j++) {
			cout << Matrix[i][j] << " ";
		}
	}
	cout << endl;
	
}

void crisscross_reduction(char** Matrix, int Matrix_size_i, int Matrix_size_j) {
	int isFit = 0;
	size_t i = 0, j = 0;
	for (size_t i = 0; i < Matrix_size_i; i++) { 
		for (size_t j = 0; j < Matrix_size_j; j++) {
			if (Matrix[i][j] != Matrix_symbol) {
				isFit++;
			}
		}
		if (isFit == Matrix_size_j) {
			swap(Matrix[i], Matrix[i + 1]);
			isFit = 0;
		}
	}
	for (size_t j = 0; j < Matrix_size_j; j++) {
		for (size_t i = 0; i < Matrix_size_i; i++) {
			if (Matrix[i][j] != Matrix_symbol) {
				isFit++;
			}
		}
		if (isFit == Matrix_size_i) {
			swap(Matrix[j], Matrix[j+1]);
			isFit = 0;
		}
	}
}