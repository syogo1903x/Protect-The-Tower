#pragma once

enum HIT_CHECK
{
	WALL_RIGHT,
	WALL_LEFT,
	WALL_FRONT,
	WALL_BACK,
	WALL_UP
};

class Stage
{
public:
	~Stage();

	// �V���O���g��
	static Stage &StageInctance()
	{
		static Stage stageInstance;
		return stageInstance;
	}

	// ������
	void Init(char *_stage);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���
	void Release();

	// �Q�b�^�[
	bool GetFailur() { return isFailure; }
	const int &GetModel() const { return modelHandle; }

	// �Z�b�^�[
	static void SetDangerTrans(int i, float _set) { dangerModelTransmission[i] += _set; }
	void SetFailur(bool _set) { isFailure = _set; }

private:
	Stage();

	// �X�e�[�W���f��
	int modelHandle;
	// �X�J�C�h�[�����f��
	int skydomeModelHandle;
	float count;
	VECTOR pos;

	int dangerModelHandle[4];
	static float dangerModelTransmission[4];
	bool isFailure;
};

#define STAGE				Stage::StageInctance()