CC = g++ -g -std=c++11 
CFLAGS  = -g -Wall

vaccineMonitor: main.o helpers.o person.o skip-list.o linkedList.o hashTable.o bloom-filter.o date.cpp

	$(CC) $(CFLAGS) -o vaccineMonitor helpers.o main.o person.o skip-list.o linkedList.o hashTable.o bloom-filter.o date.o

main.o: main.cpp helpers.cpp

	$(CC) $(CFLAGS) -c main.cpp helpers.cpp

helpers.o: helpers.cpp skip-list.cpp linkedList.cpp person.cpp hashTable.cpp bloom-filter.cpp date.cpp person.cpp

	$(CC) $(CFLAGS) -c helpers.cpp skip-list.cpp person.cpp linkedList.cpp hashTable.cpp bloom-filter.cpp date.cpp person.cpp

skip-list.o: skip-list.cpp linkedList.cpp person.cpp bloom-filter.cpp date.cpp 

	$(CC) $(CFLAGS) -c skip-list.cpp linkedList.cpp person.cpp bloom-filter.cpp date.cpp

linkedList.o: linkedList.cpp person.cpp bloom-filter.cpp

	$(CC) $(CFLAGS) -c linkedList.cpp person.cpp bloom-filter.cpp

hashTable.o: hashTable.cpp person.cpp linkedList.cpp

	$(CC) $(CFLAGS) -c hashTable.cpp person.cpp bloom-filter.cpp

person.o: person.cpp date.cpp

	$(CC) $(CFLAGS) -c person.cpp date.cpp

bloom-filter.o: bloom-filter.cpp

	$(CC) $(CFLAGS) -c bloom-filter.cpp

date.o: date.cpp

	$(CC) $(CFLAGS) -c date.cpp
clean: 

	rm -rf *.o

run:
	./vaccineMonitor -c inputFile.txt -b 100000

bash:
	: > inputFile.txt
	./testFile.sh countriesFile.txt virusesFile.txt 2500 NO

