PROJ_NAME := trabalhocg
SOURCE := $(shell find source/ -type f -name '*.cpp')
HEADER := $(shell find source/ -type f -name '*.hpp')
OBJECT := $(addprefix objects/,$(subst .cpp,.o,$(subst source/,,$(SOURCE))))

CXX := g++
STD_FLAGS := -std=c++11
GLUT_FLAGS := -lGL -lGLU -lglut
MAKEFLAGS += "-j -l $(shell grep -c ^processor /proc/cpuinfo) "

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
	@ mkdir -p objects/models
	@ mkdir -p objects/utils
	@ mkdir -p objects/controllers
	@ mkdir -p objects/models/camera
	@ mkdir -p objects/utils/others
	@ mkdir -p objects/utils/style
	@ mkdir -p objects/utils/gameShapes
	@ mkdir -p objects/utils/libs
	@ mkdir -p objects/utils/math
	@ mkdir -p objects/utils/shapes
	@ mkdir -p objects/utils/shapes/2d
	@ mkdir -p objects/utils/shapes/3d

clean:
	@ rm -rf ./objects/*.o $(PROJ_NAME)
	@ rm -rf ./objects/views
	@ rm -rf ./objects/models
	@ rm -rf ./objects/controllers
	@ rm -rf ./objects/models/camera
	@ rm -rf ./objects/utils/math
	@ rm -rf ./objects/utils/others
	@ rm -rf ./objects/utils/style
	@ rm -rf ./objects/utils/gameShapes
	@ rm -rf ./objects/utils/libs
	@ rm -rf ./objects/utils/shapes/2d
	@ rm -rf ./objects/utils/shapes/3d
	@ rm -rf ./objects/utils/shapes
	@ rm -rf ./objects/utils
	@ rmdir objects

run: all
	./$(PROJ_NAME)
