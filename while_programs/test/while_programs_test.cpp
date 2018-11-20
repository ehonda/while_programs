#include "gtest/gtest.h"

#include "while_programs.h"

namespace while_programs_test {

using namespace while_programs;

class WhileProgramsTest : public testing::Test {
protected:
	RegisterMemory mem_;
};

TEST_F(WhileProgramsTest, register_memory_test) {
	// mem: 0 0
	EXPECT_EQ(mem_.get(0), 0);
	EXPECT_EQ(mem_.get(1), 0);

	mem_.set(1, 1);
	// mem: 0 1
	EXPECT_EQ(mem_.get(0), 0);
	EXPECT_EQ(mem_.get(1), 1);

	mem_.set(1, 0);
	// mem: 0 0
	EXPECT_EQ(mem_.get(0), 0);
	EXPECT_EQ(mem_.get(1), 0);
}

TEST_F(WhileProgramsTest, elementary_program_skip) {
	// mem: 0
	const auto p = Skip();

	p(mem_);
	// mem: 0
	EXPECT_EQ(mem_.get(0), 0);
}

TEST_F(WhileProgramsTest, elementary_program_inc) {
	// mem: 0
	const auto p = Inc(0);

	p(mem_);
	// mem: 1
	EXPECT_EQ(mem_.get(0), 1);
}

TEST_F(WhileProgramsTest, elementary_program_dec) {
	// mem: 0
	const auto p = Dec(0);
	mem_.set(0, 1);
	// mem: 1
	
	p(mem_);
	// mem: 0
	EXPECT_EQ(mem_.get(0), 0);

	p(mem_);
	// mem: 0
	EXPECT_EQ(mem_.get(0), 0);
}

TEST_F(WhileProgramsTest, elementary_program_seq) {
	// mem: 0
	const auto p = Inc(0);
	const auto q = Seq(p, p);
	
	q(mem_);
	// mem: 2
	EXPECT_EQ(mem_.get(0), 2);
}

TEST_F(WhileProgramsTest, elementary_program_ifz) {
	// mem: 0 0
	const auto p = Inc(0);
	const auto q = Inc(1);
	const auto r = IfZ(0, p, q);

	r(mem_);
	// mem: 1 0
	EXPECT_EQ(mem_.get(0), 1);
	EXPECT_EQ(mem_.get(1), 0);

	r(mem_);
	// mem: 1 1
	EXPECT_EQ(mem_.get(0), 1);
	EXPECT_EQ(mem_.get(1), 1);
}

TEST_F(WhileProgramsTest, elementary_program_while) {
	mem_ = getInputMemory({ 3 });
	// mem: 0 3

	const auto p = Seq(Inc(0), Seq(Inc(0), Dec(1)));
	const auto q = While(1, p);

	q(mem_);
	// mem: 6 0
	EXPECT_EQ(mem_.get(0), 6);
	EXPECT_EQ(mem_.get(1), 0);
}

}
