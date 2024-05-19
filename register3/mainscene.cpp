# pragma once
# include "mainScene.hpp"


mainscene::mainscene(const InitData& init)
	: IScene{ init },
	menub{ Vec2(50,50),smicon},
	backb{Vec2(100,50),bkicon},
	priceb{ U"価格設定" ,psicon,300 },
	expb{ U"履歴エクスポート",epicon,450 },
	keyb{U"キーコンフィグ",ksicon, 600}
{
	Scene::SetBackground(ColorF{ 0.8,0.8, 0.8 });
	Window::SetFullscreen(true);
	Scene::SetResizeMode(ResizeMode::Keep);
	Scene::Resize(1920, 1080);

	if (num < 1)
	{
		inithistory();
		initconfig();
		if(!isPoworOn)num++;
	}
	isPoworOn = true;
}

void mainscene::update()
{
	if (menub.iscliced())setting = true;

	if (getData().inputback.down())
	{
		if (faseflag == 1)
		{
			if (!coo)
			{
				num1 = 0, num3 = 0;
				count = 0;
				sum = 0;
				count = 0;
				pay = 0;
				payback = 0;
				faseflag = 0;
				coo = false;
				pon = 0;
				ponerror = false;
				iszero = false;
				iszero2 = false;
			}
			else
			{
				pon = 0;
				coo = false;
			}
			
		}
		else if (faseflag == 3)
		{
			pay = 0;
			payback = 0;
		}
		else if (faseflag == 2)
		{
			coo = false;
			iszero2 = false;
			pon = 0;
			sum = num1 * getData().set1 + num3 * getData().set3 ;
			pay = 0;
			payback = 0;
		}
		else if (faseflag == 4)
		{
			kakunin = false;
		}
		returnnum = 0;
		inputtext = U"";
		faseflag = (faseflag - 1) < 0 ? 0 : faseflag - 1;
	}


	if (faseflag == 0)
	{
		count = inputnum();
		if (getData().inputenter.down())
		{
			if (count > 0)
			{
				num1 = 0;
				num3 = 0;
				num3 = count / 3;
				num1 = count  - num3 * 3;

				faseflag = nextfase(faseflag);
				iszero = false;
			}
			else
			{
				iszero = true;
			}
		}
		sum = num1 * getData().set1 + num3 * getData().set3;
	}
	else if (faseflag == 1)
	{
		if (!coo)
		{
			if (inputcoopon())
			{
				
				coo = true;
				//inoutcoopn内でpon変更
			}
			else if (getData().inputcoo.down())
			{
				pon = 1;
				coo = true;
			}
			if(KeyNum0.down()) faseflag = nextfase(faseflag);
		}
		else
		{
			if (getData().inputcoo.down() or Key0.down() or KeyNum0.down())
			{
				pon = 0;
				coo = false;
			}
		}
		if (pon * 3 > count and coo)
		{
			pon = 0;
			coo = false;
			ponerror = true;
		}
		if (getData().inputenter.down()) faseflag = nextfase(faseflag);
	}
	else if (faseflag == 2)
	{
		ponerror = false;
		pay = inputnum();
		if (getData().inputenter.down())
		{
			if (sum <= pay)
			{
				//ここでおつり計算
				payback =  pay - sum;
				iszero2 = false;
				faseflag = nextfase(faseflag);
			}
			else
			{
				iszero2 = true;
			}
		}
	}
	else if (faseflag == 3)
	{
		if (getData().inputenter.down())
		{
			kakunin = true;
			faseflag = nextfase(faseflag);
		}
	}
	else if (faseflag == 4)
	{
		if (getData().inputkakutei.down())
		{
			num1 = 0, num3 = 0;
			csv.writeRow(Format(num), DateTime::Now(), count, sum, pon, pay, payback);
			csv.save(U"history.csv");
			conf[7][0] = Format(num);
			num++;
			conf.save(U"config.csv");
			count = 0;
			sum = 0;
			count = 0;
			pay = 0;
			payback = 0;
			faseflag = 0;
			coo = false;
			pon = 0;
			ponerror = false;
			kakunin = false;
		}
	}
	

	if (setting)
	{
		if (backb.iscliced())
		{
			setting = false;
			settingerror = false;
		}
		if (priceb.iscliced())
		{
			if (faseflag == 0)
			{
				settingerror = false;

				changeScene(State::pricesetting, 0.1s);
			}
			else
			{
				settingerror = true;
			}
		}
		if (expb.iscliced())
		{
			if (faseflag == 0)
			{
				settingerror = false;
				path = Dialog::SaveFile({ FileFilter::CSV() });
				if (path == none)
				{
					csv.save(U"history.csv");
				}
				else
				{
					csv.save(*path);
				}
				//changeScene(U"expotdata", 0.1s);
			}
			else
			{
				settingerror = true;
			}
		}

		if (keyb.iscliced())
		{
			if (faseflag == 0)
			{
				settingerror = false;
				changeScene(State::keysetting, 0.1s);
			}
			else
			{
				settingerror = true;
			}
		}
	}
}

