#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/**
 * ヘッダーの読み込み
 * 上から3行 
 */
void getHeader(fstream &file, int &width, int &height, int &maxChroma){
    string line;

    //P6であることを確認
    getline(file, line);
    if(line != "P6"){
        cout << "Different types of files" << endl;
        return;
    }

    //高さ、横幅（空白区切り）
    getline(file, line, ' ');
    width = stoi(line);
    getline(file, line);
    height = stoi(line);
    
    //彩度の最大値
    getline(file, line);
    maxChroma = stoi(line); 
}

void writeHeader(fstream &file, int width, int height, int maxChroma){
    file << "";
}

int main(){
    string READ_FILE = "./test.ppm";
    string WRITE_FILE = "./out_test.ppm";

    fstream readFile(READ_FILE, ios::in|ios::binary);
    if(!readFile.is_open()){
        return EXIT_FAILURE;
    }

    int width, height, maxChroma = 0;
    getHeader(readFile, width, height, maxChroma);   
    if(width == 0 || height == 0){
        return EXIT_FAILURE;
    }

    //ファイル書き込み
    fstream writeFile;
    writeFile.open(WRITE_FILE, ios::in|ios::binary);
    writeHeader(writeFile, width, height, maxChroma);

    writeFile.close();


    readFile.close();
    return 0;    
}