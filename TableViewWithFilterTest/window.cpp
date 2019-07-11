#include "window.h"
#include <QDoubleValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>


Window::Window(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout{this};
    m_p_orgin_table_view = new QTableView{};
    m_p_filtered_table_view = new QTableView{};
    m_filter_model = new DefectSortFilterProxyModel{};

    m_p_filtered_table_view->setModel(m_filter_model);

    m_p_orgin_table_view->setAlternatingRowColors(true);
    m_p_filtered_table_view->setAlternatingRowColors(true);

    m_p_filtered_table_view->setSortingEnabled(true);

    m_filter_edit = new QLineEdit{this};
    m_filter_edit->setValidator( new QDoubleValidator(0.0, 100.0, 3,this) );
    m_filter_button = new QPushButton{this};
    m_filter_button->setText("filter");

    auto spin_box = new QSpinBox();
    spin_box->show();

    auto h_layout = new QHBoxLayout{};
    h_layout->addWidget(m_filter_edit);
    h_layout->addWidget(m_filter_button);

    connect(m_filter_button, &QPushButton::clicked, this, &Window::doFilter);

    layout->addLayout(h_layout);
    layout->addWidget(m_p_orgin_table_view);
    layout->addWidget(m_p_filtered_table_view);


    resize(400, 500);
}

Window::~Window()
{

}

void Window::doFilter()
{
    auto num = m_filter_edit->text().toInt();
    m_filter_model->setFilter(num);
}


void Window::setSourceModel(QAbstractItemModel *model) {
    m_p_orgin_table_view->setModel(model);
    m_filter_model->setSourceModel(model);
}
