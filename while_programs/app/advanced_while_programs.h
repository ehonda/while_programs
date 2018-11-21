#pragma once

#include <vector>

#include "while_programs.h"

namespace while_programs {

// -------------------------------------------------------
// ADDITION

// Basic add functionality
Program while_add_and_erase(RegisterIndex add_to, RegisterIndex erase_from);
Program while_add_and_move(RegisterIndex add_to, RegisterIndex move_from,
	RegisterIndex move_to);
Program while_add_and_restore(RegisterIndex add_to, RegisterIndex add_from,
	RegisterIndex restore_from);

// Sum functions
Program while_plus();
Program while_sum(std::size_t n);

// -------------------------------------------------------
// MULTIPLICATION

Program while_multiply();
Program while_product(std::size_t n);

// -------------------------------------------------------
// CONSTANTS

// Base b representation of natural numbers
class BaseBRepresentation {
public:
	using BigEndianRepresentation = std::vector<Nat>;
	using LittleEndianRepresentation = std::vector<Nat>;

	BaseBRepresentation();
	BaseBRepresentation(Nat base, const BigEndianRepresentation& rep);

	Nat getBase() const noexcept;
	const BigEndianRepresentation& getBigEndianRepresentation() const noexcept;
	const LittleEndianRepresentation& getLittleEndianRepresentation() const noexcept;


private:
	const Nat base_;
	const BigEndianRepresentation rep_;
	LittleEndianRepresentation little_endian_rep_;
};

// Write constant programs
Program while_write_constant_sequentially(Nat n);
Program while_constant_from_factors(const std::vector<Nat>& factors);
Program while_write_constant_from_base_b_rep(const BaseBRepresentation& rep);

// -------------------------------------------------------


}
