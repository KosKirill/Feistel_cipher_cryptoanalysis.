#include "encrypt.h"
#include "ui_encrypt.h"
#include <QFileDialog>
#include <QPushButton>
#include <QTextStream>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include <QHeaderView>
#include <QTextEdit>
#include <QRandomGenerator>
#include <ctime>
#include <cstdlib>
#include <QDataStream>
#include <chrono>
#include <QtMath>
using namespace std::chrono;


encrypt::encrypt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::encrypt)
{
    ui->setupUi(this);
    this->resize(1205, 800);


    QLabel *all = new QLabel(this);
    all-> move(830, 160);
    all->resize(70, 25);
    all->setText("All blocks");

    before_enc = new QTextEdit(this);
    before_enc->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    before_enc->resize(400, 280);
    before_enc->move(0,105);

    after_enc = new QTextEdit(this);
    after_enc->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    after_enc->resize(400, 280);
    after_enc->move(405,105);

    before_dec = new QTextEdit(this);
    before_dec->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    before_dec->resize(400, 280);
    before_dec->move(0,505);

    after_dec = new QTextEdit(this);
    after_dec->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    after_dec->resize(400, 280);
    after_dec->move(405,505);

    cli = new QTextEdit(this);
    cli->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    cli->resize(350, 500);
    cli->move(830, 200);

    QPushButton *chose_file_br = new QPushButton(this);
    chose_file_br->resize(100,35);
    chose_file_br->setText(tr("Chose file"));
    chose_file_br->move(450, 405);
    connect(chose_file_br, SIGNAL (released()), this, SLOT (chose_br_pushed()));

    QPushButton *encrypt  = new QPushButton(this);
    encrypt->resize(75, 30);
    encrypt->setText(tr("encrypt"));
    encrypt->move(310, 45);
    connect(encrypt, SIGNAL (released()), this, SLOT (encrypt_pushed()));

    QPushButton *decrypt  = new QPushButton(this);
    decrypt->resize(75, 30);
    decrypt->setText(tr("decrypt"));
    decrypt->move(310, 445);
    connect(decrypt, SIGNAL (released()), this, SLOT (decrypt_pushed()));

    box = new QCheckBox(this);
    box->move(400, 453);
    QLabel *l13 = new QLabel(this);
    l13->resize(75, 15);
    l13->move(420, 453);
    l13->setText("Brute force");
    connect(box, SIGNAL (stateChanged(int)), this, SLOT (box_changed(int)));

    boxs = new QCheckBox(this);
    boxs->move(400, 53);
    QLabel *l23 = new QLabel(this);
    l23->resize(75, 15);
    l23->move(420, 53);
    l23->setText("CBC");

    de_boxs = new QCheckBox(this);
    de_boxs->move(500, 453);
    QLabel *l33 = new QLabel(this);
    l33->resize(75, 15);
    l33->move(520, 453);
    l33->setText("CBC");

    QLabel *l1 = new QLabel(this);
    l1->resize(400, 45);
    l1->move(0, 0);
    l1->setText("Encryption");
    QFont font = l1->font();
    font.setPointSize(12);
    font.setBold(true);
    l1->setFont(font);

    QLabel *k1 = new QLabel(this);
    k1->resize(30, 30);
    k1->move(5, 45);
    k1->setText("key");

    a = new QTextEdit(this);
    a->resize(270, 30);
    a->move(30, 45);
    a->setText("11111111111111111111111111111111");

    QLabel *l2 = new QLabel(this);
    l2->resize(400, 45);
    l2->move(0, 400);
    l2->setText("Decryption");
    QFont font2 = l1->font();
    font2.setPointSize(12);
    font2.setBold(true);
    l2->setFont(font);

    QLabel *k3 = new QLabel(this);
    k3->resize(30, 30);
    k3->move(830, 110);
    k3->setText("key");



    QLabel *l3 = new QLabel(this);
    l3->resize(400, 45);
    l3->move(910, 0);
    l3->setText("Error propagtion");
    l3->setFont(font);

    c = new QTextEdit(this);
    c->resize(270, 30);
    c->move(870, 110);
    c->setText("11111111111111111111111111111111");

    QPushButton *analyse = new QPushButton(this);
    analyse->resize(100,35);
    analyse->setText(tr("analyse"));
    analyse->move(900, 155);
    connect(analyse, SIGNAL (released()), this, SLOT (analyse_pushed()));

    QPushButton *cycle_ex = new QPushButton(this);
    cycle_ex->resize(150,35);
    cycle_ex->setText(tr("cycle experiments"));
    cycle_ex->move(1000, 155);
    connect(cycle_ex, SIGNAL (released()), this, SLOT (cycle_ex_pushed()));


    b = new QTextEdit(this);
    b->resize(270, 30);
    b->move(30, 445);
    b->setText("11111111111111111111111111111111");

    QPushButton *chose_file_en = new QPushButton(this);
    chose_file_en->resize(100,35);
    chose_file_en->setText(tr("Chose file"));
    chose_file_en->move(120, 5);
    connect(chose_file_en, SIGNAL (released()), this, SLOT (chose_encrypt_pushed()));

    QPushButton *chose_synchro_en = new QPushButton(this);
    chose_synchro_en->resize(100,35);
    chose_synchro_en->setText(tr("Chose synchro"));
    chose_synchro_en->move(220, 5);
    connect(chose_synchro_en, SIGNAL (released()), this, SLOT (chose_synchro_enc_pushed()));


    QPushButton *save_table_en = new QPushButton(this);
    save_table_en->resize(100,35);
    save_table_en->setText(tr("Save file"));
    save_table_en->move(320, 5);
    connect(save_table_en, SIGNAL (released()), this, SLOT (save_encrypt_pushed()));

    QLabel *be = new QLabel(this);
    be->resize(100, 35);
    be->move(170, 75);
    be->setText("Before");
    QFont font3 = be->font();
    font3.setPointSize(10);
    font3.setBold(true);
    be->setFont(font3);

    QLabel *ae = new QLabel(this);
    ae->resize(100, 35);
    ae->move(575, 75);
    ae->setText("After");
    ae->setFont(font3);

    QPushButton *chose_file_de = new QPushButton(this);
    chose_file_de->resize(100,35);
    chose_file_de->setText(tr("Chose file"));
    chose_file_de->move(120, 405);
    connect(chose_file_de, SIGNAL (released()), this, SLOT (chose_decrypt_pushed()));

    QPushButton *chose_synch_de = new QPushButton(this);
    chose_synch_de->resize(100,35);
    chose_synch_de->setText(tr("Chose synchro"));
    chose_synch_de->move(220, 405);
    connect(chose_synch_de, SIGNAL (released()), this, SLOT (chose_synchro_dec_pushed()));

    QPushButton *save_table_de = new QPushButton(this);
    save_table_de->resize(100,35);
    save_table_de->setText(tr("Save file"));
    save_table_de->move(320, 405);
    connect(save_table_de, SIGNAL (released()), this, SLOT (save_decrypt_pushed()));

    QLabel *k2 = new QLabel(this);
    k2->resize(30, 30);
    k2->move(5, 445);
    k2->setText("key");

    QLabel *bd = new QLabel(this);
    bd->resize(100, 35);
    bd->move(170, 475);
    bd->setText("Before");
    bd->setFont(font3);

    QLabel *ad = new QLabel(this);
    ad->resize(100, 35);
    ad->move(575, 475);
    ad->setText("After");
    ad->setFont(font3);


}

