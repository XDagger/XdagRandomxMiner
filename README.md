# DaggerRandomxMiner
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FXDagger%2FXdagRandomxMiner.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FXDagger%2FXdagRandomxMiner?ref=badge_shield)

Stand-alone RandomX CPU/GPU miner for XDAG (Dagger coin)

This miner does not require files wallet.dat and dnet_key.dat. Storage folder is still necessary.

Using https://github.com/tevador/RandomX master@ac574e3

**Launch parameters:**

	1) CPU benchmark: DaggerMiner.exe -cpu -M -t 4
	
	2) CPU mining: DaggerMiner.exe -cpu -a <WALLET_ADDRESS> -p <POOL_ADDRESS> -t 8  
	
**The project supports Windows, Linux and Mac OS now.**   
**Binary file available for Window**  
[Download](https://github.com/XDagger/XdagRandomxMiner/releases/tag/v0.4)  


## How to build

## Windows:  
The project has  dependencies: Boost and OpenSSL
Boost and OpenSSL libraries are included by Nuget Manager and should be downloaded automatically.

Need special privilege called as SeLockMemoryPrivilege to use huge pages.

[Enable the Lock Pages in Memory Option (Windows)](https://msdn.microsoft.com/en-gb/library/ms190730.aspx)

On Windows 10 once you obtain the privilege, admin rights no longer required to use huge pages, but on Windows 7 admin rights always required.

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


## License
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FXDagger%2FXdagRandomxMiner.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2FXDagger%2FXdagRandomxMiner?ref=badge_large)