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

int main(){
    const string READ_FILE = "./test.ppm";
    const string WRITE_FILE = "./out_test.ppm";

    //参照するファイル
    fstream readFile(READ_FILE, ios::in|ios::binary);
    if(!readFile.is_open()){
        return EXIT_FAILURE;
    }
    //ヘッダー読み込み
    int width, height, maxChroma = 0;
    getHeader(readFile, width, height, maxChroma);   
    if(width == 0 || height == 0){
        return EXIT_FAILURE;
    }

    //ファイル書き込み
    fstream beforeWriteFile(WRITE_FILE);
    if(beforeWriteFile.is_open()){
        //ファイル削除
        remove(WRITE_FILE.c_str());
    }
    fstream writeFile;
    writeFile.open(WRITE_FILE, ios::out|ios::binary);
    writeHeader(writeFile, width, height, maxChroma);

    //内容
    unsigned char p;
    const int RGB_COUNT = 3;
    //黒と白の区切り
    const int VALUE = 205;
    int sum = 0;
    int c = 0;
    while(readFile.read((char*)&p, sizeof p)){
        sum += (int)p;
        if(++c % RGB_COUNT == 0){
            unsigned char wr = (VALUE < (sum / RGB_COUNT)) ? 255 : 0;
            sum = 0;
            c = 0;
            for(int i=0; i < RGB_COUNT; ++i){
                writeFile << wr;
            }
        }
    }

    writeFile.close();
    readFile.close();
    return 0;    
}