# RandomX Algorithm in XDAG



## Linux Requirements:

#### Install RandomX library

```bash
git clone https://github.com/tevador/RandomX.git
cd RandomX
mkdir build && cd build
cmake -DARCH=native ..
make
sudo make install
```

#### Enable huge pages

Temporary (until next reboot) reserve huge pages

```bash
sudo sysctl -w vm.nr_hugepages=1280
```

Permanent huge pages reservation

```bash
sudo bash -c "echo vm.nr_hugepages=1280 >> /etc/sysctl.conf"
```

- A miner using randomx hash needs 1280 huge pages, about 2.5 Gigabytes


The miner can't change PoW algorithm automatically.   So miner must start new version after algorithm fork manually.

## CPU RandowX Benchmark

```bash
DaggerMiner -cpu  -M -t <MINING_THREAD_NUMBER> 
```

## CPU RandowX Miner 

```bash
DaggerMiner -cpu  -p <POOL_ADDRESS>:<POOL_PORT> -t <MINING_THREAD_NUMBER> -a <WALLET_ADDRESS>
```

miner not support GPU yet.
