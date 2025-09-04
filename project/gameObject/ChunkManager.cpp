#include "ChunkManager.h"

ChunkManager* ChunkManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ChunkManager();
	}

	return instance;
}

void ChunkManager::Finalize()
{
	delete instance;
	instance = nullptr;
}

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

Chunk* ChunkManager::FindChunk(const std::string& filename)
{
	if (chunks_.contains(filename))
	{
		return chunks_.at(filename).get();
	}
	return nullptr;
}
