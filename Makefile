ep1: main.o input.o vector_field.o vector_operations.o draw.o sphere.o
	g++ main.o vector_field.o input.o vector_operations.o draw.o sphere.o -lglut -o ep1
	
main.o: main.cpp draw.h vector_field.h input.h draw.h
	g++ -c main.cpp 
	
input.o: input.cpp input.h vector_field.h
	g++ -c input.cpp
	
vector_field.o: vector_field.cpp vector_field.h vector_operations.cpp
	g++ -c vector_field.cpp

vector_operations.o: vector_operations.cpp vector_operations.h  vector_field.h
	g++ -c vector_operations.cpp

draw.o: draw.cpp draw.h vector_field.h vector_operations.h
	g++ -c draw.cpp -lglut
sphere.o: sphere.cpp sphere.h vector_field.h
	g++ -c sphere.cpp
clean:
	rm -f *~ *.o ep1
