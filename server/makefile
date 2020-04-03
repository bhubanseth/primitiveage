LLIBS = -lprotoc -lprotobuf -lpthread

primitiveage_server: primitiveage_server.cc fake_types.pb.o $(SUBDIRS)
	(make -C framework; g++ -std=c++11 -o primitiveage_server primitiveage_server.cc framework/server.o fake_types.pb.o framework/network.pb.o $(LLIBS))

client: client.cc fake_types.pb.o framework/network.pb.o
	(make -C framework network.pb.o; g++ -std=c++11 -o client  client.cc fake_types.pb.o framework/network.pb.o $(LLIBS))

fake_types.pb.o: fake_types.pb.h fake_types.pb.cc
	g++ -std=c++11 -c fake_types.pb.h fake_types.pb.cc -lprotoc -lprotobuf -lpthread
