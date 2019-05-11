#include "ParticleEmitter.h"
#include <stdio.h>

int ParticleEmitter::particleGraphHandle;

// コンストラクタ
ParticleEmitter::ParticleEmitter()
{
	// パーティクルの画像を読み込む
	particleGraphHandle = LoadGraph("img/particle.png");
	particlesRandData = NULL;

	// 各変数の初期化
	particleData.positionRange = VGet(0, 0, 0);	// 出現範囲
	particleData.minDirection  = VGet(0, 0, 0);	// 最小の方向
	particleData.maxDirection  = VGet(0, 0, 0);	// 最大の方向
	particleData.minRotation   = 0;				// 最小の回転角
	particleData.maxRotation   = 0;				// 最大の回転角
	particleData.minScale      = 0;				// 最小の大きさ
	particleData.maxScale      = 0;				// 最大の大きさ
	particleData.minSpeed      = 0;				// 最小のスピード
	particleData.maxSpeed      = 0;				// 最大のスピード
	particleData.minStartTime  = 0;				// 最小の発生時間
	particleData.maxStartTime  = 0;				// 最大の発生時間
	particleData.minLifeTime   = 0;				// 最小の生成時間
	particleData.maxLifeTime   = 0;				// 最大の生成時間
	particleData.colorRed      = 0;				// 赤
	particleData.colorGreen    = 0;				// 緑
	particleData.colorBlue     = 0;				// 青
	particleData.alpha         = 0;				// 透明度
	particleNum				   = 0;				// 生成数
	centerPosition             = VGet(0,0,0);
	isActive                   = false;
}

// デストラクタ
ParticleEmitter::~ParticleEmitter()
{

}


// パーティクルのデータをセット
void ParticleEmitter::SetParticle(ParticleData _particle)
{
	// パーティクルのデータを格納
	particleData.positionRange = _particle.positionRange;	// 出現範囲
	particleData.minDirection  = _particle.minDirection;	// 最小の方向
	particleData.maxDirection  = _particle.maxDirection;	// 最大の方向
	particleData.minRotation   = _particle.minRotation;		// 最小の回転角
	particleData.maxRotation   = _particle.maxRotation;		// 最大の回転角
	particleData.minScale      = _particle.minScale;		// 最小の大きさ
	particleData.maxScale      = _particle.maxScale;		// 最大の大きさ
	particleData.minSpeed      = _particle.minSpeed;		// 最小のスピード
	particleData.maxSpeed      = _particle.maxSpeed;		// 最大のスピード
	particleData.minStartTime  = _particle.minStartTime;	// 最小の発生時間
	particleData.maxStartTime  = _particle.maxStartTime;	// 最大の発生時間
	particleData.minLifeTime   = _particle.minLifeTime;		// 最小の生成時間
	particleData.maxLifeTime   = _particle.maxLifeTime;		// 最大の生成時間
	particleData.colorRed      = _particle.colorRed;		// 赤
	particleData.colorGreen    = _particle.colorGreen;		// 緑
	particleData.colorBlue     = _particle.colorBlue;		// 青
	particleData.alpha         = _particle.alpha;			// 透明度
	particleNum				   = _particle.particleNum;		// 生成数
	// パーティクルを生成
	particlesRandData = new ParticleRandData[particleNum];
}

// 初期化
void ParticleEmitter::Initialize()
{
	for (int i = 0; i < particleNum; i++)
	{
		particlesRandData[i].isActive = false;
	}
}