encrypt::~encrypt()
{
    delete ui;
}
void encrypt:: chose_synchro_enc_pushed()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Chose file", "C:/Users/MiPro/Documents");
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qInfo() << "File not opened";
    }

    QByteArray arrfile = file.readAll();

    QBitArray bits(arrfile.count()*8);
    if(bits.size() != 32)
    {
        QMessageBox::warning(this, tr("Synchro warning"),
                                       tr("Synchro length must be 32 chars"),
                                       QMessageBox::Ok);
        return;
    }


    QString bit_array;

    for(int i = 0; i < arrfile.count(); ++i) {
      for(int b = 0; b < 8; b++) {
        bits.setBit( i * 8 + b, arrfile.at(i) & (1 << (7 - b)) );
    }
    }

    synchro_enc = bits;

    boxs->setCheckState(Qt::Checked);
    de_boxs->setCheckState(Qt::Checked);
    qInfo() << "readed";
}

void encrypt:: chose_synchro_dec_pushed()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Chose file", "C:/Users/MiPro/Documents");
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qInfo() << "File not opened";
    }

    QByteArray arrfile = file.readAll();

    QBitArray bits(arrfile.count()*8);
    if(bits.size() != 32)
    {
        QMessageBox::warning(this, tr("Synchro warning"),
                                       tr("Synchro length must be 32 chars"),
                                       QMessageBox::Ok);
        return;
    }


    QString bit_array;

    for(int i = 0; i < arrfile.count(); ++i) {
      for(int b = 0; b < 8; b++) {
        bits.setBit( i * 8 + b, arrfile.at(i) & (1 << (7 - b)) );
    }
    }

    synchro_dec = bits;
    de_boxs->setCheckState(Qt::Checked);
    qInfo() << "readed";
}

