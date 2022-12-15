.ONESHELL:

all: reinit link-example

reinit: FORCE
	rm -rf .pio
	rm -rf CMakeLists.txt
	rm -rf CMakeListsPrivate.txt
	find . -type d -name "cmake-build-*" -exec rm -rf {} +
	platformio -c clion init --ide clion

erase-flash: FORCE
	platformio run --target erase

link-example: FORCE
	rm -f src/main.cpp
	ln examples/DualSenseControllerDemo/DualSenseControllerDemo.ino src/main.cpp


#
# Programs
#

.PHONY: FORCE
FORCE:
