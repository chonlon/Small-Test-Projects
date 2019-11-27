#pragma once

#include <QtWidgets/QWidget>

class DefectFilterParamWidget : public QWidget
{
    Q_OBJECT

public:
    DefectFilterParamWidget(QWidget *parent = Q_NULLPTR);

    /// <summary>
    /// add single condition to ui at current defect.
    /// </summary>
    /// <param name= "row"> the row condition will be added to, if row didn't exit yet, new row will be added</param>
    /// <param name= "column">the column you want add to </param>
    void addCondition(uint8_t row, uint8_t column);

    /// <summary>
    /// delete single condition to ui at current defect.
    /// </summary>
    /// <returns> if condition specified by row and column didn't exit, return false.</returns>
    bool deleteCondition(uint8_t row, uint8_t column);


    bool deleteConditionRow(int row);

    void addDefect(const QString& name);
    /// <summary>
    /// invoke this function will reset defect button group and set checked button to position 0.
    /// </summary>
    void setDefects(const QVector<QString>& defect_names);

    void emitDefectDeleted(int index) { emit defectDeleted(index); }
signals:
    /// <summary>
    /// this signal only emit when add button was clicked.
    /// </summary>
    void conditionAdded();

    /// <summary>
    /// this signal only emit when delete button was clicked.
    /// </summary>
    void conditionDeleted(uint8_t row, uint8_t column);


    void defectAdded();
    void defectDeleted(int index);
public slots:

private slots:
    void addEmptyDefect();
    void deleteCurrentDefect();
private:
    struct Impl;

    Impl *impl_{nullptr};
};