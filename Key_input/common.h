#pragma once

////////////////////////////////////
// include
////////////////////////////////////
#include <CommonStates.h>
#include "release.h"

////////////////////////////////////
// 名前空間
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Common
{
private:
    static CommonStates* state_;        // CommonStatesクラスポインタ

public:
    static bool init();                     // 初期化
    static void destroy() { SAFE_DELETE_ARRAY( state_ ); }// 破棄

    // インターフェイスの取得
    // CommonStateポインタを返す
    static CommonStates* getCommon() { return state_; }
};