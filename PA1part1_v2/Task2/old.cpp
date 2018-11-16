//  unsigned char * makeWord16Again(std::string line)
// {
// 	unsigned char * result = const_cast<unsigned char *>( reinterpret_cast< const unsigned char*> (line.data()) );
// 	unsigned char  x[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// 	if(sizeof(result) <  16)
// 	{
// 	//		std::cout<< sizeof(result)<<std::endl;
// 		int val = sizeof(result);

// 		for (int i = 0; i < 16-val; ++i)
// 		{
// 			x [i] = result[i];
// 		}

// 		//result+=bytes;
// 	}


// 	return x;
// }









			// for (int i = 0; i < ciphertext_len; ++i)
			// {
			// 	if(ciphertextCharP[i] != ourCiphertext[i])
			// 	{
			// 		std::cout << "our "<< ourCiphertext << "normal " << ciphertextCharP << std::endl ;

			// 		state == 0;
			// 		break;
			// 	}
			// }
			// // if(state)
			// // {
			// // 	realkey = key ;
			// // 	break;
			// // }