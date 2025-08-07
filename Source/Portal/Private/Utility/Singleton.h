#pragma once

template<class Class>
class Singleton
{
public:
	static Class& Get()
	{
		if (Instance == nullptr)
			Instance = new Class();
		return *Instance;
	}

	static void Destroy()
	{
		if (Instance != nullptr)
			delete Instance;
	}
	
private:
	static Class* Instance;
	
};

template<class Class>
Class* Singleton<Class>::Instance = nullptr;