#pragma once
////////////////////////////////////
// Include
////////////////////////////////////
#include <Windows.h>

////////////////////////////////////
// class
////////////////////////////////////
class Error
{
public:
    static void showDialog( const char* Message )   // エラーメッセージ
    {
        MessageBox(
            NULL,
            Message,                // 表示したい文字列
            "Error",                // タイトル
            MB_OK | MB_ICONERROR ); // ボックスのデザイン
    }
};