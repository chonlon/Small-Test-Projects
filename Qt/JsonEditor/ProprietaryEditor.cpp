#include "ProprietaryEditor.h"
#include <QJsonObject>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QMenu>
#include <QJsonDocument>
#include <QMessageBox>
#include "TypeSelector.h"
#include "AddTypeSelector.h"
#include <QDir>

void ProprietaryEditor::initConfigJson()
{
    auto dir = QDir{config_file_path_};
    dir.cdUp();
    json_setting_path_ = dir.absolutePath() + "/setting-no-edit";
    json_.reset(new JsonHandler{config_file_path_});
    setting_json_.reset(new JsonHandler{json_setting_path_});

    auto setting = setting_json_->getObject();
    backtrackTraversal(json_->getObject(), &setting, nullptr);
    setting_json_->setObject(setting);
}


ProprietaryEditor::ProprietaryEditor(QWidget* parent)
    : QWidget(parent)
{
    ui_.setupUi(this);
    auto editors_layout = new QVBoxLayout{ui_.editors_widget};

    config_file_path_editor_ = EditorFactory::getEditor(EditorFactory::FileNameEditor, this);
    script_file_path_editor_ = EditorFactory::getEditor(EditorFactory::FileNameEditor, this);
    resume_file_path_editor_ = EditorFactory::getEditor(EditorFactory::FileNameEditor, this);
    devices_editor_          = EditorFactory::getEditor(EditorFactory::LineEditor, this);

    connect(config_file_path_editor_, &EditorBase::modified, this, &ProprietaryEditor::onEditorModified);
    connect(config_file_path_editor_, &EditorBase::returnPressed, this, &ProprietaryEditor::onEditorEnterPressed);
    connect(script_file_path_editor_, &EditorBase::modified, this, &ProprietaryEditor::onEditorModified);
    connect(script_file_path_editor_, &EditorBase::returnPressed, this, &ProprietaryEditor::onEditorEnterPressed);
    connect(resume_file_path_editor_, &EditorBase::modified, this, &ProprietaryEditor::onEditorModified);
    connect(resume_file_path_editor_, &EditorBase::returnPressed, this, &ProprietaryEditor::onEditorEnterPressed);
    connect(devices_editor_, &EditorBase::modified, this, &ProprietaryEditor::onEditorModified);
    connect(devices_editor_, &EditorBase::returnPressed, this, &ProprietaryEditor::onEditorEnterPressed);

    config_file_path_editor_->setReminder(u8"设置文件路径:");
    script_file_path_editor_->setReminder(u8"脚本文件路径:");
    resume_file_path_editor_->setReminder(u8"resume参数:");
    devices_editor_->setReminder(u8"devices设置:");

    editors_layout->addWidget(config_file_path_editor_);
    editors_layout->addWidget(script_file_path_editor_);
    editors_layout->addWidget(resume_file_path_editor_);
    editors_layout->addWidget(devices_editor_);


    readSetting();
    initConfigJson();

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, &QWidget::customContextMenuRequested, this, &ProprietaryEditor::onCustomContextMenuRequested);
    connect(ui_.treeWidget, &QTreeWidget::itemPressed, this, &ProprietaryEditor::onItemPressed);

    type_selector_     = new TypeSelector{this};
    add_type_selector_ = new AddTypeSelector{this};

    connect(ui_.run_button, &QPushButton::clicked, this, &ProprietaryEditor::startInvokeScript);
    connect(ui_.stop_button, &QPushButton::clicked, this, &ProprietaryEditor::stopRunningScript);
}

ProprietaryEditor::~ProprietaryEditor()
{
    json_->flush();
    setting_json_->flush();
}

