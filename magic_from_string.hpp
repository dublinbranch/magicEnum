#include "magic_enum.hpp"
#include <QByteArray>
#include <QString>
#include <concepts>

namespace magic_enum {
template <typename T, typename K>
[[nodiscard]] T cast(const K& string) {
	return enum_cast<T>(string.toStdString()).value();
}

template <typename T, typename K>
[[nodiscard]] T cast(const std::string& string) {
	return enum_cast<T>(string).value();
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
