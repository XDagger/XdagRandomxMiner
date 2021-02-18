# DaggerRandomxMiner
Stand-alone RandomX CPU/GPU miner for XDAG (Dagger coin)

This miner does not require files wallet.dat and dnet_key.dat. Storage folder is still necessary.

Using https://github.com/tevador/RandomX master@ac574e3

**Launch parameters:**

	1) CPU benchmark: DaggerMiner.exe -cpu -M -t 4
	
	2) CPU mining: DaggerMiner.exe -cpu -a <WALLET_ADDRESS> -p <POOL_ADDRESS> -t 8  
	
**The project supports Windows, Linux and Mac OS now.**   
**Binary file available for Window**  
[Download](https://github.com/swordlet/DaggerRandomxMiner/releases/tag/Pre_0.4.0)  


## How to build

## Windows:  
The project has  dependencies: Boost and OpenSSL
Boost and OpenSSL libraries are included by Nuget Manager and should be downloaded automatically.

### Launch parameters:

	1) CPU benchmark: DaggerMiner.exe -cpu -M -t 4
	
	2) CPU mining: DaggerMiner.exe -cpu -a <WALLET_ADDRESS> -p <POOL_ADDRESS> -t 8  


## Linux:

Check dependencies: libboost-dev, libboost-system-dev, openssl, librandomx.  

Download this source code, then cd to source folder. Build with cmake.

### Launch parameters:

	1) CPU benchmark: ./DaggerMiner -cpu -M -t 4
	
	2) CPU mining: ./DaggerMiner -cpu -a <WALLET_ADDRESS> -p <POOL_ADDRESS> -t 8
	

## Mac:  
Install Boost with brew.  
Open XCode project to build Mac OS version.  

### Launch parameters:
	1) CPU benchmark: ./DaggerMiner -cpu -M -t 4
	
	2) CPU mining: ./DaggerMiner -cpu -a <WALLET_ADDRESS> -p <POOL_ADDRESS> -t 8



**This miner not support GPU yet.**