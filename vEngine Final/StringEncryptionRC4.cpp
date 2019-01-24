#include "stdafx.h"

namespace vEngine {
	StringEncryptionRC4::StringEncryptionRC4(void) : j(0), i(0)
	{
	}
	StringEncryptionRC4::~StringEncryptionRC4(void)
	{
	}
	void StringEncryptionRC4::KeySchedulingAlgorithm(std::string key)
	{
		int length = key.size();
		int a = 0;

		for (int x = 0; x < 256; x++)
		{
			m_String[x] = x;
			m_Key[x] = key[a];
			a++;
			if (a > length - 1)
				a = 0;
		}

		for (int x = 0; x < 256; x++)
		{
			a = (a + m_String[x] + m_Key[x]) % 256;
			Swap(m_String, x, a);
		}
	}
	char StringEncryptionRC4::PseudoRandomGenerationAlgorithm()
	{
		i = (i + 1) % 256;
		j = (j + m_String[i]) % 256;

		Swap(m_String, i, j);

		int index = (m_String[i] + m_String[j]) % 256;
		char c = m_String[index];
		return c;
	}
	std::string StringEncryptionRC4::Encrypt(std::string plainText)
	{
		int length = plainText.size();
		std::string cipher = plainText;
		char c;
		for (int x = 0; x <= length; x++)
		{
			c = PseudoRandomGenerationAlgorithm();
			cipher[x] = cipher[x] ^ c;
		}

		return cipher;
	}

	// helper function
	static void Swap(int* S, int a, int b)
	{
		int tmp = S[a];
		S[a] = S[b];
		S[b] = tmp;
	}

}