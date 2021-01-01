# USART-PARSER-STM32F407

## How to run
### Clone the repository
```
git clone https://github.com/aTTiny73/USART-PARSER-STM32F407.git
```
### Cd into cloned repository and run upload.sh script
```
sh upload.sh
```
### Install picocom with command
```
sudo apt install picocom
```
### Connect USB/USART dongle pins RX->PA2 , TX->PA3 and plug in the dongle into PC, run the following command:
```
picocom /dev/ttyUSB0 -b 115200
```
