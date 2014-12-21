/* HogeFO.cpp

�ȉ��̎d�l�͈�������ɂ��L�q�̂���(���݂͕ς���Ă���\��������)

void _stdcall load(char* path);

DLL�ڑ����ɌĂ΂��B
�����ɂ�DLL�̒u���Ă���p�X���n�����B�i�u\�v���I���ɕt���j
�����͏ȗ��\�B
�i�������������s�v�ŉ����t�H���_��Win32API���g�p���Ď��͂Ŏ擾����ꍇ���j
����ł͏������i�ꉹ���j�ɐڑ��E�������J��Ԃ��̂ŏd�����������Ă͂����Ȃ��B

void _stdcall unload();

DLL�ڑ��������ɌĂ΂��B
�����͏ȗ��\�B
����ł͏������i�ꉹ���j�ɐڑ��E�������J��Ԃ��̂ŏd�����������Ă͂����Ȃ��B

int _stdcall exists(char* name, int tone);

���݃`�F�b�N�B
name: ����ł͌����ݒ�̂P�J������"��.wav"������g���q����菜���������񂪓n�����
�d�l�͊m�肵�Ă��Ȃ��B�G�C���A�X���邢�͉����̉̎������̂܂ܓn���d�l���l���Ă���
tone: ���K�̐��l���n�����\��ł��邪�{�̑��Ŗ������B��ɂO���n��B
���̖��O�Ńf�[�^��Ԃ����Ƃ��o����ꍇ�͂O�ȊO���A
�Y���f�[�^���Ȃ��ꍇ�͂O��Ԃ��悤�Ɏ�������B
�����͏ȗ��\�B
�ȗ������ꍇ�����锭���ɑ΂��ăf�[�^�����݂���Ɖ��肳���B

void* _stdcall getpcmdata(char* name, int tone);

Wave�f�[�^�擾�B
������exists()�Ɠ����B
�g�Œ����wav�t�H�[�}�b�g�h�̃t�@�C���C���[�W���������Ɋi�[���A
���̃|�C���^��Ԃ��悤��������B
���g�Œ����wav�t�H�[�}�b�g�h�Ƃ́A
WAVE�w�b�_�EFormatChunk�EDataChunk����\�������wav�t�H�[�}�b�g�t�@�C���B
�]����Chunk���܂�ł͂����Ȃ��B

�Ԃ��f�[�^��p�ӂł��Ȃ������ꍇNULL��Ԃ����Ƃ��o���邪�A
����ȊO�̖����ȃ|�C���^�͕Ԃ��Ă͂����Ȃ��B

void _stdcall freepcm(void *p);

getpcmdata()�œn���ꂽ���������J������R�[�h����������B

void* _stdcall getfrqdata(char* name, int tone);

���g���\�f�[�^�擾�B
������exists()�Ɠ����B
�����͕K�{�ł͂Ȃ��B
.frq�̃t�@�C���C���[�W���������Ɋi�[���A
���̃|�C���^��Ԃ��悤��������B
�ȗ��\�B�ȗ������ꍇ�{�̑��ł͎��t�@�C����ǂ݂ɍs���B

�Ԃ��f�[�^��p�ӂł��Ȃ������ꍇNULL��Ԃ����Ƃ��o���邪�A
����ȊO�̖����ȃ|�C���^�͕Ԃ��Ă͂����Ȃ��B

void _stdcall freefrq(void *p);

getfrqdata()�œn���ꂽ���������J������R�[�h����������B
getfrqdata()���ȗ������ꍇ�A�ȗ��\�B

void _stdcall setup(int hwnd);

�����̐ݒ�_�C�A���O������������B
�����̃v���t�B�[����Setup�{�^������Ă΂��B
�ȗ��\�B


���R���p�C��

VC�̏ꍇ
cl HogeFO.cpp HogeFO.def /LD


*/
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>


//���W���[����
char modulepath[512];

/* DLL�ڑ����ɌĂ΂��B*/
void _stdcall load(char* path)
{
	strcpy(modulepath, path);//�n�����̂�"\"�t���ł��B
}

/* ���݃`�F�b�N */
int _stdcall exists(char* name, int tone)
{
	if (name == 0 || *name == 0)
	{
		return 0;
	}
	char filepath[512];
	strcpy(filepath, modulepath);
	strcat(filepath, name);
	strcat(filepath, ".wav");


	return !access(filepath, 0);

}

void *loadFileAll(char *filename)
{
	FILE *f = fopen(filename, "rb");
	void *p = 0;
	if (f)
	{
		long size;
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		p = malloc(size);
		
		fread(p, size, 1, f);
		
		fclose(f);
	}
	return p;
}

/* Wave�f�[�^�擾 */
void* _stdcall getpcmdata(char* name, int tone)
{
	if (name == 0 || *name == 0)
	{
		return 0;
	}
	
	char filepath[512];
	strcpy(filepath, modulepath);
	strcat(filepath, name);
	strcat(filepath, ".wav");
	
	return loadFileAll(filepath);
}

/* �f�[�^�J�� */
void _stdcall freepcm(void *p)
{
	free(p);
}

/* ���g���\�f�[�^�擾 */
void* _stdcall getfrqdata(char* name, int tone)
{
	if (name == 0 || *name == 0)
	{
		return 0;
	}
	
	char filepath[512];
	strcpy(filepath, modulepath);
	strcat(filepath, name);
	strcat(filepath, "_wav.frq");
	
	return loadFileAll(filepath);
}

/* ���g���\�f�[�^�J�� */
void _stdcall freefrq(void *p)
{
	free(p);
}


void _stdcall setup(int hwnd)
{
	// �t�@�C���o�̓X�g���[���̏�����
	std::ofstream ofs("hoge.txt", std::ios_base::out | std::ios_base::app);

	// �t�@�C����1�s����������
	ofs << "hoge" << std::endl;
	
}
