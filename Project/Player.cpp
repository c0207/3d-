#include "Player.h"

/**
 * �R���X�g���N�^
 */
CPlayer::CPlayer() :
	m_Mesh(),
	m_Pos(0.0f, 0.0f, 0.0f),
	m_RotZ(0.0f) {
}

/**
 * �f�X�g���N�^
 */
CPlayer::~CPlayer() {
}

/**
 * �ǂݍ���
 */
bool CPlayer::Load(void) {
	// ���b�V���̓ǂݍ���
	if (!m_Mesh.Load("player.mom"))
	{
		return false;
	}
	return true;
}

/**
 * ������
 */
void CPlayer::Initialize(void) {
	m_Pos = Vector3(0.0f, 0.0f, -FIELD_HALF_Z + 2.0f);
	m_RotZ = 0;
}

/**
 * �X�V
 */
void CPlayer::Update(void) {
	//��]����
	float Roll = 0;
	//�L�[�{�[�h�ł̈ړ�
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Pos.x = max(m_Pos.x - PLAYER_SPEED, -FIELD_HALF_X);
		Roll -= MOF_MATH_PI;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_Pos.x = max(m_Pos.x + PLAYER_SPEED, -FIELD_HALF_X);
		Roll += MOF_MATH_PI;
	}
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Pos.z = max(m_Pos.z + PLAYER_SPEED, -FIELD_HALF_Z);

	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_Pos.z = max(m_Pos.z - PLAYER_SPEED, -FIELD_HALF_Z);

	}
	//��]
	float RotSpeed = MOF_ToRadian(10);
	if (Roll == 0)
	{
		RotSpeed = min(ads(m_RotZ) * 0.1f, RotSpeed);
	}
	if (ads(m_RotZ)) <= RotSpeed || signbit(m_RotZ) != signbit(Roll))
	{
		m_RotZ += Roll;
	}
	m_ROtZ -= copysignf(min(RotSpeed, abs(m_RotZ)), m_RotZ);

}

/**
 * �`��
 */
void CPlayer::Render(void){
	//���[���h�s��쐬
	CMatrix44 matworld; 
	matworld.RotationZ(m_RotZ);    //��]�s������߂�
	matworld.SetTranslation(m_Pos);    //�쐬������]�s��̈ړ������ɍ��W���Z�b�g
}

/**
 * �f�o�b�O�����`��
 */
void CPlayer::RenderDebugText(void){
	// �ʒu�̕`��
	CGraphicsUtilities::RenderString(10,40,MOF_XRGB(0,0,0),
			"�v���C���[�ʒu X : %.1f , Y : %.1f , Z : %.1f",m_Pos.x,m_Pos.y,m_Pos.z);
}

/**
 * ���
 */
void CPlayer::Release(void){
	m_Mesh.Release();
}