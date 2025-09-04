#include "ChunkManager.h"

//インスタンスのゲッター
ChunkManager* ChunkManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ChunkManager();
	}

	return instance;
}

//終了
void ChunkManager::Finalize()
{
	delete instance;
	instance = nullptr;
}

//Chunk読み込み
void ChunkManager::LoadChunk(const std::string& filename)
{
	if (chunks_.contains(filename))
	{
		return;
	}

	std::unique_ptr<Chunk>chunk = std::make_unique<Chunk>();
	chunk->LoadChunkCsv("resource/" + filename +".csv");

	chunks_.insert(std::make_pair(filename, std::move(chunk)));
}

//Chunkの検索
Chunk* ChunkManager::FindChunk(const std::string& filename)
{
	if (chunks_.contains(filename))
	{
		return chunks_.at(filename).get();
	}
	return nullptr;
}
