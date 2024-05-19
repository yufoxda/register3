# pragma once
# include <Siv3D.hpp>

class ubutton
{
	/*
	Arg::leftcenter


	*/
private:
	Vec2 pos;
	const Font dfont{ FontMethod::MSDF, 35 };
	const Font font{ FontMethod::MSDF,70, Typeface::Bold };
public:
	Rect area;
	Texture icon;
	ubutton(Vec2 position, const Texture& icontex)
	{
		icon = icontex;
		area = Rect{ Arg::leftCenter=position.asPoint(),icon.width(),icon.height()};
		pos = area.center();
	}
	ubutton(Vec2 position, const Texture& icontex,bool isback)
	{
		icon = icontex;
		if (isback)
		{
			area = Rect{ Arg::rightCenter(int32(1920 - position.x),int32(1080 - position.y)),icon.width(),icon.height() };
		}
		else
		{
			area = Rect{ Arg::rightCenter = position.asPoint(),icon.width(),icon.height() };
		}		
		pos = area.center();
	}
	void buttonDraw() const
	{
		icon.drawAt(pos, ColorF{ 0.25 });
	}
	bool iscliced()
	{
		return area.leftClicked();
	}
};
