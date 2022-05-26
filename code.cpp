#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/**
 * ヘッダーの読み込み
 * 上から3行 
 */
void getHeader(fstream &file, int &width, int &height){
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
    int maxChroma = stoi(line); 
}

int main(){
    string READ_FILE = "./test.ppm";

    fstream file(READ_FILE, ios::in|ios::binary);
    if(!file.is_open()){
        return EXIT_FAILURE;
    }

    int width, height;
    getHeader(file, width, height);   
    


    file.close();
    return 0;    
}