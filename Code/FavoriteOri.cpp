#include"FavoriteOri.h"
using namespace std;
Artifact* FavoriteOri::operator[](int i)
{
    return favorite[i];
}
void FavoriteOri::import(Artifact** Art, const int& amount)
{
    for (int i = 0; i < 5; i++)
    {
        favorite[i]=new Artifact();
        for (int j = 0; j < amount; j++)
        {
            if (Art[j]->Get_id() == f_id[i])
            {
				favorite[i] = Art[j];
				CRIT_score += Art[j]->Get_CRIT_score();
                if(favorite[i]->Get_MainAttribute()=="lifePercentage")
                {
                    Num[0]++;
                }
                if(favorite[i]->Get_MainAttribute()=="attackPercentage")
                {
                    Num[1]++;
                }
                if(favorite[i]->Get_MainAttribute()=="defendPercentage")
                {
                    Num[2]++;
                }
                if(favorite[i]->Get_MainAttribute()=="elementalMastery")
                {
                    Num[3]++;
                }
                if(favorite[i]->Get_MainAttribute()=="recharge")
                {
                    Num[4]++;
                }
                if(favorite[i]->Get_MainAttribute()=="critical")
                {
                    Num[5]++;
                }
                if(favorite[i]->Get_MainAttribute()=="criticalDamage")
                {
                    Num[6]++;
                }
				break;
			}
		}
	}
}
void FavoriteOri::confirm()
{
	this->append_total();
	this->judge_set();
	importState = 1;
}

