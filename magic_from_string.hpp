#include "fmt/format.h"
#include "fmt/ranges.h"
#include "magic_enum.hpp"
#include <QByteArray>
#include "QStacker/exceptionv2.h"
#include <QString>
#include <concepts>

namespace magic_enum {
template <typename Type>
std::vector<Type> getEnabled(const Type& t) {
	static constexpr auto& values = magic_enum::enum_values<Type>();
	std::vector<Type>      set;
	for (const auto& c : values) {
		using namespace bitwise_operators;
		if (to_underlying(t & c)) {
			set.push_back(c);
		}
	}
	return set;
}

template <typename Type>
std::vector<std::string_view> asString(const std::vector<Type>& t) {
	std::vector<std::string_view> res;
	for (const auto& c : t) {
		res.push_back(enum_name(c));
	}
	return res;
}

template <typename Type>
std::string composeError(std::string_view key, Type) {
	auto names = magic_enum::enum_names<Type>();
	return fmt::format("The key >>>{}<<< is not contained in the enum >>>{}<<<", key, fmt::join(names, " - "));
}

template <typename T, typename K>
[[nodiscard]] T fromString(const K& string) {
	return enum_cast<T>(string.toStdString()).value();
}

template <typename T, typename K>
[[nodiscard]] T fromString(const std::string& string) {
	return enum_cast<T>(string).value();
}

template <typename T>
void fromString(const std::string& string, T& t) {
	auto opt = enum_cast<T>(string);
	if (opt.has_value()) {
		t = opt.value();
	} else {
		auto msg = composeError(string, t);
		throw ExceptionV2(msg);
	}
}

template <typename E>
[[nodiscard]] QString enum_nameQS(E e) {
	std::string copy(magic_enum::enum_name(e));
	return QString::fromStdString(copy);
}

} // namespace magic_enum

template <typename T>
// [[nodiscard]] emette un warning se viene ignorato il valore ritornato della funzione
//enable_if attiva se... la condizione è se T è un enum, e ritorna una QString
[[nodiscard]] std::enable_if_t<std::is_enum_v<T>, QString> asString(T t) {
	return magic_enum::enum_nameQS(t);
}
