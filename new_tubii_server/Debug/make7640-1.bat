@echo off
arm-xilinx-linux-gnueabi-gcc -L"C:\Users\Ian\Documents\GitHub\workspace_tubii\new_tubii_server\src" -o "new_tubii_server.elf"  ./src/adlist.o ./src/ae.o ./src/ae_epoll.o ./src/anet.o ./src/async.o ./src/blocked.o ./src/data.o ./src/db.o ./src/dict.o ./src/hiredis.o ./src/logging.o ./src/net.o ./src/networking.o ./src/read.o ./src/sds.o ./src/server.o ./src/sha1.o ./src/sock.o ./src/tubii-server.o ./src/tubii_client.o ./src/util.o   -lm -lpthread -lpq