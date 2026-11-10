// This file is part of Desktop App Toolkit,
// a set of libraries for developing nice desktop applications.
//
// For license and copyright information please follow this link:
// https://github.com/desktop-app/legal/blob/master/LEGAL
//
#include "ui/widgets/menu/menu_common.h"

#include "styles/palette.h"

#include <QAction>
#include <QtCore/QVariant>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include "styles/style_widgets.h"

namespace Ui::Menu {

void PaintBackground(QPainter &p, not_null<QWidget*> widget,
		const QRect &rect, const style::Menu &st, bool selected) {
	const auto backdrop = st.frosted
		? widget->window()->property(kBackdropProperty).value<QPixmap>() : QPixmap();
	if (!backdrop.isNull()) {
		const auto origin = widget->mapTo(widget->window(), rect.topLeft());
		const auto ratio = backdrop.devicePixelRatio();
		p.drawPixmap(rect, backdrop, QRect(origin * ratio, rect.size() * ratio));
	} else {
		p.fillRect(rect, st.itemBg);
	}
	if (!selected) return;
	if (st.itemRadius > 0) {
		p.save();
		p.setRenderHint(QPainter::Antialiasing);
		p.setPen(Qt::NoPen);
		auto color = st.itemBgOver->c;
		if (st.frosted) {
			color = st::menuIconFg->c;
			color.setAlphaF(0.15);
		}
		p.setBrush(color);
		p.drawRoundedRect(QRectF(rect).adjusted(st.itemInset, 0, -st.itemInset, 0), st.itemRadius, st.itemRadius);
		p.restore();
	} else {
		p.fillRect(rect, st.itemBgOver);
	}
}

not_null<QAction*> CreateAction(
		QWidget *parent,
		const QString &text,
		Fn<void()> &&callback) {
	const auto action = new QAction(text, parent);
	parent->connect(
		action,
		&QAction::triggered,
		action,
		std::move(callback),
		Qt::QueuedConnection);
	return action;
}

} // namespace Ui::Menu
