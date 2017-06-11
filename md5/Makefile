SRC_DIR = ./src
TEST_DIR = ./test
OBJ = md5.o test.o
CC = g++
all = md5_test

$(all): $(OBJ)
	$(CC) -o $(all) $(SRC_DIR)/* $(TEST_DIR)/*

md5.o:
	$(CC) -c $(SRC_DIR)/md5.cpp

test.o:
	$(CC) -c $(TEST_DIR)/test.cpp

clean:
	rm -f *.o
