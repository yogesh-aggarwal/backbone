format:
	@find ./source ./cmd -name '*.cpp' -or -name '*.hpp' -exec clang-format -i {} +

clean:
	@rm -rf build/
