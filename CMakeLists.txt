cmake_minimum_required(VERSION 3.16)
project(expression_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXECUTABLE_SUFFIX .html)

OPTION(WASM_ENABLED "Option description" OFF) # Enabled by default
if(WASM_ENABLED)
    add_definitions(-DWASM)
endif()
add_executable(expression_system main.cpp expression_system/tree/expression.hpp expression_system/tree/number.hpp expression_system/tree/parameter.hpp expression_system/tree/function_invocation.hpp expression_system/substituted_elements/internal_function.hpp expression_system/substituted_elements/expression_function.hpp expression_system/substituted_elements/function.hpp expression_system/calculator/declarations_stack.hpp expression_system/utility/named.cpp expression_system/utility/named.hpp expression_system/calculator/calculator.hpp expression_system/calculator/declarations_calculator.hpp expression_system/parser/string_parser.hpp expression_system/utility/slice_view.cpp expression_system/utility/slice_view.hpp expression_system/utility/string_utility.cpp expression_system/utility/string_utility.hpp expression_system/utility/transform_view.hpp expression_system/parser/tree/parse_unit.hpp expression_system/parser/tree/number_unit.hpp expression_system/parser/tree/block_unit.hpp expression_system/parser/tree/function_invocation_unit.hpp expression_system/parser/tree/parameter_unit.hpp expression_system/parser/tree/operator_unit.hpp expression_system/parser/tree/expression_unit.hpp expression_system/parser/token.cpp expression_system/parser/token.hpp)

if(WASM_ENABLED)
set_target_properties(expression_system PROPERTIES LINK_FLAGS "-fexceptions -s 'EXTRA_EXPORTED_RUNTIME_METHODS=[\"cwrap\"]' -s EXPORTED_FUNCTIONS=['_run','_free_str']")
endif()