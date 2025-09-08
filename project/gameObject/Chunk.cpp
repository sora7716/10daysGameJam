#include "Chunk.h"
#include <fstream>
#include <sstream>
#include <cassert>

//初期化
void Chunk::Initialize(const std::string& filePath, int textureHandle)
{
	//csvファイルの読み込み
	LoadChunkCsv(filePath);
	//テクスチャハンドルを受け取る
	textureHandle_ = textureHandle;
}

//CSV読み込み
void Chunk::LoadChunkCsv(const std::string& filePath)
{
	std::ifstream file;

	file.open(filePath);

	assert(file.is_open());

	std::stringstream mapChipCsv;

	mapChipCsv << file.rdbuf();

	file.close();

	for (uint32_t y = 0; y < kMaxHeight; y++)
	{
		std::string line;

		std::getline(mapChipCsv, line);

		std::istringstream line_stream(line);

		for (uint32_t x = 0; x < kMaxWidth; x++)
		{
			std::string word;

			std::getline(line_stream, word, ',');

			if (!word.empty())
			{
				int number = std::stoi(word);
				chunk_[y][x] = number;
			}
		}
	}
}
