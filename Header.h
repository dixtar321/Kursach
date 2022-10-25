#pragma once

#include <iostream>
#include <vector>
using namespace std;

//мул сом енот крот лемур койот панда тукан мустанг гиппопотам

void start();
void output(vector<string>& Array);
void input(vector<string>& Array);
void caps_func(vector<string>& Array);
void caps_func_rus(vector<string>& Array);
int correct_insert_check(vector<string>& Array);
int isalpha_rus(char c);
int max_size(vector<string>& Array);
void making_matrix(vector<string>& Array);
void delete_matrix(char** mtrx, size_t size);
void making_crisscross(vector<string>& Array, char** Matrix);
char check_words_crisscross(string& Array_1, string& Array_2);
int check_words_crisscross_int(string& Array_1, string& Array_2);
void unique_check(vector<string>& Array);
int find_w_begin_horizontally(char** Matrix, string Array, int n, int m);
int find_w_begin_vertically(char** Matrix, string Array, int n, int m);
void best_first_word(vector<string>& Array);
void crisscross_reduction(char** Matrix, int Matrix_size_i, int Matrix_size_j);