#include<fstream>
#include<iostream>
using namespace std;
int main(){
  ifstream inputFile("stageData.txt", ifstream::binary);
  inputFile.seekg(0, ifstream::end);
  int fileSize = static_cast<int>(inputFile.tellg());
  inputFile.seekg(0, ifstream::beg);
  char * fileImage = new char[fileSize];
  inputFile.read(fileImage, fileSize);

  cout.write(fileImage, fileSize);
}
