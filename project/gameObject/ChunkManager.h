#pragma once
#include "Chunk.h"
#include <map>
#include <memory>
#include <string>

class ChunkManager
{
private://メンバ変数

	std::map<std::string, std::unique_ptr<Chunk>>chunks_;

private://静的メンバ変数

	static inline ChunkManager* instance = nullptr;

private://メンバ関数

	ChunkManager() = default;
	~ChunkManager() = default;

	ChunkManager(const ChunkManager&) = delete;

	ChunkManager operator= (const ChunkManager&) = delete;
	

public://メンバ関数

	static ChunkManager* GetInstance();

	void Finalize();

	void LoadChunk(const std::string& filename);

	Chunk* FindChunk(const std::string& filename);

};

