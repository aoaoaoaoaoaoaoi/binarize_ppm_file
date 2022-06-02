# ppmファイルの二値化
## 設定値
以下部分に直接記載<br>

code.cppの64-71行目
```c++
    //読み込みファイル
    const string READ_FILE = "./test.ppm";
    const int MAX_WIDTH = 600;
    const int MAX_HEIGHT = 600;
    //出力ファイル
    const string WRITE_FILE = "./out_test.ppm";
    //黒と白の区切り
    const int VALUE = 205;
```

|  定数  |  内容  |
| ---- | ---- |
|  READ_FILE  |  変換前のppmファイル  |
|  MAX_WIDTH  |  変換前のファイルの最大の横幅  |
|  MAX_HEIGHT  |  変換前のファイルの最大の縦幅  |
|  WRITE_FILE  |  変換した出力ppmファイル  |
|  VALUE  |  白と黒の区切り（RGB平均値）  |

## 内容
ファイルの各色のRGBの平均値を算出し、```VALUE```で区切って二値化する

