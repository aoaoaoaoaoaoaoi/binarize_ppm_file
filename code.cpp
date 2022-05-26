#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

int main(){
    string READ_FILE = "./test.ppm";

    fstream file(READ_FILE, ios::in|ios::binary);
    if(!file.is_open()){
        return EXIT_FAILURE;
    }

    //ヘッダーの読み込み
    //上から3行はイメージの情報なので上限なしに読み込んでも問題ない
    string line;

    //P6であることを確認
    getline(file, line);
    if(line != "P6"){
        cout << "Different types of files" << endl;
    }
    //高さ、横幅（空白区切り）
    getline(file, line, ' ');
    int width = stoi(line);
    getline(file, line);
    int height = stoi(line);
    //彩度の最大値
    getline(file, line);
    int maxChroma = stoi(line);   
    

    cout << line << endl;

    file.close();
    return 0;    
}