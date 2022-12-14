.ONESHELL:

all: reinit

reinit: FORCE
	rm -rf .pio
	rm -rf CMakeLists.txt
	rm -rf CMakeListsPrivate.txt
	find . -type d -name "cmake-build-*" -exec rm -rf {} +
	platformio -c clion init --ide clion

erase-flash: FORCE
	platformio run --target erase

#
# Programs
#

.PHONY: FORCE
FORCE:
