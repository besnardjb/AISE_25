CC=gcc

all: pascontent content

pascontent: main.c
	cpp $^ -o ./pascontent.i
	$(CC) $^ -o $@

content: main.c
	cpp -DCONTENT $^ -o ./content.i
	$(CC) -DCONTENT $^ -o $@

clean:
	rm -fr content pascontent pascontent.i content.i
