#pragma once
#include <array>
#include <string>

class Chunk
{
private://定数

	static inline const int kMaxWidth = 5;
	static inline const int kMaxHeight = 5;

private://メンバ変数


private:


public://メンバ関数
	std::array<std::array<int, kMaxWidth>, kMaxHeight> chunk_ ={};
	void LoadMapChipCsv(const std::string& filePath);


};

