#pragma once
#include <iostream>
#include <vector>
using namespace std;

//ЯЕИВЮЯ УНПНЬЮЪ ОНЦНДЮ
//ЛСК ЯНЛ ЕМНР ЙПНР КЕЛСП ЙНИНР ОЮМДЮ РСЙЮМ ЛСЯРЮМЦ ЦХООНОНРЮЛ
//ЮБНЙЮДН ЯЕЦНДМЪ ЦПЮМЮР ЮКШВЮ ЯЛНПНДХМЮ ОНЛХДНП БХМНЦПЮД ВРН БННАЫЕЛ ЛЮМЦН МЕЙРЮПХМ ОПХБЕР ЯСУНТПСЙРШ ГЮМЪРЮ ЙЮЙ ДЕКЮЕЬЭ
///деиярбхрекэмнярэ йнмярхрсжхнммши хмбеярхжхнммши хмрепеянбюрэяъ меднярюрнвмши тнплхпнбюрэяъ цслюмхрюпмши псйнбндхрекэ хяонкэгнбюрэ едхмярбеммши бнгцкюбкърэ бярпевюрэяъ гюйнмвхрэяъ гюцкъдшбюрэ цемепюкэмши юпахрпюфмши чпхдхвеяйхи опедкнфемхе мюопюбкемхе деиярбнбюрэ ярюкхмяйхи юаянкчрмши пюяяйюгюрэ пюгпеьемхе сопюбкемхе гюялеърэяъ мюярпнемхе акеяръыхи нрйпшбюрэ йпнунрмши ондкефюрэ пюгнапюрэ пняйньмши мюонкмхрэ гюонлмхрэ сопюбкърэ меунпньхи бепнърмши йнккейрхб нянаеммши бшгшбюрэ мемсфмши нрдюбюрэ гюбхяерэ нубюрхрэ опнйспнп напюрхрэ наьхпмши оняюдхрэ опеоюпюр яебепмши яберяйхи йкюяямши кчахлши якедхрэ дмебмни вюянбни феярйхи яхярелю репоерэ мюкхвхе ярюбхрэ сярюкши унпньхи яюднбши оноюярэ якнлюрэ йюахмер сбепърэ гюмърши юооюпюр лемэьхи ярпнхрэ осярни всфдши бшфхрэ йнкемн назейр опелхъ юбцсяр бнярнй свемхй лъямни бепмши гюдмхи пеяспя гюйнм онбнд кхмхъ пюлйю бевеп окюрю реръ апюр дюрэ ъыхй всдн ябер рнл сл

class crisscross_versions {
private:
	int Size;
	int* visited;
public:
	crisscross_versions(int my_size) {
		Size = my_size;
		visited = new int[Size];
		for (size_t i = 0; i < Size; i++) {
			visited[i] = 0;
		}
	};
	void making_crisscross(vector<string>& Array, char** Matrix, int mtrx_i, int mtrx_j);
	char** making_matrix(vector<string>& Array);
	~crisscross_versions() {
		delete[] visited;
	};
};

void start();
void output(vector<string>& Array);
void input(vector<string>& Array);
void caps_func(vector<string>& Array);
void caps_func_rus(vector<string>& Array);
int correct_insert_check(vector<string>& Array);
int isalpha_rus(char c);
int max_size(vector<string>& Array);
void delete_matrix(char** mtrx, size_t size);
char check_words_crisscross(string& Array_1, string& Array_2);
int check_words_crisscross_int(string& Array_1, string& Array_2);
void unique_check(vector<string>& Array);
int find_w_begin_horizontally(char** Matrix, string Array, int n, int m);
int find_w_begin_vertically(char** Matrix, string Array, int n, int m);
void best_first_word(vector<string>& Array);
void crisscross_reduction(char** Matrix, int Matrix_size_i, int Matrix_size_j);
void words_sort(vector<string>& Array);