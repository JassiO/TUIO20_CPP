ENDIANESS=OSC_HOST_LITTLE_ENDIAN
PLATFORM=$(shell uname)

LD_FLAGS = -lGL -lGLU -lglut
SDL_FLAGS = -lSDL

TUIO_DEMO = Tuio2Demo
TUIO_DUMP = Tuio2Dump
TUIO_SIMULATOR = Tuio2Simulator
TUIO_TEST = Tuio2Test
TUIO_STATIC  = libTUIO2.a
TUIO_SHARED  = libTUIO2.so

INCLUDES = -I../TUIO2 -I../oscpack
#CFLAGS  = -g -Wall -O3 -fPIC
CFLAGS  =  -w -O3 -fPIC
CXXFLAGS = $(CFLAGS) $(INCLUDES) -D$(ENDIANESS)
SHARED_OPTIONS = -shared -Wl,-soname,$(TUIO_SHARED)

ifeq ($(PLATFORM), Darwin)
	CC = gcc
	CXX = g++ -stdlib=libstdc++
	CFLAGS += -mmacosx-version-min=10.5 -arch i386 -arch x86_64
	CXXFLAGS += -mmacosx-version-min=10.5 -arch i386 -arch x86_64
	TUIO_SHARED  = libTUIO.dylib
	LD_FLAGS = -framework OpenGL -framework GLUT -framework SDL -framework Cocoa
	SDL_FLAGS = 
 	SHARED_OPTIONS = -dynamiclib -Wl,-dylib_install_name,$(TUIO_SHARED)
	OBJC_SOURCES = SDLMain.m
	OBJC_OBJECTS = SDLMain.o
	SDL_LDFLAGS =
endif

DEMO_SOURCES = Tuio2Demo.cpp $(OBJC_SOURCES)
DEMO_OBJECTS = Tuio2Demo.o $(OBJC_OBJECTS)
DUMP_SOURCES = Tuio2Dump.cpp
DUMP_OBJECTS = Tuio2Dump.o
TEST_SOURCES = Tuio2Test.cpp
TEST_OBJECTS = Tuio2Test.o
SIMULATOR_SOURCES = Tuio2Simulator.cpp $(OBJC_SOURCES)
SIMULATOR_OBJECTS = Tuio2Simulator.o $(OBJC_OBJECTS)

COMMON_TUIO_SOURCES = ../TUIO2/TuioTime.cpp ../TUIO2/TuioPoint.cpp ../TUIO2/TuioObject.cpp ../TUIO2/TuioComponent.cpp ../TUIO2/TuioToken.cpp ../TUIO2/TuioPointer.cpp ../TUIO2/TuioBounds.cpp ../TUIO2/TuioSymbol.cpp ../TUIO2/TuioDispatcher.cpp ../TUIO2/TuioManager.cpp 
SERVER_TUIO_SOURCES = ../TUIO2/TuioServer.cpp ../TUIO2/UdpSender.cpp ../TUIO2/TcpSender.cpp ../TUIO2/FlashSender.cpp ../TUIO2/WebSockSender.cpp
CLIENT_TUIO_SOURCES = ../TUIO2/TuioClient.cpp ../TUIO2/OscReceiver.cpp ../TUIO2/UdpReceiver.cpp ../TUIO2/TcpReceiver.cpp
OSC_SOURCES = ../oscpack/osc/OscTypes.cpp ../oscpack/osc/OscOutboundPacketStream.cpp ../oscpack/osc/OscReceivedElements.cpp ../oscpack/osc/OscPrintReceivedElements.cpp ../oscpack/ip/posix/NetworkingUtils.cpp ../oscpack/ip/posix/UdpSocket.cpp

COMMON_TUIO_OBJECTS = $(COMMON_TUIO_SOURCES:.cpp=.o)
SERVER_TUIO_OBJECTS = $(SERVER_TUIO_SOURCES:.cpp=.o)
CLIENT_TUIO_OBJECTS = $(CLIENT_TUIO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
OSC_OBJECTS = $(OSC_SOURCES:.cpp=.o)

all: dump demo simulator static shared test

static:	$(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS)
	ar rcs $(TUIO_STATIC) $(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS)

shared:	$(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS)
	$(CXX) $+ -lpthread $(SHARED_OPTIONS) -o $(TUIO_SHARED)
	
dump:	$(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(OSC_OBJECTS) $(DUMP_OBJECTS)
	$(CXX) $+ -lpthread -o $(TUIO_DUMP)

demo:	$(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(OSC_OBJECTS) $(DEMO_OBJECTS)
	$(CXX) $+ -lpthread -o $(TUIO_DEMO) $(LD_FLAGS) $(SDL_FLAGS)

simulator:	$(COMMON_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS) $(SIMULATOR_OBJECTS)
	$(CXX) $+ -lpthread -o $(TUIO_SIMULATOR) $(LD_FLAGS) $(SDL_FLAGS)

test:	$(COMMON_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $+ -lpthread -o $(TUIO_TEST) $(SDL_LDFLAGS) $(LD_FLAGS)

clean:
	rm -f $(TUIO_DUMP) $(TUIO_DEMO) $(TUIO_SIMULATOR) $(TUIO_TEST) $(TUIO_STATIC) $(TUIO_SHARED) 
	rm -f $(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(TEST_OBJECTS) $(OSC_OBJECTS) $(DUMP_OBJECTS) $(DEMO_OBJECTS) $(SIMULATOR_OBJECTS)
