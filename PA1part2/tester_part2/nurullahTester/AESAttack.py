import sys
import vulnerable as v
def main():
	#ciphertext = v.encr(sys.argv[1])
	#print(sys.argv)
	ciphertext = sys.argv[1] 
	desPlain = sys.argv[2]
	#print(ciphertext)
	#print(desPlain)
	T = ['']*16
	i = 0
	val = 31
	k = 15
	#print(ciphertext[0:31]+chr(i))
	xorVal = 1
	state = 0
	newfor = 15
	newXor = 2
	newVal=31
	whileval = len(desPlain)+0

	lastCipher = sys.argv[1]
	while(val>15):
		#print(val)
		i = 0
		if(state):
			# newXor = 2	
			newfor = 15
			newVal = 31
			for x in range(0,31-val):	
				new = list(ciphertext)
				new[newVal] = chr( T[newfor] ^ newXor)
				ciphertext = ''.join(new)
				newfor = newfor - 1 
				newVal = newVal - 1			
		#ciphertext[val+1] = chr( T[k+1] ^ xorVal)
			newXor = newXor + 1
		temp = ciphertext[val] 
		while(i<256):
			new = list(ciphertext)
			new[val] = chr(i)
			ciphertext = ''.join(new)
			#print(ciphertext[0:32])
			#print(''.join(new))
			if(v.decr(ciphertext) == "SUCCESS" and ord(temp) != i):
				# print(xorVal)
				# print(k)
				# print(temp)
				T[k] = ord(chr(i)) ^ xorVal
				xorVal = xorVal + 1 
 				k = k-1 
 				state=1 
				break
			elif(i==255):
				T[k] = ord(temp) ^ xorVal
				#sys.stderr.write(str(ord(temp))+"\n")
				xorVal = xorVal + 1 
 				k = k-1
 				state = 1  
			i = i + 1
		val = val - 1

	i = 0
	retCipher = ciphertext[0:32]
	
	desPlain = desPlain + chr(1)
	lastVal = len(desPlain)
	ind = 32-len(desPlain)
	tind = 0
	while(lastVal > 0):
		new = list(ciphertext)
		new[ind] = chr(T[16-lastVal]^ord(desPlain[tind]))
		ciphertext = ''.join(new)
		tind= tind+1
		ind = ind +1
		lastVal= lastVal -1
		#chiphertext=ciphertext[32-len(desPlain):32]^T[16-len(desPlain):16]

	#sys.stderr.write(str(T))
	result = lastCipher[0:32-len(desPlain)] + ciphertext[32-len(desPlain):32] +lastCipher[32:]
	sys.stdout.write(result)

	#print("0000000000000000")
	return result


#print(main())
main()