#pragma once
#include <DxLib.h>

// パーティクルのデータを格納する構造体
struct ParticleData
{
	VECTOR positionRange;	// 出現範囲
	VECTOR minDirection;	// 最小の方向
	VECTOR maxDirection;	// 最大の方向
	float  minRotation;		// 最小の回転角
	float  maxRotation;		// 最大の回転角
	float  minScale;		// 最小の大きさ
	float  maxScale;		// 最大の大きさ
	float  minSpeed;		// 最小のスピード
	float  maxSpeed;		// 最大のスピード
	int    minStartTime;	// 最小の発生時間
	int    maxStartTime;	// 最大の発生時間
	int    minLifeTime;		// 最小の生成時間
	int    maxLifeTime;		// 最大の生成時間
	int    colorRed;		// 赤
	int    colorGreen;		// 緑
	int    colorBlue;		// 青
	int    alpha;			// 透明度
	int    particleNum;		// 生成数
};


// パーティクル
class ParticleEmitter
{
public:
				 ParticleEmitter();	// コンストラクタ
				~ParticleEmitter();	// デストラクタ

			void Initialize();		// 初期化
			void Update();			// 更新
			void Draw();			// 描画

	inline float GetRand(float _min,float _max);		// 乱数を取得
			void SetParticle(ParticleData _particle);	// パーティクルを生成
			
			// セッター関数群
			void SetCenterPosition(VECTOR _set) { centerPosition             = _set; }	// 中心座標
			void SetActive		  (bool   _set) { isActive                   = _set; }	// 生成中か
			void SetPositionRange (VECTOR _set) { particleData.positionRange = _set; }	// 出現範囲
			void SetMinDirection  (VECTOR _set) { particleData.minDirection  = _set; }	// 最小の方向
			void SetMaxDirection  (VECTOR _set) { particleData.maxDirection  = _set; }	// 最大の方向
			void SetMinRotation   (float  _set) { particleData.minRotation   = _set; }	// 最小の回転角
			void SetMaxRotation   (float  _set) { particleData.maxRotation   = _set; }	// 最大の回転角
			void SetMinScale      (float  _set) { particleData.minScale      = _set; }	// 最小の大きさ
			void SetMaxScale      (float  _set) { particleData.maxScale      = _set; }	// 最大の大きさ
			void SetMinSpeed      (float  _set) { particleData.minSpeed      = _set; }	// 最小のスピード
			void SetMaxSpeed      (float  _set) { particleData.maxSpeed      = _set; }	// 最大のスピード
			void SetMinStartTime  (int    _set) { particleData.minStartTime  = _set; }	// 最小の発生時間
			void SetMaxStartTime  (int    _set) { particleData.maxStartTime  = _set; }	// 最大の発生時間
			void SetMinLifeTime   (int    _set) { particleData.minLifeTime   = _set; }	// 最小の生成時間
			void SetMaxLifeTime   (int    _set) { particleData.maxLifeTime   = _set; }	// 最大の生成時間
			void SetColorRed      (int    _set) { particleData.colorRed      = _set; }	// 赤
			void SetColorGreen    (int    _set) { particleData.colorGreen    = _set; }	// 緑
			void SetColorBlue     (int    _set) { particleData.colorBlue     = _set; }	// 青
			void SetAlpha         (int    _set) { particleData.alpha         = _set; }	// 透明度
			void SetParticleNum   (int    _set) { particleData.particleNum   = _set; }	// 生成数

private:
	// パーティクルの乱数を格納する構造体
	struct ParticleRandData
	{
		VECTOR position;		// 出現位置
		VECTOR direction;		// 向き
		float  Rotation;		// 回転角
		float  scale;			// 大きさ
		float  speed;			// スピード
		int    startTime;		// 発生時間
		int    startCount;		// 発生時間のカウント
		int    lifeTime;		// 生成時間
		int    lifeCount;		// 生成時間のカウント
		bool   isActive;		// 生成されているか
	};

	static int        particleGraphHandle;	// グラフィックハンドル
	ParticleData      particleData;			// パーティクルのデータを格納
	VECTOR			  centerPosition;		// 中心座標
	ParticleRandData *particlesRandData;	// パーティクルの乱数を格納
	int				  colorRed;				// 赤
	int				  colorGreen;			// 緑
	int				  colorBlue;			// 青
	int               alpha;				// 透明度
	int				  particleNum;			// 生成数
	bool              isActive;				// パーティクルが生成中か

};