main: main.o JNIHelper.o
	g++ -std=c++11  main.o JNIHelper.o -o testjava  -lpthread -ljvm

main.o: main.cpp include/JNIHelper.h
	g++ -std=c++11 -c main.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include -lpthread

JNIHelper.o: src/JNIHelper.cpp include/JNIHelper.h
	g++ -std=c++11 -c src/JNIHelper.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -lpthread
