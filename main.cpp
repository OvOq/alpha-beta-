#define _CRT_SECURE_NO_WARNINGS    
#include<windows.h> 
#include<cstring>
#include<cstdio>
#include<cstdlib> 
#include<iostream> 
#include<string> 
using namespace std;
int MAX_NUM(1 << 20); // ������
int end_state = (1 << 18) - 1; // �ս�״̬�����б�Ȩֵ֮�ʹﵽ��������Ϸ����
int Tir[10]; // ��9�������ε���ɫ��Ϣ��0-��ɫ��1-��ɫ��2-��ɫ
int Map[20]; // ��18���ߵ���ɫ��Ϣ��0-��ɫ��1-��ɫ��2-��ɫ
int Brim_Tag[20]; // ��ѡ���ı�, 0-δѡ��1-ѡ��
int tri_map[9] = { 7, 56, 98, 448, 3584, 6160, 28672, 49280, 229376 }; // 9�������ε�Ȩֵ
int brim_map[11][11] = {
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, 0, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1, 0, -1, 2, 3, 4, -1, -1, -1, -1, -1 },
	{ -1, 1, 2, -1, -1, 5, 6, -1, -1, -1, -1 },
	{ -1, -1, 3, -1, -1, 7, -1, 9, 10, -1, -1 },
	{ -1, -1, 4, 5, 7, -1, 8, -1, 11, 12, -1 },
	{ -1, -1, -1, 6, -1, 8, -1, -1, -1, 13, 14 },
	{ -1, -1, -1, -1, 9, -1, -1, -1, 15, -1, -1 },
	{ -1, -1, -1, -1, 10, 11, -1, 15, -1, 16, -1 },
	{ -1, -1, -1, -1, -1, 12, 13, -1, 16, -1, 17 },
	{ -1, -1, -1, -1, -1, -1, 14, -1, -1, 17, -1 },
};// brim_map[i][j] = k <==> ��i�������͵�j������֮���ǵ�k���ߣ�-1����û�б�
/*int FastLog2(int x) // ȡ����
{
	float fx; 
	unsigned long ix, exp; 
	fx = (float)x; 
	ix = *(unsigned long*)&fx; 
	exp = (ix >> 23) & 0xFF; 
	return exp - 127;
}*/
void ChingShowColor(int x)
{
	switch (x)
	{
	case 0:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf); break;
	case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); break;
	case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;
	default:
		break;
	}
}

