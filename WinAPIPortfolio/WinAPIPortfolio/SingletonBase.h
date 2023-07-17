#pragma once
template <class T>
class SingletonBase
{
protected:
	//�̱��� �ν��Ͻ�
	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* getSingleton(void);	//�̱��� ��������
	void releaseSingleton(void);	//�̱��� �޸𸮿��� ����
};

//�̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::singleton = 0;

//�̱��� ��������
template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� �޸𸮿��� ����
template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete(singleton);
		singleton = 0;
	}
}