void setFavorite(Artifact** Art, const int ArtAmount, FavoriteOri* f, int& f_size) //编辑（增加、修改）操作
{
//    // 以读写方式打开主目录下的json文件，若该文件不存在则会自动创建
//    QFile fileFav(QDir::currentPath() + "/favorite.json");
//    fileFav.open(QIODevice::ReadWrite);


    int choice, mod;
    string name;
//    cout << "f_size : " << f_size << endl<< endl;
//    cout << "【1】增加收藏组合\n【2】编辑收藏组合\n【0】返回并保存\n请输入对应操作序号" << endl;
//    while (cin >> choice) {
//        if (choice == 0)  //保存
//        {
//            Json::Value temp;
//            for (int i = 0; i < f_size; i++) {
//                f[i].id = i + 1;
//            }
//            for (int i = 0; i < f_size; i++) {
//                temp["name"] = f[i].getName();
//                temp["flower"] = f[i].f_id[0];
//                temp["feather"] = f[i].f_id[1];
//                temp["sand"] = f[i].f_id[2];
//                temp["cup"] = f[i].f_id[3];
//                temp["head"] = f[i].f_id[4];
//                temp["id"] = f[i].id;
//                root["favorite"].append(temp);
//            }
//            string s = writer.write(root);
//            ofstream found;
//            found.open("favorite.json", ios::out);   //写入操作
//            if (!found.is_open())
//            {
//                cout << "初始化失败" << endl;
//                return;
//            }
//            found.seekp(0, ios::beg);  //从头覆写
//            found << s;
//            found.close();

//            break;
//        }
//        else if (choice == 1) {
//            bool state[6] = {};  //各部位输入状态
//            bool State = 0; //总输入状态
//            int order = f_size + 1;
//            while (1) {
//                cout << "当前正在编辑组合序号/名称为： " << order;
//                if (!name.empty())
//                    cout << " / " << name;
//                cout << endl;
//                cout << "请输入编辑组合操作的序号：（输入0退出）" << endl;
//                if (!State) {
//                    cout << "【1】生之花" ;
//                    if (state[1])	cout << "*";
//                    cout << "    【2】死之羽";
//                    if (state[2])	cout << "*";
//                    cout << "    【3】时之沙";
//                    if (state[3])	cout << "*";
//                    cout << "    【4】空之杯";
//                    if (state[4])	cout << "*";
//                    cout << "    【5】理之冠";
//                    if (state[5])	cout << "*";
//                    cout << "    【6】更改组合名称";
//                    if (state[0])	cout << "*";
//                    cout << endl;

//                    cin >> mod;
//                    if (mod == 0) break;
//                    else if (mod == 1) {
//                        f[f_size].setFlower(Art, ArtAmount, state);
//                    }
//                    else if (mod == 2) {
//                        f[f_size].setFeather(Art, ArtAmount, state);
//                    }
//                    else if (mod == 3) {
//                        f[f_size].setSand(Art, ArtAmount, state);
//                    }
//                    else if (mod == 4) {
//                        f[f_size].setCup(Art, ArtAmount, state);
//                    }
//                    else if (mod == 5) {
//                        f[f_size].setHead(Art, ArtAmount, state);
//                    }
//                    else if (mod == 6) {
//                        f[f_size].setName();
//                        state[0] = 1;
//                    }
//                    else {
//                        cout << "无效指令！请重新输入：" << endl;
//                        continue;
//                    }
//                    if (state[1] && state[2] && state[3] && state[4] && state[5]) {
//                        State = 1;
//                    }
//                }
//                else {
//                    cout << "【1】生之花*    【2】死之羽*    【3】时之沙*    【4】空之杯*    【5】理之冠*    【6】更改组合名称    【7】确认" << endl;
//                    cin >> mod;
//                    if (mod == 0) break;
//                    else if (mod == 1) {
//                        f[f_size].setFlower(Art, ArtAmount, state);
//                    }
//                    else if (mod == 2) {
//                        f[f_size].setFeather(Art, ArtAmount, state);
//                    }
//                    else if (mod == 3) {
//                        f[f_size].setSand(Art, ArtAmount, state);
//                    }
//                    else if (mod == 4) {
//                        f[f_size].setCup(Art, ArtAmount, state);
//                    }
//                    else if (mod == 5) {
//                        f[f_size].setHead(Art, ArtAmount, state);
//                    }
//                    else if (mod == 6) {
//                        f[f_size].setName();
//                        state[0] = 1;
//                    }
//                    else if (mod == 6) {
//                        f[f_size].setName();
//                        state[0] = 1;
//                    }
//                    else if (mod == 7) {
//                        if (!state[0]) {
//                            f[f_size].setName(order);
//                        }
//                        f[f_size].confirm();
//                        ++f_size;
//                        cout << "已确认！" << endl;
//                        break;
//                    }
//                    else {
//                        cout << "无效指令！请重新输入：" << endl;
//                        continue;
//                    }
//                }
//            }
//        }
//        else if (choice == 2) {
//            int c;
//            while (1) {
//                system("cls");
//                Display_Fav(f, f_size);
//                cout << "请选择收藏序号: (输入0返回)" << endl;
//                cin >> c;
//                if (c == 0) {
//                    break;
//                }
//                else if (c < 0 || c > f_size) {
//                    cerr << "illegal input!" << endl;
//                    continue;
//                }
//                else {
//                    int ch;
//                    Favorite* temp = &f[c - 1];
//                    bool state[6] = {};
//                    while (1) {
//                        system("cls");
//                        DisplayAllArtifact(Art, ArtAmount);
//                        Display_Fav(temp, 1);
//                        cout << "请选择编辑操作：" << endl;
//                        cout << "【1】修改生之花";
//                        if (state[1])	cout << "*";
//                        cout << "    【2】修改死之羽";
//                        if (state[2])	cout << "*";
//                        cout << "    【3】修改时之沙";
//                        if (state[3])	cout << "*";
//                        cout << "    【4】修改空之杯";
//                        if (state[4])	cout << "*";
//                        cout << "\n【5】修改理之冠";
//                        if (state[5])	cout << "*";
//                        cout << "    【6】修改组合名称";
//                        if (state[0])	cout << "*";
//                        cout << "    【7】删除    【0】返回" << endl;
//                        //cout << "请选择编辑操作：【1】修改生之花	【2】修改死之羽	【3】修改时之沙	【4】修改空之杯	【5】修改理之冠	【6】修改名称		【7】删除	【0】返回" << endl;
//                        cin >> ch;
//                        if (ch == 0) break;
//                        else if (ch == 1) {
//                            temp->setFlower(Art, ArtAmount, state);
//                        }
//                        else if (ch == 2) {
//                            temp->setFeather(Art, ArtAmount, state);
//                        }
//                        else if (ch == 3) {
//                            temp->setSand(Art, ArtAmount, state);
//                        }
//                        else if (ch == 4) {
//                            temp->setCup(Art, ArtAmount, state);
//                        }
//                        else if (ch == 5) {
//                            temp->setHead(Art, ArtAmount, state);
//                        }
//                        else if (ch == 6) {
//                            temp->setName();
//                            state[0] = 1;
//                        }
//                        else if (ch == 7) {
//                            for (int i = c - 1; i < f_size; i++) {
//                                int j = i + 1;
//                                f[i] = f[j];
//                            }
//                            --f_size;
//                            for (int i = 0; i < f_size; i++) {
//                                f[i].id = i + 1;
//                            }
//                            break;
//                        }
//                        else {
//                            cout << "无效指令！请重新输入：" << endl;
//                            continue;
//                        }
//                    }
//                }
//            }
//        }
//        else {
//            cout << "无效输入，请重新输入:" << endl;
//            continue;
//        }
//        system("cls");
//        DisplayAllArtifact(Art, ArtAmount);
//        cout << "已确认（当前收藏数：" << f_size << "）" << endl;
//        cout << "【1】增加收藏组合\n【2】编辑收藏组合\n【0】返回并保存\n请输入对应操作序号" << endl;
//    }
}

