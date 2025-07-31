BUILD_DIR := build

.PHONY: all test clean

all:
	@rm -rf ${BUILD_DIR}
	@mkdir -p ${BUILD_DIR}
	@cmake -S . -B ${BUILD_DIR}
	@cmake --build ${BUILD_DIR} --target Robopro -j$(shell nproc)

test:
	@rm -rf ${BUILD_DIR}
	@mkdir -p ${BUILD_DIR}
	@cmake -S . -B ${BUILD_DIR}
	@cmake --build ${BUILD_DIR} --target robotmath_test -j$(shell nproc)
	@ctest --test-dir ${BUILD_DIR} --output-on-failure

clean:
	@rm -rf ${BUILD_DIR}

valgrind:
	@rm -rf ${BUILD_DIR}
	@mkdir -p ${BUILD_DIR}
	@cmake -S . -B ${BUILD_DIR}
	@cmake --build ${BUILD_DIR} --target robotmath_test -j$(shell nproc)
	valgrind --leak-check=full --track-origins=yes \
	         --error-exitcode=1 \
	         ${BUILD_DIR}/bin/tests/robotmath_test