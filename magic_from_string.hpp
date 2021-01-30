#include "fmt/format.h"
#include "magic_enum.hpp"
#include <QByteArray>
#include <QStacker/qstacker.h>
#include <QString>
#include <concepts>

namespace magic_enum {
template <typename Type>
std::string join(const Type& t) {
	std::string final;
	auto        size = t.size();
	for (uint i = 0; i < size; i++) {
		final.append(t[i]);

		if (i != size - 1)
			final.append(" - ");
	}
	return final;
}

template <typename Type>
std::string composeError(const std::string& key, Type en) {
	auto& names      = magic_enum::enum_names<Type>();
	auto  nameString = join(names);
	return fmt::format("The key >>>{}<<< is not contained in the enum >>>{}<<<", key, nameString);
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
		auto  msg         = composeError(string, t);
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
