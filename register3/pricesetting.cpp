# pragma once
# include "pricesetting.hpp"

pricesetting::pricesetting(const InitData& init)
	: IScene{ init },
	set1{U"単品",Format(getData().set1),Vec2(900,300)},
	set3{U"３個セット",Format(getData().set3),Vec2(900,set1.area.bottomY()+textoffsety) },
	backb{Vec2(100,50),icon}
{
	Scene::SetBackground(ColorF{ 0.8,0.8, 0.8 });

}

void pricesetting::update()
{
	if (set1.iscliced())
	{
		change1 = true;
		change3 = false;
		resetinput();
	}
	if (set3.iscliced())
	{
		change3 = true;
		change1 = false;
		resetinput();
	}

	if (change1)
	{
		set1.activedraw();
		set1.nowkeyupdate(Format(inputnum()));
	}
	else if (change3)
	{
		set3.activedraw();
		set3.nowkeyupdate(Format(inputnum()));
	}

	if (backb.iscliced())
	{
		change1 = false; change3 = false;
		getData().set1 = Parse<int32>(set1.nowkeyname);
		getData().set3 = Parse<int32>(set3.nowkeyname);
		conf[1][1] = Format(getData().set1);
		conf[2][1] = Format(getData().set3);
		conf.save(U"config.csv");
		csv.writeRow(U"", U"", U"", U"", U"", U"", U"", getData().set1, getData().set3);
		csv.save(U"history.csv");
		resetinput();
		changeScene(State::mainscene, 0.1s);
	}
}

void pricesetting::draw()const
{
	set1.text_texboxdraw();
	set3.text_texboxdraw();
	backb.buttonDraw();
}

int32 pricesetting::inputnum()
{
	inputtext = returnnum == 0 ? U"" : Format(returnnum);
	TextInput::UpdateText(inputtext);
	if (ParseOpt<int32>(inputtext) or inputtext.size() == 0)
	{
		returnnum = inputtext.size() == 0 ? 0 : Parse<int32>(inputtext);
	}
	return returnnum;
}

void pricesetting::resetinput()
{
	inputtext = U"";
	returnnum = 0;
}
