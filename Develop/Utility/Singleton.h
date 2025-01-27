#pragma once

template <class Type>
class Singleton
{
protected:
	Singleton() = default;

	// �R�s�[�K�[�h
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	// ~�R�s�[�K�[�h

protected:
	~Singleton() = default;

public:
	static Type* GetInstance()
	{
		static Type* instance = new Type();
		return instance;
	}
};
