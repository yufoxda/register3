# pragma once
# include "Common.hpp"

//メイン
class pricesetting : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	pricesetting(const InitData& init);

	void update() override;

	void draw() const override;

private:

	int32 inputnum();
	void resetinput();
	String inputtext;
	int32 returnnum;

	const Font dfont{ FontMethod::MSDF, 36 };
	const Font font{ FontMethod::MSDF,70, Typeface::Bold };
	int32 textoffsety = 200;

	bool change1 = false, change2 = false, change3 = false, change4 = false, change5 = false;
	const Texture icon{ 0xf3e5_icon, 40 };


	tex_texbox set1;
	tex_texbox set3;
	ubutton backb;

	int32 inp = 0;

};
