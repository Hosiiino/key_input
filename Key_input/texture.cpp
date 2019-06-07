////////////////////////////////////
// Include
////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <WICTextureLoader.h>
#include <cstdio>

#include "texture.h"
#include "direct3d.h"
#include "error.h"

////////////////////////////////////
// 読み込み
////////////////////////////////////
ID3D11ShaderResourceView* Texture::load( const wchar_t* FileName )
{
    ID3D11ShaderResourceView* texture;

    // テクスチャの読み込み
    if( FAILED( CreateWICTextureFromFileEx(     // bmp,jpg,pngがこの関数で読み込める
        Direct3D::getDevice(),      // D3Dデバイスインターフェイス
        Direct3D::getContext(),     // デバイスコンテキストインターフェイス
        FileName,                   // ファイル名(ワイド文字で指定)
        0,                          // ミップマップレベル
        D3D11_USAGE_DEFAULT,        // 使用方法
        D3D11_BIND_SHADER_RESOURCE, // バインドの種類
        0,                          // CUPアクセス方法
        0,                          // フラグオプション
        WIC_LOADER_DEFAULT,         // SRGBフラグ
        NULL,                       // リソースデータ受取先ポインタ
        &texture ) ) )              // シェーダーリソースビュー受取先ポインタ 
    {
        // エラー
        char file_name[ 256 ], str[ 256 ];                              // ファイルネーム格納用変数file_nameと文字列格納用変数str
        wcstombs( file_name, FileName, 256 );                           // Unicode文字をマルチバイト文字に変換
        sprintf( str, "テクスチャの読み込みに失敗(%s)", file_name );    // strに文字を格納
        Error::showDialog( str );                                       // エラーメッセージ表示

        return NULL;
    }

    return texture;
}