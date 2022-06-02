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

/**
 * ヘッダー行の書き込み
 */ 
void writeHeader(fstream &file, int width, int height, int maxChroma){
    file << "P6" << endl;
    file << width << " " << height << endl;
    file << maxChroma << endl;
}

/**
 * 二値化した値を書き込む
 */ 
void binalize(fstream &readFile, fstream &writeFile, int value){
    unsigned char p;
    const int RGB_COUNT = 3;
    //黒と白の区切り
    const int VALUE = 205;
    int sum = 0;
    int c = 0;
    while(readFile.read((char*)&p, sizeof p)){
        sum += (int)p;
        if(++c % RGB_COUNT == 0){
            unsigned char wr = (value < (sum / RGB_COUNT)) ? 255 : 0;
            sum = 0;
            c = 0;
            for(int i=0; i < RGB_COUNT; ++i){
                writeFile << wr;
            }
        }
    }
}

int main(){
    //読み込みファイル
    const string READ_FILE = "./test.ppm";
    const int MAX_WIDTH = 600;
    const int MAX_HEIGHT = 600;
    //出力ファイル
    const string WRITE_FILE = "./out_test.ppm";
    //黒と白の区切り
    const int VALUE = 205;

    //読み込みファイル
    fstream readFile(READ_FILE, ios::in|ios::binary);
    if(!readFile.is_open()){
        return EXIT_FAILURE;
    }
    int width, height, maxChroma = 0;
    getHeader(readFile, width, height, maxChroma);   
    if(width == 0 || height == 0 || MAX_WIDTH < width || MAX_HEIGHT < height){
        return EXIT_FAILURE;
    }

    //書き込みファイル
    fstream beforeWriteFile(WRITE_FILE);
    if(beforeWriteFile.is_open()){
        //ファイル削除
        remove(WRITE_FILE.c_str());
    }
    fstream writeFile;
    writeFile.open(WRITE_FILE, ios::out|ios::binary);
    writeHeader(writeFile, width, height, maxChroma);

    //二値化
    binalize(readFile, writeFile, VALUE);

    writeFile.close();
    readFile.close();
    return 0;    
}