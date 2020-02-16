#ifndef decrypt_H
#define decrypt_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QTextEdit>
namespace Ui {
class decrypt;
}

class decrypt : public QDialog
{
    Q_OBJECT

public:
    QString post_text;
    QLabel *a;
    QLabel *b;
    QLabel *label;
    QTableWidget* tableWidget;
    QMap<QChar, double> decomposed_text;
    QMap<QChar, double> received_table;
    explicit decrypt(QWidget *parent = nullptr);
    ~decrypt();
    QString pre_text;


    int solveCongruences(int A[], int B[], int M[], int n);


private slots:
    void table_pushed();
    void chose_pushed();
    void decrypt_pushed();
    void save_pushed();
private:
    Ui::decrypt *ui;
};

#endif // decrypt_H