void mainscene::draw() const
{
	//ヘッダー
	Rect{ 0,0,1920, 100 }.draw(ColorF{ 1,1,1 });
	menub.buttonDraw();
	RectF{ Arg::center(menub.area.centerX(),menub.area.centerY()),menub.area.top().length() + 8,menub.area.right().length() + 8 }.rounded(5).drawFrame(3, ColorF{0});

	dfont(Format(DateTime::Now())).drawAt(50, Vec2{ 960, 50 }, ColorF{ 0, 0, 0 });
	dfont(U"会計番号:{}"_fmt(num)).draw(55, Arg::rightCenter = Vec2{ 1870, 50 }, ColorF{ 0, 0, 0 });

	//左
	hyorect.rounded(10).draw(ColorF{ 0.9,0.9,0.9 });
	dfont(U"品目").draw(Arg::topCenter=Vec2{ hyorect.top().length()/6 + hyorect.leftX() ,hyorect.topY() + hyoofs}, ColorF{0, 0, 0});										dfont(U"単価").draw( Arg::topCenter = Vec2{hyorect.centerX() ,hyorect.topY() + hyoofs}, ColorF{0, 0, 0});																				dfont(U"個数").draw( Arg::topCenter = Vec2{  hyorect.rightX()-hyorect.top().length() / 6 , hyorect.topY() + hyoofs}, ColorF{0, 0, 0});
	RectF{ 100,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 1.5 ,960 - 200,5 }.rounded(5).draw(ColorF{ 0.5 });
	dfont(U"単品").draw(Arg::topCenter = Vec2{ hyorect.top().length() / 6 + hyorect.leftX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 2 }, ColorF{ 0, 0, 0 });							dfont(U"￥{}"_fmt(getData().set1)).draw(Arg::topCenter = Vec2{ hyorect.centerX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 2 }, ColorF{ 0, 0, 0 });				dfont(U"x{}"_fmt(num1)).draw(Arg::topCenter = Vec2{ hyorect.rightX() - hyorect.top().length() / 6 , hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 2 }, ColorF{ 0, 0, 0 });
	dfont(U"3個セット").draw(Arg::topCenter = Vec2{ hyorect.top().length() / 6 + hyorect.leftX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 3 }, ColorF{ 0, 0, 0 });				dfont(U"￥{}"_fmt(getData().set3)).draw(Arg::topCenter = Vec2{ hyorect.centerX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 3 }, ColorF{ 0, 0, 0 });				dfont(U"x{}"_fmt(num3)).draw(Arg::topCenter = Vec2{ hyorect.rightX() - hyorect.top().length() / 6 , hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 3}, ColorF{ 0, 0, 0 });
	dfont(U"クーポン").draw(Arg::topCenter = Vec2{ hyorect.top().length() / 6 + hyorect.leftX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 4 }, ColorF{ 0, 0, 0 });																																															dfont(U"+{}"_fmt(pon)).draw(Arg::topCenter = Vec2{ hyorect.rightX() - hyorect.top().length() / 6 , hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 4 }, ColorF{ 0, 0, 0 });
	RectF{ 100,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 5.5 ,960 - 200,5 }.rounded(5).draw(ColorF{ 0.5 });
	font(U"提供個数").draw(Arg::center = Vec2{ hyorect.top().length() / 4 + hyorect.leftX() , syuryo.centerY() }, ColorF{ 0, 0, 0 });																																												font(U"{}個"_fmt(pon+count)).draw(Arg::center = Vec2{ hyorect.rightX() - hyorect.top().length() / 4 , syuryo.centerY() }, ColorF{ 0, 0, 0 });
	//dfont(U"          内クーポン").draw(Arg::topCenter = Vec2{ hyorect.top().length() / 6 + hyorect.leftX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoofs2) * 7 + hyoy }, ColorF{ 0, 0, 0 });																																									dfont(U"x{}"_fmt(pon)).draw(Arg::topCenter = Vec2{ hyorect.rightX() - hyoofs, hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 7 }, ColorF{ 0, 0, 0 });
	dfont(U"小計").draw(Arg::topCenter = Vec2{ hyorect.top().length() / 4 + hyorect.leftX() ,hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 6 }, ColorF{ 0, 0, 0 });																																																					dfont(U"￥{}"_fmt(sum)).draw(Arg::topCenter = Vec2{ hyorect.rightX() - hyorect.top().length() / 4 , hyorect.topY() + hyoofs + (dfont.ascender() + hyoy) * 6 }, ColorF{ 0, 0, 0 });

	howkey.rounded(10).draw(ColorF{ 0.9,0.9,0.9 });
	font(U"進む・確定:"+getData().inputenter.name()).drawAt(30, howkey.centerX(), howkey.topY() + howkey.left().length() / 4, ColorF{0});
	font(U"    戻る          :"+getData().inputback.name()).drawAt(30, howkey.centerX(), howkey.topY() + 2 * howkey.left().length() / 4, ColorF{0});
	font(U" クーポン    :"+getData().inputcoo.name()).drawAt(30, howkey.centerX(), howkey.topY() + 3 * howkey.left().length() / 4, ColorF{0});

	//右
	kosuu.rounded(20).draw(ColorF{ 1,1,1 });
	//font(U"注文個数").drawAt(40, Vec2{ kosuu.centerX() - 200,kosuu.centerY() }, ColorF{0 });
	font(U"クーポンなし").draw(40, Arg::topCenter = Vec2{ font(U"注文個数").drawAt(60,Vec2{ kosuu.centerX() - 200,kosuu.centerY()-30 }, ColorF{0 }).bottomCenter()}, ColorF{0, 0, 0});
	font(U"{}"_fmt(count)).draw(80, Arg::center = Vec2{ kosuu.centerX() +200,kosuu.centerY() }, ColorF{ 0, 0, 0 });

	cooponarea.rounded(20).draw(coo ? ColorF{ 0.1, 0.1, 0.6 } : ColorF{ 0.9, 0.9, 0.9 });
	font(U"クーポン利用").drawAt(60, Vec2(cooponarea.center()), coo ? ColorF{ 1 } : ColorF{0});
	
	goukeiran.rounded(10).draw(ColorF{ 1,1,1 });
	font(U"合計").draw(40, Vec2{ goukeiran.leftX() + 50,goukeiran.topY() + 30 }, ColorF{ 0, 0, 0 });
	font(U"お預かり").draw(40, Vec2{ goukeiran.leftX() + 50,goukeiran.topY() + 30 + 50+30}, ColorF{ 0, 0, 0 });
	font(U"おつり").draw(50, Arg::bottomLeft = Vec2{ goukeiran.leftX() + 50,goukeiran.bottomY() -30 }, ColorF{ 0, 0, 0 });
	font(U"￥{}"_fmt(sum)).draw(50, Arg::topRight = Vec2{ goukeiran.rightX() - 50,goukeiran.topY() + 30 }, ColorF{ 0, 0, 0 });
	font(U"￥{}"_fmt(pay)).draw(50, Arg::topRight = Vec2{ goukeiran.rightX() - 50,goukeiran.topY() + 30 + 50 + 30 }, ColorF{ 0, 0, 0 });
	font(U"￥{}"_fmt(payback)).draw(80, Arg::bottomRight = Vec2{ goukeiran.rightX() - 50,goukeiran.bottomY() - 30 }, ColorF{ 0, 0, 0 });

	syuryo.rounded(30).draw(faseflag == 3 ? ColorF{ 1,0.9,0.4 } : ColorF{ 0.9	, 0.9, 0.9 });
	font(U"取引終了").drawAt(60, Vec2{ syuryo.center() }, ColorF{ 0,0,0 });

	//エラー表示
	if (iszero2)dfont(U"正しく入力").draw(50, Arg::topCenter = Vec2{ goukeiran.centerX(),goukeiran.topY() + 50 + 50 + 20 + 15 + 100 }, ColorF{ 1, 0, 0 });
	if (iszero) dfont(U"入力").draw(50, Arg::topCenter = Vec2{ Rect{ 985, 150,885, 150 }.centerX(),Rect{ 985, 150,885, 150 }.centerY() + 15 }, ColorF{ 0.9, 0.1, 0.1 });
	if (ponerror)dfont(U"3個以上で１枚です").drawAt(30, Vec2{cooponarea.centerX(),cooponarea.centerY() + 70}, ColorF{1, 0, 0});

	//入力欄表示
	if (faseflag == 0)
	{
		kosuu.rounded(20).drawFrame(5, ColorF{ 0.9,0.1,0.1 });
	}
	else if (faseflag == 1)
	{
		cooponarea.rounded(20).drawFrame(5, ColorF{ 0.9,0.1,0.1 });
	}
	else if (faseflag == 2)
	{
		Rect{ 985,goukeiran.topY() + 30 + 50 + 30, 885, 80 }.rounded(20).drawFrame(5, ColorF{ 0.9,0.1,0.1 });
	}
	else if (faseflag == 3)
	{
		syuryo.rounded(30).drawFrame(5, ColorF{ 1,0,0 });
	}

	//確認画面
	if (kakunin)
	{
		Rect{ 0,0,1920, 1080 }.draw(ColorF{ 0.7,0.7,0.7,0.9 });
		Rect{ Arg::center(1920 / 2,(1080 - 100) / 2),800,900 }.rounded(20).draw();
		font(U"おつり渡しましたか？").drawAt(960, 300, ColorF{ 1,0,0 });
		font(U"￥{}"_fmt(payback)).drawAt(960, (1080 - 100) / 2, ColorF{ 0 });
		font(getData().inputkakutei.name()+U"で次の会計に行きます").drawAt(40,1920 / 2, 700, ColorF{ 0 });
	}

	//セッティング画面
	if (setting)
	{
		Rect{ 0,0,1920, 1080 }.draw(ColorF{ 0.7,0.7,0.7,0.9 });
		backb.buttonDraw();
		priceb.icon_texdraw();
		expb.icon_texdraw();
		keyb.icon_texdraw();
		if (settingerror)font(U"未終了の会計があります").draw(30, Arg::center=Vec2(960, 700), ColorF{ 1, 0, 0 });
	}
}

