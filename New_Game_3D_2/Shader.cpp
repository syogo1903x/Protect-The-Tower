#include "Common.h"

Shader::Shader()
{
}

Shader::~Shader()
{

}

void Shader::Init()
{
	pixelShaderHandle = LoadVertexShader("VertexShader.vso");
	vertexShaderHandle = LoadVertexShader("PixelShader.pso");

	// �v���O���}�u���V�F�[�_�[���f���Q�D�O���g�p�ł��Ȃ��ꍇ�̓G���[��\�����ďI��
	if (GetValidShaderVersion() < 200)
	{
		// �G���[�\��
		DrawString(0, 0, "�v���O���}�u���V�F�[�_�[�Q�D�O���g�p�ł��Ȃ����̂悤�ł�", GetColor(255, 255, 255));

		// �L�[���͑҂�
		WaitKey();

		// �c�w���C�u�����̌�n��
		DxLib_End();
	}

	// ���f���̕`��ɃI���W�i���V�F�[�_�[���g�p����ݒ���n�m�ɂ���
	MV1SetUseOrigShader(TRUE);

	// �g�p���钸�_�V�F�[�_�[���Z�b�g
	SetUseVertexShader(vertexShaderHandle);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(pixelShaderHandle);

	// �W�����C�g���I�t�ɂ���
	SetLightEnable(FALSE);

	// �f�B���N�V���i�����C�g���쐬����
	directionalLightHandle = CreateDirLightHandle(VGet(-1.0f, -1.0f, 0.0f));

	// �|�C���g���C�g�n���h�����쐬����
	pointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 1000.0f, 0.86f, 0.0000f, 0.0000f);

	// �X�|�b�g���C�g���쐬����
	spotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 1000.0f, 0.391586f, 0.001662f, 0.0f);

	// �X�|�b�g���C�g�̃A���r�G���g�J���[�𖳌��ɂ���
	SetLightAmbColorHandle(spotLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// �X�|�b�g���C�g�̃f�B�t���[�Y�J���[��΂ɂ���
	SetLightDifColorHandle(spotLightHandle, GetColorF(0.0f, 1.0f, 0.0f, 0.0f));

	lightAngle = 0;

}


void Shader::Update()
{

}

void Shader::Release()
{
	// �f�B���N�V���i�����C�g�̍폜
	DeleteLightHandle(directionalLightHandle);


	// �ǂݍ��񂾒��_�V�F�[�_�[�̍폜
	DeleteShader(vertexShaderHandle);

	// �ǂݍ��񂾃s�N�Z���V�F�[�_�[�̍폜
	DeleteShader(pixelShaderHandle);
}
