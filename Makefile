BUILD_DIR := build

all: clean build

format:
	@find ./source ./cmd \( -name '*.cpp' -or -name '*.hpp' -or -name '*.tcc' \) -exec clang-format -i {} +

clean:
	@rm -rf $(BUILD_DIR)

generate:
	@cmake -B $(BUILD_DIR) -S .

build: generate
	@cmake --build $(BUILD_DIR) --config Release
