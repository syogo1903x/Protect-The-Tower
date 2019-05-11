#include "Animation.h"

// アニメーション変更
float AnimationChange(int _playAnim, int _animationNomber, int _modelHandle, int _animAttachIndex, float _totalTime)
{
	// モーション入れ込み
	_playAnim = _animationNomber;
	// 今までアタッチしていたアニメーションのデタッチ
	MV1DetachAnim(_modelHandle, _animAttachIndex);
	// ３Ｄモデルの PlayAnim 番目のアニメーションをアタッチする
	_animAttachIndex = MV1AttachAnim(_modelHandle, _playAnim, -1, FALSE);
	// アタッチしたアニメーションの総再生時間を取得する
	_totalTime = MV1GetAttachAnimTotalTime(_modelHandle, _animAttachIndex);

	return _totalTime;
}