void ShowTri(int *Map, int *Tir)
{
	int Map_i = 0, Tir_i = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "         01" << endl;//1#
	ChingShowColor(Map[Map_i++]);
	cout << "        /";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "\\" << endl;//2#
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "      02";
	ChingShowColor(Map[Map_i++]);
	cout << "----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "03" << endl;//3#
	ChingShowColor(Map[Map_i++]);
	cout << "     /";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "\\";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "/";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "\\" << endl;//4#
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "   04";
	ChingShowColor(Map[Map_i++]);
	cout << "----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "05";
	ChingShowColor(Map[Map_i++]);
	cout << "----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "06" << endl;//5#
	ChingShowColor(Map[Map_i++]);
	cout << "  /";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "\\";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "/";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "\\";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "/";
	ChingShowColor(Tir[Tir_i++]);
	cout << "��";
	ChingShowColor(Map[Map_i++]);
	cout << "\\" << endl;//6#
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "07";
	ChingShowColor(Map[Map_i++]);
	cout << "----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "08";
	ChingShowColor(Map[Map_i++]);
	cout << "----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "09";
	ChingShowColor(Map[Map_i++]);
	cout << "----";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "10" << endl;//7#
}
int AddingTir(int brim, int color) { // �����������ж����������Ƿ�����
	int add = 0;
	if (brim == 2) {
		if (Tir[1] == 0 && Brim_Tag[0] && Brim_Tag[1]) {
			add++;
			Tir[1] = color;
		}
		if (Tir[3] == 0 && Brim_Tag[4] && Brim_Tag[5]) {
			add++;
			Tir[3] = color;
		}
	}
	if (brim == 4) {
		if (Tir[2] == 0 && Brim_Tag[3] && Brim_Tag[7]) {
			add++;
			Tir[2] = color;
		}
		if (Tir[3] == 0 && Brim_Tag[2] && Brim_Tag[5]) {
			add++;
			Tir[3] = color;
		}
	}
	if (brim == 5) {
		if (Tir[4] == 0 && Brim_Tag[6] && Brim_Tag[8]) {
			add++;
			Tir[4] = color;
		}
		if (Tir[3] == 0 && Brim_Tag[4] && Brim_Tag[2])
		{
			add++;
			Tir[3] = color;
		}
	}
	if (brim == 7) {
		if (Tir[6] == 0 && Brim_Tag[10] && Brim_Tag[11]) {
			add++;
			Tir[6] = color;
		}
		if (Tir[2] == 0 && Brim_Tag[4] && Brim_Tag[3]) {
			add++;
			Tir[2] = color;
		}
	}
	if (brim == 8) {
		if (Tir[8] == 0 && Brim_Tag[12] && Brim_Tag[13]) {
			add++;
			Tir[8] = color;
		}
		if (Tir[4] == 0 && Brim_Tag[6] && Brim_Tag[5]) {
			add++;
			Tir[4] = color;
		}
	}
	if (brim == 10) {
		if (Tir[6] == 0 && Brim_Tag[7] && Brim_Tag[11]) {
			add++;
			Tir[6] = color;
		}
		if (Tir[5] == 0 && Brim_Tag[9] && Brim_Tag[15]) {
			add++;
			Tir[5] = color;
		}
	}
	if (brim == 11) {
		if (Tir[6] == 0 && Brim_Tag[10] && Brim_Tag[7]) {
			add++;
			Tir[6] = color;
		}
		if (Tir[7] == 0 && Brim_Tag[16] && Brim_Tag[12]) {
			add++;
			Tir[7] = color;
		}
	}
	if (brim == 12) {
		if (Tir[7] == 0 && Brim_Tag[11] && Brim_Tag[16]) {
			add++;
			Tir[7] = color;
		}
		if (Tir[8] == 0 && Brim_Tag[8] && Brim_Tag[13]) {
			add++;
			Tir[8] = color;
		}
	}
	if (brim == 13) {
		if (Tir[8] == 0 && Brim_Tag[12] && Brim_Tag[8]) {
			add++;
			Tir[8] = color;
		}
		if (Tir[9] == 0 && Brim_Tag[17] && Brim_Tag[14]) {
			add++;
			Tir[9] = color;
		}
	}
	if (brim == 0) {
		if (Tir[1] == 0 && Brim_Tag[1] && Brim_Tag[2]) {
			add++;
			Tir[1] = color;
		}
	}
	if (brim == 1) {
		if (Tir[1] == 0 && Brim_Tag[0] && Brim_Tag[2]) {
			add++;			
			Tir[1] = color;
		}
	}
	if (brim == 3) {
		if (Tir[2] == 0 && Brim_Tag[4] && Brim_Tag[7]) {
			add++;
			Tir[2] = color;
		}
	}
	if (brim == 6) {
		if (Tir[4] == 0 && Brim_Tag[5] && Brim_Tag[8]) {
			add++;
			Tir[4] = color;
		}
	}
	if (brim == 9) {
		if (Tir[5] == 0 && Brim_Tag[10] && Brim_Tag[15]) {
			add++;
			Tir[5] = color;
		}
	}
	if (brim == 15) {
		if (Tir[5] == 0 && Brim_Tag[9] && Brim_Tag[10]) {
			add++;
			Tir[5] = color;
		}
	}
	if (brim == 16) {
		if (Tir[7] == 0 && Brim_Tag[11] && Brim_Tag[12]) {
			add++;
			Tir[7] = color;
		}
	}
	if (brim == 17) {
		if (Tir[9] == 0 && Brim_Tag[13] && Brim_Tag[14]) {
			add++;
			Tir[9] = color;
		}
	}
	if (brim == 14) {
		if (Tir[9] == 0 && Brim_Tag[13] && Brim_Tag[17]) {
			add++;
			Tir[9] = color;
		}
	}

	return add;
}
int next_state(int cur_state, int brim, int *cnt) // ���¾����ߵ�Ȩֵ�ܺ�
{
	int i;
	int new_state = (cur_state | brim); // �¾�����Ȩֵ��
	for (i = 0; i < 9; i++) {
		if (((cur_state & tri_map[i]) != tri_map[i]) && ((new_state & tri_map[i]) == tri_map[i]))	(*cnt)++;
	} // �����������Σ���Ӧ���ҷ���++
	return new_state;
}
int AlphaBeta(int player, int cur_state, int alpha, int beta, int a_score, int b_score) // alphabeta��֦��player:0-�췽��1-����
{
	int remain; // ʣ����Ȩֵ��
	int new_state; // �±����ڵ��¾�������Ȩֵ��
	int a_tag; // a�ļ�ʱ�÷�
	int b_tag; // b�ļ�ʱ�÷�
	//int val;
	if (a_score >= 5) return 1;
	else if (b_score >= 5) return -1;
	remain = ((~cur_state) & end_state); 
	if (player) {
		while (remain) {
			int val;
			int move = ( remain  & ( - remain ) ); // magic, do not touch
			a_tag = a_score;
			new_state = next_state(cur_state, move, &a_tag);
			if (a_tag > a_score) val = AlphaBeta(player, new_state, alpha, beta, a_tag, b_score);
			else val = AlphaBeta(player^1, new_state, alpha, beta, a_score, b_score);
			if (alpha < val) alpha = val;
			if (alpha >= beta) return alpha;
			remain -= move;
		}
		return alpha;
	}
	else {
		while (remain) {
			int val;
			int move = (remain & (-remain)); // magic, do not touch
			b_tag = b_score;
			new_state = next_state(cur_state, move, &b_tag);
			if (b_tag > b_score) val = AlphaBeta(player, new_state, alpha, beta, a_score, b_tag);
			else val = AlphaBeta(player ^ 1, new_state, alpha, beta, a_score, b_score);
			if (val < beta) beta = val;
			if (alpha >= beta) return beta;
			remain -= move;
		}
		return beta;
	}
}
int WIN_JUDGE(int cnt) {
	int red, blue;
	red = 0; blue = 0;
	if (cnt == end_state) {
		for (int i = 0; i < 9; i++) {
			if (Tir[i] == 1) red++;
			if (Tir[i] == 2) blue++;
		}
		if (red >= 7) {
			Sleep(600);
			system("cls");
			printf("                                      your score:%d, my score: %d\n", red, blue);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			ShowTri(Map, Tir);
			cout << "Congratulations�� YOU WIN! ";
			system("pause");
			exit(0);
		}
		if (blue >= 7) {
			Sleep(600);
			system("cls");
			printf("                                      your score:%d, my score: %d\n", red, blue);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			ShowTri(Map, Tir);
			cout << "HAHA! I WIN! ";
			system("pause");
			exit(0);
		}
		if (red > blue) return 1; // red win 
		else return -1; // blue win
	}
	return 0; // nobody win
}
int Select_Edge(int move, int player, int cur_state, int *ct, int *score) // �ж��±��ܷ��γ���������
{
	
	int cct = *ct;
	
	if (move == 1)
	{
		Brim_Tag[0] = 1;
		int new_state = (cur_state | move); // ��ǰ���沢��һ�����γ��¾��� 
		for (int i = 0; i < 9; i++) // �����¾������γ�һ���µĵ�λ�����Σ��������������ϱ�����ɫ 
		{
			if (((cur_state & tri_map[i]) != tri_map[i]) && ((new_state & tri_map[i]) == tri_map[i]))
			{
				Tir[i+1] = 2;
				(*ct)++;
			}
		}
		Sleep(600);
		system("cls");
		printf("  i chose 1 - 2                       your score:%d, my score: %d\n", (*score), (*ct));
		Map[0] = 2;
		ShowTri(Map, Tir);
		if (*ct > cct) return 1;//����1˵�����ҵı��ܹ��ֳ��µ������Σ�����0˵������ 
		else return 0;
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (move == 1 << brim_map[i][j])
			{
				(*ct) += AddingTir(brim_map[i][j], 2);
				Brim_Tag[brim_map[i][j]] = 1;	
				Sleep(600);
				system("cls");
				printf("  i chose %d-%d                       your score:%d, my score: %d\n", i, j, (*score), (*ct));
				Map[brim_map[i][j]] = 2;
				ShowTri(Map, Tir);
				if (*ct > cct) return 1;
				else return 0;
			}
		}
	}
}
void NewGame() //game index
{
	int player; // ���ҽ�ɫ��0 - �췽�����У���1 - ����
	int color;
	string su, sv;
	memset(Map, 0, sizeof(Map));
	memset(Tir, 0, sizeof(Tir));
	memset(Brim_Tag, 0, sizeof(Brim_Tag));
	
	rechoose:	
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xf);
	cout << "The player character in the game is represented by a number" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "0 for red and 1 for blue" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
	cout << "now please choose your role:";
	cin >> player;

	if (player == 0) {// ����ѡ��0�췽������
		int brim;
		int playerScore, Cscore; // ���ҵ÷������Ե÷�
		int cur_state = 0; // ��ǰ�������б�Ȩֵ��
		int Cscore_add; // �������ܷ������� 1-�ǣ�0-����AddingTir�ķ���ֵ)
		
		playerScore = 0; Cscore = 0;
		color = 1;
		system("cls");
		cout << "you are the RED, computer is the BLUE, you can go first" << endl;
		ShowTri(Map, Tir);
		while (cin >> su >> sv) {
			int u, v;
			int u_len, v_len;
			int val = 0;

			u_len = su.size();
			v_len = sv.size();

			if (u_len == 1) {
				u = su.at(0) - '0';
				if (u < 0 || u > 9) {
					cout << "input error, puts again : " << endl;
					continue;
				}
			}
			if (u_len == 2) {
				if (su.at(0) == '1' && su.at(1) == '0') u = 10;
				else if (su.at(0) == '0') u = su.at(1) - '0';
				else {
					cout << "input error, puts again : " << endl;
					continue;
				}
			}
			if (v_len == 1) {
				v = sv.at(0) - '0';
				if (v < 0 || v > 9) {
					cout << "input error, puts again : " << endl;
					continue;
				}
			}
			if (v_len == 2) {
				if (sv.at(0) == '1' && sv.at(1) == '0') v = 10;
				else if (sv.at(0) == '0') v = sv.at(1) - '0';
				else {
					cout << "input error, puts again : " << endl;
					continue;
				}
			}
			brim = brim_map[u][v];
			if (brim == -1) {
				cout << "no such brim~  puts again: ";
				continue;
			}
			if (Brim_Tag[brim] == 1) {
				cout << "this brim has been chosen, choose another one : ";
				continue;
			}

			system("cls");
			Brim_Tag[brim] = 1;
			Map[brim] = color;

			int scoreTag = AddingTir(brim, color);
			playerScore += scoreTag;
			cur_state = (cur_state | (1 << brim));
			printf("  you chose %d-%d                     your score:%d, my score: %d\n", u, v, playerScore, Cscore);
			ShowTri(Map, Tir);
			if (WIN_JUDGE(cur_state) == 1) {
				system("cls");
				printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				ShowTri(Map, Tir);
				cout << "Congratulations�� YOU WIN! ";
				system("pause");
				exit(0);
			}
			else if (WIN_JUDGE(cur_state) == -1) {
				system("cls");
				printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				ShowTri(Map, Tir);
				cout << "HAHA�� I WIN! ";
				system("pause");
				exit(0);
			}
			if (scoreTag) {
				system("cls");
				printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
				ShowTri(Map, Tir);
				cout << "nice try! you can make the very next move:";
				continue;
			}
			int thinknum = -1;	//------------------------------------------------����������--------------------------------------------------------------
		C_go:
			Cscore_add = 1;
			int remain = ((~cur_state) & end_state); // ʣ�����ߵı�Ȩֵ��
			int move;	
			while (remain) {
				thinknum++;
				cout << "emmmm i see ";
				for (int ii = 0; ii < thinknum; ii++) {
					if (thinknum == 1)
					{
						cout << "again";
					}
					else
					{
						cout << " and again";
					}
				}
				cout << " ..." << endl;
				Sleep(700);
				if (thinknum >= 20) {
					system("cls");
					string dead;
					cout << "55555 " << endl;
					cout << "something wrong with my head, and that lazy programmer said she didn't want to debug anymore, i'm gonna die" << endl;
					cout << "so just press any key to bury me" << endl;
					system("pause");
					system("cls");
					cout << "wait wait" << endl;
					cout << "you will be back right ? will you miss me ? i konw you are happy with me :)" << endl;
					cout << "if you miss me ,please press A:";
					cin >> dead;
					if (dead.size()!=1 || (dead.size()==1 && dead.at(0) != 'A') )
					{
						system("cls");
						cout << "oh then i will die ruefully,,," << endl;
						cout << "goodbye" << endl;
						system("pause");
						exit(0);
					}
					else
					{
						system("cls");
						cout << "tks, and i'll miss you two...bye" << endl;
						system("pause");
						exit(0);
					}

				}
				move = (remain & (-remain)); // ����ѡ�ıߵ�Ȩֵ(2�Ľ׳�)	
				remain -= move;
				int Cscore_tag = Cscore;
				int val;
				int new_state = next_state(cur_state, move, &Cscore_tag);
				if (Cscore_tag > Cscore) {
					val = AlphaBeta(0, new_state, -MAX_NUM, MAX_NUM, playerScore, Cscore_tag);
					if (val == -1)
					{
						Cscore_add = Select_Edge(move, 1, cur_state, &Cscore, &playerScore);
						cur_state |= move;
						if (WIN_JUDGE(cur_state) == -1) {
							Sleep(600);
							system("cls");
							printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							ShowTri(Map, Tir);
							cout << "HAHA! I WIN! ";
							system("pause");
							exit(0);
						}
						else if (WIN_JUDGE(cur_state) == 1)
						{
							Sleep(600);
							system("cls");
							printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							ShowTri(Map, Tir);
							cout << "Congratulations�� YOU WIN! ";
							system("pause");
							exit(0);
						}
						break;
					}
				}
				else
				{
					val = AlphaBeta(1, new_state, -MAX_NUM, MAX_NUM, playerScore, Cscore);
					if (val == -1) {
						Cscore_add = Select_Edge(move, 1, cur_state, &Cscore, &playerScore);
						cur_state |= move;
						break;
					}
				}
			}
			if (Cscore_add) {
				Sleep(600);
				if (WIN_JUDGE(cur_state) == -1) {
					Sleep(600);
					system("cls");
					printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					ShowTri(Map, Tir);
					cout << "HAHA! I WIN! ";
					system("pause");
					exit(0);
				}
				else if (WIN_JUDGE(cur_state) == 1)
				{
					Sleep(600);
					system("cls");
					printf("                                      your score:%d, my score: %d\n", playerScore, Cscore);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					ShowTri(Map, Tir);
					cout << "Congratulations�� YOU WIN! ";
					system("pause");
					exit(0);
				}
				goto C_go;
			}
		}
	}
	else if (player == 1) { // ����ѡ��1���������� -----------------------------------------------------δд------------------------
		system("cls");
		cout << "no ! you can not chose this cuz the programmer hasn't finist this part " << endl;
		cout << "choose again!" << endl;
		system("pause");
		goto rechoose;
	}
	else {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		cout << "Input error, silly goose~" << endl;
		cout << "press any key to reinput " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
		system("pause");
		goto rechoose;
	}
	ShowTri(Map, Tir);
	cout << "press to out" << endl;
	system("pause");
}

