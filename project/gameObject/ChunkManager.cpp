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
	//チャンクの連想配列の中に存在するか
	if (chunks_.contains(filename))
	{
		//存在していた場合は早期リターン
		return;
	}

	//チャンクを生成
	std::unique_ptr<Chunk>chunk = std::make_unique<Chunk>();
	//csvファイルの読み込み
	chunk->LoadChunkCsv("resource/" + filename + ".csv");

	//生成したチャンクを連想配列に挿入
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
