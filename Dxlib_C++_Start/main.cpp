//main.cpp

//#################### ヘッダファイル読み込み #######################
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"

//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);			//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();			//KEYDOWNクラスのオブジェクトを生成

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	SetAlwaysRunFlag(TRUE);										//非アクティブに設定

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	//ゲームのメインループ
	while (GameMainLoop())
	{
		/*
		ループ内で異常が発生するまで無限ループ
		ゲーム終了やエラー等が発生したらループ終了
		*/
	}

	Delete_Class();			//使用したクラスを破棄

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//無限ループ内のゲーム処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	keydown->KeyDownUpdate();	//キーの入力状態を更新する

	fps->Update();				//FPSの処理[更新]

	//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

	//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	fps->Draw(0,0);				//FPS描画

	ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

	fps->Wait();				//FPSの処理[待つ]

	return true;				//正常

}

//ゲーム内で使用したクラスを削除する処理
void Delete_Class()
{

	delete fps;			//fps破棄
	delete keydown;		//keydown破棄

	return;
}
