#include "stdafx.h"
#include "soundTestScene.h"


soundTestScene::soundTestScene()
{
}

soundTestScene::~soundTestScene()
{
}

HRESULT soundTestScene::init()
{
	musicSet();
	listSet();

	imgSet();

	controlSet();


	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	return S_OK;
}

void soundTestScene::release()
{
}

void soundTestScene::update()
{
	keyControl();
}

void soundTestScene::render()
{
	Rectangle(getMemDC(), _rc);

	_music.playImg->render(getMemDC(), _music.play.left, _music.play.top);
	Rectangle(getMemDC(), _music.play);
	Rectangle(getMemDC(), _music.stop);
	Rectangle(getMemDC(), _music.next);
	Rectangle(getMemDC(), _music.previos);
	Rectangle(getMemDC(), _music.pause);

	char str[128];
	sprintf_s(str, "x : %ld                y: %ld", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 20, 20, str, strlen(str));

	TextOut(getMemDC(), 20, 60, _list[_listCnt].name, strlen(_list[_listCnt].name));
	TextOut(getMemDC(), 20, 80, _list[_listCnt].title, strlen(_list[_listCnt].title));

	TextOut(getMemDC(), _music.playX, _music.playY, _con[0].con, strlen(_con[0].con));
	TextOut(getMemDC(), _music.stopX, _music.stopY, _con[1].con, strlen(_con[1].con));
	TextOut(getMemDC(), _music.nextX, _music.nextY, _con[2].con, strlen(_con[2].con));
	TextOut(getMemDC(), _music.previosX, _music.previosY, _con[3].con, strlen(_con[3].con));
	TextOut(getMemDC(), _music.pauseX, _music.pauseY, _con[4].con, strlen(_con[4].con));
	TextOut(getMemDC(), _music.resumeX, _music.resumeY, _con[5].con, strlen(_con[5].con));

	char cnt[128];
	sprintf_s(cnt, "%d", SOUNDMANAGER->getLength());
	TextOut(getMemDC(), 20, 100, cnt, strlen(cnt));
}
//��Ʈ�ѷ� ��
void soundTestScene::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//Ž����
		if (PtInRect(&_rc, _ptMouse))
		{
			OPENFILENAME ofn;
			char filePathSize[1028] = "";
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = filePathSize;
			ofn.nMaxFile = sizeof(filePathSize);
			ofn.nFilterIndex = true;
			ofn.nMaxFileTitle = NULL;
			ofn.lpstrFileTitle = NULL;
			ofn.lpstrInitialDir = NULL;
			ofn.lpstrFilter = ("�������������ϸ�");
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&ofn) == FALSE) return;

			char temp[1028];
			strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

			char* context = NULL;
			char* token = strtok_s(temp, "\\", &context);

			while (strlen(context))
			{
				token = strtok_s(NULL, "\\", &context);
			}

			SOUNDMANAGER->addSound(token, ofn.lpstrFile, false, false);
			SOUNDMANAGER->play(token);
		}
		//play
		if (PtInRect(&_music.play, _ptMouse))
		{
			SOUNDMANAGER->play(_list[_listCnt].name, 0.5f);
		}
		//stop
		if (PtInRect(&_music.stop, _ptMouse))
		{
			SOUNDMANAGER->stop(_list[_listCnt].name);
		}

		//next
		if (PtInRect(&_music.next, _ptMouse))
		{
			if (_listCnt == PLAYLISTMAX - 1)_listCnt = PLAYLISTMAX - 1;
			else _listCnt++;
		}
		//previos
		if (PtInRect(&_music.previos, _ptMouse))
		{
			if (_listCnt == 0)_listCnt = 0;
			else _listCnt--;
		}
		//pause
		if (PtInRect(&_music.pause, _ptMouse))
		{
			SOUNDMANAGER->pause(_list[_listCnt].name);
		}
		//resume
		if (PtInRect(&_music.resume, _ptMouse))
		{
			SOUNDMANAGER->resume(_list[_listCnt].name);
		}
	}
}

void soundTestScene::imgSet()
{
	IMAGEMANAGER->addImage("play", "image/play.bmp", 50, 50, true, RGB(255, 0, 255));
	/*IMAGEMANAGER->addImage("play", "image/play.bmp", 99, 99, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("play", "image/play.bmp", 99, 99, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("play", "image/play.bmp", 99, 99, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("play", "image/play.bmp", 99, 99, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("play", "image/play.bmp", 99, 99, true, RGB(255, 0, 255));*/
}

