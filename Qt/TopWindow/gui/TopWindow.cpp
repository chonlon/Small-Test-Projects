﻿#include "TopWindow.h"
#include "ui_TopWindow.h"
#include "util/NinePatchPainter.h"

#include <QDebug>
#include <QSizeGrip>
#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

class TopWindowPrivate {
public:
	TopWindowPrivate(const QMargins &windowPaddings,
		const QMargins &borderImageBorders,
		const QString  &borderImagePath,
		bool  borderImageHorizontalStretch,
		bool  borderImageVerticalStretch) {
		ninePatchPainter = new NinePatchPainterNew(QPixmap(borderImagePath),
			borderImageBorders.left(),
			borderImageBorders.top(),
			borderImageBorders.right(),
			borderImageBorders.bottom(),
			borderImageHorizontalStretch,
			borderImageVerticalStretch);
		sizeGrip = new QSizeGrip(NULL);
		padding = windowPaddings;
	}

	NinePatchPainterNew *ninePatchPainter; // 九宫格绘图工具类
	QPoint windowPositionBeforeMoving;  // 移动窗口前窗口左上角的坐标
	QPoint mousePressedPosition;        // 按下鼠标时鼠标的全局坐标
	QSizeGrip *sizeGrip;         // 修改窗口大小的 handle
	QMargins   padding;          // 窗口的 padding
	bool       resizable = true; // 默认是可以缩放窗口的
};

TopWindow::TopWindow(QWidget *centralWidget,
	const QMargins &windowPaddings,
	const QMargins &borderImageBorders,
	const QString  &borderImagePath,
	bool  borderImageHorizontalStretch,
	bool  borderImageVerticalStretch) : ui(new Ui::TopWindow) {
	ui->setupUi(this);
	ui->restoreButton->hide();
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	d = new TopWindowPrivate(windowPaddings, borderImageBorders, borderImagePath,
		borderImageHorizontalStretch, borderImageVerticalStretch);

	// 去掉 padding 和 spacing
	QGridLayout *l = qobject_cast<QGridLayout*>(layout());
	l->setSpacing(0);
	l->setContentsMargins(d->padding);

	// 替换 central widget
	centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	delete l->replaceWidget(ui->centralWidget, centralWidget);
	delete ui->centralWidget;

	// 添加 size grip 到窗口右下角
	l->addWidget(d->sizeGrip, 1, 0, Qt::AlignRight | Qt::AlignBottom);

	// 信号槽事件处理
	handleEvents();
}

TopWindow::~TopWindow() {
	delete ui;
	delete d;

	qDebug() << "~TopWindow()";
}

void TopWindow::setTitle(const QString &title) {
	ui->titleLabel->setText(title);
}

void TopWindow::setTitleBar(QWidget *titleBar) {
	ui->titleBar->hide();
	delete layout()->replaceWidget(ui->titleBar, titleBar);
}

void TopWindow::setTitleBarVisible(bool visible) {
	ui->titleBar->setVisible(visible);
}

void TopWindow::setTitleBarButtonsVisible(bool min, bool max, bool close) {
	ui->minButton->setVisible(min);
	ui->maxButton->setVisible(max);
	ui->closeButton->setVisible(close);
}

void TopWindow::setResizable(bool resizable) {
	d->resizable = resizable;
	d->sizeGrip->setVisible(resizable);
}

void TopWindow::showMaximized() {
	layout()->setContentsMargins(0, 0, 0, 0); // 最大化窗口时不需要阴影，所以去掉窗口的 padding
	ui->maxButton->hide();
	ui->restoreButton->show();
	d->sizeGrip->setVisible(false);

	QWidget::showMaximized();
}

void TopWindow::showNormal() {
	layout()->setContentsMargins(d->padding); // 恢复窗口大小时显示阴影，所以加上窗口的 padding
	ui->maxButton->show();
	ui->restoreButton->hide();
	d->sizeGrip->setVisible(d->resizable);

	QWidget::showNormal();
}

