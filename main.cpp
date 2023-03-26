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
bool in_air,jump;
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
	if(map[y + 1][x] == '#')	return;
	if(!in_air&&map[int(y+G)][x] == ' ' && y + G > 31 && y < 30 && y > 0){
		while(map[y + 1][x] == ' ' && y < 30 && y > 0) y ++;
		if(y>=30)	y=29;
		G = 1;
	} else if((!in_air&&map[int(y+G)][x] == '#')|| y+G  > 29){	G = 1;
	} else {
		int to=y;
		while(map[to+1][x]==' '&&to-y<=G)	to++;
		y=to;
		G*=1.2;
	}
}
int main(){
	hideCursor();
	while(1){
		if(_kbhit()){
			//input
			char ch=_getch();
			ch=tolower(ch);
			if(ch=='w'&&!in_air&&y>1&&map[y+1][x]=='#')	in_air=true,jump=true;	//着地
			else if(ch=='a'&& x > 1 && map[y][x - 1] == ' ')	x--;
			else if(ch=='d'&& x < 30 && map[y][x + 1] == ' ')	x++;
		}
		//move
		if(in_air&&jump&&cnt<4&&map[y-1][x]==' '){
			cnt++;
			y--;
			G=1;
		}
		if(in_air&&(cnt==4||map[y+1][x]=='#'||y==1)){
			jump=false;
			cnt=-1;
		}
		if(map[y+1][x]=='#'||y==1)	in_air=false;
		if(!jump)	Gmg(x, y);
		//print map
		for(int i = 0; i <= 30 ; i++)
			for(int j = 0; j <= 30; j ++){
				gotoXY(j,i);
				if(i==y&&j==x)	cout << "@";
				else	cout<<map[i][j];
			}
	}
	return 0;
}
