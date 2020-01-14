#pragma once
#include <QLabel>
#include <QHBoxLayout>

class EditorBase : public QWidget
{
Q_OBJECT
public:
    explicit EditorBase(QWidget* parent = nullptr);
    ~EditorBase() override = default;

    virtual QVariant getValue() const = 0;
     /**
     * \brief 设置EditorBase的编辑的值, 使用此函数不会导致编辑框显示已被修改.
     * \param val 
     */
    virtual void setValue(const QVariant& val) = 0;


    /**
     * \brief 使编辑框显示的已被修改状态变回正常状态.
     */
    virtual void setNormal() = 0;

    void setReminder(const QString& string);

    QString getReminderText() const;

    /**
     * \brief 快速获得Editor类型
     * \return Editor类型
     */
    uint8_t getType() const;

signals:
    void editFinished();
    void modified();
    void returnPressed();
protected:
    QHBoxLayout layout_{this};
    QLabel reminder_;

    bool has_modified_{false};

    uint8_t type_{UINT8_MAX};
public slots:
    void emitModified();
};
