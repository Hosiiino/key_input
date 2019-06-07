#pragma once

////////////////////////////////////
// include
////////////////////////////////////
#include <d3d11.h>
#include <Keyboard.h>
#include "release.h"


////////////////////////////////////
// 名前空間
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Key
{
private:
    static Keyboard* key_;                   // Keyclassポインタ
    static Keyboard::State state_;
    static  Keyboard::KeyboardStateTracker tracker_;

public:
    static bool init();                      // 初期化
    static void update();                    // 更新
    static void destroy() { SAFE_DELETE_ARRAY( key_ ); }   // 破棄

    // インターフェイスの取得
    // Keyboard のポインタを返す
    static Keyboard::State& getKeyState() { return state_; }
    static Keyboard::KeyboardStateTracker& getKeyTracker() { return tracker_; }
};