// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float4 Position        : POSITION;     // ���W( ���[�J����� )
	float3 Tan             : TANGENT0;     // �ڐ�( ���[�J����� )
	float3 Bin             : BINORMAL0;    // �]�@��( ���[�J����� )
	float3 Normal          : NORMAL0;      // �@��( ���[�J����� )
	float4 Diffuse         : COLOR0;       // �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1;       // �X�y�L�����J���[
	float4 TexCoords0      : TEXCOORD0;	// �e�N�X�`�����W
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 Position        : POSITION;     // ���W( �v���W�F�N�V������� )
	float2 TexCoords0      : TEXCOORD0;    // �e�N�X�`�����W
	float3 VPosition       : TEXCOORD1;    // ���W( �r���[��� )
	float3 VTan            : TEXCOORD2;    // �ڐ�( �r���[��� )
	float3 VBin            : TEXCOORD3;    // �]�@��( �r���[��� )
	float3 VNormal         : TEXCOORD4;    // �@��( �r���[��� )
};



// C++ ���Őݒ肷��萔�̒�`
float4              cfProjectionMatrix[4]   : register(c2);		// �r���[�@�@���@�ˉe�s��
float4              cfViewMatrix[3]         : register(c6);		// ���[���h�@���@�r���[�s��
float4              cfTextureMatrix[3][2] : register(c88);		// �e�N�X�`�����W����p�s��
float4              cfLocalWorldMatrix[3]   : register(c94);		// ���[�J���@���@���[���h�s��


																	// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;
	float4 lWorldPosition;
	float4 lViewPosition;
	float3 lWorldNrm;
	float3 lWorldTan;
	float3 lWorldBin;
	float3 lViewNrm;
	float3 lViewTan;
	float3 lViewBin;


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���[�J�����W�����[���h���W�ɕϊ�
	lWorldPosition.x = dot(VSInput.Position, cfLocalWorldMatrix[0]);
	lWorldPosition.y = dot(VSInput.Position, cfLocalWorldMatrix[1]);
	lWorldPosition.z = dot(VSInput.Position, cfLocalWorldMatrix[2]);
	lWorldPosition.w = 1.0f;

	// ���[���h���W���r���[���W�ɕϊ�
	lViewPosition.x = dot(lWorldPosition, cfViewMatrix[0]);
	lViewPosition.y = dot(lWorldPosition, cfViewMatrix[1]);
	lViewPosition.z = dot(lWorldPosition, cfViewMatrix[2]);
	lViewPosition.w = 1.0f;

	// �r���[���W���ˉe���W�ɕϊ�
	VSOutput.Position.x = dot(lViewPosition, cfProjectionMatrix[0]);
	VSOutput.Position.y = dot(lViewPosition, cfProjectionMatrix[1]);
	VSOutput.Position.z = dot(lViewPosition, cfProjectionMatrix[2]);
	VSOutput.Position.w = dot(lViewPosition, cfProjectionMatrix[3]);

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )




	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �J�n )

	// �]�@���A�ڐ��A�@�����r���[�x�N�g���ɕϊ�
	lWorldTan.x = dot(VSInput.Tan, cfLocalWorldMatrix[0].xyz);
	lWorldTan.y = dot(VSInput.Tan, cfLocalWorldMatrix[1].xyz);
	lWorldTan.z = dot(VSInput.Tan, cfLocalWorldMatrix[2].xyz);

	lWorldBin.x = dot(VSInput.Bin, cfLocalWorldMatrix[0].xyz);
	lWorldBin.y = dot(VSInput.Bin, cfLocalWorldMatrix[1].xyz);
	lWorldBin.z = dot(VSInput.Bin, cfLocalWorldMatrix[2].xyz);

	lWorldNrm.x = dot(VSInput.Normal, cfLocalWorldMatrix[0].xyz);
	lWorldNrm.y = dot(VSInput.Normal, cfLocalWorldMatrix[1].xyz);
	lWorldNrm.z = dot(VSInput.Normal, cfLocalWorldMatrix[2].xyz);

	lViewTan.x = dot(lWorldTan, cfViewMatrix[0].xyz);
	lViewTan.y = dot(lWorldTan, cfViewMatrix[1].xyz);
	lViewTan.z = dot(lWorldTan, cfViewMatrix[2].xyz);

	lViewBin.x = dot(lWorldBin, cfViewMatrix[0].xyz);
	lViewBin.y = dot(lWorldBin, cfViewMatrix[1].xyz);
	lViewBin.z = dot(lWorldBin, cfViewMatrix[2].xyz);

	lViewNrm.x = dot(lWorldNrm, cfViewMatrix[0].xyz);
	lViewNrm.y = dot(lWorldNrm, cfViewMatrix[1].xyz);
	lViewNrm.z = dot(lWorldNrm, cfViewMatrix[2].xyz);

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �I�� )




	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// �e�N�X�`�����W�ϊ��s��ɂ��ϊ����s�������ʂ̃e�N�X�`�����W���Z�b�g
	VSOutput.TexCoords0.x = dot(VSInput.TexCoords0, cfTextureMatrix[0][0]);
	VSOutput.TexCoords0.y = dot(VSInput.TexCoords0, cfTextureMatrix[0][1]);

	// ���_���W��ۑ�
	VSOutput.VPosition = lViewPosition.xyz;

	// �ڐ���ۑ�
	VSOutput.VTan = lViewTan;

	// �]�@����ۑ�
	VSOutput.VBin = lViewBin;

	// �@����ۑ�
	VSOutput.VNormal = lViewNrm;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return VSOutput;
}