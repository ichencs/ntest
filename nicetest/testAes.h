#pragma once
#include <iostream>
#include <bitset>
#include <string>

using namespace std;
typedef bitset<8> nbyte;
typedef bitset<32> word;

const int Nr = 10;  // AES-128需要 10 轮加密
const int Nk = 4;   // Nk 表示输入密钥的 word 个数

class testAes
{
public:
	testAes();
	~testAes();
public:
	void test();
	void SubBytes(nbyte mtx[4 * 4]);
	void ShiftRows(nbyte mtx[4 * 4]);
	nbyte GFMul(nbyte a, nbyte b);
	void MixColumns(nbyte mtx[4 * 4]);
	void AddRoundKey(nbyte mtx[4 * 4], word k[4]);
	void InvSubBytes(nbyte mtx[4 * 4]);
	void InvShiftRows(nbyte mtx[4 * 4]);
	void InvMixColumns(nbyte mtx[4 * 4]);
	word Word(nbyte& k1, nbyte& k2, nbyte& k3, nbyte& k4);
	word RotWord(word& rw);
	word SubWord(word& sw);
	void KeyExpansion(nbyte key[4 * Nk], word w[4 * (Nr + 1)]);
	void encrypt(nbyte in[4 * 4], word w[4 * (Nr + 1)]);
	void decrypt(nbyte in[4 * 4], word w[4 * (Nr + 1)]);

};

