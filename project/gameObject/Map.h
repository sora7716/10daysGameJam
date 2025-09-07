#pragma once
#include <vector>
#include "Vector2.h"
#include "Chunk.h"

enum class BlockType
{
	kBlank,
	kBlock,
};

class Map
{
public://定数

	static inline const int kBlockSize = 32;

private://メンバ変数

	Vector2 origin_ = {};
	std::vector<std::vector<int>>map_;

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mapSize">マップのサイズ</param>
	void Initialize(const Vector2Int& mapSize);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// セッター：map
	/// </summary>
	/// <param name="chunk">chunkの2次元配列</param>
	/// <param name="begin">マップの読み込み開始位置</param>
	void SetMap(const std::array<std::array<int, Chunk::kMaxWidth>, Chunk::kMaxHeight>& chunk, const Vector2Int& begin);

	/// <summary>
	/// セッター：mapの原点
	/// </summary>
	/// <param name="origin">原点</param>
	void SetOrigin(const Vector2& origin) { origin_ = origin; };

	/// <summary>
	/// 逆転」
	/// </summary>
	/// <param name="pos">読み込む位置</param>
	void Flip(const Vector2Int& pos);

	void Swap(Chunk* under,Chunk* top,const Vector2Int& pos);

};

