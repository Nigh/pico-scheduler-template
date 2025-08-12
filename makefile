

BUILD_DIR = build


.PHONY: clean default build rebuild

default: build

build:
	docker run --rm -v ${PWD}:/workspace xianii/pico-sdk:latest /bin/bash -c "cmake . -G Ninja -Bbuild -S. && ninja -C build"

clean:
	@if [ -d "./$(BUILD_DIR)" ]; then rm ./$(BUILD_DIR) -rf; fi

rebuild: clean build

format:
	bash format.sh