void ProprietaryEditor::backtrackTraversal(const QJsonObject& obj, QJsonObject* setting, QTreeWidgetItem* parent)
{
    for (auto i = obj.begin(); i != obj.end(); ++i) {
        if ((*i).isObject()) {
            QTreeWidgetItem* item;
            if (parent == nullptr) {
                item = new QTreeWidgetItem{ui_.treeWidget};
            } else {
                item = new QTreeWidgetItem{parent};
            }

            QJsonObject _obj;
            if (!setting->value(i.key()).isUndefined()) {
                _obj = setting->value(i.key()).toObject();
            }
            item->setText(0, i.key());
            backtrackTraversal((*i).toObject(), &_obj, item);
            setting->insert(i.key(), _obj);
            qDebug() << "NODE:" << i.key();
        } else if ((*i).isDouble()) {
            QTreeWidgetItem* item;
            if (parent == nullptr) {
                item = new QTreeWidgetItem{ui_.treeWidget};
            } else {
                item = new QTreeWidgetItem{parent};
            }
            EditorBase* w;
            if (setting->value(i.key()).isUndefined()) {
                if ((*i).toString().contains('.')) setting->insert(i.key(), "double");
                else setting->insert(i.key(), "int");
            }
            if (setting->find(i.key()).value().toString() == "int") {
                w = EditorFactory::getEditor(EditorFactory::IntSpinBox, this);
                w->setValue((*i).toInt());
            } else {
                w = EditorFactory::getEditor(EditorFactory::DoubleSpinBox, this);
                w->setValue((*i).toDouble());
            }
            ui_.treeWidget->setItemWidget(item, 0, w);
            w->setReminder(i.key());
            widget_to_node_[w] = item;
            connect(w, &EditorBase::modified, this, &ProprietaryEditor::onItemModified);
            connect(w, &EditorBase::returnPressed, this, &ProprietaryEditor::onItemEnterPressed);
        } else if ((*i).isString()) {
            QTreeWidgetItem* item;
            if (parent == nullptr) {
                item = new QTreeWidgetItem{ui_.treeWidget};
            } else {
                item = new QTreeWidgetItem{parent};
            }
            EditorBase* w;
            if (setting->value(i.key()).isUndefined()) {
                if ((*i).toString().contains('/')) setting->insert(i.key(), "dir");
                else setting->insert(i.key(), "string");
            }
            if (setting->find(i.key()).value().toString() == "dir") {
                w = EditorFactory::getEditor(EditorFactory::DirEditor, this);
            } else {
                w = EditorFactory::getEditor(EditorFactory::LineEditor, this);
            }
            ui_.treeWidget->setItemWidget(item, 0, w);
            w->setValue((*i).toString());
            w->setReminder(i.key());
            widget_to_node_[w] = item;
            connect(w, &EditorBase::modified, this, &ProprietaryEditor::onItemModified);
            connect(w, &EditorBase::returnPressed, this, &ProprietaryEditor::onItemEnterPressed);
        }
    }
}

void ProprietaryEditor::replaceNode(const QVector<QString>& key_list, int current_index, const QJsonValue& node, QJsonObject* needReplaceOne)
{
    if (current_index < 0) return;

    const auto i = needReplaceOne->find(key_list[current_index]);
    auto obj     = i.value().toObject();
    replaceNode(key_list, current_index - 1, node, &obj);
    if (current_index == 0) {
        if (node.isNull())
            needReplaceOne->remove(i.key());
        else
            needReplaceOne->insert(i.key(), node);
    } else {
        needReplaceOne->insert(i.key(), obj);
    }
}

void ProprietaryEditor::addNodeAt(const QVector<QString>& key_list, int current_index, const QString& key, const QJsonValue& node, QJsonObject* need_replace_one)
{
    if (current_index < 0) return;

    const auto i = need_replace_one->find(key_list[current_index]);
    auto obj     = i.value().toObject();
    addNodeAt(key_list, current_index - 1, key, node, &obj);
    if (current_index == 0) {
        obj.insert(key, node);
    }
    need_replace_one->insert(i.key(), obj);
}

