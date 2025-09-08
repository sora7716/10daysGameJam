#pragma once
#include <vector>
#include "calc/Vector2.h"
#include "Chunk.h"

//ブロックタイプ
enum class BlockType
{
	kBlank,
	kBlock,
};

class Map
{
public://定数

	//ブロックサイズ
	static inline const int kBlockSize = 32;

	//マップの最大サイズ
	static inline const Vector2Int kMaxMapSize = { 40,23 };

private://メンバ変数

	//マップ
	std::vector<std::vector<int>>map_;

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// mapのセッター
	/// </summary>
	/// <param name="chunk">chunkの2次元配列</param>
	/// <param name="begin">マップの読み込み開始位置</param>
	void SetMap(const std::array<std::array<int, Chunk::kMaxWidth>, Chunk::kMaxHeight>& chunk, const Vector2Int& begin);

	/// <summary>
	/// 逆転
	/// </summary>
	/// <param name="pos">読み込む位置</param>
	void FlipChunk(const Vector2Int& pos);

	/// <summary>
	/// 切り替え
	/// </summary>
	/// <param name="under">下のチャンク</param>
	/// <param name="top">上のチャンク</param>
	/// <param name="underChunkPos">下のチャンクの位置</param>
	void SwapChunk(Chunk* under,Chunk* top,const Vector2Int& underChunkPos);

};

