#pragma once

#include <functional>
#include <map>
#include <ostream>
#include <string>

namespace while_programs {

// -------------------------------------------------------
// REGISTER MEMORY

using Nat = unsigned;
using RegisterIndex = unsigned;

// TODO: implement operator==
class RegisterMemory {
public:
	Nat get(RegisterIndex i) const;
	void set(RegisterIndex i, Nat n);

private:
	std::map<RegisterIndex, Nat> registers_;
};

RegisterMemory getInputMemory(const std::vector<Nat>& input);
Nat readOutput(const RegisterMemory& m);

// -------------------------------------------------------


// -------------------------------------------------------
// WHILE CLASS

using Action = std::function<void(RegisterMemory&)>;

class Program {
public:
	Program();
	Program(const Action& action, const std::string& desc, std::size_t size);

	const std::string& getDesc() const noexcept;
	std::size_t getSize() const noexcept;
	void operator()(RegisterMemory& m) const;

private:
	const Action action_;
	const std::string desc_;
	const std::size_t size_;
};

std::ostream& operator<<(std::ostream& os, const Program& p);

// -------------------------------------------------------
// ELEMENTARY PROGRAMS

Program Skip();
Program Inc(RegisterIndex i);
Program Dec(RegisterIndex i);
Program Seq(const Program& p, const Program& q);
Program IfZ(RegisterIndex i, const Program& p, const Program& q);
Program While(RegisterIndex i, const Program& p);

// -------------------------------------------------------

}
