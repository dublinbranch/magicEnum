#include "magic_enum.hpp"
#include <QByteArray>
#include <QString>

namespace magic_enum {
template <typename T>
[[nodiscard]] T enum_cast(const QByteArray& string) {
	return enum_cast<T>(string.toStdString()).value();
}

template <typename T>
[[nodiscard]] T enum_cast(const QString& string) {
	return enum_cast<T>(string.toStdString()).value();
}

template <typename E>
QString enum_nameQS(E e) {
	std::string copy(magic_enum::enum_name(e));
	return QString::fromStdString(copy);
}

} // namespace magic_enum
