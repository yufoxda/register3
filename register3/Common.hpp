# pragma once
# include <Siv3D.hpp>
# include "texbox.hpp"

// シーンの名前
enum class State
{
	mainscene,
	pricesetting,
	keysetting,
};


//シーン間で共有するデータ
struct settingdata
{
	int32 set1 = 100;
	int32 set3 = 200;

	Input inputenter = KeyEnter;
	Input inputback = KeyNumDecimal;
	Input inputcoo = KeyNumAdd;
	Input inputkakutei = KeyNumSubtract;
};

using App = SceneManager<State, settingdata>;

static int32 num = 0;

static CSV csv{ U"history.csv" };

static CSV conf{ U"config.csv" };

static bool isPoworOn = false;
