#pragma once
#include "SingletonBase.h"



class Player :public SingletonBase<Player>
{
private:
	enum STATE {
		IDLE, MOVE,
		JUMP, SLAP,
		DOWN, ATTACK,
		UPATTACK,DOWNATTACK
	};
	STATE _currentState;

	RECT _rc;
	//�÷��̾� ����
	int _speed;
	int _attack;

	//�ִϸ��̼� ��Ʈ��
	int _cnt;
	int _idx;
	bool _isLeft;

	int _eyes; //���ִϸ��̼�

	//�Ӹ� �ִϸ��̼�
	int _breathCnt;
	int _breath;
	bool _breathIn;
	// ����
	float _gravity;
	float _jumpPower;
	bool _isJumping;
	bool _isGravity;

	float _gravityJumpPower;

	//���� �����Ӱ��
	int _frame;
	int _jumpStartFrame;
	bool _jumpEnd;

	int _head;
	//�浹����
	bool _colRight;
	bool _colLeft;
	bool _colTop;
	bool _down;

	//Į ȹ��
	bool _knife;
	bool _txtKnife;
	bool _usingKnife;
	bool _panalKnife;

	//1����
	bool _txtCom;
	bool _colCom;
	//bool _panalCom;

	//���ݰ���
	RECT _rangeATK;
	bool _isATK;
	int _atkIdx;

	bool _isUpATK;
	int _atkUpIdx;

	bool _isDownATK;
	int _atkDownIdx;

	//�ϴ�����
	bool _downJump;
	bool _goDownJump;

public:	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void idle(void);
	void move(void);
	void jump(void);
	void down(void);
	void clap(void);
	void Attack(void);
	void AttackUP(void);
	void AttackDown(void);

	void titlePlayer(HDC hdc);

	inline STATE getState() { return _currentState; }
	inline RECT getPlayerPos() { return _rc; }

	inline RECT getATKRange() { return _rangeATK; }

	inline bool getIsJumping() { return _isJumping; }
	inline bool getColRight() { return _colRight; }

	inline float getColTop() { return _gravityJumpPower; }

	inline bool getKnife() { return _knife; }
	inline bool getTxtKnife() { return _txtKnife; }
	inline bool getUsingKnife() { return _usingKnife; }
	inline bool getPanalKnife() { return _panalKnife; }
	inline bool getTxtCom() { return _txtCom; }
	inline bool getDownJump() { return _downJump; }
	inline bool getGoDownjump() { return _goDownJump; }
	

	
	inline void setIdle() { _currentState = IDLE; }

	//inline void setATKRange(RECT rangeATK) { _rangeATK = rangeATK; }

	inline void setPlayerPosLeft(int x) { _rc.left += x; _rc.right += x; }
	inline void setPlayerPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	inline void setPlayerPosBottom(int y){ _rc.top -= y; _rc.bottom -= y; }
	inline void setPlayerPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	inline void setPlayerPos(RECT rc) { _rc = rc; }
	inline void setIsJumping(bool isJumping) { _isJumping = isJumping; }
	inline void setPlayerPos(int left, int top, int right, int bottom) { _rc.left = left; _rc.top = top; _rc.right = right; _rc.bottom = bottom; }
	inline void setIsGravity(bool isGravity) { _isGravity = isGravity; }
	inline void setColRight(bool colRight) { _colRight = colRight; }
	inline void setColLeft(bool colLeft) { _colLeft = colLeft; }
	inline void setColTop(bool colTop) { _colTop = colTop; }
	inline void setKnife(bool knife) { _knife = knife; }
	inline void setTxtKnife(bool txtKnife) { _txtKnife = txtKnife; }
	inline void setPanalKnife(bool panalKnife) { _panalKnife = panalKnife; }
	inline void setTxtCom(bool txtCom) { _txtCom = txtCom; }
	inline void setcolCom(bool colCom) { _colCom = colCom; }
	inline void setDownJump(bool downJump) { _downJump = downJump; }
	inline void setGoDownJump(bool goDoinJump) { _goDownJump = goDoinJump; }
	//void setPanalCom(bool panalCom) { _panalCom = panalCom; }
	
	


//	void savePosition();

	Player();
	~Player();
};