void FavoriteOri::setFlower(Artifact** Art, int selectedNum)
{
//    cout << "请输入系统内生之花的序号：（输入0返回）" << endl;
//    while (cin >> n) {
//        if (n == 0)	return;
//        if (n > ArtAmount) {
//            cout << "序号不存在！请重新输入：" << endl;
//            continue;
//        }
//        if (!Art[n - 1]->confirm_position(1)) {
//            cout << "输入序号对应圣遗物不是生之花，请重新输入：" << endl;
//            continue;
//        }
//        else {
//            break;
//        }
//    }
    f_id[0] = Art[selectedNum]->Get_id();
    favorite[0] = Art[selectedNum];//浅复制，可能会有问题
//    stat[1] = 1;
}
void FavoriteOri::setFeather(Artifact** Art, int selectedNum)
{
//    int n;
//    cout << "请输入系统内死之羽的序号：（输入0返回）" << endl;
//    while (cin >> n) {
//        if (n == 0)	return;
//        if (n > ArtAmount) {
//            cout << "序号不存在！请重新输入：" << endl;
//            continue;
//        }
//        if (!Art[n - 1]->confirm_position(2)) {
//            cout << "输入序号对应圣遗物不是死之羽，请重新输入：" << endl;
//            continue;
//        }
//        else {
//            break;
//        }
//    }
    f_id[1] = Art[selectedNum]->Get_id();
    favorite[1] =Art[selectedNum];
//    state[2] = 1;
}
void FavoriteOri::setSand(Artifact** Art, int selectedNum)
{
//    int n;
//    cout << "请输入系统内时之沙的序号：（输入0返回）" << endl;
//    while (cin >> n) {
//        if (n == 0)	return;
//        if (n > ArtAmount) {
//            cout << "序号不存在！请重新输入：" << endl;
//            continue;
//        }
//        if (!Art[n - 1]->confirm_position(3)) {
//            cout << "输入序号对应圣遗物不是时之沙，请重新输入：" << endl;
//            continue;
//        }
//        else {
//            break;
//        }
//    }
    f_id[2] = Art[selectedNum]->Get_id();
    favorite[2] =Art[selectedNum];
    if(!sandTemp.isEmpty())
    {
        if(sandTemp=="lifePercentage") Num[0]--;
        if(sandTemp=="attackPercentage") Num[1]--;
        if(sandTemp=="defendPercentage") Num[2]--;
        if(sandTemp=="elementalMastery") Num[3]--;
        if(sandTemp=="recharge") Num[4]--;
        sandTemp.clear();
    }
    if(Art[selectedNum]->Get_MainAttribute()=="lifePercentage")
    {
        sandTemp=Art[selectedNum]->Get_MainAttribute();
        Num[0]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="attackPercentage")
    {
        sandTemp=Art[selectedNum]->Get_MainAttribute();
        Num[1]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="defendPercentage")
    {
        sandTemp=Art[selectedNum]->Get_MainAttribute();
        Num[2]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="elementalMastery")
    {
        sandTemp=Art[selectedNum]->Get_MainAttribute();
        Num[3]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="recharge")
    {
        sandTemp=Art[selectedNum]->Get_MainAttribute();
        Num[4]++;
    }
//    state[3] = 1;
}
void FavoriteOri::setCup(Artifact** Art, int selectedNum)
{
//    int n;
//    cout << "请输入系统内空之杯的序号：（输入0返回）" << endl;
//    while (cin >> n) {
//        if (n == 0)	return;
//        if (n > ArtAmount) {
//            cout << "序号不存在！请重新输入：" << endl;
//            continue;
//        }
//        if (!Art[n - 1]->confirm_position(4)) {
//            cout << "输入序号对应圣遗物不是空之杯，请重新输入：" << endl;
//            continue;
//        }
//        else {
//            break;
//        }
//    }
    f_id[3] = Art[selectedNum]->Get_id();
    favorite[3] =Art[selectedNum];
    if(!cupTemp.isEmpty())
    {
        if(cupTemp=="lifePercentage") Num[0]--;
        if(cupTemp=="attackPercentage") Num[1]--;
        if(cupTemp=="defendPercentage") Num[2]--;
        if(cupTemp=="elementalMastery") Num[3]--;
        cupTemp.clear();
    }
    if(Art[selectedNum]->Get_MainAttribute()=="lifePercentage")
    {
        cupTemp=Art[selectedNum]->Get_MainAttribute();
        Num[0]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="attackPercentage")
    {
        cupTemp=Art[selectedNum]->Get_MainAttribute();
        Num[1]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="defendPercentage")
    {
        cupTemp=Art[selectedNum]->Get_MainAttribute();
        Num[2]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="elementalMastery")
    {
        cupTemp=Art[selectedNum]->Get_MainAttribute();
        Num[3]++;
    }
//    state[4] = 1;
}
void FavoriteOri::setHead(Artifact** Art, int selectedNum)
{
//    int n;
//    cout << "请输入系统内理之冠的序号：（输入0返回）" << endl;
//    while (cin >> n) {
//        if (n == 0)	return;
//        if (n > ArtAmount) {
//            cout << "序号不存在！请重新输入：" << endl;
//            continue;
//        }
//        if (!Art[n - 1]->confirm_position(5)) {
//            cout << "输入序号对应圣遗物不是理之冠，请重新输入：" << endl;
//            continue;
//        }
//        else {
//            break;
//        }
//    }
    f_id[4] = Art[selectedNum]->Get_id();
    favorite[4] =Art[selectedNum];
    if(!headTemp.isEmpty())
    {
        if(headTemp=="lifePercentage") Num[0]--;
        if(headTemp=="attackPercentage") Num[1]--;
        if(headTemp=="defendPercentage") Num[2]--;
        if(headTemp=="elementalMastery") Num[3]--;
        if(headTemp=="critical") Num[5]--;
        if(headTemp=="criticalDamage") Num[6]--;
        headTemp.clear();
    }
    if(Art[selectedNum]->Get_MainAttribute()=="lifePercentage")
    {
        headTemp=Art[selectedNum]->Get_MainAttribute();
        Num[0]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="attackPercentage")
    {
        headTemp=Art[selectedNum]->Get_MainAttribute();
        Num[1]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="defendPercentage")
    {
        headTemp=Art[selectedNum]->Get_MainAttribute();
        Num[2]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="elementalMastery")
    {
        headTemp=Art[selectedNum]->Get_MainAttribute();
        Num[3]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="critical")
    {
        headTemp=Art[selectedNum]->Get_MainAttribute();
        Num[5]++;
    }
    if(Art[selectedNum]->Get_MainAttribute()=="criticalDamage")
    {
        headTemp=Art[selectedNum]->Get_MainAttribute();
        Num[6]++;
    }
//    state[5] = 1;
}
void FavoriteOri::setName(QString na)
{
    name = na;
}
//void FavoriteOri::setName(int i)
//{
//	stringstream st;
//	st << i;
//	name = st.str();
//}
QString FavoriteOri::getName()
{
    return name;
}
//void Display_Fav(FavoriteOri* f, const int &f_size)
//{
//	if (f_size == 0) cout << "尚无组合。" << endl;
//	else
//	{
//		cout.setf(ios::left);
//		for (int i = 0; i < f_size; i++)
//		{
//			cout << endl;
//			cout << "收藏序号/名称:" << f[i].id << " / " << f[i].getName() << endl << endl;
//			if (!f[i].set_two1.empty())	cout << "二件套：" << f[i].set_two1 << '\t';
//			if (!f[i].set_two2.empty())	cout << "二件套：" << f[i].set_two2 << '\t';
//			if (!f[i].set_four.empty())	cout << "四件套：" << f[i].set_four;
//			cout << endl << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout.width(25);
//				cout << f[i][j]->Get_Name();
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout.width(25);
//				if (f[i][j]->Get_position() == "flower") cout << "生之花";
//				if (f[i][j]->Get_position() == "feather") cout << "死之羽";
//				if (f[i][j]->Get_position() == "sand") cout << "时之沙";
//				if (f[i][j]->Get_position() == "cup") cout << "空之杯";
//				if (f[i][j]->Get_position() == "head") cout << "理之冠";
//			}
//			cout << endl << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout.width(25);
//				cout << f[i][j]->Get_MainAttributeChinese();
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				if (f[i][j]->Get_MainAttributeValue() > 1)
//				{
//					cout.width(25);
//					cout << f[i][j]->Get_MainAttributeValue();
//				}
//				else
//				{
//					cout << fixed << setprecision(1) << f[i][j]->Get_MainAttributeValue() * 100;
//					if (f[i][j]->Get_MainAttributeValue() * 100 > 10 || f[i][j]->Get_MainAttributeValue() * 100 == 10) cout.width(21);
//					else cout.width(22);
//					cout << "%";
//				}
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				for (int k = 0; k < f[i][j]->Get_star(); k++)
//				{
//					cout << "★";
//					if (k == f[i][j]->Get_star() - 2) cout.width(25 - f[i][j]->Get_star() - f[i][j]->Get_star() + 2);
//				}
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout << "+";
//				cout.width(24);//确保+20而不是+   20
//				cout << f[i][j]->Get_level();
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout << "·" << f[i][j]->Get_SubAttributeChinese1() << "+";
//				DisplaySubValue(f[i][j]->Get_SubAttributeValue1(), f[i][j]->Get_SubAttributeChinese1());
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout << "·" << f[i][j]->Get_SubAttributeChinese2() << "+";
//				DisplaySubValue(f[i][j]->Get_SubAttributeValue2(), f[i][j]->Get_SubAttributeChinese2());
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				cout << "·" << f[i][j]->Get_SubAttributeChinese3() << "+";
//				DisplaySubValue(f[i][j]->Get_SubAttributeValue3(), f[i][j]->Get_SubAttributeChinese3());
//			}
//			cout << endl;
//			for (int j = 0; j < 5; j++)
//			{
//				if (!f[i][j]->Get_SubAttribute4().empty())
//				{
//					cout << "·" << f[i][j]->Get_SubAttributeChinese4() << "+";
//					DisplaySubValue(f[i][j]->Get_SubAttributeValue4(), f[i][j]->Get_SubAttributeChinese4());
//				}
//			}
//			cout << endl << endl << "双暴总分：" << f[i].CRIT_score << endl;
//			cout << "生命: +" << f[i].total_life << " / +" << f[i].total_Life * 100 << "%\t";
//			cout << "攻击: +" << f[i].total_attack << " / +" << f[i].total_Attack * 100 << "%\t";
//			cout << "防御: +" << f[i].total_defend << " / +" << f[i].total_Defend * 100 << "%\t";
//			cout << "元素精通：+" << f[i].total_elementalMastery << "\t充能：+" << f[i].total_recharge * 100 << "%\t治疗：+" << f[i].total_cure * 100 << "%\n";
//			cout << "暴击率：+" << f[i].total_critical * 100 << "%\t" << "暴击伤害：+" << f[i].total_criticalDamage * 100<< "%\n";
//			if (f[i].total_physicalBonus)	cout << "物伤：+" << f[i].total_physicalBonus * 100  << "%" << endl;
//			if (f[i].total_fireBonus)	cout << "火伤：+" << f[i].total_fireBonus * 100 << "%" << endl;
//			if (f[i].total_waterBonus)	cout << "水伤：+" << f[i].total_waterBonus * 100 << "%" << endl;
//			if (f[i].total_thunderBonus)	cout << "雷伤：+" << f[i].total_thunderBonus * 100 << "%" << endl;
//			if (f[i].total_windBonus)	cout << "风伤：+" << f[i].total_windBonus * 100 << "%" << endl;
//			if (f[i].total_iceBonus)	cout << "冰伤：+" << f[i].total_iceBonus * 100 << "%" << endl;
//			if (f[i].total_rockBonus)	cout << "岩伤：+" << f[i].total_rockBonus * 100 << "%" << endl;
//			if (0)	cout << "草伤：+" << f[i].total_grassBonus * 100 << "%" << endl;
//			cout << endl << endl << endl;
//		}
//	}
//}
int FavoriteOri::getID(int i)
{
    return f_id[i];
}
void FavoriteOri::addEffect(QString s, double v)
{
	if (s == "lifeStatic")	total_life += v;
	if (s == "lifePercentage")	total_Life += v;
	if (s == "attackStatic")	total_attack += v;
	if (s == "attackPercentage")	total_Attack += v;
	if (s == "defendStatic")	total_defend += v;
	if (s == "defendPercentage")	total_Defend += v;
	if (s == "critical")	total_critical += v;
	if (s == "criticalDamage")	total_criticalDamage += v;
	if (s == "recharge")	total_recharge += v;
	if (s == "elementalMastery")	total_elementalMastery += v;
	if (s == "cureEffect")	total_cure += v;
	if (s == "physicalBonus")	total_physicalBonus += v;
	if (s == "fireBonus")	total_fireBonus += v;
	if (s == "waterBonus")	total_waterBonus += v;
	if (s == "grassBonus")	total_grassBonus += v;
	if (s == "thunderBonus")	total_thunderBonus += v;
	if (s == "windBonus")	total_windBonus += v;
	if (s == "iceBonus")	total_iceBonus += v;
	if (s == "rockBonus")	total_rockBonus += v;
}
void FavoriteOri::append_total()
{
    for (int i = 0; i < 5; i++)
    {
		this->addEffect(favorite[i]->Get_MainAttribute(), favorite[i]->Get_MainAttributeValue());
		this->addEffect(favorite[i]->Get_SubAttribute1(), favorite[i]->Get_SubAttributeValue1());
		this->addEffect(favorite[i]->Get_SubAttribute2(), favorite[i]->Get_SubAttributeValue2());
		this->addEffect(favorite[i]->Get_SubAttribute3(), favorite[i]->Get_SubAttributeValue3());
		this->addEffect(favorite[i]->Get_SubAttribute4(), favorite[i]->Get_SubAttributeValue4());
	}
}
void FavoriteOri::judge_set()
{
	int count = 0;
	bool flag = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (favorite[i]->Get_setName() == favorite[j]->Get_setName())
            {
                if (set_two1.isEmpty())
                {
					set_two1 = favorite[i]->Get_setName();
					count++;
				}
                else if (favorite[i]->Get_setName() != set_two1)
                {
					set_two2 = favorite[i]->Get_setName();
				}
				else
				{
					count++;
				}
			}
            if (!flag && count >= 6)
            {
				set_four = favorite[i]->Get_setName();
			}
		}
	}
}
void FavoriteOri::clear()
{
    for(int i=0;i<5;i++)
    {
        f_id[i]=-1;
        delete[] favorite[i];
    }
	CRIT_score = 0;
	total_critical = 0;
	total_criticalDamage = 0;
	total_recharge = 0;
	total_elementalMastery = 0;
	total_attack = 0;
	total_Attack = 0;
	total_defend = 0;
	total_Defend = 0;
	total_life = 0;
	total_Life = 0;
	total_cure = 0;
	total_physicalBonus = 0;
	total_fireBonus = 0;
	total_waterBonus = 0;
	total_grassBonus = 0;
	total_thunderBonus = 0;
	total_windBonus = 0;
	total_iceBonus = 0;
	total_rockBonus = 0;
	set_two1 = ""; set_two2 = ""; set_four = "";
}