int main()
{
	int beginner; // ��ʼʱ��ѡ������
	system("title      MADE BY OvOq");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "welcome to The Triangle World...\n";
	system("pause");
	reinput :	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "Now please enter the number to choose next step:" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0xf);
	cout << "1 - Start the game directly" << endl;
	cout << "2 - Game operation instructions" << endl;
	cout << "3 - Stop and exit" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "your choice:";
	cin >>  beginner;
	switch (beginner) // (�Ԩ���)
	{
		case 3: return 0; // �˳�
		case 1: NewGame(); break; // ֱ�ӿ�ʼ
		case 2: { // ����˵������ʼ��Ϸ
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "Rules are as follows:" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
			cout << "1. The game has two players: you and i : )" << endl;
			cout << "2. Two players alternately select the edge, and the red side first;" << endl;
			cout << "3. Whoever uses the colored edges to form a triangle scores, the score is the number of newly generated triangle(s);" << endl;
			cout << "4. The scorer can continue to select the next edge until the newly selected edge does not directly form a new triangle;" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "5. Entering such as 1 3 (or 3 1) means that you choose side 1-3 ;" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << endl;
			cout << "now tap to enjoy your game" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
			system("pause");
			NewGame();
			break;
		}
		default: { // ��������
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "Input error, silly goose" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);
			system("pause");
			goto reinput;
			break;
		}
	}
	return 0;
}
