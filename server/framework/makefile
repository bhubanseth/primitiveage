server.o: server.h server.cc base_handler.h network.pb.o
	g++ -std=c++11 -c server.h server.cc base_handler.h network.pb.o -lprotoc -lprotobuf -lpthread

client: client.cc fake_types.pb.o network.pb.o
	g++ -std=c++11 -o client  client.cc fake_types.pb.o network.pb.o -lprotoc -lprotobuf -lpthread

network.pb.o: network.pb.h network.pb.cc
	g++ -std=c++11 -c network.pb.h network.pb.cc -lprotoc -lprotobuf -lpthread

clean:
	rm server.o network.pb.o
