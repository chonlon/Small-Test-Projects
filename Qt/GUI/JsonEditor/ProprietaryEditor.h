#pragma once

#include <QtWidgets/QWidget>
#include "ui_ProprietaryEditor.h"
#include "EditorFactory.h"
#include "JsonHandler.h"
#include <QProcess>
#include <QTimer>


const auto SettingFilePath = "setting.json";

class TypeSelector;
class AddTypeSelector;

class ProprietaryEditor : public QWidget
{
Q_OBJECT

public:

    ProprietaryEditor(QWidget* parent = Q_NULLPTR);
    ~ProprietaryEditor() override;

    /**
     * \brief 读入json并初始化界面, 如果obj中的某个属性在setting中没有设置, 会自动判断节点属性并写入setting_json对应的param setting中.
     * \param obj 传入界面展示的Json文本对应的Obj.
     * \param setting 用于设置每个节点的类型属性, 主要递归时使用, 使用时传入setting对应的obj即可.
     * \param parent 当前被设置的界面json树的节点的上一个节点, 主要递归时使用, 使用时传入nullptr即可.
     */
    void backtrackTraversal(const QJsonObject& obj, QJsonObject* setting, QTreeWidgetItem* parent);

    /**
     * \brief 替换needReplaceOne中的某个节点的值, 节点通过key_list来定位, 也可用于删除, 当传入node为空值时, 节点会被删除
     * \param key_list 从该节点到顶部节点的所有key, index = 0是节点key, 最后一个是顶部的key.
     * \param current_index 当前的index, 主要是递归时使用, 使用时只用传入key_list.size() - 1 即可.
     * \param node 替换后的值
     * \param needReplaceOne 当前处理的object, 主要是递归时使用的, 使用时传入顶层object即可.
     */
    void replaceNode(const QVector<QString>& key_list, int current_index, const QJsonValue& node, QJsonObject* needReplaceOne);

    void addNodeAt(const QVector<QString>& key_list, int current_index, const QString& key, const QJsonValue& node, QJsonObject* need_replace_one);
public slots:
    void onItemPressed(QTreeWidgetItem* item, int column);

    void onItemModified();
    void onItemEnterPressed();

    void onEditorModified();
    void onEditorEnterPressed();
private slots:
    void startInvokeScript();
    void stopRunningScript();
private:
    void readSetting();
    void initConfigJson();

    Ui::ProprietaryEditorClass ui_;

    JsonHandler setting_{SettingFilePath};
    //将初始化延迟到从setting中读完设置以后.
    QScopedPointer<JsonHandler> json_{nullptr};
    QScopedPointer<JsonHandler> setting_json_{nullptr};

    QString json_setting_path_{};

    QMap<QWidget*, QTreeWidgetItem*> widget_to_node_;
    QWidgetList value_modified_widgets_{};

    TypeSelector* type_selector_{nullptr};
    AddTypeSelector* add_type_selector_{nullptr};

    EditorBase* config_file_path_editor_{nullptr};
    EditorBase* script_file_path_editor_{nullptr};
    EditorBase* resume_file_path_editor_{nullptr};
    EditorBase* devices_editor_{nullptr};
    QWidgetList value_modified_editors_{};

    QString config_file_path_{};
    QString script_file_path_{};
    QString resume_file_path_{};
    QString devices_{};

    QStringList arguments_{};
    QProcess* process_{nullptr};

    QTimer log_flush_timer_;
#ifdef _WIN32
    QString program_ = "python";
#elif defined __linux__
    QString program_ = "python";
#endif
};
