PROJ_NAME := trabalhocg
SOURCE := $(shell find source/ -type f -name '*.cpp')
HEADER := $(shell find source/ -type f -name '*.hpp')
OBJECT := $(addprefix objects/,$(subst .cpp,.o,$(subst source/,,$(SOURCE))))

CXX := g++
STD_FLAGS := -std=c++11
GLUT_FLAGS := -lGL -lGLU -lglut

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJECT)
	$(CXX) $^ $(STD_FLAGS) $(GLUT_FLAGS) -o $@

objects/%.o: source/%.cpp
	$(CXX) $< -c -o $@

objects/%.o: source/views/%.cpp source/views/%.hpp
	$(CXX) $< -c -o $@

objects/%.o: source/utils/shapes/%.cpp source/utils/shapes/%.hpp
	$(CXX) $< -c -o $@

objects/%.o: source/utils/%.cpp source/utils/%.hpp
	$(CXX) $< -c -o $@

objFolder:
	@ mkdir -p objects
	@ mkdir -p objects/views
	@ mkdir -p objects/utils
	@ mkdir -p objects/utils/style
	@ mkdir -p objects/utils/linear
	@ mkdir -p objects/utils/shapes
	@ mkdir -p objects/utils/shapes/2d
	@ mkdir -p objects/utils/shapes/3d

clean:
	@ rm -rf ./objects/*.o $(PROJ_NAME)
	@ rm -rf ./objects/views
	@ rm -rf ./objects/utils/linear
	@ rm -rf ./objects/utils/style
	@ rm -rf ./objects/utils/shapes/2d
	@ rm -rf ./objects/utils/shapes/3d
	@ rm -rf ./objects/utils/shapes
	@ rm -rf ./objects/utils
	@ rmdir objects

run: all
	./$(PROJ_NAME)
