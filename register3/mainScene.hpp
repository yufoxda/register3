# pragma once
# include "Common.hpp"

//メイン
class mainscene : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	mainscene(const InitData& init);

	void update() override;

	void draw() const override;

private:
	void initconfig();
	void inithistory();
	int32 nextfase(int32);
	int32 inputnum();
	bool inputcoopon();
	int32 returnnum=0;

	const Font dfont{ FontMethod::MSDF, 35 };
	const Font font{ FontMethod::MSDF,70, Typeface::Bold };

	bool coo = false;
	bool iszero = false;
	bool iszero2 = false;
	bool setting = false;
	bool kakunin = false;

	bool ponerror = false;
	bool settingerror = false;

	int32 hyoy = 25;
	int32 hyoofs = 50;
	int32 hyoofs2 = 5;

	int32 sioffset = 100;
	/*
	///////////外枠////////////////////////////////
	)hyoofts                            )hyoofs
	/	 文字文字文字文字文字文字文字文字文字文字文字文字
	/    文字文字文字文字文字文字文字文字文字文字文字文字
	/	 文字文字文字文字文字文字文字文字文字文字文字文字
	/　　)hyoy          )hyoy
	/	 文字文字文字文字文字文字文字文字文字文字文字文字
	/　　文字文字文字文字文字文字文字文字文字文字文字文字
	*/

	int32 faseflag = 0;
	int32 count = 0;
	int32 sum = 0;
	int32 pay = 0;
	int32 payback = 0;
	int32 pon = 0;


	int32 num1 = 0, num3 = 0;

	String inputtext;

	Rect hyorect{ 50, 350, 885, 680 };
	Rect howkey{ 50,150,885,150 };
	Rect kosuu{ 985, 150,885, 150 };

	Rect maisuu = Rect{ 985, 333,885, 397 };
	Rect cooponarea{ 985, 350,885, 100 };
	
	Rect goukeiran = Rect{ 985,500, 885, 330};
	Rect syuryo{ 985, 880,885, 150 };

	Rect iconarea; Rect iconarea2; Rect iconarea3; Rect iconarea4; Rect iconarea5;
	const Texture smicon{ 0xf0c9_icon, 50 };
	const Texture bkicon{ 0xf3e5_icon, 40 };
	const Texture epicon{ 0xf56e_icon, 80 };
	const Texture psicon{ 0xf013_icon, 80 };
	const Texture ksicon{ 0xf11c_icon, 80 };

	ubutton menub;
	ubutton backb;
	icontex expb;
	icontex priceb;
	icontex keyb;
	
	Optional<FilePath> path;
};
