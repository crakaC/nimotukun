#include<iostream>

using namespace std;
void draw();
void inputKey();
void updateGame();
void move(int dx, int dy);
void init();
bool movable(int x, int y,int dx, int dy);
bool check();
int field[10][10];
bool blocks[10][10];
const int X = 8, Y = 5;
const char* STAGE[X]={
  "########",
  "# .. p #",
  "# oo   #",
  "#      #",
  "########"
};

char key;
int px,py;
int main(){
  init();
  while(true){
    inputKey();
    updateGame();
    draw();
    if(check()){
      cout << "congratulation!"<<endl;
      break;
    }
  }
}
void init(){
  for(int y = 0; y < Y; y++){
    for(int x = 0; x < X; x++){
      switch(STAGE[y][x]){
      case '#':
	field[y][x] = 0;break;
      case 'p':
	px = x; py = y;
	cout <<"(px,py) = "<<px<<", "<<py<<endl;
	field[y][x] = 1;
	break;
      case 'o':
	blocks[y][x] = true;
	field[y][x] = 1;
	break;
      case '.':
	field[y][x] = 2;
	break;
      case ' ':
	field[y][x] = 1;
	break;
      }
    }
  }
}
void draw(){
  for(int y = 0; y < Y; y++){
    for(int x = 0; x < X; x++){
      if(blocks[y][x]){
	if(field[y][x] == 2)
	  cout << 'O';
	else
	  cout << 'o';
	continue;
      }
      if(px == x && py == y){
	cout <<'p';
	continue;
      }
      
      char c;
      switch(field[y][x]){
      case 0:
	c = '#';
	break;
      case 1:
	c = ' ';break;
      case 2:
	c = '.';break;
      }
      cout << c;
    }
    cout << endl;
  }
}

void inputKey(){
  cout <<"a:left s:right w:up z:down .command?"<<flush;
  cin >> key;
}

void updateGame(){
  int dx = 0,dy = 0;
  cout << "key = "<< key << endl;
  switch(key){
  case 'a':
    dx = -1;break;
  case 's':
    dx = 1;break;
  case 'w':
    dy = -1;break;
  case 'z':
    dy = 1;break;
  }
  move(dx,dy); 
}
 
void move(int dx, int dy){
  int nx = px + dx;
  int ny = py + dy;
  if(0 <= nx && nx < X && 0 <= ny && ny < Y && movable(nx,ny,dx,dy)){
    px = nx, py = ny;
  }
}

bool movable(int x, int y, int dx, int dy){
  //壁
  if(field[y][x] == 0){
    return false;
  }
  //blockでない
  else if(blocks[y][x] == false){
    return true;
  }
  //blockを動かせる
  else if(blocks[y][x] && field[y+dy][x+dx]>=1){
    blocks[y][x] = false;
    blocks[y+dy][x+dx] = true;
    return true;
  }
  else{
    return false;
  }
}

bool check(){
  for(int y = 0; y < Y; y++){
    for(int x = 0; x < X ; x++){
      if(blocks[y][x] && field[y][x] != 2)
	return false;
    }
  }
  return true;
}
