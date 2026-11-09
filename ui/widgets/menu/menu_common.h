// This file is part of Desktop App Toolkit,
// a set of libraries for developing nice desktop applications.
//
// For license and copyright information please follow this link:
// https://github.com/desktop-app/legal/blob/master/LEGAL
//
#pragma once

class QPainter;
class QRect;
namespace style { struct Menu; }

namespace Ui::Menu {

inline constexpr auto kBackdropProperty = "desktop-app-menu-backdrop";
void PaintBackground(QPainter &p, not_null<QWidget*> widget,
	const QRect &rect, const style::Menu &st, bool selected = false);

enum class TriggeredSource {
	Mouse,
	Keyboard,
};

struct CallbackData {
	QAction *action = nullptr;
	int actionTop = 0;
	TriggeredSource source;
	int index = 0;
	bool selected = false;
	bool preventClose = false;
};

not_null<QAction*> CreateAction(
	QWidget *parent,
	const QString &text,
	Fn<void()> &&callback);

} // namespace Ui::Menu
