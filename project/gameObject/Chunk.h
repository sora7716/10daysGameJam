#pragma once
#include <array>
#include <string>

class Chunk
{
public://定数

	//チャンクのサイズ
	static inline const int kMaxWidth = 5;
	static inline const int kMaxHeight = 5;

private://メンバ変数

	//チャンクの二次元配列
	std::array<std::array<int, kMaxWidth>, kMaxHeight> chunk_ = {};
	//テクスチャハンドル
	int textureHandle_ = -1;

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(const std::string& filePath, int textureHandle);

	/// <summary>
	/// ゲッター：chunk
	/// </summary>
	/// <returns>chunk</returns>
	std::array<std::array<int, kMaxWidth>, kMaxHeight>GetChunk()const { return chunk_; };

	/// <summary>
	/// テクスチャハンドルのセッター
	/// </summary>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void SetTextureHandle(int textureHandle) { textureHandle_ = textureHandle; };

	/// <summary>
	/// テクスチャハンドルのゲッター
	/// </summary>
	/// <returns>テクスチャハンドル</returns>
	int GetTextureHandle()const { return textureHandle_; };

private://メンバ関数

	/// <summary>
	/// CSV読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadChunkCsv(const std::string& filePath);

};

