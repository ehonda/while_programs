#include "while_programs.h"

namespace while_programs {

// -------------------------------------------------------
// REGISTER MEMORY

Nat RegisterMemory::get(RegisterIndex i) const {
	if (const auto r_i = registers_.find(i); r_i != registers_.cend())
		return r_i->second;
	return Nat(0);
}

void RegisterMemory::set(RegisterIndex i, Nat n) {
	registers_[i] = n;
}

RegisterMemory getInputMemory(const std::vector<Nat>& input) {
	RegisterMemory m;
	for (std::size_t i = 0; i < input.size(); ++i)
		m.set(RegisterIndex(i + 1), input[i]);
	return m;
}

Nat readOutput(const RegisterMemory& m) {
	return m.get(RegisterIndex(0));
}

// -------------------------------------------------------


// -------------------------------------------------------
// WHILE PROGRAMS

Program::Program()
	: Program([](auto& m) {}, "", 0)
{
}

Program::Program(const Action& action, const std::string& desc, std::size_t size)
	: action_(action), desc_(desc), size_(size)
{
}

const std::string& Program::getDesc() const noexcept {
	return desc_;
}

std::size_t Program::getSize() const noexcept {
	return size_;
}

void Program::operator()(RegisterMemory & m) const {
	action_(m);
}

std::ostream& operator<<(std::ostream& os, const Program & p) {
	os << "p = " << p.getDesc() << std::endl
		<< "size = " << p.getSize();
	return os;
}

// -------------------------------------------------------

// -------------------------------------------------------
// ELEMENTARY PROGRAMS

Program Skip() {
	const auto action = [](auto&) {};
	const auto desc = "Skip";
	const std::size_t size = 1u;
	return Program(action, desc, size);
}

Program Inc(RegisterIndex i) {
	const auto action = 
		[i](RegisterMemory& m) { m.set(i, m.get(i) + 1); };
	const auto desc =
		"Inc " + std::to_string(i);
	const std::size_t size = 1u;

	return Program(action, desc, size);
}

Program Dec(RegisterIndex i) {
	const auto action = 
		[i](RegisterMemory& m) {
			if (const auto n_i = m.get(i); n_i > Nat(0))
				m.set(i, n_i - 1);
		};
	const auto desc =
		"Dec " + std::to_string(i);
	const std::size_t size = 1u;

	return Program(action, desc, size);
}

Program Seq(const Program& p, const Program& q) {
	const auto action =
		[p, q](RegisterMemory& m) { p(m); q(m); };
	const auto desc =
		"Seq (" + p.getDesc() + ") (" + q.getDesc() + ")";
	const std::size_t size = 1u + p.getSize() + q.getSize();

	return Program(action, desc, size);
}

Program IfZ(RegisterIndex i, const Program& p, const Program& q) {
	const auto action =
		[i, p, q](RegisterMemory& m) {
			if (m.get(i) == Nat(0))
				p(m);
			else
				q(m);
		};
	const auto desc =
		"IfZ " + std::to_string(i) 
		+ " (" + p.getDesc() + ") (" + q.getDesc() + ")";
	const std::size_t size = 1u + p.getSize() + q.getSize();

	return Program(action, desc, size);
}

Program While(RegisterIndex i, const Program& p) {
	const auto action =
		[i, p](RegisterMemory& m) {
			while (m.get(i) != 0)
				p(m);
		};
	const auto desc =
		"While " + std::to_string(i) + " (" + p.getDesc() + ")";
	const std::size_t size = 1u + p.getSize();

	return Program(action, desc, size);
}

// -------------------------------------------------------

}
