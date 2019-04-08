clean: 
	rm -rf $(shell find ./ -name "*.o")
	rm -rf ./caesar-cipher/caesar
	rm -rf ./hill-cipher/hill
	rm -rf ./DES/des
	rm -rf ./AES/aes
	rm -rf ./RSA/rsa