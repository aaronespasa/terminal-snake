.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

snake:
	cd build && \
	cmake .. && \
	make && \
	cd .. && \
	./build/snake