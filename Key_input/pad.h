#pragma once
////////////////////////////////////
// Include
////////////////////////////////////
#include <GamePad.h>


////////////////////////////////////
// 名前空間
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Pad
{
private:
    static GamePad pad_;             // ゲームパッドクラス
    static GamePad::State state_;    // 1P入力格納構造体
    static GamePad::State state2_;   // 2P入力格納構造体
    static GamePad::ButtonStateTracker tracker_;

public:
    static void update();           // 更新処理

    // 入力構造体を返す
    static const GamePad::State& getState() { return state_; }      //1P
    static const GamePad::State& getState2() { return state2_; }    //2P
    static const  GamePad::ButtonStateTracker& getKeyTracker() { return tracker_; }

};
