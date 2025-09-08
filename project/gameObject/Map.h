#pragma once
#include <vector>
#include "gameObject/ResourceData.h"
#include "Chunk.h"

//描画用データ
struct MapDrawData 
{
	Vector2Int begin;
	int textureHandle;
};

//マップ
class Map
{
public://定数

	//ブロックサイズ
	static inline const int kBlockSize = 32;

	//マップの最大サイズ
	static inline const Vector2Int kMaxMapSize = { 41,23 };

private://メンバ変数

	//ブロックの向きを逆転するかのフラグ
	bool isReversal = false;

	//ブロックの向きを入れ替えるようのフラグ
	bool isReplacement = false;

	//マップ
	std::vector<std::vector<int>>map_;

	//テクスチャ
	std::vector<MapDrawData>mapDrawData_;

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
	/// <param name="chunk">chunkのクラス</param>
	/// <param name="begin">マップの読み込み開始位置</param>
	void SetMap(const Chunk* chunk, const Vector2Int& begin);

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
	void SwapChunk(Chunk* under, Chunk* top, const Vector2Int& underChunkPos);

	/// <summary>
	/// マップのゲッター
	/// </summary>
	/// <returns>map</returns>
	std::vector<std::vector<int>> GetMap() { return map_; };

};

