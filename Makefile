OBJFILES := $(patsubst %.cxx,build/%.o,$(wildcard *.cxx))

build/LibRooCubicSpline.so: $(OBJFILES) build/splinedict.o | build
	$(CXX) $(shell root-config --ldflags --glibs) -lRooFitCore -lRooFit -shared $^ -o $@

build/%.o: %.cxx | build
	$(CXX) $(shell root-config --cflags) -I. -c $< -o $@

build/splinedict.o: build/splinedict.cxx | build
	$(CXX) $(shell root-config --cflags) -I. -c $< -o $@

build/splinedict.cxx: build/links | build
	cd build && rootcling -f splinedict.cxx Roo*.h LinkDef.h

build/links:
	cd build && ln -sf ../*.h .
	touch $@

build:
	mkdir -p build

test: build/LibRooCubicSpline.so
	python -c "import ROOT; ROOT.gSystem.Load('build/LibRooCubicSpline.so'); from ROOT import RooCubicSplineFun"

clean:
	rm -rf build

.PHONY: clean test
