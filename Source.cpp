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
#include <fstream>
#include <string>
#define N 1000
using namespace std;
#define Matrix_symbol '�'

void start() { 
	vector<string> Array;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "�������� �����:" << endl;
	//input(Array);
	///*
	char words[]= "C:/Users/alex_/OneDrive/������� ����/�������/�����������/����� 3/��������/CrissCross/words.txt";
	int correct_words_input = input_from_file(Array, words);
	if (correct_words_input == -1) {
		cout << "�������� ����, ����� �������� ���" << endl;
		return;
	}
	if (correct_words_input == -2) {
		cout << "������! ������������ ���� ����. ������� �����" << endl;
		return;
	}
	if (correct_words_input == -3) {
		cout << "�������� ����, ����� �������� ���" << endl;
		return;
	}
	//*/
	unique_check(Array);
	words_sort(Array);
	output(Array);
	crisscross_versions a(Array.size());
	char** mtx_main;
	mtx_main = a.making_matrix(Array);
	a.making_crisscross(Array, mtx_main);
	crisscross_reduction(mtx_main, max_size(Array) * max_size(Array) + 2, max_size(Array) * max_size(Array) + 2);
	delete_matrix(mtx_main, max_size(Array) * max_size(Array) + 2);
}

void words_sort(vector<string>& Array) {
	for (size_t i = 0; i < Array.size() - 1; i++) {
		for (size_t j = 0; j < Array.size() - 1 - i; j++) {
			if (Array[j].size() < Array[j + 1].size())
				swap(Array[j], Array[j + 1]);
		}
	}
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
			for(size_t k = 0; k < 34; k++)
				if(Array[i][j] == lower[k])
					Array[i][j] = upper[k];
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

int input_from_file(vector<string>& Array, char* words) {
	char Arr[255];
	char Tmp[N] = { 0 };
	int begin = 0;
	int end, count = 0;
	string s;
	ifstream file(words);
	while (getline(file, s)) {
		Array.push_back(s);
	}
	file.close();

	if (Array.size() < 2) {
		return -1;
	}
	if (correct_insert_check(Array) > 0) {
		return -2;
	}
	if (isalpha_rus(Array[0][0]) == 2)
		caps_func(Array);
	else if (isalpha_rus(Array[0][0]) == 1)
		caps_func_rus(Array);

	return 1;
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

char** crisscross_versions::making_matrix(vector<string>& Array) {
	int mtx_size = max_size(Array) * max_size(Array) + 2;
	char** Matrix = new char*[mtx_size];
	for (size_t i = 0; i < mtx_size; i++)
		Matrix[i] = new char[mtx_size];

	for (size_t i = 0; i < mtx_size; i++) {
		for (size_t j = 0; j < mtx_size; j++) {
			Matrix[i][j] = Matrix_symbol;
		}
	}
	return Matrix;
}

int check_words_crisscross_v2(string& Array_1, string& Array_2, int idx_symb) {
	int true_count = 0;
	int symb_address = 0;

	vector<string> Array;
	Array.push_back(Array_1);
	Array.push_back(Array_2);

	if (Array[0] != Array[1]) {
		for (size_t i = 0; i < Array[0].size(); i++) {
			if (Array[0][i] == Array[1][idx_symb]) {
				symb_address = i;
				return symb_address;
			}
		}
	}
	else
		return -1;
	return -1;
}


int check_words_crisscross(string& Array_1, string& Array_2) {
	int true_count = 0;

	char* symb = new char[Array_1.size() + Array_2.size()];
	for (size_t i = 0; i < Array_1.size(); i++)
		symb[i] = 0;

	int* symb_address = new int[Array_1.size() + Array_2.size()];
	for (size_t i = 0; i < Array_1.size(); i++)
		symb_address[i] = 0;

	vector<string> Array;
	Array.push_back(Array_1);
	Array.push_back(Array_2);
	int k = 0;

	if (Array[0] != Array[1]) {
		for (size_t i = 0; i < Array[0].size(); i++) {
			for (size_t j = 0; j < Array[1].size(); j++) {
				if (Array[0][i] == Array[1][j]) {
					symb[k] = Array[0][i];
					symb_address[k] = i;
					k++;
				}
			}
		}
		if (k == 0)
			return -1;
		int word_center = Array_1.size() / 2;
		for (size_t i = 0; i < word_center; i++) {
			for (size_t j = 0; j < word_center; j++) {
				if (Array_1[word_center + j] == symb[i]) {
					return word_center + j;
				}
				if (Array_1[word_center - j] == symb[i]) {
					return word_center - j;
				}
			}
		}
		return -1;
	}
	else
		return -1;
}

int check_words_crisscross_int(string& Array_1, string& Array_2) { // �� �����
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
		if (Matrix[n_tmp][m] == Array[i]) /////////////////////////////////////////////
			isFit++;
		n_tmp++;
	}
	if (isFit == Array.size())
		return 1;
	else
		return 0;
}

void best_first_word(vector<string>& Array){ // �� ������������, �� ����� �������
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
}

void crisscross_versions::making_crisscross(vector<string>& Array, char** Matrix) { 
	int mtrx_i = 0, mtrx_j = 0;
	int Matrix_size_i = max_size(Array) * max_size(Array) + 2;
	int Matrix_size_j = max_size(Array) * max_size(Array) + 2;
	int first_word = 0;
	char symb_for_check = 0;
	int words_symb = -1;

	for (size_t counter = 0; counter < Array.size(); counter++) {
		for (size_t i = 0; i < Array.size(); i++) {
			if (Array[counter] == Array[i])
				continue;
			for (size_t j = 0; j < Array[i].size()/2; j++) {
				int word_center = Array[i].size() / 2;
				words_symb = check_words_crisscross_v2(Array[counter], Array[i], word_center-j);
				if (words_symb == -1)
				words_symb = check_words_crisscross_v2(Array[counter], Array[i], word_center+j);
				if ((words_symb == -1) || (visited[i] == 1)) {
					continue;
				}
				char symb_for_check = Array[counter][words_symb];

				if (first_word == 0) {
					first_word = 1;
					visited[counter] = 1;
					if (Array[counter].size() % 2 == 0) {
						mtrx_i = (max_size(Array) * max_size(Array) + 2) / 2;
						mtrx_j = (max_size(Array) * max_size(Array) + 2) / 2 - max_size(Array) / 2;
						for (size_t f = 0; f < Array[counter].size(); f++) {
							Matrix[mtrx_i][mtrx_j + f] = Array[counter][f];
						}
					}

					else {
						mtrx_i = (max_size(Array) * max_size(Array) + 2) / 2;
						mtrx_j = (max_size(Array) * max_size(Array) + 2) / 2 - max_size(Array) / 2;
						for (size_t j1 = 0; j1 < Array[counter].size(); j1++) {
							Matrix[mtrx_i][mtrx_j + j1] = Array[counter][j1];
						}
					}
				}


				int break_count = 0;
					for (size_t n = 0; n < Matrix_size_i; n++) {
						for (size_t m = 0; m < Matrix_size_j; m++) {
							if ((Matrix[n][m] == Array[counter][0]) && (Matrix[n][m + 1] == Array[counter][1])) {
								if (find_w_begin_horizontally(Matrix, Array[counter], n, m)) { // ���������� ����� � ������� (�������������)
									mtrx_i = n;
									mtrx_j = m;
									break_count++;
								}
							}
							else if ((Matrix[n][m] == Array[counter][0]) && (Matrix[n + 1][m] == Array[counter][1])) {
								if (find_w_begin_vertically(Matrix, Array[counter], n, m)) { // ���������� ����� � ������� (�����������)
									mtrx_i = n;
									mtrx_j = m;
									break_count++;
								}
							}
						}if (break_count == 1) break;
					}


				for (size_t t = 0; t < Array[counter].size(); t++) {
					if (Matrix[mtrx_i][mtrx_j + t] == symb_for_check) {
						mtrx_j += t;
						break;
					}
					else if (Matrix[mtrx_i + t][mtrx_j] == symb_for_check) {
						mtrx_i += t;
						break;
					}
				}

				int symb_idx = 0;
				for (size_t n = 0; n < Array[i].size(); n++) {
					if (Array[i][n] == symb_for_check) {
						symb_idx = n;
						break;
					}
				}


				int horizontally_check = -2, vertically_check = -2;

				int iter = 0;
				//vertically
				if (Matrix[mtrx_i - symb_idx - 1][mtrx_j] == Matrix_symbol) // �������� ����� ������� �����
					vertically_check++;
				for (size_t q = symb_idx; q > 0; q--) {
					if ((Matrix[mtrx_i - q][mtrx_j] == Matrix_symbol) && (Matrix[mtrx_i - q][mtrx_j - 1] == Matrix_symbol) && (Matrix[mtrx_i - q][mtrx_j + 1] == Matrix_symbol))
						vertically_check++;
					iter++;
				}
				int tmp_for_vertically = 0;
				for (size_t q = 1; Array[i].size() != iter; q++, iter++) {
					if ((Matrix[mtrx_i + q][mtrx_j] == Matrix_symbol) && (Matrix[mtrx_i + q][mtrx_j - 1] == Matrix_symbol) && (Matrix[mtrx_i + q][mtrx_j + 1] == Matrix_symbol))
						vertically_check++;
					tmp_for_vertically = q;
				}
				if (Matrix[mtrx_i + tmp_for_vertically + 1][mtrx_j] == Matrix_symbol) // �������� � ����� �����
					vertically_check++;



				//horizontally
				iter = 0;

				if (Matrix[mtrx_i][mtrx_j - symb_idx - 1] == Matrix_symbol) // �������� ����� ������� �����
					horizontally_check++;

				for (size_t q = symb_idx; q > 0; q--) {
					if ((Matrix[mtrx_i][mtrx_j - q] == Matrix_symbol) && (Matrix[mtrx_i - 1][mtrx_j - q] == Matrix_symbol) && (Matrix[mtrx_i + 1][mtrx_j - q] == Matrix_symbol))
						horizontally_check++;
					iter++;
				}

				for (size_t q = 1; Array[i].size() != iter; q++, iter++) {
					if ((Matrix[mtrx_i][mtrx_j + q] == Matrix_symbol) && (Matrix[mtrx_i - 1][mtrx_j + q] == Matrix_symbol) && (Matrix[mtrx_i + 1][mtrx_j + q] == Matrix_symbol))
						horizontally_check++;
				}

				if (Matrix[mtrx_i][mtrx_j + symb_idx + 1] == Matrix_symbol) // �������� � ����� �����
					horizontally_check++;


				if (vertically_check == Array[i].size()) { //word isFit to vertically, writting
					int p = 0, u = 0; // i, j, k ��� ��������

					for (size_t q = symb_idx; q > 0; q--, p++) {
						Matrix[mtrx_i - q][mtrx_j] = Array[i][p];
						u++;
					}p++;

					for (size_t q = 1; Array[i].size() - 1 != u; q++, p++, u++) {
						Matrix[mtrx_i + q][mtrx_j] = Array[i][p];
					}
					visited[i] = 1;
				}

				else if (horizontally_check == Array[i].size()) { //word isFit to horizontally, writting
					int p = 0, u = 0;

					for (size_t q = symb_idx; q > 0; q--, p++) {
						Matrix[mtrx_i][mtrx_j - q] = Array[i][p];
						u++;
					}p++;
					for (size_t q = 1; Array[i].size() - 1 != u; q++, p++, u++) {
						Matrix[mtrx_i][mtrx_j + q] = Array[i][p];
					}
					visited[i] = 1;
				}
				else
					continue;
			}
		}
	}
}

void crisscross_reduction(char** Matrix, int Matrix_size_i, int Matrix_size_j) {
	// �������� ��������� ������� (������, �����, ������, �����)
	int tmp_cut[4][2] = {0};
	int tmp_cut_result[4][2];
	int break_count = 0;
	for (int i = 0; i < Matrix_size_i; i++) { //������
		for (int j = 0; j < Matrix_size_j; j++) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[0][0] = i - 1;
				tmp_cut[0][1] = j;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	break_count = 0;
	for (int j = 0; j < Matrix_size_i; j++) { // �����
		for (int i = 0; i < Matrix_size_j; i++) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[1][0] = i;
				tmp_cut[1][1] = j - 1;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	break_count = 0;
	for (int i = Matrix_size_i - 1; i > 0; i--) { // �����
		for (int j = Matrix_size_i - 1; j > 0; j--) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[2][0] = i + 1;
				tmp_cut[2][1] = j;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	break_count = 0;
	for (int j = Matrix_size_i - 1; j > 0; j--) { // ������
		for (int i = Matrix_size_i - 1; i > 0; i--) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[3][0] = i;
				tmp_cut[3][1] = j + 1;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	tmp_cut_result[0][0] = tmp_cut[0][0]; // ����� ������� ����� 
	tmp_cut_result[0][1] = tmp_cut[1][1];	

	tmp_cut_result[1][0] = tmp_cut[0][0]; // ������ ������� �����
	tmp_cut_result[1][1] = tmp_cut[3][1];
	
	tmp_cut_result[2][0] = tmp_cut[2][0]; // ������ ������ �����
	tmp_cut_result[2][1] = tmp_cut[3][1];

	tmp_cut_result[3][0] = tmp_cut[2][0]; // ����� ������ �����
	tmp_cut_result[3][1] = tmp_cut[1][1];


	int mtx_size_i = tmp_cut_result[3][0] - tmp_cut_result[0][0] + 1;
	int mtx_size_j = tmp_cut_result[2][1] - tmp_cut_result[0][1] + 1;

	for (size_t i = tmp_cut[0][0], q1 = 0; q1 < mtx_size_i; i++, q1++) { //output matrix
		cout << endl << "\t";
		for (size_t j = tmp_cut[1][1], q2 = 0; q2 < mtx_size_j; j++, q2++) {
			cout << Matrix[i][j] << " ";
		}
	}
	cout << endl;
}