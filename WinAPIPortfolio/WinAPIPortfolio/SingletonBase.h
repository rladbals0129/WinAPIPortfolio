#pragma once
template <class T>
class SingletonBase
{
protected:
	//ΩÃ±€≈Ê ¿ŒΩ∫≈œΩ∫
	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* getSingleton(void);	//ΩÃ±€≈Ê ∞°¡Æø¿±‚
	void releaseSingleton(void);	//ΩÃ±€≈Ê ∏ﬁ∏∏Æø°º≠ «ÿ¡¶
};

//ΩÃ±€≈Ê √ ±‚»≠
template <typename T>
T* SingletonBase<T>::singleton = 0;

//ΩÃ±€≈Ê ∞°¡Æø¿±‚
template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

//ΩÃ±€≈Ê ∏ﬁ∏∏Æø°º≠ «ÿ¡¶
template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete(singleton);
		singleton = 0;
	}
}

