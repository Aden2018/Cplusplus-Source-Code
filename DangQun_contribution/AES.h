///////////////////////////////
// http://mingcn.cnblogs.com //
//  xelz CopyRight (c) 2010  //
///////////////////////////////
//AES�ӽ���Դ����
//DATE:2014/8/26
//Author:������
//Abstract:
//		��������Կ���ھ�̬������,���Ĺ��캯��,ֱ���þ�̬����
//��ʼ����Կ

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
	AES();		//��Կ����
	virtual ~AES();
	unsigned char* Cipher(unsigned char* input);
	unsigned char* InvCipher(unsigned char* input);
	void* Cipher(void* input, int length=0);
	void* InvCipher(void* input, int length);
	enum { ENC_LEN=16 };
private:
	static unsigned char Sbox[256];				//S-Box ������
	static unsigned char InvSbox[256];			//������
	unsigned char w[11][4][4];
	static unsigned char x_key[16];				//��Կ
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
	// ת��ʮ������Ϊ�ַ���ʾ
	void Hex2Str(string & src, string & dst);
	void Str2Hex(string & src, string & dst);
};

#endif // !defined(AFX_AES_H__6BDD3760_BDE8_4C42_85EE_6F7A434B81C4__INCLUDED_)
