//
// Created by Name on 14.07.2021.
//

#ifndef EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_NAMED_HPP_
#define EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_NAMED_HPP_

#include <memory>
#include <string>

namespace expression_system::utility {

class Named {
public:
	using ValueType = std::shared_ptr<const std::string>;

	template <typename... Args>
	static auto make_value(Args&&... args) -> ValueType;

	explicit Named(ValueType name);

	[[nodiscard]] const std::string& name() const;

private:
	ValueType _name;
};


//////////////////////////////////////////////////////
//                  Implementation                  //
//////////////////////////////////////////////////////


template <typename... Args>
auto Named::make_value(Args&& ... args) -> Named::ValueType {
	return std::make_shared<ValueType::element_type>(std::forward<Args>(args)...);
}

}

#endif //EXPRESSION_SYSTEM_EXPRESSION_SYSTEM_NAMED_HPP_
