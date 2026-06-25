CC = gcc
CFLAGS = -Wall -Wextra -g

FLEX = flex
BISON = bison

TARGET = betac

all: $(TARGET) 

parser.tab.h parser.tab.c: parser.y
	$(BISON) -d -v parser.y

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

$(TARGET): parser.tab.c lex.yy.c ast.c munch.c liveness.c main.c
	$(CC) $(CFLAGS) parser.tab.c lex.yy.c ast.c munch.c liveness.c main.c -o $(TARGET) -lfl

clean:
	rm -f $(TARGET) parser.tab.c parser.tab.h lex.yy.c parser.output
	rm -f *.o

run: $(TARGET)
	./$(TARGET) test.c
