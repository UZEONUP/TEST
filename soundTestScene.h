#pragma once
#include "gameNode.h"
#include <commdlg.h>//OPENFILENAME
#define PLAYLISTMAX 11

struct tagControl
{
	RECT play;			//play
	image* playImg;
	float playX, playY;
	RECT stop;			//stop
	image* stopImg;
	float stopX, stopY;
	RECT next;			//next
	image* nextImg;
	float nextX, nextY;
	RECT previos;		//previos
	image* preImg;
	float previosX, previosY;
	RECT pause;			//pause
	image* pauseImg;
	float pauseX, pauseY;
	RECT resume;		//resume
	image* reImg;
	float resumeX, resumeY;
};

struct tagPlayList
{
	char name[128];
	char title[1028];
};

struct tagCon
{
	char con[128];
};


class soundTestScene : public gameNode
{
private:
	tagControl _music;
	tagPlayList _list[PLAYLISTMAX];
	RECT _rc;
	tagCon _con[6];
	int _listCnt;

public:
	soundTestScene();
	~soundTestScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	void imgSet();
	void musicSet();
	void listSet();
	void controlSet();
};

