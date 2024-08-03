# UART  

picocom --imap spchex,tabhex,crhex,lfhex,nrmhex,8bithex -b 9600 -r -l /dev/ttyUSB0  
picocom --flow none --baud 9600 --parity none --databits 8 --stopbits 1 --noreset --nolock --imap spchex,tabhex,crhex,lfhex,nrmhex,8bithex /dev/ttyUSB0
picocom --flow none --baud 9600 --parity none --databits 8 --stopbits 1 --noreset --nolock --echo /dev/ttyUSB0 
