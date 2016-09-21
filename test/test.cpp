#include "carriage.h"
#include "carriage_buffers.h"
#include "carriage_dispatcher.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
using namespace XXYY;
TEST_CASE("Test for Carriage", "[Carriage]") {
	Carriage a(10, 1);
	REQUIRE(a.index == 1);
	REQUIRE(a.destination == 10);
}
TEST_CASE("Test for CarriageBuffer", "[CarriageBuffer]") {
	CarriageBuffers a(0);
	Carriage c(10, 1);
	SECTION("test Push & allocate function") {
		for (int i = 0; i < 10; i++) {
			c.index = i;
			c.destination = 10-i;
			a.Push(c);
		}
		REQUIRE(a.size() == 10);
    }
	SECTION("test buffer function") {
		REQUIRE(a.size() == 0);
		REQUIRE(a.Buffer(0) == nullptr);
		for (int i = 0; i < 10; i++) {
			c.index = i;
			c.destination = 10-i;
			a.Push(c);
		}
		REQUIRE(a.Buffer(0) != nullptr);
	}
	SECTION("test popsome & popall function II") {
		for (int i = 0; i < 10; i++) {
			c.index = 10-i;
			c.destination = i;
			a.Push(c);
		}
		REQUIRE(a.size() == 1);
	}
}
TEST_CASE("Test for carriage_dispatcher", "[CarriageDipatcher]") {
	int a1[4] = {1, 3, 2, 4};
	int a2[4] = {4, 3, 2, 1};
	std::vector<uint32_t> a(a1, a1+4);
	CarriageDipatcher x(a);
	x.ContinueFor(100);
	REQUIRE(x.buffers_used() == 2);
	std::vector<uint32_t> b(a2, a2+4);
	CarriageDipatcher y(b);
	y.ContinueFor(100);
	REQUIRE(y.buffers_used() == 1);
}
// int main() {
// XXYY::Carriage a(10,10);
// return 0;
// 随机数组
// carriage测试 构造函数
// carriage_buffers测试 push popsome popall buffer size
// push->size
// popsome->size
// buffer 越界与合法
// popall->size
// carriage_dispatcher测试 Nextstep continuefor buffer
// 构造 vector
// continuefor & Nextstep 防止空的情况 直到empty
// buffer 越界与合法
// 检测合理性
// }