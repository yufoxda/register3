# pragma once
# include <Siv3D.hpp>
# include "userbutton.hpp"


/*
icon tex
or
tex texbox(tex)
*/


/*
Vec2(y,interval)

rightcenter(half-intarval-ZZ



*/
class icontex:ubutton
{
private:
	String tex;
	int32 centerofs = 50;
	const Font font{ FontMethod::MSDF,70, Typeface::Bold };
public:
	Rect area;

	icontex(String intex, const Texture& icontex,int32 y):ubutton(Vec2(960-25,y), icontex,false)
	{
		tex = intex;
		area = Rect{ Arg::leftCenter=Vec2(960 + centerofs / 2,y ).asPoint(),int32(font(tex).region().bottom().length()),font.height()};
	}
	bool iscliced()
	{
		return (area.leftClicked() or ubutton::area.leftClicked());
	}
	void icon_texdraw()const
	{
		ubutton::buttonDraw();
		area.rounded(10).draw(ColorF{ 1 });
		font(tex).drawAt(area.center(), ColorF{ 0 });
	}
	void activedraw()
	{
		area.rounded(10).drawFrame(5, ColorF{ 1,0,0 });
	}

	void updatetex(String intex)
	{
		tex = intex;
	}
};

class tex_texbox
{
public:
	Rect area;
	String nowkeyname;
	tex_texbox(String intex, String keyname,Vec2 poss)
	{
		tex = intex;
		nowkeyname = keyname;
		pos = poss;
		area = Rect{ Arg::leftCenter(int32(pos.x + offset),int32(pos.y)),300,font.height() };
	}
	void text_texboxdraw()const
	{
		font(tex).draw(Arg::rightCenter(pos), ColorF{0});
		area.rounded(10).draw( ColorF{ 1 });
		font(nowkeyname).drawAt(area.center(), ColorF{ 0 });
	}
	bool iscliced()
	{
		return area.leftClicked();
	}
	void activedraw()const
	{
		area.rounded(10).drawFrame(5, ColorF{ 1,0,0 });
	}

	void nowkeyupdate(String intext)
	{
		nowkeyname = intext;
	}
private:

	String tex;
	int32 offset = 100;
	Vec2 pos;
	const Font font{ FontMethod::MSDF,70, Typeface::Bold };
};
