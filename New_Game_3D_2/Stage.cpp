#include "Common.h"

float Stage::dangerModelTransmission[4];

Stage::Stage()
{

}

Stage::~Stage()
{
	//Release();
}

void Stage::Init(char *_stage)
{
	isFailure = false;
	// �X�e�[�W�̐���
	modelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::GAMESTAGE));

	// �X�J�C�h�[���̓ǂݍ���
	skydomeModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::SKYDOOM));

	if (modelHandle < 0)
	{
		isFailure = true;
		// printfDx("�X�e�[�W���f���ǂݍ��݃G���[\n");
	}

	pos = VGet(0, 0, 0);

	// �X�e�[�W�ŃT�C�Y�̕ύX
	if (_stage == "stage/���ʘOver0.93/���ʘO.pmx") { MV1SetScale(modelHandle, VGet(2, 2, 2)); }
	if (_stage == "stage/���O�r�[�O���E���h1.05/���O�r�[�O���E���h�i�Ő��j.pmx") { MV1SetScale(modelHandle, VGet(1, 1, 1)); }
	if (_stage == "stage/���̓s���e���X�e�[�W/���̓s���e���X�e�[�W.pmx") { MV1SetScale(modelHandle, VGet(4, 2, 1)); }

	// �͈͊O�ɏo�Ȃ��悤�ɂ���ǂ̃��f��
	for (int i = 0; i < 4; i++)
	{
		dangerModelHandle[i] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::GAMESTAGE_OUT));
		MV1SetScale(dangerModelHandle[i], VGet(4.25f, 5, 6));
		dangerModelTransmission[i] = 0.0f;
	}

	// �ǃ��f���̈ʒu�ݒ�
	MV1SetPosition(dangerModelHandle[0], VGet(320, 0, 0));
	MV1SetRotationXYZ(dangerModelHandle[0], VGet(0, 1.57f, 0));
	MV1SetPosition(dangerModelHandle[1], VGet(0, 0, 260));
	MV1SetPosition(dangerModelHandle[2], VGet(-320, 0, 0));
	MV1SetRotationXYZ(dangerModelHandle[2], VGet(0, 1.57f, 0));
	MV1SetPosition(dangerModelHandle[3], VGet(0, 0, -430));

	MV1SetScale(skydomeModelHandle, VGet(2, 2, 2));
	count = 0;
}

// �X�V
void Stage::Update()
{
	// ��]
	count += 0.0005f;
	MV1SetRotationXYZ(skydomeModelHandle, VGet(0, count, 0));

	// �X�e�[�W�̈ʒu�ݒ�
	MV1SetPosition(modelHandle, pos);
	MV1SetPosition(skydomeModelHandle, pos);
}

// �`��
void Stage::Draw()
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(skydomeModelHandle);

	for (int i = 0; i < 4; i++)
	{
		if (dangerModelTransmission[i] > 1.0f) { dangerModelTransmission[i] = 1.0f; }
		if (dangerModelTransmission[i] < 0.0f) { dangerModelTransmission[i] = 0.0f; }

		MV1SetOpacityRate(dangerModelHandle[i], dangerModelTransmission[i]);
		MV1DrawModel(dangerModelHandle[i]);
	}
}

// ���
void Stage::Release()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(skydomeModelHandle);
	skydomeModelHandle = NULL;


	for (int i = 0; i < 4; i++)
	{
		MV1DeleteModel(dangerModelHandle[i]);
		dangerModelHandle[i] = NULL;
	}
}
