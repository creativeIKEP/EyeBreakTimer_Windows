#pragma once
#include<windows.h>
#define MAX_LEN 256


static LANGID lang = GetUserDefaultUILanguage();
static bool isJapanese = (lang == 0x0411);

static LPWSTR LANG_PAUSE = isJapanese ? new WCHAR[MAX_LEN]{ L"一時停止" } : new WCHAR[MAX_LEN]{ L"Pause" };
static LPWSTR LANG_RESTART = isJapanese ? new WCHAR[MAX_LEN]{ L"再開" } : new WCHAR[MAX_LEN]{ L"Restart" };
static LPWSTR LANG_SETTING = isJapanese ? new WCHAR[MAX_LEN]{ L"設定" } : new WCHAR[MAX_LEN]{ L"Setting" };
static LPWSTR LANG_EXIT = isJapanese ? new WCHAR[MAX_LEN]{ L"終了" } : new WCHAR[MAX_LEN]{ L"Exit" };

static LPWSTR LANG_TIMER_MESSAGE = isJapanese ? new WCHAR[MAX_LEN]{ L"分が経過しました。目を休憩させましょう。" } : new WCHAR[MAX_LEN]{ L"minutes have passed. Break your eyes." };

static LPWSTR LANG_SETTIME = isJapanese ? new WCHAR[MAX_LEN]{ L"設定時間" } : new WCHAR[MAX_LEN]{ L"SetTime" };
static LPWSTR LANG_MINUTES = isJapanese ? new WCHAR[MAX_LEN]{ L"分" } : new WCHAR[MAX_LEN]{ L"minutes" };
static LPWSTR LANG_LOCKEDPAUSE = isJapanese ? new WCHAR[MAX_LEN]{ L"PC画面ロック時にタイマーを一時停止" } : new WCHAR[MAX_LEN]{ L"Pause timer when PC was locked" };
static LPWSTR LANG_UNLOCKED_RESTART = isJapanese ? new WCHAR[MAX_LEN]{ L"PC画面ロック解除時にタイマーを再開" } : new WCHAR[MAX_LEN]{ L"Restart timer when PC was unlocked" };
static LPWSTR LANG_UNLOCKED_RESET = isJapanese ? new WCHAR[MAX_LEN]{ L"PC画面ロック解除時にタイマーをリセットして開始" } : new WCHAR[MAX_LEN]{ L"Reset time and start timer when PC was unlocked" };
