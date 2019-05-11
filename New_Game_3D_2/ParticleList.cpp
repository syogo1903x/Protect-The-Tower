#include "ParticleList.h"

int ParticleList::particleNum = 100;

// 静的インスタンスの生成
ParticleList& ParticleList::CreateParticleList()
{
	static ParticleList particleList;
	return particleList;
}

// コンストラクタ
ParticleList::ParticleList()
{
	// パーティクルのメモリを確保
	particle = new ParticleEmitter*[particleNum];
	for (int i = 0; i < particleNum; i++)
	{
		// NULLで初期化
		particle[i] = NULL;
	}
}

// デストラクタ
ParticleList::~ParticleList()
{
	// 解放ができていなければ、関数を呼ぶ
	if (particle != NULL)
	{
		DestroyParticle();
	}
}

// パーティクルの生成
ParticleEmitter* ParticleList::CreateParticle(ParticleData _particle)
{
	for (int i = 0; i < particleNum; i++)
	{
		// 確保しようとしているデータがNULLだったら
		if (particle[i] == NULL)
		{
			// パーティクルのデータを確保
			particle[i] = new ParticleEmitter();
			if (particle[i] != NULL)
			{
				// 引数のデータをパーティクルに渡す
				particle[i]->SetParticle(_particle);
				// セットされたパーティクルを返す
				return particle[i];
			}
		}
		else
		{
			// データが既に格納されていたらスキップする
			continue;
		}
	}
}

// パーティクルの削除
void ParticleList::DestroyParticle()
{
	for (int i = 0; i < particleNum; i++)
	{
		delete(particle[i]);
		particle[i] = NULL;
	}
	delete[](particle);
	particle = NULL;
}

// 初期化
void ParticleList::Initialize()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (particle[i] != NULL)
		{
			// パーティクル
			particle[i]->Initialize();
		}
	}
}

// 更新
void ParticleList::Update()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (particle[i] != NULL)
		{
			// パーティクル
			particle[i]->Update();
		}
	}
}

// 描画
void ParticleList::Draw()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (particle[i] != NULL)
		{
			// パーティクル
			particle[i]->Draw();
		}
	}
}