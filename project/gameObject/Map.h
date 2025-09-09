#pragma once
#include <memory>
#include <vector>
#include <list>
#include "ResourceData.h"
#include "Chunk.h"
#include "GameSwitch.h"

//前方宣言
class Player;

//描画用データ
struct MapDrawData
{
	Vector2Int begin;
	int textureHandle;
};

//入れ替えようのスイッチに使うデータ
struct ChunkTransitionData
{
	GameSwitch* switchResource;
	Chunk* upperChunk;
	Chunk* underChunk;
	Vector2Int begin;
	bool isTransitionChunk;
};

//反転用のスイッチに使うデータ
struct ChunkInvertData 
{
	GameSwitch* switchResource;
	Vector2Int begin;
	bool isInvertChunk;
};

//線分
struct Segment 
{
	Vector2 origin;
	Vector2 diff;
};

//境界線

//マップ
class Map
{
public://定数

	//ブロックサイズ
	static inline const int kBlockSize = 32;

	//マップの最大サイズ
	static inline const Vector2Int kMaxMapSize = { 41,23 };

private://メンバ変数

	//マップ
	std::vector<std::vector<int>>map_;

	//テクスチャ
	std::vector<MapDrawData>mapDrawData_;

	//チャンクの切り替えスイッチのリスト
	std::list<ChunkTransitionData>chunkTransitionSwitchList_;

	//チャンクの反転スイッチのリスト
	std::list<ChunkInvertData>chunkInvertSwitchList_;

	//マウスの座標
	const Vector2Int* mousePos_ = {};

	//プレイヤー
	Player* player_ = nullptr;

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mousePos">マウスの座標</param>
	/// <param name="player">プレイヤー</param>
	void Initialize(const Vector2Int* mousePos,Player*player);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
    /// チャンク切り替えスイッチの生成
    /// </summary>
    /// <param name="upperChunk">上のチャンク</param>
    /// <param name="underChunk">下のチャンク</param>
    /// <param name="begin">読み込み開始位置</param>
	/// <param name="textureHandles">テクスチャハンドル達</param>
	void CreateChunkTransitionSwitch(Chunk* upperChunk, Chunk* underChunk, const Vector2Int& begin, int* textureHandles);

	/// <summary>
	/// チャンクの反転スイッチの生成
	/// </summary>
	/// <param name="chunk">チャンク</param>
	/// <param name="begin">読み込み開始位置</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void CreateChunkInvertSwitch(Chunk* chunk, const Vector2Int& begin, int textureHandle);

	/// <summary>
	/// チャンクの反転スイッチの初期化
	/// </summary>
	/// <param name="begin">読み込み開始位置</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void InitializeInvertSwitch(const Vector2Int& begin,int textureHandle);

	/// <summary>
    /// マップのゲッター
    /// </summary>
    /// <returns>map</returns>
	std::vector<std::vector<int>> GetMap() { return map_; };

private:

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
	void InvertChunk(const Vector2Int& pos);

	/// <summary>
	/// 切り替え
	/// </summary>
	/// <param name="under">下のチャンク</param>
	/// <param name="upper">上のチャンク</param>
	/// <param name="begin">開始位置(upperのorigin)</param>
	void SwapChunk(Chunk* under, Chunk* upper, const Vector2Int& begin);

};

