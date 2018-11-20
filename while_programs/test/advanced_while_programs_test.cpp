#include "gtest/gtest.h"

#include "advanced_while_programs.h"

namespace while_programs_test {

using namespace while_programs;

class AdvancedWhileProgramsTest : public testing::Test {
protected:
	void expectMemory(const std::vector<Nat>& values) const {
		for (std::size_t i = 0; i < values.size(); ++i)
			EXPECT_EQ(mem_.get(i), values[i]);
	}

	RegisterMemory mem_;
};

// -------------------------------------------------------
// ADDITION

TEST_F(AdvancedWhileProgramsTest, while_add_and_erase_test) {
	mem_ = getInputMemory({ 3 });
	const auto p = while_add_and_erase(0, 1);
	p(mem_);
	expectMemory({ 3, 0 });
}

TEST_F(AdvancedWhileProgramsTest, while_add_and_move_test) {
	mem_ = getInputMemory({ 3 });
	const auto p = while_add_and_move(0, 1, 2);
	p(mem_);
	expectMemory({ 3, 0, 3 });
}

TEST_F(AdvancedWhileProgramsTest, while_add_and_restore_test) {
	mem_ = getInputMemory({ 3 });
	const auto p = while_add_and_restore(0, 1, 2);
	p(mem_);
	expectMemory({ 3, 3, 0 });
}

TEST_F(AdvancedWhileProgramsTest, while_plus) {
	mem_ = getInputMemory({ 3, 2 });
	const auto p = while_plus();
	p(mem_);
	expectMemory({ 5, 0, 0 });
}

TEST_F(AdvancedWhileProgramsTest, while_sum) {
	mem_ = getInputMemory({ 2, 2, 3, 4 });
	const auto p = while_sum(4);
	p(mem_);
	expectMemory({ 11, 0, 0, 0, 0 });
}

// -------------------------------------------------------
// MULTIPLICATION

TEST_F(AdvancedWhileProgramsTest, while_multiply_test) {
	mem_ = getInputMemory({ 3, 2 });
	const auto p = while_multiply();
	p(mem_);
	expectMemory({ 6, 0, 0 });
}

// -------------------------------------------------------
// CONSTANTS

// Base b rep
TEST_F(AdvancedWhileProgramsTest, base_b_rep_throws_for_invalid_rep) {
	EXPECT_THROW(BaseBRepresentation(0, { }), std::invalid_argument);
	EXPECT_THROW(BaseBRepresentation(1, { }), std::invalid_argument);
	EXPECT_THROW(BaseBRepresentation(2, { 1, 0, 2 }), std::invalid_argument);
	// Leading zeros are not allowed (except for a single 0)
	EXPECT_THROW(BaseBRepresentation(2, { 0, 1, 1 }), std::invalid_argument);
}

TEST_F(AdvancedWhileProgramsTest, base_b_little_endian_rep) {
	const BaseBRepresentation rep(2, { 1, 1, 0, 0 });
	const BaseBRepresentation::LittleEndianRepresentation expected
		= { 0, 0, 1, 1 };
	const auto actual = rep.getLittleEndianRepresentation();
	EXPECT_EQ(actual, expected);
}

// Write constants
TEST_F(AdvancedWhileProgramsTest, while_constant_seq_test) {
	const auto p = while_write_constant_sequentually(5);
	p(mem_);
	expectMemory({ 5 });
}

TEST_F(AdvancedWhileProgramsTest, while_constant_base_b_test) {
	// 1100_2 = 12
	const auto p_2_12
		= while_write_constant_from_base_b_rep(
			{ 2, { 1, 1, 0, 0 } });
	p_2_12(mem_);
	expectMemory({ 12 });


	// 1120_3 = 42
	mem_ = RegisterMemory();
	const auto p_3_42
		= while_write_constant_from_base_b_rep(
			{ 3, { 1, 1, 2, 0} });
	p_3_42(mem_);
	expectMemory({ 42 });


	// 2626_7 = 1000
	mem_ = RegisterMemory();
	const auto p_7_1000
		= while_write_constant_from_base_b_rep(
			{ 7, { 2, 6, 2, 6} });
	p_7_1000(mem_);
	expectMemory({ 1000 });
}

// -------------------------------------------------------

}