void encrypt::chose_br_pushed()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Chose file", "C:/Users/MiPro/Documents");
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qInfo() << "File not opened";
    }

    after_dec->clear();
    QByteArray arrfile = file.readAll();

    QBitArray bits(arrfile.count()*8);
    if(bits.size() < 32)
    {
        QMessageBox::warning(this, tr("Text warning"),
                                       tr("Text length must be more than 32 chars"),
                                       QMessageBox::Ok);
        return;
    }


    QString bit_array;

    for(int i = 0; i < arrfile.count(); ++i) {
      for(int b = 0; b < 8; b++) {
        bits.setBit( i * 8 + b, arrfile.at(i) & (1 << (7 - b)) );
    }
    }

    for(int i = 0; i< bits.size(); i++)
    {
        if(bits[i] == true)
            bit_array.append("1");
        else
            bit_array.append("0");
    }


    Y_ = bits;
        //qInfo() << bits[i];


    after_dec->setText(bit_array);

    qInfo() << "readed";

}

void encrypt::chose_encrypt_pushed()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Chose file", "C:/Users/MiPro/Documents");
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qInfo() << "File not opened";
    }

    before_enc->clear();
    QByteArray arrfile = file.readAll();

    QBitArray bits(arrfile.count()*8);
    if(bits.size() < 32)
    {
        QMessageBox::warning(this, tr("Text warning"),
                                       tr("Text length must be more than 32 chars"),
                                       QMessageBox::Ok);
        return;
    }


    QString bit_array;

    for(int i = 0; i < arrfile.count(); ++i) {
      for(int b = 0; b < 8; b++) {
        bits.setBit( i * 8 + b, arrfile.at(i) & (1 << (7 - b)) );
    }
    }

    pre_text = bits;

    for(int i = 0; i< bits.size(); i++)
    {
        if(bits[i] == true)
            bit_array.append("1");
        else
            bit_array.append("0");
    }

        //qInfo() << bits[i];


    before_enc->setText(bit_array);

    qInfo() << "readed";

}

void encrypt::save_encrypt_pushed()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                         "C:/Users/MiPro/Documents/untitled.txt",
                                                         tr("Text files (*.txt)"));
    QFile f( filename );
    f.open( QIODevice::WriteOnly );
    QByteArray foo = convert(post_text_enc);

    qInfo() << post_text_enc;
    qInfo() << foo;
    f.write(foo);
    f.close();
}

void encrypt::chose_decrypt_pushed()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Chose file", "C:/Users/MiPro/Documents");
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qInfo() << "File not opened";
    }

    before_dec->clear();
    QByteArray arrfile = file.readAll();

    QBitArray bits(arrfile.count()*8);
    if(bits.size() < 32)
    {
        QMessageBox::warning(this, tr("Text warning"),
                                       tr("Text length must be more than 32 chars"),
                                       QMessageBox::Ok);
        return;
    }


    QString bit_array;

    for(int i = 0; i < arrfile.count(); ++i) {
      for(int b = 0; b < 8; b++) {
        bits.setBit( i * 8 + b, arrfile.at(i) & (1 << (7 - b)) );
    }
    }


        X_ = bits;
        pre_text_dec = bits;



    for(int i = 0; i< bits.size(); i++)
    {
        if(bits[i] == true)
            bit_array.append("1");
        else
            bit_array.append("0");
    }

        qInfo() << bits;


    before_dec->setText(bit_array);

    qInfo() << "readed";

}

void encrypt::save_decrypt_pushed()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                         "C:/Users/MiPro/Documents/untitled.txt",
                                                         tr("Text files (*.txt)"));
    QFile f( filename );
    f.open( QIODevice::WriteOnly );
    QByteArray foo = convert(post_text_dec);

    f.write(foo);
    f.close();
}

