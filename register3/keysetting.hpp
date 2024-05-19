# pragma once
# include "Common.hpp"

//メイン
class keysetting : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	keysetting(const InitData& init);

	void update() override;

	void draw() const override;
	
private:
	bool isok(int32 kk);

	const Font dfont{ FontMethod::MSDF, 36 };
	const Font font{ FontMethod::MSDF,70, Typeface::Bold };

	int32 textoffsety = 100;
	int32 width = 400;

	const Texture icon{ 0xf3e5_icon, 40 };

	bool change1 = false, change2 = false, change3 = false, change4 = false;
	bool notok=false;

	tex_texbox keyenter;
	tex_texbox keyback;
	tex_texbox keycoopon;
	tex_texbox keykakutei;

	ubutton backb;

	Array<Input> keys;
};
