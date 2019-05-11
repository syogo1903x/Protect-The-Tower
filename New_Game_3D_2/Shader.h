#pragma once


class Shader
{
public:
	~Shader();

	static  Shader &ShaderInstance()
	{
		static Shader instance;
		return instance;
	}

	void Init();
	void Update();
	void Release();

private:
	Shader();

	int pixelShaderHandle;
	int vertexShaderHandle;

	int directionalLightHandle;
	int pointLightHandle;
	int spotLightHandle;

	int shaderScreen;
	float lightAngle;

	VECTOR directionalLightPos;
	VECTOR pointLightPos;
	VECTOR spotLightPos;
};

#define SHADER			Shader::ShaderInstance()