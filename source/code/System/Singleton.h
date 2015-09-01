#pragma once

template<class T>
class Singleton
{
protected:
	Singleton() { _instance = static_cast<T*>(this); }
	virtual ~Singleton() { _instance = nullptr; }

public:
	static void Initialize() { new T; }
	static void Deinitialize() { delete _instance; }

	static T& GetInstance() { return *_instance; }
	static T* GetInstancePtr() { return _instance; }

private:
	static T* _instance;
};

template<class T> T* Singleton<T>::_instance = nullptr;