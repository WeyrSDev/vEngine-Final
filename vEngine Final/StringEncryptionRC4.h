#pragma once
#include "stdafx.h"

namespace vEngine {
	class StringEncryptionRC4
	{
	public:
		StringEncryptionRC4(void);
		~StringEncryptionRC4(void);
	public:
		void KeySchedulingAlgorithm(std::string key);
		char PseudoRandomGenerationAlgorithm();
		std::string Encrypt(std::string plainText);
	private:
		int m_String[256];
		int m_Key[256];
		int i;
		int j;
	};
	static void Swap(int* S, int a, int b);
}