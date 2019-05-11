#include "Shot.h"

// コンストラクタ
Shot::Shot()
{
	// プレイヤーで弾のモデルを変える
	if (SceneMenu::GetPlayer() == "character/original/Ruby_Gun/Ruby.pmx")
	{
		modelHandle = MV1LoadModel("Item/パワーストーン/パワーストーン.pmx");
	}
	else
	{
		modelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::BULLET_SHOT));
		MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));
	}

	se = new SoundEffect("Music/SE/short_punch1.mp3");
}

// デストラクタ
Shot::~Shot()
{
	// 解放
	for (itr = bullet.begin(); itr != bullet.end(); itr++)
	{
		bullet.erase(itr);
	}

	// 撃たれていない弾の削除
	for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
	{
		notBullet.erase(notItr);
		MV1DeleteModel((*notItr)->modelHandle);
		(*notItr)->modelHandle = NULL;
	}

	// 弾のモデル開放
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		se = NULL;
		delete(se);
	}
}

// 初期化
void Shot::CreateShot(int _creater)
{

	// 初期化　未使用リスト追加
	for (int i = 0; i < _creater; i++)
	{
		bul[i] = new GunShot();
		notBullet.push_back(bul[i]);
	}


	// 未使用リスト
	if (!notBullet.empty())
	{
		for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
		{
			(*notItr)->pos = VGet(0, 100, 0);
			(*notItr)->dir = ZEROCLEAR;
			(*notItr)->life = 6;
			(*notItr)->isActive = false;
			(*notItr)->modelHandle = MV1DuplicateModel(modelHandle);

			MV1SetDifColorScale((*notItr)->modelHandle, GetColorF(0.f, 0.f, 0.f, 1.0f));

			//if (SceneMenu::GetPlayer() == "character/original/Ruby_Gun/Ruby.pmx") { MV1SetScale((*notItr)->modelHandle, VGet(1, 1, 1)); }
			//else { MV1SetScale((*notItr)->modelHandle, VGet(1, 1, 1)); }


			// ポジション更新
			MV1SetPosition((*notItr)->modelHandle, (*notItr)->pos);
		}
	}

	// 
	bukketNumber = _creater;
	bulletCount = 0;
}

// 弾の更新
void Shot::BulletShot(VECTOR _dir, VECTOR _pos)
{
	// 球数分回す
	if (!notBullet.empty())
	{
		for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
		{
			// 初期化
			(*notItr)->pos = VGet(_pos.x, _pos.y + 6, _pos.z);
			(*notItr)->dir = _dir;
			(*notItr)->life = 6;
		}
	}



	if (!bullet.empty())
	{
		// 弾が出ていれば
		for (itr = bullet.begin(); itr != bullet.end(); itr++)
		{
			// 弾の処理
			(*itr)->life -= 0.1f;

			// 弾のライフを減らす
			if ((*itr)->life < 0.0f)
			{
				notBullet.push_back(*itr);
				bullet.remove(*itr);
				break;
			}

			// ベロシティ
			velocity = VScale((*itr)->dir, 60.0f);

			// 移動更新
			(*itr)->pos = VAdd((*itr)->pos, velocity);

			// ポジション更新
			MV1SetPosition((*itr)->modelHandle, (*itr)->pos);

			// 回転更新
			MV1SetRotationXYZ((*itr)->modelHandle, _dir);
		}
	}
}

// 一発だけ出す
void Shot::OneBulletPlay()
{
	bulletCount = 0;
	//
	se->PlaySoundEffect();
	// 球数分回す
	if (!notBullet.empty())
	{
		//
		for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
		{
			bullet.push_back(*notItr);
			notBullet.remove(*notItr);
			break;
		}
	}
}

// 弾を続けて出す
void Shot::BulletPlay()
{
	// 弾の発射数
	bulletCount++;

	// 弾を連続で出す
	if(bulletCount % 6 == 0)
	{
		//
		se->PlaySoundEffect();
		// 球数分回す
		if (!notBullet.empty())
		{
			//
			for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
			{
				bullet.push_back(*notItr);
				notBullet.remove(*notItr);
				break;
			}
		}
	}
}

// 弾の表示
void Shot::Draw()
{
	// 描画
	if (!bullet.empty())
	{
		for (itr = bullet.begin(); itr != bullet.end(); itr++)
		{
			MV1DrawModel((*itr)->modelHandle);
		}
	}
}
