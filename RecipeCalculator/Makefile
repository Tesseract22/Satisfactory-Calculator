CXX=g++
CXX_FLAGS=-std=c++17 -Iincludes
exec: bin/exec
SAN = -fsanitize=address,null -fno-omit-frame-pointer
bin/exec: src/main.cc src/Readers.cc src/satisfactory.cc
	$(CXX) $(CXX_FLAGS) -o bin/exec src/main.cc src/Readers.cc src/satisfactory.cc $(SAN)

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -f bin/*
