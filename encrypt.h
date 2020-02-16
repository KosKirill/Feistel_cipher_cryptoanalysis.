#ifndef encrypt_H
#define encrypt_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QTextEdit>
#include <QBitArray>
#include <QCheckBox>
typedef long long int ll;
namespace Ui {
class encrypt;
}

class encrypt : public QDialog
{
    Q_OBJECT

public:
    int gcd(int a, int b);
    ll findlcm(QVector<int> arr);
    QCheckBox *box;
    QCheckBox *boxs;
    QCheckBox *de_boxs;
    QTextEdit *a;
    QTextEdit *b;
    QTextEdit *c;
    QTextEdit *d;
    QTextEdit *before_enc;
    QTextEdit *after_enc;
    QTextEdit *before_dec;
    QTextEdit *after_dec;
    QTextEdit *cli;
    QTableWidget* tableWidget;
    QMap<QChar, float> decomposed_text;
    QString bit_array_post_enc;
    QString bit_array_post_dec;
    explicit encrypt(QWidget *parent = nullptr);
    ~encrypt();
    QBitArray X_;
    QBitArray Y_;
    QBitArray synchro_enc;
    QBitArray synchro_dec;
    QBitArray pre_text;
    QBitArray pre_text_dec;
    QBitArray post_text_enc;
    QBitArray post_text_dec;
    QString tostr(QBitArray src);
    QByteArray convert(const QBitArray &__bits);
    QBitArray sp_alg(QBitArray open, QBitArray key);
    QList<QBitArray> split_bit(QBitArray src, int n);
    QPair<QBitArray, QBitArray> tact_subs(QBitArray X1, QBitArray X2, QBitArray key);
    QBitArray overall(QBitArray X1, QBitArray X2, QList<QBitArray> keys);
    //QBitArray overall_decrypt(QBitArray X1, QBitArray X2, QList<QBitArray> keys);
    QBitArray concat(QBitArray X1, QBitArray X2);
private slots:
    void box_changed(int state);
    void analyse_pushed();
    void save_encrypt_pushed();
    void chose_encrypt_pushed();
    void chose_synchro_enc_pushed();
    void chose_synchro_dec_pushed();
    void save_decrypt_pushed();
    void chose_decrypt_pushed();
    void encrypt_pushed();
    void decrypt_pushed();
    void chose_br_pushed();
    void cycle_ex_pushed();
private:
    Ui::encrypt *ui;
};

#endif // encrypt_H