void ProprietaryEditor::onItemPressed(QTreeWidgetItem* item, int column)
{
    // todo 这里是没有处理或者说处理子节点个数是零的字典是错误的.
    if (!(QGuiApplication::mouseButtons() & Qt::RightButton)) return;
    auto getItemName = [this](QTreeWidgetItem* item) -> QString {
        if (item->childCount() == 0) {
            auto w = reinterpret_cast<EditorBase*>(ui_.treeWidget->itemWidget(item, 0));
            if (!w) {
                qWarning() << "WARNING!! YOU USED WIDGET UNEXCEPTED WHICH IS NOT INHERITED FORM EditorBase.";
                return "";
            }
            return w->getReminderText();
        }
        return item->text(0);
    };
    auto t = getItemName(item);

    //ui_.treeWidget->itemWidget(curItem, 0);
    auto seekTop = [&getItemName, this](QTreeWidgetItem* item, QVector<QString>* key_list) {
        while (item) {
            key_list->push_back(getItemName(item));
            item = item->parent();
        }
    };

    QMenu menu;
    menu.addAction(u8"删除" + t,
                   [&item, &seekTop, this]() {
                       qDebug() << "ready to delete";

                       auto ret = QMessageBox::question(this, u8"确认删除?", u8"即将删除当前节点, 确定?");
                       if (ret != QMessageBox::Yes) return;
                       QVector<QString> key_list;
                       seekTop(item, &key_list);
                       auto obj         = json_->getObject();
                       auto setting_obj = setting_json_->getObject();
                       replaceNode(key_list, key_list.size() - 1, QJsonValue{}, &obj);
                       replaceNode(key_list, key_list.size() - 1, QJsonValue{}, &setting_obj);

                       json_->setObject(obj);
                       json_->flush();
                       setting_json_->setObject(setting_obj);

                       delete item;
                   });

    // replace current edit or add current edit.
    menu.addAction(u8"转换类型",
                   [&item, &seekTop, this]() {
                       auto w = reinterpret_cast<EditorBase*>(ui_.treeWidget->itemWidget(item, 0));
                       type_selector_->setCurrentValue(qMakePair(w->getType(), w->getValue()));
                       const auto ret = type_selector_->exec();
                       if (ret == QDialog::Accepted) {
                           auto value = type_selector_->getValue();

                           const auto type = static_cast<EditorFactory::EditorType>(value.first);

                           QVector<QString> key_list;
                           seekTop(item, &key_list);
                           auto obj         = json_->getObject();
                           auto setting_obj = setting_json_->getObject();
                           replaceNode(key_list, key_list.size() - 1, QJsonValue{EditorFactory::getTypeString(type)}, &setting_obj);
                           if (value.first == EditorFactory::IntSpinBox || value.first == EditorFactory::DoubleSpinBox) {
                               replaceNode(key_list, key_list.size() - 1, QJsonValue{value.second.toDouble()}, &obj);
                           } else {
                               replaceNode(key_list, key_list.size() - 1, QJsonValue{value.second.toString()}, &obj);
                           }
                           json_->setObject(obj);
                           json_->flush();
                           setting_json_->setObject(setting_obj);

                           auto w_temp = w;
                           w           = EditorFactory::getEditor(type, this);
                           w->setReminder(key_list[0]);
                           w->setValue(value.second);
                           ui_.treeWidget->setItemWidget(item, 0, w);
                           widget_to_node_[w] = item;
                           connect(w, &EditorBase::modified, this, &ProprietaryEditor::onItemModified);
                           connect(w, &EditorBase::returnPressed, this, &ProprietaryEditor::onItemEnterPressed);
                           w_temp->deleteLater();
                       }
                       qDebug() << "ready to replace";
                   });

    if (item->childCount() != 0) {
        menu.addAction(u8"向" + t + u8"中添加",
                       [&item, &seekTop, this]() {
                           auto ret = add_type_selector_->exec();
                           if (ret == QDialog::Accepted) {
                               auto value = add_type_selector_->getValue();
                               auto name  = add_type_selector_->getTypeName();
                               QVector<QString> key_list;
                               seekTop(item, &key_list);
                               auto obj         = json_->getObject();
                               auto setting_obj = setting_json_->getObject();
                               const auto type  = static_cast<EditorFactory::EditorType>(value.first);

                               addNodeAt(key_list, key_list.size() - 1, name, QJsonValue{EditorFactory::getTypeString(type)}, &setting_obj);

                               if (value.first == EditorFactory::IntSpinBox || value.first == EditorFactory::DoubleSpinBox) {
                                   addNodeAt(key_list, key_list.size() - 1, name, QJsonValue{value.second.toDouble()}, &obj);
                               } else {
                                   addNodeAt(key_list, key_list.size() - 1, name, QJsonValue{value.second.toString()}, &obj);
                               }
                               json_->setObject(obj);
                               json_->flush();
                               setting_json_->setObject(setting_obj);

                               const auto item_to_add = new QTreeWidgetItem{item};
                               auto w                 = EditorFactory::getEditor(type, this);
                               ui_.treeWidget->setItemWidget(item_to_add, 0, w);
                               w->setReminder(name);
                               w->setValue(value.second);
                               widget_to_node_[w] = item_to_add;
                               connect(w, &EditorBase::modified, this, &ProprietaryEditor::onItemModified);
                               connect(w, &EditorBase::returnPressed, this, &ProprietaryEditor::onItemEnterPressed);

                               // 添加widget以后上下的widget可能会叠在一起, 需要重绘一下treewidget.
                               ui_.treeWidget->repaint();
                           }
                           qDebug() << "ready to add";
                       });
    }

    menu.exec(QCursor::pos());
}

void ProprietaryEditor::onItemModified()
{
    auto w = qobject_cast<QWidget*>(sender());
    if (value_modified_widgets_.contains(w)) return;
    value_modified_widgets_.push_back(qobject_cast<QWidget*>(sender()));
}

