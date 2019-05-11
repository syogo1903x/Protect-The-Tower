#pragma once
#include "ParticleEmitter.h"

class ParticleEmitter;

// パーティクル / 管理クラス
class ParticleList final
{
public:
	// 静的インスタンスの生成
	static ParticleList& CreateParticleList();

	~ParticleList();	// デストラクタ

	void Initialize();	// 初期化
	void Update();		// 更新
	void Draw();		// 描画

	// パーティクルの生成
	ParticleEmitter* CreateParticle(ParticleData _particle);
	void             DestroyParticle();

private:
	ParticleList();						// シングルトン
	ParticleEmitter **particle;
	static int        particleNum;		// パーティクルの数
};

#define PARTICLE_LIST ParticleList::CreateParticleList()