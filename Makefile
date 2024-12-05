start:
	@RUST_BACKTRACE=1 cargo run

build:
	@cargo build

release:
	@cargo build --release