void encrypt::encrypt_pushed()
{

    QString key_str = a->toPlainText();
    QBitArray key_bit(32);
    if(key_str.size() != 32)
    {
        QMessageBox::warning(this, tr("Key warning"),
                                       tr("Key length must be 32 chars"),
                                       QMessageBox::Ok);
        return;
    }
    for(int i = 0; i < key_str.size(); i++)
    {
        if(key_str[i] == '1')
            key_bit.setBit(i);
        else if(key_str[i] != '0')
        {
            QMessageBox::warning(this, tr("Key warning"),
                                           tr("Key must be binary"),
                                           QMessageBox::Ok);
            return;
        }
    }

    QList<QBitArray> key = split_bit(key_bit, 16);
    key.append(~key[0]);
    key.append(~key[1]);

    QList<QBitArray> splited_pre = split_bit(pre_text, 32);
    QList<QBitArray> splited_post;

    qInfo() << splited_pre.size();

    for(int i = 0; i < splited_pre.size(); i++)
    {
        if(boxs->checkState())
        {

            if(i != splited_pre.size() - 1)
            {

                QList<QBitArray> temp = split_bit(splited_pre[i], 16);
                if(i == 0)
                {
                    qInfo() << "XOR OPRAND: " << synchro_enc;
                    splited_post.append(synchro_enc ^ overall(temp[0], temp[1], key));
                }
                else
                {

                     splited_post.append(splited_post[i-1] ^ overall(temp[0], temp[1], key));
                }

            }
            else
            {
                int presize = splited_pre[i].size();
                splited_pre[i].resize(32);

               for(int m = presize; m < 32; m++)
                   splited_pre[i][m] = 0;

               QList<QBitArray> temp = split_bit(splited_pre[i], 16);
               if(i == 0)
                splited_post.append(synchro_enc ^ overall(temp[0], temp[1], key));
               else
                splited_post.append(splited_post.last() ^ overall(temp[0], temp[1], key));


               QList<uint> arrfile_x;
               arrfile_x.append(32 - presize);
               QBitArray bits_x(arrfile_x.count()*32);
               for(int k = 0; k < arrfile_x.count(); ++k) {
                 for(int b = 0; b < 32; b++) {
                   bits_x.setBit( k * 32 + b, arrfile_x.at(k) & (1 << (31 - b)) );
               }
               }

               temp = split_bit(bits_x, 16);
               splited_post.append(splited_post.last() ^ overall(temp[0], temp[1], key));


            }
        }
        else
        {
            if(splited_pre[i].size() == 32)
            {

                QList<QBitArray> temp = split_bit(splited_pre[i], 16);
                splited_post.append(overall(temp[0], temp[1], key));

            }
            else
            {
                int diff = 32 - splited_pre[i].size();
                QBitArray Y_star(diff);
                QBitArray Y_T(splited_pre[i].size());

                for(int j = 0; j < 32; j++)
                {
                    if(j < splited_pre[i].size())
                        Y_T[j] = splited_post[splited_post.size() - 1][j];
                    else
                        Y_star[j - splited_pre[i].size()] = splited_post[splited_post.size() - 1][j];
                }

                QList<QBitArray> temp = split_bit(concat(splited_pre[i],Y_star), 16);
                splited_post[splited_post.size() - 1] = overall(temp[0], temp[1], key);
                splited_post.append(Y_T);

            }

        }

    }
    int ex = 0;
    int overall_size = 0;
    for(auto elem: splited_post)
        overall_size += elem.size();

    post_text_enc.resize(overall_size);
    for(int i = 0; i < splited_post.size(); i++)
        for(int j = 0; j < splited_post[i].size(); j++)
        {
            post_text_enc[ex] = splited_post[i][j];
            ex++;
        }



    for(int i = 0; i< post_text_enc.size(); i++)
    {
        if(post_text_enc[i] == true)
            bit_array_post_enc.append("1");
        else
            bit_array_post_enc.append("0");
    }

    pre_text_dec = post_text_enc;
    after_enc->setText(bit_array_post_enc);
    before_dec->setText(bit_array_post_enc);
    bit_array_post_enc.clear();
}

