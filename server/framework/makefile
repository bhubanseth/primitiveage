CC=g++
CFLAGS=-I.
primitiveage_server: server.cc server.h primitiveage_server.cc fake_types.pb.h fake_types.pb.cc
	$(CC) -std=c++11 primitiveage_server.cc server.h server.cc -o primitiveage_server fake_types.pb.h fake_types.pb.cc -lprotoc -lprotobuf -lpthread 
client: client.cc fake_types.pb.h fake_types.pb.cc
	$(CC) -std=c++11 -o client  client.cc fake_types.pb.h fake_types.pb.cc -lprotoc -lprotobuf -lpthread
base_handler.o: base_handler.h base_handler.cc
	$(CC) -std=c++11 -c base_handler.cc base_handler.h -o base_handler.o