bool FavoriteOri::isEmpty()
{
    int flag=0;
    for(int i=0;i<5;i++)
    {
        if(f_id[i]>-1) flag++;
    }
    if(!name.isEmpty()) flag++;
    if(flag!=6) return true;
    else return false;
}

//void ViewFunction(FavoriteOri* f, const int& f_size, Character*** Char,int * c_size, Weapon*** Weap, int* w_size)
//{
//	while (1) {
//		int mod;
//		Display_Fav(f, f_size);
//		cout << "请选择收藏序号：【0】返回" << endl;
//		cin >> mod;
//		if (mod == 0) {
//			break;
//		}
//		else if (mod > 0) {
//			while (1) {
//				int ch;
//                FavoriteOri* temp = &f[mod - 1];
//				cout << "【1】添加角色和武器\n【2】查看效果\n【0】返回" << endl;
//				cin >> ch;
//				if (ch == 0) {
//					break;
//				}
//				else if (ch == 1) {
//					f[mod - 1].setCharWeap(Char,c_size, Weap, w_size);
//				}
//				else if (ch == 2 && f[mod - 1].CW_isNULL()) {
//					cout << "角色或武器未添加！" << endl;
//					continue;
//				}
//				else if (ch == 2 && !f[mod - 1].CW_isNULL()) {
//					View view(f[mod - 1]);
//					Display_Fav(temp, 1);
//					view.show_View();
//				}
//				else {
//					cout << "无效输入！" << endl;
//					continue;
//				}
//			}
//		}
//		else {
//			cout << "无效输入！" << endl;
//			continue;
//		}
//	}
//}