void encrypt::decrypt_pushed()
{

    if(box->checkState())
    {
         QList<QBitArray> splited_ex = split_bit(X_, 32);
         QList<QBitArray> splited_ey = split_bit(Y_, 32);
         QBitArray X(32);
         QBitArray Y(32);
         QBitArray X1(32);
         QBitArray Y1(32);
         bool found = false;
         for(int i = 0; i < splited_ex.size() - 1; i++)
             for(int j = 0; j < splited_ex.size() - 1; j++)
                 if(splited_ex[i] == ~splited_ex[j])
                 {
                    X = splited_ex[i];
                    X1 = splited_ex[j];

                    Y = splited_ey[i];
                    Y1 = splited_ey[j];
                    found = true;
                 }
         auto start = high_resolution_clock::now();
         if(found)
         {
             cli->append("Pair found");
             cli->append("Begining smart brute force");
             QHash<QBitArray, int> key_hash;
             QBitArray key(32);
             uint max_val = -1;
             uint value;
             while(true)
             {
                 value = QRandomGenerator::global()->generate();
                 QList<uint> arrfile_x;
                 arrfile_x.append(value);
                 QBitArray bits_x(arrfile_x.count()*32);
                 for(int i = 0; i < arrfile_x.count(); ++i) {
                   for(int b = 0; b < 32; b++) {
                     bits_x.setBit( i * 32 + b, arrfile_x.at(i) & (1 << (31 - b)) );
                 }
                 }



                 key = bits_x;
                 qInfo() << bits_x;
                 QList<QBitArray> key_array = split_bit(key, 16);
                 key_array.append(~key_array[0]);
                 key_array.append(~key_array[1]);

                 QList<QBitArray> temp = split_bit(X, 16);
                 QBitArray result = (overall(temp[0], temp[1], key_array));

                 if(result == Y)
                 {
                     cli->append("Key found");
                     cli->append(tostr(key));
                     break;

                 }
                 else if(~result == Y1)
                 {
                     cli->append("Key found");
                     cli->append(tostr(~key));
                     break;
                 }
                 else
                 {
                     qInfo() << "not "  << key;
                     qInfo() << "not "  << ~key;
                 }
            }
         }
         else
         {
             X = splited_ex[0];
             Y = splited_ey[0];
             qInfo() << "start";
             cli->append("Pair not found");
             cli->append("Begining full brute force");
             QBitArray key(32);
             uint max_val = -1;
             QList<uint> arrfile_x;
             QBitArray bits_x(32);
             QList<QBitArray> key_array;
             QList<QBitArray> temp;
             QBitArray result;
             uint value;
             while(true)
             {
                 value = QRandomGenerator::global()->generate();

                 arrfile_x.clear();
                 arrfile_x.append(value);
                 QBitArray bits_x(32);
                 for(int i = 0; i < arrfile_x.count(); ++i) {
                   for(int b = 0; b < 32; b++) {
                     bits_x.setBit( i * 32 + b, arrfile_x.at(i) & (1 << (31 - b)) );
                 }
                 }

                 qInfo() << bits_x;

                 key = bits_x;

                 key_array = split_bit(key, 16);
                 key_array.append(~key_array[0]);
                 key_array.append(~key_array[1]);
                 key_array[0].swap(key_array[3]);
                 key_array[1].swap(key_array[2]);

                 temp = split_bit(Y, 16);
                 result = (overall(temp[0], temp[1], key_array));

                 if(result == X)
                 {
                     cli->append("Key found");
                     cli->append(tostr(key));
                     break;

                 }
                 else
                 {
//                     qInfo() << "not ";
//                     qInfo() << key;
                 }

             }
         }
         auto stop = high_resolution_clock::now();

         auto duration = duration_cast<minutes>(stop - start);

         // To get the value of duration use the count()
         // member function on the duration object
         qInfo() << duration.count();
    }
    else
    {
        QString key_str = b->toPlainText();
        QBitArray key_bit(32);
        if(key_str.size() != 32)
        {
            QMessageBox::warning(this, tr("Key warning"),
                                           tr("Key length must be 32 chars"),
                                           QMessageBox::Ok);
            return;
        }
        for(int i = 0; i < key_str.size(); i++)
        {
            if(key_str[i] == '1')
                key_bit.setBit(i);
            else if(key_str[i] != '0')
            {
                QMessageBox::warning(this, tr("Key warning"),
                                               tr("Key must be binary"),
                                               QMessageBox::Ok);
                return;
            }
        }

        QList<QBitArray> key = split_bit(key_bit, 16);
        key.append(~key[0]);
        key.append(~key[1]);
        key[0].swap(key[3]);
        key[1].swap(key[2]);

        QList<QBitArray> splited_pre = split_bit(pre_text_dec, 32);
        QList<QBitArray> splited_post;

        for(int i = 0; i < splited_pre.size(); i++)
        {
            if(boxs->checkState())
            {
                if(i != splited_pre.size() - 2)
                {

                    QList<QBitArray> temp;
                    if(i == 0)
                        temp = split_bit(splited_pre[i] ^ synchro_dec, 16);
                    else
                    {
                        temp = split_bit(splited_pre[i] ^ splited_pre[i - 1], 16);
                    }
                    splited_post.append(overall(temp[0], temp[1], key));
                }
                else
                {
                    QList<QBitArray> temp;
                    if(i == 0)
                    {
                        temp = split_bit(splited_pre[i] ^ synchro_dec, 16);
                    }
                    else
                    {
                        temp = split_bit(splited_pre[i] ^ splited_pre[i - 1], 16);
                    }

                    QBitArray result = overall(temp[0], temp[1], key);



                    qInfo() << result;

                    temp = split_bit(splited_pre[i + 1] ^ splited_pre[i], 16);
                    QBitArray num_bits = overall(temp[0], temp[1], key);



                    QByteArray foo = convert(num_bits);
                    QDataStream ds(foo);
                    int size;
                    ds >> size;
                    size = 32 - size;

                    QBitArray last(size);
                    for(int ix = 0; ix < size;  ix++)
                    {
                        last[ix] = result[ix];
                    }
                    splited_post.append(last);
                    break;

                }
            }
            else
            {
                if(splited_pre[i].size() == 32)
                {
                    QList<QBitArray> temp = split_bit(splited_pre[i], 16);
                    splited_post.append(overall(temp[0], temp[1], key));

                }
                else
                {
                    int diff = 32 - splited_pre[i].size();
                    QBitArray Y_star(diff);
                    QBitArray Y_T(splited_pre[i].size());
                    for(int j = 0; j < 32; j++)
                    {
                        if(j < splited_pre[i].size())
                            Y_T[j] = splited_post[splited_post.size() - 1][j];
                        else
                            Y_star[j - splited_pre[i].size()] = splited_post[splited_post.size() - 1][j];
                    }

                    QList<QBitArray> temp = split_bit(concat(splited_pre[i],Y_star), 16);
                    splited_post[splited_post.size() - 1] = overall(temp[0], temp[1], key);
                    splited_post.append(Y_T);

                }
            }

        }

        int ex = 0;
        int c = 0;
        int overall_size = 0;
        for(auto a: splited_post)
            overall_size += a.size();
        post_text_dec.resize(overall_size);
        for(int i = 0; i < splited_post.size(); i++)
            for(int j = 0; j < splited_post[i].size(); j++)
            {
                post_text_dec[ex] = splited_post[i][j];
                ex++;
            }



        for(int i = 0; i< post_text_dec.size(); i++)
        {
            if(post_text_dec[i] == true)
               bit_array_post_dec.append("1");
            else
                bit_array_post_dec.append("0");
        }

        after_dec->setText(bit_array_post_dec);
        bit_array_post_dec.clear();
    }

}

