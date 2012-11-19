#include<iostream>
using namespace std;

const char gStageData[]= "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

const int gStageWidth = 8;
const int gStageHeight = 5;

enum Object{
  OBJ_SPACE,
  OBJ_WALL,
  OBJ_GOAL,
  OBJ_BLOCK,
  OBJ_BLOCK_ON_GOAL,
  OBJ_MAN,
  OBJ_MAN_ON_GOAL,

  OBJ_UNKNOWN,
};

void initialize(Object* state, int w, int h, const char* stageData);
void draw(const Object* state, int w, int h);
void update(Object* state, char input, int w, int h);
bool checkClear(const Object* state, int w, int h);

int main(){
  //状態配列を確保
  Object* state = new Object[ gStageWidth * gStageHeight ];
  //ステージ初期化
  initialize( state, gStageWidth, gStageHeight, gStageData );
  while(true){
    draw( state, gStageWidth, gStageHeight);
    if(checkClear( state, gStageWidth, gStageHeight )){
      break;
    }
    cout << "a:left s:right w:up z:down. command? "<<endl;
    char input;
    cin >> input;
    update( state, input, gStageWidth, gStageHeight );
  }
  cout << "Congratulation's! you win."<<endl;
  delete[] state;
  state = 0;

  return 0;
}

void initialize(
		Object* state,
		int width,
		int height,
		const char* stageData){
  const char* d = stageData; // reading pointer
  int x = 0;
  int y = 0;
  while(*d != '\0'){
    Object t;
    switch(*d){
    case '#': t = OBJ_WALL; break;
    case ' ': t = OBJ_SPACE; break;
    case 'o': t = OBJ_BLOCK; break;
    case 'O': t = OBJ_BLOCK_ON_GOAL; break;
    case '.': t = OBJ_GOAL; break;
    case 'p': t = OBJ_MAN; break;
    case 'P': t = OBJ_MAN_ON_GOAL; break;
    case '\n': //次の行へ
      x = 0;
      ++y;
      t = OBJ_UNKNOWN;
      break;
    default : t = OBJ_UNKNOWN; break;
    }

    ++d;
    if( t!= OBJ_UNKNOWN ){
      state[y*width + x] = t;
      ++x;
    }
  }
}

void draw(const Object* state, int width, int height){
  const char font[] = {' ', '#', '.', 'o', 'O', 'p', 'P'};
  for(int y = 0; y < height; ++y){
    for(int x = 0; x < width; ++x){
      Object o = state[ y*width + x ];
      cout << font[o];
    }
    cout << endl;
  }
}

void update(Object* s, char input, int w, int h){
  //入力を移動値に変換
  int dx = 0;
  int dy = 0;
  switch(input){
  case'a':dx = -1; break;
  case 's':dx = 1; break;
  case'w':dy = -1;break;
  case 'z':dy = 1;break;
  }
  //プレイヤの位置を求める
  int i = -1;//意味はないが初期化
  for(i = 0; i < w*h; ++i){
    if(s[i] == OBJ_MAN || s[i] == OBJ_MAN_ON_GOAL){
      break;
    }
  }
  int x = i%w;
  int y = i/w;

  //移動後の座標
  int tx = x + dx;
  int ty = y + dy;
  //座標チェック
  if(tx < 0 || w <= tx || ty < 0 || h <= ty){
    return;
  }

  //移動先が空白またはゴール。人が移動
  int p = y*w + x; //人の位置
  int tp = ty*w + tx;//ターゲット位置
  if(s[tp] == OBJ_SPACE || s[tp] ==OBJ_GOAL){
    //ゴールならゴールの上に
    s[tp] = (s[tp] == OBJ_GOAL)? OBJ_MAN_ON_GOAL : OBJ_MAN;
    //もともとゴール上ならゴールに
    s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
  }
  //移動先が箱。その方向の次のますが空白またはゴールであれば移動。
  else if(s[tp] == OBJ_BLOCK || s[tp] == OBJ_BLOCK_ON_GOAL){
    //2マス先をチェック
    int tx2 = tx + dx;
    int ty2 = ty + dy;
    //範囲内かどうか
    if(tx2 < 0 || ty2 < 0 || w <= tx2 || h <= ty2){
      return ;//押せない
    }

    int tp2 = ty2 * w + tx2;
    if(s[tp2] == OBJ_SPACE || s[tp2] == OBJ_GOAL){
      //順次入れ替え
      s[tp2] = (s[tp2] == OBJ_GOAL)?
	OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
      s[tp] = (s[tp] == OBJ_BLOCK_ON_GOAL)?
	OBJ_MAN_ON_GOAL : OBJ_MAN;
      s[p] = (s[p] == OBJ_MAN_ON_GOAL)?
	OBJ_GOAL : OBJ_SPACE;
    }
  }
}

bool checkClear(const Object* s, int width, int height){
  for(int i = 0; i < width * height; i++){
    if(s[i] == OBJ_BLOCK){
      return false;
    }
  }
  return true;
}
