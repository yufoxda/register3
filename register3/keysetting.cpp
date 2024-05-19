# pragma once
# include "keysetting.hpp"


keysetting::keysetting(const InitData& init)
	: IScene{ init },
	keyenter{U"進む・確定",getData().inputenter.name(),Vec2(835,200)},
	keyback{U"戻る",getData().inputback.name(),Vec2(835,keyenter.area.bottomY() + textoffsety)},
	keycoopon{U"クーポン",getData().inputcoo.name(),Vec2(835,keyback.area.bottomY() + textoffsety) },
	keykakutei{ U"最終確定",getData().inputkakutei.name(),Vec2(835,keycoopon.area.bottomY() + textoffsety) },
	backb{Vec2(100,50),icon}
{
	Scene::SetBackground(ColorF{ 0.8,0.8, 0.8 });
	conf.load(U"config.csv");
}

void keysetting ::update()
{
	if (keyenter.iscliced())
	{
		change1 = true;
		notok = false;
		change2 = false, change3 = false; change4 = false;
	}
	if (keyback.iscliced())
	{
		change2 = true; notok = false;
		change1 = false, change3 = false; change4 = false;
	}
	if (keycoopon.iscliced())
	{
		change3 = true; notok = false;
		change1 = false, change2 = false; change4 = false;
	}
	if (keykakutei.iscliced())
	{
		change4 = true; notok = false;
		change1 = false, change2 = false, change3 = false;
	}
	if (change1)
	{
		keys = Keyboard::GetAllInputs();
		if (!keys.isEmpty()  and isok(keys[0].code()))
		{
			getData().inputenter = keys[0];
			keyenter.nowkeyupdate(keys[0].name());
			conf[3][2] = Format(keys[0].code());
			change1 = false;
		}
	}
	else if (change2)
	{
		keys = Keyboard::GetAllInputs();
		if (!keys.isEmpty())
		{
			if (isok(keys[0].code()))
			{
				getData().inputback = keys[0];
				keyback.nowkeyupdate(keys[0].name());
				change2 = false;
			}
			
		}
	}
	else if (change3)
	{
		keys = Keyboard::GetAllInputs();
		if (!keys.isEmpty())
		{
			if (isok(keys[0].code()))
			{
				getData().inputcoo = keys[0];
					keycoopon.nowkeyupdate(keys[0].name());
					change3 = false;
			}
		}
	}
	else if (change4)
	{
		keys = Keyboard::GetAllInputs();
		if (!keys.isEmpty())
		{
			if (isok(keys[0].code()))
			{
				getData().inputkakutei = keys[0];
				keykakutei.nowkeyupdate(keys[0].name());
				change3 = false;
			}
		}
	}
	if (notok) font(U"割り当て済です").drawAt(960, 800, ColorF(1, 0, 0));
	if (backb.iscliced())
	{
		conf[3][2] = Format(getData().inputenter.code());
		conf[4][2] = Format(getData().inputback.code());
		conf[5][2] = Format(getData().inputcoo.code());
		conf[6][2] = Format(getData().inputkakutei.code());
		conf.save(U"config.csv");
		conf.load(U"config.csv");
		changeScene(State::mainscene, 0.2s);
	}
}


void keysetting::draw()const
{
	keyenter.text_texboxdraw();
	keyback.text_texboxdraw();
	keycoopon.text_texboxdraw();
	keykakutei.text_texboxdraw();
	if (change1)
	{
		keyenter.activedraw();
	}
	else if (change2)
	{
		keyback.activedraw();
	}
	else if (change3)
	{
		keycoopon.activedraw();
	}
	else if (change4)
	{
		keykakutei.activedraw();
	}

	backb.buttonDraw();
}

bool keysetting::isok(int32 kk)
{
	switch (kk)
	{
	case KeyNum0.code():
	case KeyNum1.code():
	case KeyNum2.code():
	case KeyNum3.code():
	case KeyNum4.code():
	case KeyNum5.code():
	case KeyNum6.code():
	case KeyNum7.code():
	case KeyNum8.code():
	case KeyNum9.code():
	case Key0.code():
	case Key1.code():
	case Key2.code():
	case Key3.code():
	case Key4.code():
	case Key5.code():
	case Key6.code():
	case Key7.code():
	case Key8.code():
	case Key9.code():
		notok = true;
		return false;
	default:
		if (getData().inputenter.code() == kk or getData().inputcoo.code() == kk or getData().inputback.code() == kk)
		{
			notok = true;
			return false;
		}
		return true;
	}
}
