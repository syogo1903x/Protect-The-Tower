#pragma once

#include "DxLib.h"
#include <list>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <sstream>
#include <iomanip>

// エフェクサー
#include "EffekseerForDXLib.h"

// プレイヤー
#include "Move.h"
#include "Atack.h"
#include "Jump.h"
#include "Animation.h"

// キャラクターベース
#include "CharacterBase.h"

// プレイヤー
#include "Player.h"
#include "Shot.h"

// エネミー
#include "EnemyManager.h"
#include "Enemy.h"
#include "MediumBoss.h"
#include "Boss.h"

// アイテム
#include "ItemBase.h"
#include "Recovery.h"
#include "Coin.h"
#include "Tower.h"
#include "ItemManager.h"

// 防衛アイテム
#include "DefenseManager.h"
#include "DefenseBase.h"
#include "DefenseWall.h"
#include "DefenseAtackBall.h"
#include "DefenseFire.h"
#include "DefenseSoldier.h"
#include "DefenseBuyObject.h"

// カメラ
#include "Camera.h"

//ステージ
#include "Stage.h"
// 当たり判定
#include "HitCheck.h"

// UI
#include "UI.h"
#include "MiniMap.h"

// シーン切り替え
#include "Lerp.h"
#include "SceneChangeManager.h"
#include "SceneBase.h"
#include "SceneGame.h"
#include "SceneMenu.h"
#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneDemo.h"

#include "Animation.h"
#include "KeyInput.h"
#include "PadInput.h"
#include "MouseInput.h"

// エフェクト
#include "EffectManager.h"
#include "EffectBase.h"
#include "EffectLaser.h"
#include "EffectMagicTeam.h"
#include "EffectHit.h"
#include "EffectDeathBlow.h"
#include "EffectDeathBlow_Ukon.h"
#include "EffectDeathBlow_Ruby.h"
#include "EffectDeathBlow_Chinami.h"
#include "EffectDeathBlow_Inu.h"
#include "EffectDeathBlow_Karasu.h"
#include "EffectJump.h"
#include "EffectBullet.h"
#include "EffectFire.h"
#include "EffectAppearBoss.h"
#include "EffectAppearMedium.h"
#include "EffectDown.h"
#include "EffectTowerHit.h"
#include "EffectTowerOver.h"
#include "EffectTowerDown.h"

// その他
#include "Fade.h"
#include "BackGroundMusic.h"
#include "SoundEffect.h"
#include "FontText.h"
#include "LoadFile.h"
#include "Shader.h"
#include "Loading.h"
#include "NowLoad.h"

#define SCREEN_X			1600
#define SCREEN_Y			900

#define ZEROCLEAR			VGet(0.0f, 0.0f, 0.0f)

#define PLAYER_INIT_POS		VGet(0.0f, 3.0f, 150.0f)
