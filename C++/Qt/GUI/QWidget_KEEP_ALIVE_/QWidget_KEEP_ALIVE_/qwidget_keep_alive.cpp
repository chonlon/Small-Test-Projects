#include "widget_keep_alive.h"
#include <QtWidgets/QPushButton>
#include <QVBoxLayout>

QWidget_KEEP_ALIVE::QWidget_KEEP_ALIVE(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	auto layout = new QVBoxLayout{};
	QWidget *widget = new QWidget();
	widget->setLayout(layout);
	setCentralWidget(widget);

	// 像一个dialog一样, 会带有一个问号按钮
	auto button = new QPushButton{"Dialog", this};
	layout->addWidget(button);
	connect(button, &QPushButton::clicked, [this]()
	{
		auto widget = new QWidget{this, Qt::Dialog};
		widget->show();
	});
	
	// 像一个在父窗口上显示的一个窗口, 此窗口与父窗口一同被最大化最小化.
	auto button1 = new QPushButton{"Window", this};
	layout->addWidget(button1);
	connect(button1, &QPushButton::clicked, [this]()
	{
		auto widget = new QWidget{this, Qt::Window};
		widget->show();
	});

	auto button2 = new QPushButton{"ForeignWindow", this};
	layout->addWidget(button2);
	connect(button2, &QPushButton::clicked, [this]()
	{
		auto widget = new QWidget{this, Qt::SplashScreen};
		widget->show();
	});


	auto button3 = new QPushButton{"CoverWindow", this};
	layout->addWidget(button3);
	connect(button3, &QPushButton::clicked, [this]()
	{
		auto widget = new QWidget{this, Qt::CoverWindow};
		widget->show();
	});

	auto button4 = new QPushButton{"Tool", this};
	layout->addWidget(button4);
	connect(button4, &QPushButton::clicked, [this]()
	{
		auto widget = new QWidget{this, Qt::Tool};
		widget->show();
	});
}