void encrypt::analyse_pushed()
{

    QString key_str = c->toPlainText();
    QBitArray key_bit(32);
    if(key_str.size() != 32)
    {
        QMessageBox::warning(this, tr("Key warning"),
                                       tr("Key length must be 32 chars"),
                                       QMessageBox::Ok);
        return;
    }
    for(int i = 0; i < key_str.size(); i++)
    {
        if(key_str[i] == '1')
            key_bit.setBit(i);
        else if(key_str[i] != '0')
        {
            QMessageBox::warning(this, tr("Key warning"),
                                           tr("Key must be binary"),
                                           QMessageBox::Ok);
            return;
        }
    }


    qInfo() << key_bit;

    QList<QBitArray> key = split_bit(key_bit, 16);
    key.append(~key[0]);
    key.append(~key[1]);

    QBitArray block_bit(32);

    cli->clear();

    for(int iteration = 3; iteration < 4; iteration++)
    {
        bool R_found = false;
        QList<int> bits_changed;
        cli->append(QString("********************\n"
                    "R = %1                 \n"
                    "*********************").arg(iteration));

        QBitArray preview(32);
        for(int i = 0; i< 32; i++)
        {
            bool good_bit = false;
            cli->append("------------------------");
            cli->append(QString("Changing bit: %1").arg(i));

            QMap<int, int> changed_bits;
            uint max_val = -1;
            for(uint value = 0; value < max_val; value++)
            {
                if(value == 20000)
                    break;
                QList<uint> arrfile_x;
                arrfile_x.append(value);
                QBitArray bits_x(arrfile_x.count()*32);
                for(int i = 0; i < arrfile_x.count(); ++i) {
                  for(int b = 0; b < 32; b++) {
                    bits_x.setBit( i * 32 + b, arrfile_x.at(i) & (1 << (31 - b)) );
                }
                }

                block_bit = bits_x;

                QList<QBitArray> new_list;

               for(int i = 0; i<= iteration; i++)
               {
                    new_list.append(key[i]);

               }

                QList<QBitArray> temp = split_bit(block_bit, 16);
                QBitArray control = (overall(temp[0], temp[1], new_list));
                QString control_str = tostr(control);

                cli->append("CONTROL ENCRYPTION:");
                cli->append(control_str);

                qInfo() << "block";
                qInfo() << block_bit;

                qInfo() << "Control";
                qInfo() << control_str;
                QBitArray foo = block_bit;
                QBitArray result;
                foo[i]= !foo[i];
                qInfo() << "Invert";
                qInfo() << foo;


                temp = split_bit(foo, 16);
                result = (overall(temp[0], temp[1], new_list));

                cli->append("After change:");
                cli->append(tostr(result));

                qInfo() <<"After change:";
                qInfo() << result;

                for(int i = 0; i < 32; i++)
                    if(control[i] != result[i])
                    {
                        changed_bits[i] = i;
                        preview.setBit(i);
                    }

                qInfo() << "Changed bits:";

                qInfo() << preview;

                if(changed_bits.size() == 31)
                {
                    if(i == 31)
                        R_found = true;
                    good_bit = true;
                    break;
                }
            }


            cli->append("There are unsufficient variables, incrementing R...");
            break;

        }
        if(R_found)
        {
            cli->append("********************\n");
            cli->append("R FOUND:");
            cli->append(QString("R = %1").arg(iteration));
            cli->append("********************\n");
            break;
        }
    }


     cli->append("Loop finished, R > 4");
}
QBitArray encrypt::sp_alg(QBitArray open, QBitArray key)
{
    QList<QPair<QBitArray, QBitArray>> s_conv;
    QBitArray result(open.size());
    QList<char> x = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    QList<char> y = {9,13,14,4,2,8,0,6,1,11,3,5,7,10,15,12};
    for(int i = 0; i< x.size(); i++)
    {
        QByteArray arrfile_x;
        QByteArray arrfile_y;
        arrfile_x.append(x[i]);
        arrfile_y.append(y[i]);
        QBitArray bits_x(arrfile_x.count()*4);
        QBitArray bits_y(arrfile_y.count()*4);
        for(int i = 0; i < arrfile_x.count(); ++i) {
          for(int b = 0; b < 4; b++) {
            bits_x.setBit( i * 4 + b, arrfile_x.at(i) & (1 << (3 - b)) );
        }
        }
        for(int i = 0; i < arrfile_y.count(); ++i) {
          for(int b = 0; b < 4; b++) {
            bits_y.setBit( i * 4 + b, arrfile_y.at(i) & (1 << (3 - b)) );
        }
        }

        s_conv.append(QPair<QBitArray, QBitArray>(bits_x, bits_y));
    }

    open = open ^ key;

    QList<QBitArray> splited_oped = split_bit(open, 4);
    QBitArray foo(4);



//    qInfo() << "TABLE";
//    for(auto z: s_conv)
//        qInfo() << z;

//    qInfo() << "BEFORE";
//    for(auto z: splited_oped)
//        qInfo() << z;

    for(int i = 0; i < splited_oped.size(); i++)
    {
        for(int j = 0; j < s_conv.size(); j++)
            if(splited_oped[i] == s_conv[j].first)
            {
                splited_oped[i] = s_conv[j].second;
                break;

            }
    }

//    qInfo() << "AFTER";
//    for(auto z: splited_oped)
//        qInfo() << z;

    for(int i = 0; i < splited_oped.size() * splited_oped[0].size(); i++)
    {
        //qInfo() <<  splited_oped[i / 4][i % 4];


        result[i] = splited_oped[((11 * i + 5) % 16) / 4][((11 * i + 5) % 16) % 4];
//                qInfo() << ((11 * i + 5) % 16) / 4 << " " << ((11 * i + 5) % 16) % 4;
//                qInfo() <<(11 * i + 5) % 16;
    }

    return result;
}
QList<QBitArray> encrypt::split_bit(QBitArray src, int n)
{

    QList<QBitArray> splited_oped;
    QBitArray foo(n);

    for(int i = 0; i <src.size(); i++)
    {
        foo.resize((i % n) + 1);
        foo[i % n] = src[i];
        if(i % n == n-1)
            splited_oped.append(foo);
        else if(i == src.size() - 1)
            splited_oped.append(foo);


    }
    return splited_oped;
}

