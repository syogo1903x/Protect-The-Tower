#include "Animation.h"

// �A�j���[�V�����ύX
float AnimationChange(int _playAnim, int _animationNomber, int _modelHandle, int _animAttachIndex, float _totalTime)
{
	// ���[�V�������ꍞ��
	_playAnim = _animationNomber;
	// ���܂ŃA�^�b�`���Ă����A�j���[�V�����̃f�^�b�`
	MV1DetachAnim(_modelHandle, _animAttachIndex);
	// �R�c���f���� PlayAnim �Ԗڂ̃A�j���[�V�������A�^�b�`����
	_animAttachIndex = MV1AttachAnim(_modelHandle, _playAnim, -1, FALSE);
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	_totalTime = MV1GetAttachAnimTotalTime(_modelHandle, _animAttachIndex);

	return _totalTime;
}
