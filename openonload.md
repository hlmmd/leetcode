# Openonload

[源码下载地址](https://www.openonload.org/download.html)

## 安装依赖库

```text
sudo apt update
sudo apt install binutils gettext gawk gcc sed make \
bash  automake autoconf libtool autoconf libcap-dev
sudo apt-get install linux-headers-$(uname -r)
```

## 检查固件版本

```text
ethtool -i <interface>
qinrui@qinrui:~$ ethtool -i enp3s0f0np0
driver: sfc
version: 4.1
firmware-version: 3.3.0.6269
expansion-rom-version: 
bus-info: 0000:03:00.0
supports-statistics: yes
supports-test: yes
supports-eeprom-access: no
supports-register-dump: yes
supports-priv-flags: no
```

## 安装openonload及sfnettest

在/scripts目录下执行onload\_install脚本

```text
sudo ./onload_install
```

安装完成后，需要加载驱动。

```text
sudo onload_tool reload
```

下载sfnettest源码，并解压，编译。

```text
cd src
make
```

\#测试

先修改BIOS设置  
\* Enable Turbo Boost \(sometimes called Turbo Mode\).  
\* Enable CStates.  
\* Disable any of the following settings that are present:  
\* Virtualization Technology \(also called VT-d/VT-x\)  
\* IOMMU.

### 测试命令

```text
sudo onload --profile=latency-best taskset -c 1 ./sfnt-pingpong
sudo onload --profile=latency-best taskset -c 1 ./sfnt-pingpong \
--affinity "1;1" tcp 192.168.100.101
```

```text
sudo ./sfnt-pingpong
sudo ./sfnt-pingpong --affinity "1;1" tcp 192.168.100.101
```

```text
onload: Warning: CTPIO cut-through is enabled, but the link speed of some adapters could not be determined. If latency-sensitive traffic is using an adapter running at a speed other than 10GbE then use EF_CTPIO_MODE=sf for best results

```