void soundTestScene::musicSet()
{
	SOUNDMANAGER->addSound("����", "music/4Men - First Kiss.mp3", true, true);
	SOUNDMANAGER->addSound("KCM", "music/KCM - ���� �����.mp3", true, false);
	SOUNDMANAGER->addSound("MC��", "music/MC�� - ���� (feat. Ivy).mp3", true, false);
	SOUNDMANAGER->addSound("������", "music/������ - ���� �Ѽ�.mp3", true, false);
	SOUNDMANAGER->addSound("����", "music/���� - ���� �ð� ���� ��.mp3", true, false);
	SOUNDMANAGER->addSound("����", "music/����-���� ���� ��.mp3", true, false);
	SOUNDMANAGER->addSound("��", "music/�� - �ð��� �Ž���.mp3", true, false);
	SOUNDMANAGER->addSound("����", "music/���� - ������ ��Ŭ.mp3", true, false);
	SOUNDMANAGER->addSound("������", "music/����󼼼�, ������ - ��Ÿ�� ����.mp3", true, false);
	SOUNDMANAGER->addSound("�����", "music/����� - �� ������ �״밡 �Ǿ�(������).mp3", true, false);
	SOUNDMANAGER->addSound("�㰢", "music/�㰢 - I Need You.mp3", true, false);
}

void soundTestScene::listSet()
{
	sprintf_s(_list[0].name, "����");
	sprintf_s(_list[0].title, "First Kiss");
	sprintf_s(_list[1].name, "KCM");
	sprintf_s(_list[1].title, "���� �����");
	sprintf_s(_list[2].name, "MC��");
	sprintf_s(_list[2].title, "����(feat. Ivy)");
	sprintf_s(_list[3].name, "������");
	sprintf_s(_list[3].title, "���� �Ѽ�");
	sprintf_s(_list[4].name, "����");
	sprintf_s(_list[4].title, "���� �ð����� ��");
	sprintf_s(_list[5].name, "����");
	sprintf_s(_list[5].title, "���� ���� ��");
	sprintf_s(_list[6].name, "��");
	sprintf_s(_list[6].title, "�ð��� �Ž���");
	sprintf_s(_list[7].name, "����");
	sprintf_s(_list[7].title, "������ ��Ŭ");
	sprintf_s(_list[8].name, "������");
	sprintf_s(_list[8].title, "��Ÿ�� ����");
	sprintf_s(_list[9].name, "�����");
	sprintf_s(_list[9].title, "�� ������ �״밡 �Ǿ�(������)");
	sprintf_s(_list[10].name, "�㰢");
	sprintf_s(_list[10].title, "I Need You");
	_listCnt = 0;
}

void soundTestScene::controlSet()
{
	_music.play = RectMakeCenter(100, 200, 50, 50);
	_music.playImg = IMAGEMANAGER->findImage("play");
	_music.playX = _music.play.left;
	_music.playY = _music.play.top - 10;
	sprintf_s(_con[0].con, "play");

	_music.stop = RectMakeCenter(160, 200, 50, 50);
	_music.stopX = _music.stop.left;
	_music.stopY = _music.stop.top - 10;
	sprintf_s(_con[1].con, "stop");

	_music.next = RectMakeCenter(220, 200, 50, 50);
	_music.nextX = _music.next.left;
	_music.nextY = _music.next.top - 10;
	sprintf_s(_con[2].con, "next");

	_music.previos = RectMakeCenter(280, 200, 50, 50);
	_music.previosX = _music.previos.left;
	_music.previosY = _music.previos.top - 10;
	sprintf_s(_con[3].con, "previos");

	_music.pause = RectMakeCenter(340, 200, 50, 50);
	_music.pauseX = _music.pause.left;
	_music.pauseY = _music.pause.top - 10;
	sprintf_s(_con[4].con, "pause");

	_music.resume = RectMakeCenter(400, 200, 50, 50);
	_music.resumeX = _music.resume.left;
	_music.resumeY = _music.resume.top - 10;
	sprintf_s(_con[5].con, "resume");

}
