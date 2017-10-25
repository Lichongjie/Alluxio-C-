main: main.o JNIHelper.o Client.o FileOutStream.o FileInStream.o Client.o
	g++ -std=c++11  main.o JNIHelper.o FileOutStream.o FileInStream.o Client.o -o testjava  -lpthread -ljvm

main.o: main.cpp include/JNIHelper.h include/Client.hpp  /home/innkp/pasa/jsoncpp/include/json/json.h include/FileOutStream.h include/FileInStream.h
	g++ -std=c++11 -c main.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -I/home/innkp/pasa/jsoncpp/include -lpthread -o main.o

Client.o: src/Client.cpp include/Client.hpp include/Options.hpp include/Wire.hpp include/Exceptions.hpp include/JNIHelper.h include/FileOutStream.h include/FileInStream.h
	g++ -std=c++11 -c src/Client.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -I/home/innkp/pasa/jsoncpp/include -lpthread -o Client.o

FileOutStream.o: src/FileOutStream.cpp include/FileOutStream.h include/Exceptions.hpp include/JNIHelper.h
	g++ -std=c++11 -c src/FileOutStream.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -I/home/innkp/pasa/jsoncpp/include -lpthread -o FileOutStream.o

FileInStream.o: src/FileInStream.cpp include/FileInStream.h include/Exceptions.hpp include/JNIHelper.h
	g++ -std=c++11 -c src/FileInStream.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -I/home/innkp/pasa/jsoncpp/include -lpthread -o FileInStream.o

JNIHelper.o: src/JNIHelper.cpp include/JNIHelper.h
	g++ -std=c++11 -c src/JNIHelper.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -lpthread -o JNIHelper.o

Exceptions.o: include/Exceptions.hpp
	g++ -std=c++11 -c include/Exceptions.hpp -I/home/innkp/Alluxio-Cpp/include -o  Exceptions.o

Wire.o: include/Wire.hpp
	g++ -std=c++11 -c include/Wire.hpp -I/home/innkp/Alluxio-Cpp/include  -o Wire.o

Options.o: include/Options.hpp
	g++ -std=c++11 -c include/Options.hpp -I/home/innkp/Alluxio-Cpp/include  -o Options.o


