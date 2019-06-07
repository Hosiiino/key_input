#pragma once
////////////////////////////////////
// Include
////////////////////////////////////
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include "release.h"

////////////////////////////////////
// 名前空間
////////////////////////////////////
using namespace DirectX;
using namespace SimpleMath;

////////////////////////////////////
// class
////////////////////////////////////
class Sprite
{
private:
    static SpriteBatch* sprite_;  // SpriteBatchクラスポインタ

public:
    static bool init();     // 初期化
    static void begin();    // 描画開始
    static void destroy() { SAFE_DELETE_ARRAY( sprite_ ); }      // 破棄
    static void end() { sprite_->End(); }      // 描画終了

    // 描画
    static void draw(
        ID3D11ShaderResourceView* Texture,                              // テクスチャ
        const Vector2& Position = Vector2( 0.0F, 0.0F ),    // 座標
        const RECT* Rect = NULL,                     // 描画範囲
        const float Rotation = 0.0F,                     // 回転
        const Vector2& Scale = Vector2( 1.0F, 1.0F ),    // 拡縮
        const Vector2& Origin = Vector2( 0.0F, 0.0F ),    // アンカーポイント
        const SpriteEffects Effect = SpriteEffects_None,       // エフェクト
        const float Depth = 0.0F );                   // 深度

    // SpriteBatchポインタを返す
    static SpriteBatch* getSprite() { return sprite_; }
};