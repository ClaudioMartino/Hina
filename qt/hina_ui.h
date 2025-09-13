#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class hina_ui;
}
QT_END_NAMESPACE

class hina_ui : public QMainWindow
{
    Q_OBJECT

public:
    hina_ui(QWidget *parent = nullptr);
    ~hina_ui();

private slots:
    void on_buttonExplore_clicked();

    void on_buttonGo_clicked();

private:
    Ui::hina_ui *ui;
};
#endif // CALC_H
