#pragma once
#include "Chunk.h"
#include <map>
#include <memory>
#include <string>

class ChunkManager
{
private://メンバ変数

	//チャンクのクラスの連想配列
	std::map<std::string, std::unique_ptr<Chunk>>chunks_;

private://静的メンバ変数

	//インスタンス
	static inline ChunkManager* instance = nullptr;

private://メンバ関数

	//コンストラクタを封印
	ChunkManager() = default;
	
	//デストラクタの封印
	~ChunkManager() = default;

	//コピーコンストラクタの禁止
	ChunkManager(const ChunkManager&) = delete;

	//代入演算子の禁止
	ChunkManager operator= (const ChunkManager&) = delete;
	
public://メンバ関数

	/// <summary>
	///　インスタスのゲッター
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

