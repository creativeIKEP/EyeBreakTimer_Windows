#pragma once
#include<windows.h>
#define MAX_LEN 256


static LANGID lang = GetUserDefaultUILanguage();
static bool isJapanese = (lang == 0x0411);

static LPWSTR LANG_PAUSE = isJapanese ? new WCHAR[MAX_LEN]{ L"�ꎞ��~" } : new WCHAR[MAX_LEN]{ L"Pause" };
static LPWSTR LANG_RESTART = isJapanese ? new WCHAR[MAX_LEN]{ L"�ĊJ" } : new WCHAR[MAX_LEN]{ L"Restart" };
static LPWSTR LANG_SETTING = isJapanese ? new WCHAR[MAX_LEN]{ L"�ݒ�" } : new WCHAR[MAX_LEN]{ L"Setting" };
static LPWSTR LANG_EXIT = isJapanese ? new WCHAR[MAX_LEN]{ L"�I��" } : new WCHAR[MAX_LEN]{ L"Exit" };

static LPWSTR LANG_TIMER_MESSAGE = isJapanese ? new WCHAR[MAX_LEN]{ L"�����o�߂��܂����B�ڂ��x�e�����܂��傤�B" } : new WCHAR[MAX_LEN]{ L"minutes have passed. Break your eyes." };

static LPWSTR LANG_SETTIME = isJapanese ? new WCHAR[MAX_LEN]{ L"�ݒ莞��" } : new WCHAR[MAX_LEN]{ L"SetTime" };
static LPWSTR LANG_MINUTES = isJapanese ? new WCHAR[MAX_LEN]{ L"��" } : new WCHAR[MAX_LEN]{ L"minutes" };
static LPWSTR LANG_LOCKEDPAUSE = isJapanese ? new WCHAR[MAX_LEN]{ L"PC��ʃ��b�N���Ƀ^�C�}�[���ꎞ��~" } : new WCHAR[MAX_LEN]{ L"Pause timer when PC was locked" };
static LPWSTR LANG_UNLOCKED_RESTART = isJapanese ? new WCHAR[MAX_LEN]{ L"PC��ʃ��b�N�������Ƀ^�C�}�[���ĊJ" } : new WCHAR[MAX_LEN]{ L"Restart timer when PC was unlocked" };
static LPWSTR LANG_UNLOCKED_RESET = isJapanese ? new WCHAR[MAX_LEN]{ L"PC��ʃ��b�N�������Ƀ^�C�}�[�����Z�b�g���ĊJ�n" } : new WCHAR[MAX_LEN]{ L"Reset time and start timer when PC was unlocked" };
