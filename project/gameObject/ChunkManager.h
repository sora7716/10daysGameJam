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

	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns>インスタンス</returns>
	static ChunkManager* GetInstance();

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// Chunk読み込み
	/// </summary>
	/// <param name="filename">ファイル名(拡張子無し)</param>
	void LoadChunk(const std::string& filename);

	/// <summary>
	/// Chunkの検索
	/// </summary>
	/// <param name="filename">検索するファイル名(拡張子無し)</param>
	/// <returns></returns>
	Chunk* FindChunk(const std::string& filename);

};

