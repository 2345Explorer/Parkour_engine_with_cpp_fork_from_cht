/*
 *  A parkour engine with cpp.
 *  Copyright (C) 2023  cht
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <windows.h>
#include <conio.h>
#include "main.h"
using namespace std;
int x=20, y=20,cnt=-1;
bool state;
double G=1;
string map[500]{
	"##############################",
	"#                            #",
	"#       ####                 #",
	"#               ##           #",
	"#                            #",
	"#            #               #",
	"#                            #",
	"#                            #",
	"#                ##          #",
	"#                            #",
	"#         #####              #",
	"#                            #",
	"#               #####        #",
	"#                            #",
	"#                            #",
	"#      #######               #",
	"#                            #",
	"#               ##           #",
	"#                            #",
	"#                            #",
	"#                   ####     #",
	"#                            #",
	"#              ##            #",
	"#                            #",
	"#                            #",
	"#     ##############         #",
	"#                            #",
	"#                            #",
	"#                            #",
	"##############################"
};
void Gmg(int x2, int y2){
	if(map[y + 1][x] == '#') return;
	if(state == 0 && map[int(y+G)][x] != '#' && y + G > 31 && y < 30 && y > 0){
		cout << "1" << endl;
		while(map[y + 1][x] != '#' && y < 30 && y > 0) y ++;
		if(y >= 30) y = 29;
		G = 1;
		return ;
	}
	if((state == 0 && map[int(y+G)][x] == '#')|| y+G  > 29){
		G = 1;
		return;
	}
	int to=y;
	while(map[to+1][x]!='#'&&to-y<=G)
		to++;
	y=to;
	G+=G*0.2;
}
int main(){
	hideCursor();
	while(1){
		if(_kbhit()){
			char ch=_getch();
			ch=tolower(ch);
			if(ch=='s'&&y<30)	y++;
			else if(ch=='w'&& y > 1 && state == 0 && map[y + 1][x] == '#')	state = 1;
			else if(ch=='a'&& x > 1 && map[y][x - 1] != '#') x--;
			else if(ch=='d'&& x < 30 && map[y][x + 1] != '#')	x++;
		}
		if(state == 1 && cnt < 4 && map[y - 1][x] != '#') cnt ++, y --, G = 1;
		if((cnt == 4 && state == 1) || map[y - 1][x] == '#' || y == 1){
			state = 0;
			cnt = -1;
		}
		if(state == 0)	Gmg(x, y);
		for(int i = 0; i <= 30 ; i++){
			for(int j = 0; j <= 30; j ++){
				gotoXY(j,i);
				if(i == y && j == x) cout << "@";
				else if(map[i][j] == '#') cout << "#";
				else cout << ' ';
			}
		}
	}
	return 0;
}
