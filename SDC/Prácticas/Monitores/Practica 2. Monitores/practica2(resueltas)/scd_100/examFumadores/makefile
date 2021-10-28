.SUFFIXES:
.PHONY: x1, x2, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors -I.
hmonsrcs:= HoareMonitor.hpp HoareMonitor.cpp 

x1: estanquero_lento
	./$<
	
x2: intermediario
	./$<
	
estanquero_lento: estanquero_lento.cpp
	$(compilador) $(opcionesc) -o $@ $< HoareMonitor.cpp
intermediario: intermediario.cpp
	$(compilador) $(opcionesc) -o $@ $< HoareMonitor.cpp
	
clean:
	rm -f estanquero_lento intermediario
