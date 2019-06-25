/*
学籍番号:193375
氏名:吉原直輝
科目名:ソフトウェア演習2-A
課題名:課題1(C++言語でのI/Oストリーム)
提出日:2019年6月25日
*/
#include <iostream>/*入出力を行うため*/
using namespace std;
#include <fstream>  /*ファイルI/Oを使うため*/
#include <cstring> /*string型変数を使うため*/
#include <iomanip>/*入出力のフォーマットの変更で使うため(setw)*/
#include <ctime>	/*日付を使うため*/

int main(int ac, char **av){
	#define BUFFER_MAX (500)/* 入力バッファ: アルファベットは512文字長以下と仮定 */
	#define STRING_MAX (20)	/*単語の最大長は20文字を超えないという仕様より20*/
	#define WORD_PATTERN (500) /*単語が512個以下検出されると仮定*/
	char buffer[BUFFER_MAX];/* 入力バッファ: アルファベットは512文字長以下と仮定 */
	char moji[WORD_PATTERN][STRING_MAX];/*読み込んだ文字列格納配列*/
	
	if (ac != 2){/* 引数が１個でないとき */
		cerr << "WordFind [ASCIIデータファイル名]" << endl;
		return -1;
	}

	ifstream fin(av[1], ios::in);/* 入力ファイルのオープン*/
	if (fin.fail()){/* ファイルオープンできないとき */
		cerr << "ファイル：" << av[1] << "がオープンできませんでした" << endl;
		exit(EXIT_FAILURE);/* 終了：#include を必要とする */
	}

	char c;/* 文字を保持 */
  static int cnt_moji = 0;  //カウント用変数

	while (true)	/* EOFまで読み続ける */
	{
		fill(buffer, buffer+BUFFER_MAX, '\0');/* バッファを'\0'で初期化 */
    int i=0;	//カウント用変数(読み込み用)
    static int j=0;	//カウント用変数(読み込み用)

/* 文字単位で読込み、アルファベットならバッファに入れる*/
		while  ((c = fin.get()) && isalpha(c))    //isalpha=アルファベットか否かのチェック
    {
      if (c>=0x40 && c<=0x5a)//もし先頭が大文字ならば
      {
        c = c + 0x20; //大文字を小文字に変換する
      }
			  buffer[i++] = c;/* バッファに入れる */

    }
			if(buffer[0] != '\0')//空白なら格納しない
			{
			strcpy(moji[j],buffer);//ソート用配列に格納
    	j++;
			cnt_moji++;
	  }
    if (fin.eof()) break; /* 終了 */
	}

/*ここから単語をアルファベット順にソート*/
	int k;	//カウント変数(処理用)
	int l;	//カウント変数(処理用)
	char tmp[STRING_MAX];
	for(k=1;k<cnt_moji;k++){
		for(l=1;l<cnt_moji;l++){
			if(strcmp(moji[l-1], moji[l])>0){
				strcpy(tmp, moji[l-1]);
				strcpy(moji[l-1], moji[l]);
				strcpy(moji[l], tmp);
			}
		}
	}
/*ソート終了*/

/*単語数のカウントを行い,結果を出力する*/
	time_t now = time(nullptr);// nullptr は C++11 以降に使える予約語です
	struct tm* local = localtime(&now);/*現在時刻を取得します*/

/*時間等の基本情報を出力*/
    cout << "氏名:吉原直輝 193375" << endl;
    cout << "ファイル名:"<< av[1] << endl;
    cout << "日付:" << local->tm_year+1900 <<"年" << local->tm_mon+1 << "月" <<
    local->tm_mday << "日" << local->tm_hour << "時" <<
    local->tm_min << "分" << local->tm_sec << "秒" << endl;
    cout <<"課題1:C++言語でのI/Oストリーム "<< "課題内容:英語ニュースの単語とその出現回数 " << endl;

	char pattern[STRING_MAX];
	fill(pattern, pattern+STRING_MAX, '\0');/*配列を'\0'で初期化 */
	int cnt_mojis;	/*出現回数をカウントする*/
    int cnt_s=0;
    
    k=0;
/*単語の出現回数をカウントし,結果を出力していく*/
	while(k<cnt_moji)
	{
		cnt_mojis=0;
		strcpy(pattern,moji[k]);
		while(strcmp(pattern,moji[k])==0)
		{
			cnt_mojis++;
			k++;
		}
        cnt_s++;
        cout << "(" << cnt_s << "): "<< "単語:" << left << setw(15) << pattern << " 出現回数 " << cnt_mojis << '\n';
	}
    cout << "単語総数:" << cnt_moji << endl;
	fin.close();/* ファイルのclose */
	return 0;
}
