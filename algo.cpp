#include <iostream>
#include <vector>


using namespace std;

// global variables
vector<pair<int, int> > arr_places;
vector<vector<pair<int, int> > > all_root;
vector<pair<int ,int> > mini_root;



void go_right() {
// TODO
}

bool isInCurrentPoint(int y, int x) {
	int i = 0;
	for(auto place: arr_places) {
		if(y == place.first && x == place.second) {
			arr_places.erase(arr_places.begin() + i);
			all_root.push_back(mini_root);
			return true;
		}
		i++;
	}
	return false;
}

void solve() {
	/* 
		Обозначения в матрице	
		0 - не посещённая клетка
		1 - пока не зарезервировано
		2 - посещённая клетка
		3 - стена

	*/

	// Заполняем неиспользуемые клетки
	int matrix[9][9] = {
		{0, 0, 0, 0, 0, 3, 0, 3, 0},
		{0, 3, 3, 3, 0, 3, 3, 3, 0},
		{0, 3, 0, 3, 0, 3, 0, 0, 0},
		{0, 3, 0, 3, 0, 3, 0, 3, 0},
		{0, 0, 0, 3, 0, 3, 0, 3, 0},
		{0, 3, 3, 3, 0, 3, 0, 3, 0},
		{0, 3, 0, 3, 0, 3, 0, 3, 0},
		{0, 3, 0, 3, 0, 3, 0, 3, 0},
		{0, 3, 0, 0, 0, 0, 0, 3, 0}
	};
	// Заполняем массив с нужными клетками для посещения
	
	arr_places.push_back({6, 6});
	arr_places.push_back({4, 4});
	arr_places.push_back({2, 2});
	arr_places.push_back({0, 0});
	
	// Создаём клетки местоположения машинки
	int cur_x, cur_y;
	// Передвигаем машинку вправо
	go_right();
	cur_x = 8;
	cur_y = 8;
	// Алгоритм поиска пути

	// TODO(Релизовано) Создать массив со стеками пути, которые мы прошли
	// 0 - x
	// 1 - y

	for(auto need_pos: arr_places) {
		// TODO Так же проверять были ли мы в одной из диагональных точек, чтобы не возращаться туда лишний раз
		int fill;
		fill = 3;
		while(need_pos.first != cur_y && need_pos.second != cur_x) {
			// TODO Здесь может быть ошибка, когда мы находимся в точках 0 0, 0, 1 или подобных, будет выход
			// за пределы массива, поэтому надо это просто учесть в условиях !!!
			if(isInCurrentPoint(cur_y, cur_x)) {
				fill++;	
			}
			
			if(cur_y !=0 && matrix[cur_y - 1][cur_x] != fill && matrix[cur_y - 2][cur_x] != 2) {
				// идём вверх
				matrix[cur_y - 2][cur_x] = 2;
				cur_y -= 2;	
				mini_root.push_back({1, -2});	
			} else if(cur_x != 0 && matrix[cur_y][cur_x - 1] != fill && matrix[cur_y][cur_x - 2] != 2) {
				// идём влево
				matrix[cur_y][cur_x - 2] = 2;
				cur_x -= 2;
				mini_root.push_back({0, -2});
			} else if(cur_y != 8 && matrix[cur_y + 1][cur_x] != fill && matrix[cur_y + 2][cur_x] != 2) {
				// идём вниз
				matrix[cur_y + 2][cur_x] = 2;
				cur_y += 2;
				mini_root.push_back({1, 2});
			} else if(cur_x == 8 && matrix[cur_y][cur_x + 1] != fill && matrix[cur_y][cur_x + 2] != 2) {
				// идём вправо
				matrix[cur_y][cur_x + 2] = 2;
				cur_x += 2;
				mini_root.push_back({0, 2});
			} else if(
				(cur_y !=0 && matrix[cur_y - 1][cur_x] != fill && matrix[cur_y - 2][cur_x] != 2) ||
				(cur_x != 0 && matrix[cur_y][cur_x - 1] != fill && matrix[cur_y][cur_x - 2] != 2) ||
				(cur_y != 8 && matrix[cur_y + 1][cur_x] != fill && matrix[cur_y + 2][cur_x] != 2) ||
				(cur_x == 8 && matrix[cur_y][cur_x + 1] != fill && matrix[cur_y][cur_x + 2] != 2)
			) {
				// Возвращаемся назад, на место, где мы видели путь на лево, вправа, вверх, вниз
				while(1) {
					if(mini_root.back().first == 0) {
						cur_x -= mini_root.back().second;
					}
					else if(mini_root.back().second == 1) {
						cur_y -= mini_root.back().second;
					}
					
					// TODO проверка на то, что можно ли ходит вообще или нет в другую сторону, иначе будет выход за пределы массива
					if( (matrix[cur_y - 1][cur_x] != fill && matrix[cur_y - 2][cur_x] != 2) ||
						(matrix[cur_y][cur_x - 1] != fill && matrix[cur_y][cur_x - 2] != 2) ||
						(matrix[cur_y + 1][cur_x] != fill && matrix[cur_y + 2][cur_x] != 2) ||
						(matrix[cur_y][cur_x + 1] != fill && matrix[cur_y][cur_x + 2] != 2)
					) {
						break;
					}
					mini_root.pop_back();
				}
			}
		}
		all_root.push_back(mini_root);
		mini_root.clear();
		// TODO(Реализовано)  Сделать push_back() стэк пути до фигурки
		fill++;
	}
}

int main() {
	solve();
}
