ep1: main.o input.o vector_field.o
	g++ main.o vector_field.o input.o -o ep1
	
main.o: main.cpp vector_field.h input.h
	g++ -c main.cpp
	
input.o: input.cpp input.h vector_field.h
	g++ -c input.cpp
	
vector_field.o: vector_field.cpp vector_field.h
	g++ -c vector_field.cpp

clean:
	rm -f *~ *.o ep1
