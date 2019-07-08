objects=Main.o Class_vector.o Class_matrix.o Class_diode.o Function_diode_evolving.o Function_steady_state_evaluating.o Function_random_number_generating.o
Main: $(objects)
	g++ -std=c++11 -o Main $(objects) -lgsl -lgslcblas
Main.o: Main.cpp Class_vector.h Class_matrix.h Class_diode.h
	g++ -std=c++11 -c Main.cpp
Class_vector.o: Class_vector.cpp Class_matrix.h
	g++ -std=c++11 -c Class_vector.cpp
Class_matrix.o: Class_matrix.cpp Class_vector.h
	g++ -std=c++11 -c Class_matrix.cpp
Class_diode.o: Class_diode.cpp Class_vector.h Class_matrix.h
	g++ -std=c++11 -c Class_diode.cpp
Function_diode_evolving.o: Function_diode_evolving.cpp Class_vector.h Class_matrix.h Class_diode.h
	g++ -std=c++11 -c Function_diode_evolving.cpp
Function_steady_state_evaluating.o: Function_steady_state_evaluating.cpp Class_vector.h Class_matrix.h Class_diode.h 
	g++ -std=c++11 -fopenmp -c Function_steady_state_evaluating.cpp
Function_random_number_generating.o: Function_random_number_generating.cpp
	g++ -std=c++11 -fopenmp -c Function_random_number_generating.cpp
clean:
	rm -rf $(objects)
