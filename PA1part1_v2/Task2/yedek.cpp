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

  // std::cout << sizeof(iv) << std::endl;
  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  ctx = EVP_CIPHER_CTX_new();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
  ciphertext_len += len;
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}


int main(int argc, char* argv[])
{

	unsigned char * realkey = (unsigned char *) "key not found";
    std::ifstream input("ciphertext",std::ios::binary );
    std::vector<unsigned char> ciphertext(std::istreambuf_iterator<char>(input), {});

    std::ifstream input2("plaintext.txt",std::ios::binary );
    std::vector<unsigned char> plaintext(std::istreambuf_iterator<char>(input2), {});

	unsigned char * plaintextCharP = reinterpret_cast<unsigned char*>(plaintext.data());
	
	unsigned char * ciphertextCharP = reinterpret_cast<unsigned char*>(ciphertext.data());
	//std::cout<< plaintextCharP << std::endl;
	//std::cout<< ciphertextCharP << std::endl;
	//unsigned char  ourCiphertext[32] ;

	std::string line;
	std::ifstream dict("words.txt");
	if (dict.is_open())
	{
		while (!dict.eof() )
		{
			std::getline(dict,line);
		
			//unsigned char * key = makeWord16Again(line);
			unsigned char * result = const_cast<unsigned char *>( reinterpret_cast< const unsigned char*> (line.data()) );
			unsigned char  key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
			if(sizeof(result) <  16)
			{
			//		std::cout<< sizeof(result)<<std::endl;
				int val = sizeof(result);

				for (int i = 0; i < val; ++i)
				{
					key[i] = result[i];
				}
			}
			    
			//std::cout<<sizeof(key);
			unsigned char  iv[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
			int ciphertext_len = 0;
			unsigned char  ourCiphertext[32] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					// std::cout << plaintextCharP << std::endl ;
					// std::cout << plaintext.size()  << std::endl ;
					//std::cout << key << std::endl ;
					// std::cout << iv << std::endl ;
					ciphertext_len = encrypt(plaintextCharP, plaintext.size(), key, iv, ourCiphertext);
					//std::cout << ciphertextCharP << std::endl ;



				int state=1;
				for (int i = 0; i < 32; ++i)
				{
					if(ourCiphertext[i] != ciphertextCharP[i])
					{
						state = 0;
						break;
					}
				}
				if(state)
				{
					realkey = key;
					std::cout << realkey << std::endl ;

					break;
			 	}
			
				//std::cout << ourCiphertext << std::endl ;
		}	
		dict.close();
	}

	return 0;

}