//bool FavoriteOri::CW_isNULL()
//{
//	if (character == NULL || weapon == NULL) {
//		return 1;
//	}
//	else
//		return 0;
//}
//void FavoriteOri::setCharWeap(Character*** c, int* c_size, Weapon*** w, int* w_size)
//{
//	bool state1 = 0, state2 = 0;
//	while (!state1 || !state2) {
//		while (!state1) {
//			int mod;
//			DisplayCharacterList(c, c_size);
//			cout << "请选择人物：【0】返回" << endl;
//			cin >> mod;
//			if (mod == 0) {
//				return;
//			}
//			else if (mod > 0 && mod <= c_size[0]) {
//				int i = mod - 1;
//				while (1) {
//					int ch;
//					cout << "已选择：" << c[i][0]->Get_NameChinese() << endl;
//					cout << "请选择等级：\n【1】80级未突破\t【2】80级突破\t【3】90级\t【0】返回\n";
//					cin >> ch;
//					if (ch == 0) {
//						break;
//					}
//					else if (ch == 1) {
//						character = c[i][0];
//						state1 = 1;
//						break;
//					}
//					else if (ch == 2) {
//						character = c[i][1];
//						state1 = 1;
//						break;
//					}
//					else if (ch == 3) {
//						character = c[i][2];
//						state1 = 1;
//						break;
//					}
//					else {
//						cout << "无效输入！" << endl;
//						continue;
//					}
//				}
//			}
//			else {
//				cout << "无效输入！" << endl;
//				continue;
//			}
//		}
//		while (!state2) {
//			int mod;
//			DisplayWeaponList(w, w_size);
//			cout << "请选择武器：【0】返回" << endl;
//			cin >> mod;
//			if (mod == 0) {
//				break;
//			}
//			else if (mod > 0 && mod <= w_size[0]) {
//				int i = mod - 1;
//				while (1) {
//					int ch;
//					cout << "已选择：" << w[i][0]->Get_NameChinese() << endl;
//					cout << "请选择等级：\n【1】80级未突破\t【2】80级突破\t【3】90级\t【0】返回\n";
//					cin >> ch;
//					if (ch == 0) {
//						break;
//					}
//					else if (ch == 1) {
//						weapon = w[i][0];
//						state2 = 1;
//						break;
//					}
//					else if (ch == 2) {
//						weapon = w[i][1];
//						state2 = 1;
//						break;
//					}
//					else if (ch == 3) {
//						weapon = w[i][2];
//						state2 = 1;
//						break;
//					}
//					else {
//						cout << "无效输入！" << endl;
//						continue;
//					}
//				}
//			}
//			else {
//				cout << "无效输入！" << endl;
//				continue;
//			}
//		}
//	}
//}
/*
void Favorite::view()
{
	int attack = 0, defend = 0, life = 0;
	int base_attack = character->Get_BaseAttack() + weapon->Get_BaseAttack(),
		base_defend = character->Get_BaseDefend(),
		base_life = character->Get_BaseLife();
	double percent_attack = total_Attack,
		percent_defend = total_Defend,
		percent_life = total_Life;
	double critical = total_critical,
		criticalDamage = total_criticalDamage;
	double recharge = total_recharge,
		elementalMastery = total_elementalMastery;
	double cure = total_cure,
		physicalBonus = total_physicalBonus,
		fireBonus = total_fireBonus,
		waterBonus = total_waterBonus,
		grassBonus = total_grassBonus,
		thunderBonus = total_thunderBonus,
		windBonus = total_windBonus,
		iceBonus = total_iceBonus,
		rockBonus = total_rockBonus;
	
}
*/

double FavoriteOri::Get_total_life()
{
    return total_life;
}
double FavoriteOri::Get_total_Life()
{
    return total_Life;
}
double FavoriteOri::Get_total_attack()
{
    return total_attack;
}
double FavoriteOri::Get_total_Attack()
{
    return total_Attack;
}
double FavoriteOri::Get_total_defend()
{
    return total_defend;
}
double FavoriteOri::Get_total_Defend()
{
    return total_Defend;
}
double FavoriteOri::Get_mastery()
{
    return total_elementalMastery;
}
double FavoriteOri::Get_recharge()
{
    return total_recharge;
}
double FavoriteOri::Get_total_critical()
{
    return total_critical;
}
double FavoriteOri::Get_total_criticalDamage()
{
    return total_criticalDamage;
}
int FavoriteOri::Get_Num(int n)
{
    return Num[n];
}
double FavoriteOri::Get_cScore()
{
    return CRIT_score;
}
