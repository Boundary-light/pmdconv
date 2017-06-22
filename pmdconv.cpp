//pmd�ο���https://github.com/mistydemeo/pmdmini
//midifile�ο���https://github.com/craigsapp/midifile
#ifdef _DEBUG
#pragma comment(lib,"midifile\\visual-studio\\DebugLib\\midifile.lib")
#pragma comment(lib,"pmdplay\\Debug\\pmdplay.lib")
#else
#pragma comment(lib,"midifile\\visual-studio\\ReleaseLib\\midifile.lib")
#pragma comment(lib,"pmdplay\\Release\\pmdplay.lib")
#endif
#define _WINDOWS
#include"midifile\include\MidiFile.h"
#include"pmdplay\pmdwin\pmdwinimport.h"
#include<iostream>
#include<fstream>
#define MAX_PMD_PATCH 256
int patch[MAX_PMD_PATCH];
void InitPatch()
{
	std::ifstream pf("patch.txt", std::ios::in);
	for (int i = 0; i < MAX_PMD_PATCH; i++)patch[i] = i % 128;
	if (!pf)
	{
		printf("δ�ҵ� patch.txt, ������PMD��ɫ��ΪGM��ɫ����"
			"�����㴴�����ļ�����ÿ��д��PMD��GM�Ķ�Ӧ��ɫ������ת��������MIDIЧ�����ܲ����롣\n");
	}
	else
	{
		int i = 0;
		while (i < MAX_PMD_PATCH)
		{
			pf >> patch[i];
			if (patch[i] > 127)printf("��ɫ[%d]=%d, �������ֵ 127.\n", i, patch[i]);
			if (pf.eof())break;
		}
		printf("��ȡ��%d����ɫ��\n", i);
	}
}
int Convert(const char *infile, const char *outfile)
{
	pmdwininit(".");
	setpcmrate(SOUND_44K);
	const int buf_length = 8192;
	short buf[buf_length];
	//TODO
	//��ͨ����ֱ�ӻ�ȡÿͨ��QQ�е���Ϣ���ɣ����ಿ�ֲ���Rͨ�����������Ի�ȡ��������Tom��Ҫ�ο�Kͨ���ĵ㡣
	printf("TODO:�������������С�\n�����ȡ������£����ע https://github.com/lxfly2000/pmdconv.");
	music_stop();
	return 0;
}
int main(int argc, char *argv[])
{
	char outfile[_MAX_PATH];
	const char *infile = argv[1];
	sprintf(outfile, "%s.mid", infile);
	switch (argc)
	{
	case 3:strcpy(outfile, argv[2]);
	case 2:
		break;
	default:
		printf("��������\npmdconv <�����ļ���> [����ļ���=<�����ļ���>.mid]\n");
		return 1;
	}
	InitPatch();
	return Convert(infile, outfile);
}