void TopWindow::showModal() {
	// 作为 Dialog 需要同时设置 Qt::Dialog | Qt::Popup 两个 flags
	setWindowFlags(Qt::Dialog | Qt::Popup | Qt::FramelessWindowHint);
	setWindowModality(Qt::ApplicationModal);
	show();

	// 进入局部事件循环，阻塞代码继续往下走，窗口关闭时结束此局部事件循环
	QEventLoop *loop = new QEventLoop();
	connect(this, &TopWindow::aboutClose, [=] {
		loop->exit(); // After this function has been called, the event loop returns from the call to exec().
		loop->deleteLater();
	});
	loop->exec();
}

// 使用九宫格的方式绘制背景
void TopWindow::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);
	QPainter painter(this);
	d->ninePatchPainter->paint(&painter, rect());
}

// 鼠标按下时记录此时鼠标的全局坐标和窗口左上角的坐标
void TopWindow::mousePressEvent(QMouseEvent *event) {
	d->mousePressedPosition = event->globalPos();
	d->windowPositionBeforeMoving = frameGeometry().topLeft();
}
// 鼠标放开时设置 mousePressedPosition 为空坐标
void TopWindow::mouseReleaseEvent(QMouseEvent *) {
	d->mousePressedPosition = QPoint();
}

// 鼠标移动时如果 mousePressedPosition 不为空，则说明需要移动窗口
// 鼠标移动的位移差，就是窗口移动的位移差
void TopWindow::mouseMoveEvent(QMouseEvent *event) {
	// 最大化时不可以移动窗口
	if (isMaximized()) { return; }

	if (!d->mousePressedPosition.isNull()) {
		QPoint delta = event->globalPos() - d->mousePressedPosition;
		QPoint newPosition = d->windowPositionBeforeMoving + delta;
		move(newPosition);
	}
}

// 关闭窗口时发送 aboutClose() 信号，模态对话框收到此信号时好结束事件循环
void TopWindow::closeEvent(QCloseEvent *event) {
	emit aboutClose();
	QWidget::closeEvent(event);
}

void TopWindow::handleEvents() {
	connect(ui->minButton, &QPushButton::clicked, [this] {
		showMinimized(); // 最小化
	});

	connect(ui->maxButton, &QPushButton::clicked, [this] {
		showMaximized(); // 最大化
	});

	connect(ui->restoreButton, &QPushButton::clicked, [this] {
		showNormal(); // 恢复窗口大小
	});

	connect(ui->closeButton, &QPushButton::clicked, [this] {
		close(); // 关闭窗口
	});
}

void TopWindow::message(const QString  &msg, int width, int height,
	const QMargins &windowPaddings,
	const QMargins &borderImageBorders,
	const QString  &borderImagePath,
	bool  borderImageHorizontalStretch,
	bool  borderImageVerticalStretch) {
	QLabel *messageLabel = new QLabel(msg);
	QPushButton *okButton = new QPushButton("确定");
	QWidget *centralWidget = new QWidget();
	centralWidget->setStyleSheet(".QWidget {background: white;} ");
	messageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	messageLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

	// 布局组件
	QGridLayout *l = new QGridLayout();
	l->addWidget(messageLabel, 0, 0, 1, 2);
	l->addWidget(okButton, 1, 1);
	l->setColumnStretch(0, 10);
	centralWidget->setLayout(l);

	// 使用自定义窗口
	TopWindow *window = new TopWindow(centralWidget, windowPaddings, borderImageBorders, borderImagePath,
		borderImageHorizontalStretch, borderImageVerticalStretch);
	window->setTitleBarVisible(false);
	window->setResizable(false);
	window->setWindowFlags(Qt::Dialog | Qt::Popup | Qt::FramelessWindowHint);
	window->setWindowModality(Qt::ApplicationModal);
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->resize(width, height);
	window->show();

	// 点击确定按钮关闭窗口
	connect(okButton, &QPushButton::clicked, [=] {
		window->close();
	});
}


