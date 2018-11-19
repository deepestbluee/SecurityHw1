import sys
import vulnerable as v
def main():
	print(sys.argv)
	print(v.encr(sys.argv[1]))
	ciphertext = sys.argv[1]
	desPlain = sys.argv[2]
	print(ciphertext)
	print(desPlain)
	state = 1
	i = 0
	val = 31
	print(ciphertext[:31]+chr(i))
	while(val>15):
		while(i<255):
			if(v.decr(ciphertext[:31]+chr(i)) == "SUCCESS" and ciphertext[val] != chr(i)):
				state = ord(i)
			i = i + 1
		val = val - 1
	print(state)
main()