QPair<QBitArray, QBitArray> encrypt::tact_subs(QBitArray X1, QBitArray X2, QBitArray key)
{
    X1 = X1 ^ sp_alg(X2, key);
    return QPair<QBitArray, QBitArray>(X2, X1);
}
QBitArray encrypt::concat(QBitArray X1, QBitArray X2)
{
    QBitArray result(X1.size() + X2.size());
    int i;
    for(i = 0; i< X1.size(); i++)
    {
        result[i] = X1[i];
    }
    for(; i< X1.size() + X2.size(); i++)
    {
        result[i] = X2[i - X1.size()];
    }

    return result;
}
QBitArray encrypt::overall(QBitArray X1, QBitArray X2, QList<QBitArray> keys)
{

    for(int i = 0; i< keys.size(); i++)
    {
        QPair<QBitArray, QBitArray> foo = tact_subs(X1, X2, keys[i]);
        X1 = foo.first;
        X2 = foo.second;
    }
    X1.swap(X2);
    return concat(X1, X2);
}


QByteArray encrypt::convert(const QBitArray &__bits)
{
    //
    QByteArray bytes;
    bytes.resize(__bits.count() / 8);    // Резервируем место
    bytes.fill(0);                           // Заполняем всё нулями

    // Конвертируем из QBitArray в QByteArray
    for(int b = 0; b < __bits.count(); ++b)
    {
        bytes[b/8] = (bytes.at(b/8) | ( (__bits.testBit(b) ? 1 : 0)<<(7-(b%8)) ) );
        // Конструкция (7-(b%8)) даёт прямой порядок. Для обратного (b%8)
    }

    return bytes;
}
QString encrypt::tostr(QBitArray src)
{
    QString tmp;
    for(int i = 0; i< src.size(); i++)
    {
        if(src[i] == true)
            tmp.append("1");
        else
            tmp.append("0");
    }

    return tmp;
}
void encrypt::box_changed(int state)
{
    if(state == 2)
    {
        b->clear();


    }
}

