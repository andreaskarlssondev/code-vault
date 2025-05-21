#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include <assert.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

/*
	Usage:

	{className}.SaveSync<{classType/structType}>(L"Name", ObjectToSave);
	{className}.LoadSync<{classType/structType}>(L"Name", outObject);

*/


class File
{

	public:

		template<typename T>
		bool LoadSync(const wchar_t* aName, T& outObject);

		template<typename T>
		bool SaveSync(const wchar_t* aName, const T& aObjectToSave);
		
		void SetFilePath(std::string& aFilePath) { myFilePath = aFilePath; }
		std::string& GetFilePath() const { return myFilePath; }

	private:
		
		std::string myFilePath = L"/Saves";
};


template<typename T>
inline bool File::LoadSync(const wchar_t* aName, T& outObject)
{
	std::filesystem::path filePath(std::filesystem::current_path());
	filePath.concat(mySaveFolderPath);

	if (!std::filesystem::exists(filePath))
	{
		return false;
	}

	filePath.concat("/");
	filePath.concat(aName);

	std::ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&outSaveGame), sizeof(outSaveGame));
		file.close();

#ifdef _DEBUG
		std::cout << filePath << "| File Loaded " << std::endl;
#endif // _DEBUG

		return true;
	}
	else
	{
		assert(false && "FAILED TO CREATE FILE PATH");
	}

	return false;
}




template<typename T>
inline bool File::SaveSync(const wchar_t* aName, const T& aObjectToSave)
{

	std::filesystem::path filePath(std::filesystem::current_path());
	filePath.concat(mySaveFolderPath);

#ifdef _DEBUG
	std::cout << filePath << std::endl;
#endif // _DEBUG

	if (!std::filesystem::exists(filePath))
	{
		if (!std::filesystem::create_directories(filePath))
		{
			assert(false && "FAILED TO CREATE FILE PATH");
			return false;
		}
	}

	filePath.concat("/");
	filePath.concat(aName);

	std::ofstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.write(reinterpret_cast<const char*>(&aSaveGameObject), sizeof(aSaveGameObject));
		file.close();

#ifdef _DEBUG
		std::cout << filePath << "| File Saved " << std::endl;
#endif // _DEBUG

		return true;
	}
	else
	{
		assert(false && "FAILED TO CREATE FILE PATH");
	}

	return false;
}
