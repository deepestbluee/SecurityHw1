#include <openssl/evp.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>    
#include <fstream>
#include <iterator>
#include <vector>
#include <cstring>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>



int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  ctx = EVP_CIPHER_CTX_new();

  EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);


  EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
  ciphertext_len = len;

  EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
  ciphertext_len += len;
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}


int main(int argc, char* argv[])
{

	std::string realkey = "key not found";
    std::ifstream input("ciphertext",std::ios::binary );
    std::vector<unsigned char> ciphertext(std::istreambuf_iterator<char>(input), {});

    std::ifstream input2("plaintext.txt",std::ios::binary );
    std::vector<unsigned char> plaintext(std::istreambuf_iterator<char>(input2), {});

	unsigned char * plaintextCharP = reinterpret_cast<unsigned char*>(plaintext.data());
	
	unsigned char * ciphertextCharP = reinterpret_cast<unsigned char*>(ciphertext.data());

	std::string line;
	std::ifstream dict("words.txt");
	if (dict.is_open())
	{
		while (!dict.eof() )
		{
			std::getline(dict,line);
		
			unsigned char  key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
			if(line.length() <=  16)
			{
				int val = line.length();

				for (int i = 0; i < val; ++i)
				{
					key[i] = line[i];
				}
			}
			    
				unsigned char  iv[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
				int ciphertext_len = 0;
				// unsigned char  ourCiphertext[32] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
				unsigned char  ourCiphertext[plaintext.size()+16] = {0};

				ciphertext_len = encrypt(plaintextCharP, plaintext.size(), key, iv, ourCiphertext);

				int state=1;
				for (int i = 0; i < ciphertext.size(); ++i)
				{
					if(ourCiphertext[i] != ciphertextCharP[i])
					{	
						state = 0;
						break;
					}
				}
				if(state)
				{
					realkey = line;
					break;
			 	}
			
		}	
		dict.close();
		std::cout << realkey << std::endl ;
	}



	return 0;

}

