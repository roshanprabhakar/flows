CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17 -g
SRCDIR = src
BUILDDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/gates/*.cpp) $(wildcard $(SRCDIR)/components/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES)) \
          $(patsubst $(SRCDIR)/gates/%.cpp,$(BUILDDIR)/gates/%.o,$(wildcard $(SRCDIR)/gates/*.cpp)) \
          $(patsubst $(SRCDIR)/components/%.cpp,$(BUILDDIR)/components/%.o,$(wildcard $(SRCDIR)/components/*.cpp))
TARGET = hdl

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/gates
	mkdir -p $(BUILDDIR)/components

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/gates/%.o: $(SRCDIR)/gates/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/components/%.o: $(SRCDIR)/components/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
