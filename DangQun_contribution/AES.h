///////////////////////////////
// http://mingcn.cnblogs.com //
//  xelz CopyRight (c) 2010  //
///////////////////////////////
//AES加解密源代码
//DATE:2014/8/26
//Author:凌绍清
//Abstract:
//		将加密密钥放在静态数组中,更改构造函数,直接用静态数组
//初始化密钥

#if !defined(AFX_AES_H__6BDD3760_BDE8_4C42_85EE_6F7A434B81C4__INCLUDED_)
#define AFX_AES_H__6BDD3760_BDE8_4C42_85EE_6F7A434B81C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <string>
using namespace std;

class AES  
{
public:
	
public:
	AES();		//密钥放在
	virtual ~AES();
	unsigned char* Cipher(unsigned char* input);
	unsigned char* InvCipher(unsigned char* input);
	void* Cipher(void* input, int length=0);
	void* InvCipher(void* input, int length);
	enum { ENC_LEN=16 };
private:
	static unsigned char Sbox[256];				//S-Box 加密用
	static unsigned char InvSbox[256];			//解密用
	unsigned char w[11][4][4];
	static unsigned char x_key[16];				//密钥
	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
	unsigned char FFmul(unsigned char a, unsigned char b);

	void SubBytes(unsigned char state[][4]);
	void ShiftRows(unsigned char state[][4]);
	void MixColumns(unsigned char state[][4]);
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

	void InvSubBytes(unsigned char state[][4]);
	void InvShiftRows(unsigned char state[][4]);
	void InvMixColumns(unsigned char state[][4]);

public:
	// 转换十六进制为字符显示
	void Hex2Str(string & src, string & dst);
	void Str2Hex(string & src, string & dst);
};

#endif // !defined(AFX_AES_H__6BDD3760_BDE8_4C42_85EE_6F7A434B81C4__INCLUDED_)
