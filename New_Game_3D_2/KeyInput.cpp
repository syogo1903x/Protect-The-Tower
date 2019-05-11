#include "KeyInput.h"

KeyInput::KeyInput()
{

}

KeyInput::~KeyInput()
{

}

void KeyInput::Init_Key()
{
    int i, j;

    for(i = 0; i < 2; i++)
    {
        for (j = 0; j < 256; j++)
        {
            keyState[i][j] = 0;
            key[j] = KEY_OFF;
        }
    }
    nowKey = 0; prevKey = 1;

}

void KeyInput::Update_Key()
{
    // ���݂̃L�[�ƈ�O�̃t���[���̃L�[��Ԃ����ւ���
    nowKey ^= 1;
    prevKey = nowKey ^ 1;

    // �L�[��Ԏ擾
    GetHitKeyStateAll(keyState[nowKey]);

    //
    for (int i = 0; i < 256; i++)
    {
        char nowInput = keyState[nowKey][i];
        char prevInput = keyState[prevKey][i];

        if (nowInput)
        {
            //���݉�����Ă���

            //�O�̃t���[����������Ă����H
            if (prevInput)
            {
                key[i] = KEY_PRESSED; // ��������ςȂ�
            }
            else {
                key[i] = KEY_ON;// �������ꂽ
            }

        }
        else
        {
            // ���݃L�[�͉�����Ă��Ȃ�

            // �O�̃t���[���ŉ�����Ă����H
            if (prevInput)
            {
                key[i] = KEY_RELEASE;
            }
            else {
                key[i] = KEY_OFF;
            }
        }
    }
}



KEY_STATE KeyInput::GetKey(unsigned char _keyCode)
{
    return key[_keyCode];
}