void ProprietaryEditor::onItemEnterPressed()
{
    auto getItemName = [this](QTreeWidgetItem* item) -> QString {
        if (item->childCount() == 0) {
            auto w = reinterpret_cast<EditorBase*>(ui_.treeWidget->itemWidget(item, 0));
            if (!w) {
                qWarning() << "WARNING!! YOU USED WIDGET UNEXCEPTED WHICH IS NOT INHERITED FORM EditorBase.";
                return "";
            }
            return w->getReminderText();
        }
        return item->text(0);
    };
    auto seekTop = [&getItemName,this](QTreeWidgetItem* item, QVector<QString>* key_list) {
        while (item) {
            key_list->push_back(getItemName(item));
            item = item->parent();
        }
    };
    for (auto p : value_modified_widgets_) {
        auto p_cast = qobject_cast<EditorBase*>(p);
        QVector<QString> key_list;
        auto item = widget_to_node_[p_cast];
        seekTop(item, &key_list);
        auto obj         = json_->getObject();
        auto setting_obj = setting_json_->getObject();
        auto type        = static_cast<EditorFactory::EditorType>(p_cast->getType());
        auto type_string = EditorFactory::getTypeString(type);
        replaceNode(key_list, key_list.size() - 1, QJsonValue{type_string}, &setting_obj);
        if (type == EditorFactory::IntSpinBox || type == EditorFactory::DoubleSpinBox) {
            replaceNode(key_list, key_list.size() - 1, QJsonValue{p_cast->getValue().toDouble()}, &obj);
        } else {
            replaceNode(key_list, key_list.size() - 1, QJsonValue{p_cast->getValue().toString()}, &obj);
        }


        json_->setObject(obj);
        json_->flush();
        setting_json_->setObject(setting_obj);

        p_cast->setNormal();
    }
    value_modified_widgets_.clear();
}

void ProprietaryEditor::onEditorModified()
{
    auto w = qobject_cast<QWidget*>(sender());
    if (value_modified_editors_.contains(w)) return;
    value_modified_editors_.push_back(w);
}

void ProprietaryEditor::onEditorEnterPressed()
{
    for (auto w : value_modified_editors_) {
        const auto w_cast = qobject_cast<EditorBase*>(w);
        if (w_cast == config_file_path_editor_) {
            config_file_path_ = config_file_path_editor_->getValue().toString();
            auto obj          = setting_.getObject();
            obj.insert("--config", config_file_path_);
            setting_.setObject(obj);
            initConfigJson();
            config_file_path_editor_->setNormal();
        } else if (w_cast == script_file_path_editor_) {
            script_file_path_ = script_file_path_editor_->getValue().toString();
            auto obj          = setting_.getObject();
            obj.insert("script_path", script_file_path_);
            setting_.setObject(obj);
            script_file_path_editor_->setNormal();
        } else if (w_cast == resume_file_path_editor_) {
            resume_file_path_ = resume_file_path_editor_->getValue().toString();
            auto obj          = setting_.getObject();
            obj.insert("--resume", resume_file_path_);
            setting_.setObject(obj);
            resume_file_path_editor_->setNormal();
        } else if (w_cast == devices_editor_) {
            devices_ = devices_editor_->getValue().toString();
            auto obj = setting_.getObject();
            obj.insert("--devices", devices_);
            setting_.setObject(obj);
            devices_editor_->setNormal();
        }
    }
    value_modified_editors_.clear();
}

void ProprietaryEditor::startInvokeScript()
{
    if (!process_) {
        QStringList arguments;
        if (script_file_path_.isEmpty()) {
            QMessageBox::warning(this, u8"警告", u8"需要执行的脚本文件设置为空!");
            return;
        }
        process_ = new QProcess{this};
        arguments << "-u";
        arguments << script_file_path_;
        if (!config_file_path_.isEmpty()) {
            arguments << "--config" << config_file_path_;
        }
        if (!resume_file_path_.isEmpty()) {
            arguments << "--resume" << resume_file_path_;
        }
        if (!devices_.isEmpty()) {
            arguments << "--device" << devices_;
        }
        process_->start(program_, arguments, QIODevice::Unbuffered | QIODevice::ReadOnly);

#ifdef _WIN32
        process_->setProcessChannelMode(QProcess::SeparateChannels);
#elif defined __linux__
        process_->setProcessChannelMode(QProcess::MergedChannels);
#endif  

        auto buffer = program_;
        for(auto i : arguments) {
            buffer.append(" ").append(i);
        }
        qDebug() << "exec command:" << buffer;


        log_flush_timer_.start(100);
        connect(&log_flush_timer_,
                &QTimer::timeout,
                [this]() {
                    auto out = process_->readAll();
                    if(out.isEmpty()) return;
                    ui_.plainTextEdit->appendPlainText(out);
                });
    }
    qDebug() << "Process is running";
}

void ProprietaryEditor::stopRunningScript()
{
    if (process_) {
        log_flush_timer_.stop();
        process_->kill();
        delete process_;
    }

    process_ = nullptr;
}

void ProprietaryEditor::readSetting()
{
    const auto obj = setting_.getObject();

    config_file_path_ = obj.value("--config").toString();
    config_file_path_editor_->setValue(config_file_path_);

    script_file_path_ = obj.value("script_path").toString();
    script_file_path_editor_->setValue(script_file_path_);

    resume_file_path_ = obj.value("--resume").toString();
    resume_file_path_editor_->setValue(resume_file_path_);

    devices_ = obj.value("--device").toString();
    devices_editor_->setValue(devices_);
}
