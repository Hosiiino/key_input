////////////////////////////////////
// Include
////////////////////////////////////
#include "sprite.h"
#include "direct3d.h"
#include "common.h"

////////////////////////////////////
// メンバ変数の実体を宣言
////////////////////////////////////
SpriteBatch* Sprite::sprite_;

////////////////////////////////////
// 初期化
////////////////////////////////////
bool Sprite::init()
{
    // SpriteBatchクラスのメモリを確保(new演算子で確保)
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    // メモリ確保チェック
    if( !sprite_ )
    {
        // エラー
        return false;
    }

    return true;
}

////////////////////////////////////
// 描画開始関数
////////////////////////////////////
void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getCommon()->NonPremultiplied() );
    // spriteの前後関係の設定　// この場合は後から来たものが上
}

////////////////////////////////////
// 描画関数
////////////////////////////////////
void Sprite::draw(
    ID3D11ShaderResourceView* Texture, const Vector2& Position, const RECT* Rect,
    const float Rotation, const Vector2& Scale, const Vector2& Origin,
    const SpriteEffects Effect, const float Depth )
{
    sprite_->Draw(
        Texture,                // テクスチャ
        Position,               // 座標
        Rect,                   // 描画範囲
        Colors::White,          // カラー
        Rotation,               // 回転値
        Origin,                 // アンカーポイント(原点)
        Scale,                  // 拡縮
        Effect,                 // エフェクト
        Depth                   // 深度値
    );
}