// 更新
void ParticleEmitter::Update()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (isActive == true)
		{
			if (particlesRandData[i].isActive == false)
			{
				// パーティクルの出現範囲をセット
				VECTOR tmpPosition;
				tmpPosition = VGet(GetRand(centerPosition.x - particleData.positionRange.x / 2.0f, centerPosition.x + particleData.positionRange.x / 2.0f),		// X軸
								   GetRand(centerPosition.y - particleData.positionRange.y / 2.0f, centerPosition.y + particleData.positionRange.y / 2.0f),		// Y軸
								   GetRand(centerPosition.z - particleData.positionRange.z / 2.0f, centerPosition.z + particleData.positionRange.z / 2.0f));	// Z軸
				particlesRandData[i].position = tmpPosition;

				// パーティクルの向きをセット
				VECTOR tmpDirection = VGet(GetRand(particleData.minDirection.x, particleData.maxDirection.x),	// X軸
										   GetRand(particleData.minDirection.y, particleData.maxDirection.y),	// Y軸
										   GetRand(particleData.minDirection.z, particleData.maxDirection.z));	// Z軸
				// 正規化する
				if (VSquareSize(tmpDirection) != 0)
				{
					tmpDirection = VNorm(tmpDirection);
				}
				// 正規化した向きベクトルをセット
				particlesRandData[i].direction = tmpDirection;

				// パーティクルの回転角をセット
				particlesRandData[i].Rotation = GetRand(particleData.minRotation, particleData.maxRotation);
				
				// パーティクルの大きさをセット
				particlesRandData[i].scale = GetRand(particleData.minScale, particleData.maxScale);

				// パーティクルのスピードをセット
				particlesRandData[i].speed = GetRand(particleData.minSpeed, particleData.maxSpeed);

				// パーティクルの色をセット
				colorRed   = particleData.colorRed;
				colorGreen = particleData.colorGreen;
				colorBlue  = particleData.colorBlue;

				// 透明度をセット
				alpha = particleData.alpha;

				// パーティクルの発生時間をセット
				particlesRandData[i].startTime = (int)GetRand((float)particleData.minStartTime, (float)particleData.maxStartTime);

				// パーティクルの生成時間をセット
				particlesRandData[i].lifeTime = (int)GetRand((float)particleData.minLifeTime, (float)particleData.maxLifeTime);

				particlesRandData[i].lifeCount = 0;
				particlesRandData[i].startCount = 0;
				particlesRandData[i].isActive = true;
			}

			// データが入ったら、発生時間のカウントを回す
			if (particlesRandData[i].isActive) { particlesRandData[i].startCount++; }

			// 生成したパーティクルを制御
			if (particlesRandData[i].isActive && 
				particlesRandData[i].startCount > particlesRandData[i].startTime)
			{
				particlesRandData[i].lifeCount++;
				// 移動制御
				VECTOR velocity = VScale(particlesRandData[i].direction, particlesRandData[i].speed);
				particlesRandData[i].position = VAdd(particlesRandData[i].position, velocity);

				// 生成時間が経ったら消す
				if (particlesRandData[i].lifeCount > particlesRandData[i].lifeTime)
				{
					// 変数の初期化
					particlesRandData[i].isActive = false;
					particlesRandData[i].lifeCount = 0;
					particlesRandData[i].startCount = 0;
				}
			}
		}
		else
		{
			// パーティクルが機能していない場合は、座標をワールド空間の彼方に設定
			centerPosition				  = VGet(900000, 900000, 900000);
			particlesRandData[i].position = VGet(900000, 900000, 900000);
		}
	}
}

// 描画
void ParticleEmitter::Draw()
{
	// Zバッファを使用する
	SetUseZBuffer3D(TRUE);
	// Zバッファの書き込みは行わない
	SetWriteZBuffer3D(FALSE);

	for (int i = 0; i < particleNum; i++)
	{
		if (isActive == true)
		{
			if (particlesRandData[i].isActive &&
				particlesRandData[i].startCount > particlesRandData[i].startTime)
			{
				// 描画光度を設定
				SetDrawBright(colorRed, colorGreen, colorBlue);
				// 加算ブレンドでパーティクルの描画
				SetDrawBlendMode(DX_BLENDMODE_ADD_X4, alpha * 255);
				DrawBillboard3D(particlesRandData[i].position,	// 座標
								0.5f,							// 中心座標（X軸）
								0.5f,							// 中心座標（Y軸）
								particlesRandData[i].scale,		// 大きさ
								particlesRandData[i].Rotation,	// 回転角
								particleGraphHandle,			// グラフィックハンドル
								TRUE);							// 透過処理をするか

				// 描画光度を戻す
				SetDrawBright(255, 255, 255);
				// ノーブレンド
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			}
		}
	}
}

// 乱数の取得
float ParticleEmitter::GetRand(float _min, float _max)
{
	return _min + (float)(rand() * (_max - _min + 1.0f) / (1.0f + RAND_MAX));
}