void encrypt::cycle_ex_pushed()
{
    cli->clear();
    QVector<int> cycles;
    long long int power = qPow(2, 32);
    for(int iteration = 0; iteration < 5; iteration++)
    {

        QBitArray input_block(32);

        for(int i = 0; i < 32; i++)
            input_block[i] = rand() % 2;

        QBitArray thetta1(16);
        QBitArray thetta2(16);
        QBitArray key1(32);
        QBitArray key2(32);
        for(int i = 0; i < 16; i++)
            thetta1[i] = rand() % 2;

        thetta2 = ~thetta1;

        key1 = concat(thetta1,thetta2);

        for(int i = 0; i < 16; i++)
            thetta1[i] = rand() % 2;

        thetta2 = ~thetta1;
        key2 = concat(thetta1,thetta2);


        cli->append("-------------------------------");
        cli->append(QString("j = %1").arg(iteration));
        cli->append("-------------------------------");
        cli->append("Block:");
        cli->append(convert(input_block).toHex());
        cli->append("Key0:");
        cli->append(convert(key1).toHex());
        cli->append("Key1:");
        cli->append(convert(key2).toHex());



        QList<QBitArray> key1_list = split_bit(key1, 16);
        key1_list.append(~key1_list[0]);
        key1_list.append(~key1_list[1]);

        QList<QBitArray> key2_list = split_bit(key2, 16);
        key2_list.append(~key2_list[0]);
        key2_list.append(~key2_list[1]);



        QList<QBitArray> temp;
        QBitArray result;
        temp = split_bit(input_block, 16);
        result = overall(temp[0], temp[1], key1_list);
        temp = split_bit(result, 16);
        QBitArray Xt = overall(temp[0], temp[1], key2_list);
        int ex = 0;
        auto start = high_resolution_clock::now();
        while(Xt != input_block)
        {
            temp = split_bit(Xt, 16);
            result = overall(temp[0], temp[1], key1_list);
            temp = split_bit(result, 16);
            Xt = overall(temp[0], temp[1], key2_list);
            ex++;
        }
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        cycles.append(ex);
        cli->append(QString("Cycles: %1").arg(ex));
        cli->append(QString("Time: %1").arg(duration.count()));
        long long int LCM = findlcm(cycles);
        if(LCM > power)
        {
            cli->append(QString("LCM is %1,which is more than 2^32 = %2").arg(LCM).arg(power));
        }
    }

}
int encrypt::gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Returns LCM of array elements
ll encrypt::findlcm(QVector<int> arr)
{
    // Initialize result
    ll ans = arr[0];

    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < arr.size(); i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));

    return ans;
}