int32 mainscene::nextfase(int32 fase)
{
	returnnum = 0;
	inputtext = U"";
	return fase + 1;
}

int32 mainscene::inputnum()
{
	inputtext = returnnum == 0 ? U"" : Format(returnnum);
	TextInput::UpdateText(inputtext);
	if (ParseOpt<int32>(inputtext) or inputtext.size() == 0)
	{
		returnnum = inputtext.size() == 0 ? 0 : Parse<int32>(inputtext);
	}
	return returnnum;
}

void mainscene::initconfig()
{
	if (not conf)
	{
		conf.writeRow(U"セット", U"価格");
		
		conf.writeRow(U"set1", 100);
		conf.writeRow(U"set3", 200);

		conf.writeRow(U"enter", U"InputDeviceType::Keyboard", KeyEnter.code());
		conf.writeRow(U"back", U"InputDeviceType::Keyboard", KeyNumDecimal.code());
		conf.writeRow(U"coo", U"InputDeviceType::Keyboard", KeyNumAdd.code());
		conf.writeRow(U"kakunin", U"InputDeviceType::Keyboard", KeyNumSubtract.code());
		conf.writeRow(Format(0));
		conf.save(U"config.csv");
	}
	else
	{
		getData().set1 = Parse<int32>(conf[1][1]);
		getData().set3 = Parse<int32>(conf[2][1]);
		getData().inputenter = Input(InputDeviceType::Keyboard, Parse<uint8>(conf[3][2]));
		getData().inputback = Input(InputDeviceType::Keyboard, Parse<uint8>(conf[4][2]));
		getData().inputcoo = Input(InputDeviceType::Keyboard, Parse<uint8>(conf[5][2]));
		getData().inputkakutei = Input(InputDeviceType::Keyboard, Parse<uint8>(conf[6][2]));
		num= Parse<int32>(conf[7][0]);
	}
}
void mainscene::inithistory()
{
	if (not csv)csv.writeRow(U"管理番号", U"日時", U"購入個数", U"合計金額", U"クーポン使用", U"預かり金", U"おつり", U"単価", U"3set");
	csv.writeRow(U"起動しました", U"", U"", U"", U"", U"", U"",getData().set1,getData().set3);
	csv.save(U"history.csv");
	csv.load(U"history.csv");
}

bool mainscene::inputcoopon()
{
	if (Key1.down()) { pon = 1; return true; }
	else if (KeyNum1.down()) { pon = 1; return true; }
	else if (Key2.down()) { pon = 2; return true; }
	else if (Key3.down()) { pon = 3; return true; }
	else if (Key4.down()) { pon = 4; return true; }
	else if (Key5.down()) { pon = 5; return true; }
	else if (Key6.down()) { pon = 6; return true; }
	else if (Key7.down()) { pon = 7; return true; }
	else if (Key8.down()) { pon = 8; return true; }
	else if (Key9.down()) { pon = 9; return true; }
	return false;
}
