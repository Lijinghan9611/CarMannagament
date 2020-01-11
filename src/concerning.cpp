#include "concerning.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

concerning::concerning(QWidget *parent) : QWidget(parent)
{
    label1 = new QLabel("使用帮助");
    label2 = new QLabel("本软件的功能在于方便汽修店管理车辆的信息，集维修养护、车险、洗车为一体，进行标准化管理");
    label3 = new QLabel("1、本系统的维修养护可进行查询、添加、修改、删除记录等功能，其中修改功能可以直接双击表格栏进行修改，删除则是选中表头进行删除。                                            ");
    label4 = new QLabel("2、本系统的车险功能集成了车险和出险功能，当进行单一查询的时候会将车险信息显示在第二栏，同时将出险信息显示在表格栏中，同时进行查询后可以进行添加出险信息和修改车险信息，   ");
    label5 = new QLabel("另外在显示所有车险信息时会将信息直接显示在表格里。                                                                                                                 ");
    label6 = new QLabel("3、本系统的洗车卡功能有添加新卡、打卡、充卡等功能，通过查询可以查到该车辆的洗车卡信息，然后再选择打卡或充卡，同时考虑到拥有多辆车的车主，可以同时绑定多辆车进行打卡。     ");
    label7 = new QLabel("4、本系统拥有一个客户表，当任意一辆车在进行以上任意一种服务，记录下来后都也会记录在客户信息里，后期也可以完善资料，比如电话号码、住址等信息，也可以直接查看到使用过的服务。");
    label8 = new QLabel("");
    label9 = new QLabel("关于本系统");
    label10 = new QLabel("本系统持续更新");
    label11 = new QLabel("当前版本号：v1.0");
    label12 = new QLabel("详情可联系QQ：XXXXXXXXX 进行咨询");
    label13 = new QLabel("");
    label14 = new QLabel("");
    label1->setFont(QFont("华文楷体" , 20 ,  QFont::Bold));
    label2->setFont(QFont("宋体" , 10 ,  QFont::Bold));
    label3->setFont(QFont("宋体" , 10 ));
    label4->setFont(QFont("宋体" , 10 ));
    label5->setFont(QFont("宋体" , 10 ));
    label6->setFont(QFont("宋体" , 10 ));
    label7->setFont(QFont("宋体" , 10 ));
    label8->setFont(QFont("华文楷体" , 12 ));
    label9->setFont(QFont("华文楷体" , 18 ,  QFont::Bold));
    label10->setFont(QFont("华文楷体" , 12 ));
    label11->setFont(QFont("华文楷体" , 12 ));
    label12->setFont(QFont("华文楷体" , 12 ));
    label13->setFont(QFont("华文楷体" , 12 ));
    label14->setFont(QFont("华文楷体" , 12 ));
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    label4->setAlignment(Qt::AlignCenter);
    label5->setAlignment(Qt::AlignCenter);
    label6->setAlignment(Qt::AlignCenter);
    label7->setAlignment(Qt::AlignCenter);
    label8->setAlignment(Qt::AlignCenter);
    label9->setAlignment(Qt::AlignCenter);
    label10->setAlignment(Qt::AlignCenter);
    label11->setAlignment(Qt::AlignCenter);
    label12->setAlignment(Qt::AlignCenter);
    label13->setAlignment(Qt::AlignCenter);
    label14->setAlignment(Qt::AlignCenter);

    QVBoxLayout *Layout1 = new QVBoxLayout();
    Layout1->addWidget(label1);
    Layout1->addWidget(label2);
    Layout1->addWidget(label3);
    Layout1->addWidget(label4);
    Layout1->addWidget(label5);
    Layout1->addWidget(label6);
    Layout1->addWidget(label7);
    Layout1->addWidget(label8);
    Layout1->addWidget(label9);
    Layout1->addWidget(label10);
    Layout1->addWidget(label11);
    Layout1->addWidget(label12);
    Layout1->addWidget(label13);
    Layout1->addWidget(label14);

    this->setLayout(Layout1);
}

