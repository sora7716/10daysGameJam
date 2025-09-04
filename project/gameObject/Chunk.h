#pragma once
#include <array>
#include <string>

class Chunk
{
private://定数

	static inline const int kMaxWidth = 5;
	static inline const int kMaxHeight = 5;

private://メンバ変数

	std::array<std::array<int, kMaxWidth>, kMaxHeight> chunk_ ={};

public://メンバ関数

	/// <summary>
	/// CSV読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadChunkCsv(const std::string& filePath);

	/// <summary>
	/// chunkのゲッター
	/// </summary>
	/// <returns>chunk</returns>
	std::array<std::array<int, kMaxWidth>, kMaxHeight>GetChunk() { return chunk_; };

};

